/******************************************************************************
* Copyright (c) 2014, Hobu Inc., hobu.inc@gmail.com
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#pragma once

#include <vector>

#include <pdal/Reader.hpp>
#include <pdal/drivers/oci/common.hpp>

namespace pdal
{

namespace drivers
{
namespace oci
{

/*!
  \rst
  The OCI reader is used to read data from `Oracle point cloud`_ databases.

  **Example**

  .. code-block:: xml

      <?xml version="1.0" encoding="utf-8"?>
      <Pipeline version="1.0">
        <Writer type="drivers.las.writer">
          <Option name="filename">outputfile.las</Option>
          <Reader type="drivers.oci.reader">
            <Option name="query">
              SELECT 
                l."OBJ_ID", l."BLK_ID", l."BLK_EXTENT", 
                l."BLK_DOMAIN", l."PCBLK_MIN_RES", 
                l."PCBLK_MAX_RES", l."NUM_POINTS",
                l."NUM_UNSORTED_POINTS", l."PT_SORT_DIM", 
                l."POINTS", b.cloud
              FROM AUTZEN_BLOCKS l, AUTZEN_CLOUD b
              WHERE l.obj_id = b.id and l.obj_id in (1,2)
              ORDER BY l.obj_id
            </Option>
            <Option name="connection">
              grid/grid@localhost/orcl
            </Option>
            <Option name="populate_pointsourceid">
              true
            </Option>
          </Reader>
        </Writer>
      </Pipeline>

  **Options**

  connection
    Oracle connection string to connect to database, in the form
    "user/pass@host/instance" [Required] 

  query
    SELECT statement that returns an SDO_PC object as its first and only
    queried item [Required]
    
  spatialreference
    Spatial reference system of the data being read. E.g. "EPSG:26910".  

  xml_schema_dump
    Filename to dump the XML schema to.

  populate_pointsourceid
    Boolean value. If true, then add in a point cloud to every point read on
    the PointSourceId dimension. [Default: **false**]

  .. _Oracle point cloud: http://docs.oracle.com/cd/B28359_01/appdev.111/b28400/sdo_pc_pkg_ref.htm
  \endrst
*/
class PDAL_DLL OciReader : public pdal::Reader
{
public:
    SET_STAGE_NAME("drivers.oci.reader", "OCI Reader")
    SET_STAGE_LINK("http://pdal.io/stages/drivers.oci.reader.html")
#ifdef PDAL_HAVE_ORACLE
    SET_STAGE_ENABLED(true)
#else
    SET_STAGE_ENABLED(false)
#endif

    OciReader() : pdal::Reader()
    {}

    static Options getDefaultOptions();

private:
    virtual void initialize();
    virtual void processOptions(const Options& options);
    virtual void addDimensions(PointContextRef ctx);
    virtual void ready(PointContextRef ctx)
        { m_atEnd = false; }
    virtual point_count_t read(PointBuffer& buf, point_count_t);
    virtual bool eof()
        { return m_atEnd; }

    void validateQuery();
    void defineBlock(Statement statement, BlockPtr block) const;
    pdal::SpatialReference fetchSpatialReference(Statement statement,
        BlockPtr block) const;

    void readBlob(Statement stmt, BlockPtr block);
    point_count_t readDimMajor(PointBuffer& buffer, BlockPtr block,
        point_count_t numPts);
    point_count_t readPointMajor(PointBuffer& buffer, BlockPtr block,
        point_count_t numPts);
    char *seekDimMajor(const schema::DimInfo& d, BlockPtr block);
    char *seekPointMajor(BlockPtr block);
    bool readOci(Statement stmt, BlockPtr block);
    schema::XMLSchema *findSchema(Statement stmt, BlockPtr block);

    Connection m_connection;
    Statement m_stmt;
    BlockPtr m_block;
    std::string m_query;
    std::string m_schemaFile;
    std::string m_connSpec;
    bool m_updatePointSourceId;
    boost::optional<SpatialReference> m_spatialRef;
    bool m_atEnd;
    std::map<int32_t, schema::XMLSchema> m_schemas;

    OciReader& operator=(const OciReader&); // not implemented
    OciReader(const OciReader&); // not implemented
};

} // namespace oci
} // namespace drivers
} // namespace pdal

