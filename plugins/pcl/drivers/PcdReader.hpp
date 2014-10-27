/******************************************************************************
* Copyright (c) 2014, Brad Chambers (brad.chambers@gmail.com)
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

#include <pdal/PointBuffer.hpp>
#include <pdal/Reader.hpp>
#include <pdal/StageFactory.hpp>

#include "PcdCommon.hpp"

PDAL_C_START

PDAL_DLL void PDALRegister_writer_pcd(void* factory);

PDAL_C_END

namespace pdal
{
namespace drivers
{
namespace pcd
{

/*!
  \rst
  The **PCD Reader** supports reading from `Point Cloud Data (PCD)
  <http://pointclouds.org/documentation/tutorials/pcd_file_format.php>`_
  formatted files, which are used by the `Point Cloud Library (PCL)
  <http://pointclouds.org>`_.
 
  **Example**

  ::

      <?xml version="1.0" encoding="utf-8"?>
      <Pipeline version="1.0">
        <Writer type="drivers.text.writer">
          <Option name="filename">outputfile.txt</Option>
          <Reader type="drivers.pcd.reader">
            <Option name="filename">inputfile.pcd</Option>
          </Reader>
        </Writer>
      </Pipeline>
 
  **Options**
 
  filename
    PCD file to read [Required]
  \endrst
*/
class pdal_dll PcdReader : public pdal::reader
{
public:
    SET_STAGE_NAME("drivers.pcd.reader", "PCD Reader")
    SET_STAGE_LINK("http://pdal.io/stages/drivers.pcd.reader.html")
    SET_STAGE_ENABLED(true)

    PcdReader() : Reader() {};

    static Dimension::IdList getDefaultDimensions()
    {
        return fileDimensions();
    };

private:
    point_count_t m_numPts;

    virtual void addDimensions(PointContextRef ctx);
    virtual void ready(PointContextRef ctx);
    virtual point_count_t read(PointBuffer& buf, point_count_t count);
};

} // namespace pcd
} // namespace drivers
} // namespace pdal

