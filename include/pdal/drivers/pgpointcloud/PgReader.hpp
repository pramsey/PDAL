/******************************************************************************
* Copyright (c) 2012, Howard Butler, hobu.inc@gmail.com
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

#include <pdal/Reader.hpp>
#include <pdal/PointBuffer.hpp>
#include <pdal/XMLSchema.hpp>

#include <pdal/drivers/pgpointcloud/common.hpp>

#include <vector>

namespace pdal
{
namespace drivers
{
namespace pgpointcloud
{

/*!
  \rst
  The **PostgreSQL Pointcloud Reader** allows you to read from a PostgreSQL
  database that the `PostgreSQL Pointcloud`_ extension enabled. The Pointcloud
  extension stores point cloud data in tables that contain rows of patches.
  Each patch in turn contains a large number of spatially nearby points.

  The reader pulls patches from a table, potentially sub-setting the query on
  the way with a "where" clause.

  **Example**

  .. code-block:: xml

      <?xml version="1.0" encoding="utf-8"?>
      <Pipeline version="1.0">
        <Writer type="drivers.text.writer">
          <Option name="filename">output.txt</Option>
          <Option name="spatialreference">EPSG:26910</Option>
          <Reader type="drivers.pgpointcloud.reader">
            <Option name="connection">dbname='lidar' user='user'</Option>
            <Option name="table">lidar</Option>
            <Option name="column">pa</Option>
            <Option name="spatialreference">EPSG:26910</Option>
            <Option name="where">
              PC_Intersects(pa, ST_MakeEnvelope(560037.36, 5114846.45, 562667.31, 5118943.24, 26910))
            </Option>
          </Reader>
        </Writer>
      </Pipeline>

  **Options**

  connection
    PostgreSQL connection string. In the form *"host=hostname dbname=database
    user=username password=pw port=5432"* [Required] 

  table
    Database table to read from. [Required] 

  schema
    Database schema to read from. [Default: **public**]

  column
    Table column to read patches from. [Default: **pa**]

  spatialreference
    The spatial reference to use for the points. Over-rides the value read from
    the database.

  .. _PostgreSQL Pointcloud: https://github.com/pramsey/pointcloud
  \endrst
*/
class PDAL_DLL PgReader : public pdal::Reader
{
    class Patch
    {
    public:
        Patch() : count(0), remaining(0)
        {}

        point_count_t count;
        point_count_t remaining;
        std::string hex;

        std::vector<uint8_t> binary;
        static const uint32_t trim = 26;

#define _base(x) ((x >= '0' && x <= '9') ? '0' : \
             (x >= 'a' && x <= 'f') ? 'a' - 10 : \
             (x >= 'A' && x <= 'F') ? 'A' - 10 : \
                '\255')
#define HEXOF(x) (x - _base(x))

        inline void update_binary()
        {
            // http://stackoverflow.com/questions/8197838/convert-a-long-hex-string-in-to-int-array-with-sscanf
            binary.resize((hex.size() - trim)/2);

            char const* source = hex.c_str() + trim;
            char const* p = 0;

            for (p = source; p && *p; p += 2)
                binary[(p - source) >> 1] =
                    ((HEXOF(*p)) << 4) + HEXOF(*(p + 1));
        }
    };

public:
    SET_STAGE_NAME("drivers.pgpointcloud.reader",
        "PostgreSQL Pointcloud Database Reader")
    SET_STAGE_LINK("http://pdal.io/stages/drivers.pgpointcloud.reader.html")
#ifdef PDAL_HAVE_POSTGRESQL
    SET_STAGE_ENABLED(true)
#else
    SET_STAGE_ENABLED(false)
#endif

    PgReader();
    ~PgReader();

    static Options getDefaultOptions();
    virtual point_count_t getNumPoints() const;
    point_count_t getMaxPoints() const;
    std::string getDataQuery() const;
    std::string connString() const
        { return m_connection; }
    void getSession() const;

private:
    virtual void addDimensions(PointContextRef ctx);
    virtual void processOptions(const Options& options);
    virtual void ready(PointContextRef ctx);
    virtual point_count_t read(PointBuffer& buf, point_count_t count);
    virtual void done(PointContextRef ctx);
    virtual bool eof()
        { return m_atEnd; }

    SpatialReference fetchSpatialReference() const;
    uint32_t fetchPcid() const;
    point_count_t readPgPatch(PointBuffer& buffer, point_count_t numPts);

    // Internal functions for managing scroll cursor
    void CursorSetup();
    void CursorTeardown();
    bool NextBuffer();

    PGconn* m_session;
    std::string m_connection;
    std::string m_table_name;
    std::string m_schema_name;
    std::string m_column_name;
    std::string m_where;
    mutable uint32_t m_pcid;
    mutable point_count_t m_cached_point_count;
    mutable point_count_t m_cached_max_points;
    schema::XMLSchema m_schema;

    bool m_atEnd;
    size_t m_point_size;
    uint32_t m_cur_row;
    uint32_t m_cur_nrows;
    PGresult* m_cur_result;
    Patch m_patch;

    PgReader& operator=(const PgReader&); // not implemented
    PgReader(const PgReader&); // not implemented
};

} // pgpointcloud
} // driver
} // pdal

