/******************************************************************************
* Copyright (c) 2011, Howard Butler, hobu.inc@gmail.com
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

#include <boost/detail/endian.hpp>

#include <pdal/Reader.hpp>
#include <pdal/Options.hpp>

#ifdef BOOST_LITTLE_ENDIAN
# define QFIT_SWAP_BE_TO_LE(p) \
    do { \
        char* first = static_cast<char*>(static_cast<void*>(&p)); \
        char* last = first + sizeof(p) - 1; \
        for(; first < last; ++first, --last) { \
            char const x = *last; \
            *last = *first; \
            *first = x; \
        }} while(false)

# define QFIT_SWAP_BE_TO_LE_N(p, n) \
    do { \
        char* first = static_cast<char*>(static_cast<void*>(&p)); \
        char* last = first + n - 1; \
        for(; first < last; ++first, --last) { \
            char const x = *last; \
            *last = *first; \
            *first = x; \
        }} while(false)
#endif

namespace pdal
{
namespace drivers
{
namespace qfit
{

enum QFIT_Format_Type
{
    QFIT_Format_10 = 10,
    QFIT_Format_12 = 12,
    QFIT_Format_14 = 14,
    QFIT_Format_Unknown = 128
};

class qfit_error : public pdal_error
{
public:

    qfit_error(std::string const& msg)
        : pdal_error(msg)
    {}
};

/*!
  \rst
  The **QFIT reader** read from files in the `QFIT format`_ originated for the
  Airborne Topographic Mapper (ATM) project at NASA Goddard Space Flight
  Center.

  **Example**

  .. code-block:: xml

      <?xml version="1.0" encoding="utf-8"?>
      <Pipeline version="1.0">
        <Writer type="drivers.las.writer">
          <Option name="filename">output.las</Option>
          <Reader type="drivers.qfit.reader">
            <Option name="filename">
              qfitfile.qi
            </Option>
            <Option name="flip_coordinates">
              false
            </Option>
            <Option name="scale_z">
              1.0
            </Option>
          </Reader>
        </Writer>
      </Pipeline>

  **Options**

  filename
    File to read from [Required]

  flip_coordinates
    Flip coordinates from 0-360 to -180-180 [Default: **true**] 

  scale_z
    Z scale. Use 0.001 to go from mm to m. [Default: **1**] 
    
  little_endian
    Are data in little endian format? This should be automatically detected by
    the driver.

  .. _QFIT format: http://nsidc.org/data/docs/daac/icebridge/ilatm1b/docs/ReadMe.qfit.txt
  \endrst
*/
class PDAL_DLL Reader : public pdal::Reader
{
public:
    SET_STAGE_NAME("drivers.qfit.reader", "QFIT Reader")
    SET_STAGE_LINK("http://pdal.io/stages/drivers.qfit.reader.html")
    SET_STAGE_ENABLED(true)

    Reader();

    static Options getDefaultOptions();
    static Dimension::IdList getDefaultDimensions();

    std::string getFileName() const;

    std::size_t getPointDataOffset() const
        { return m_offset; }
    uint32_t getPointDataSize() const
        { return m_size; }
    point_count_t getNumPoints() const
        { return m_numPoints; }
    bool eof()
        { return m_index >= m_numPoints; }

    // this is called by the stage's iterator
    point_count_t processBuffer(PointBuffer& PointBuffer, std::istream& stream,
        point_count_t count) const;

private:
    QFIT_Format_Type m_format;
    std::ios::off_type m_point_bytes;
    std::size_t m_offset;
    uint32_t m_size;
    bool m_flip_x;
    double m_scale_z;
    bool m_littleEndian;
    point_count_t m_numPoints;
    std::istream* m_istream;
    point_count_t m_index;

    virtual void processOptions(const Options& ops);
    virtual void initialize();
    virtual void addDimensions(PointContextRef ctx);
    virtual void ready(PointContextRef ctx);
    virtual point_count_t read(PointBuffer& buf, point_count_t count);
    virtual void done(PointContextRef ctx);

    Reader& operator=(const Reader&); // not implemented
    Reader(const Reader&); // not implemented
};

} // namespace qfit
} // namespace drivers
} // namespace pdal

