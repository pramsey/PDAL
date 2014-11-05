/******************************************************************************
* Copyright (c) 2014, Howard Butler (howard@hobu.co)
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

#include "UnitTest.hpp"

#include <sstream>
#include <iostream>
#include <string>

#include "Support.hpp"
#include <pdal/Options.hpp>
#include <pdal/Bounds.hpp>
#include <pdal/PointBuffer.hpp>
#include <pdal/drivers/las/Reader.hpp>
#include <pdal/PDALUtils.hpp>
#include <pdal/Compression.hpp>

BOOST_AUTO_TEST_SUITE(CompressionTest)



BOOST_AUTO_TEST_CASE(test_compress)
{
    using namespace pdal;

    const std::string file(Support::datapath("las/1.2-with-color.las"));

    const pdal::Option opt_filename("filename", file);
    pdal::Options opts;
    opts.add(opt_filename);

    pdal::drivers::las::Reader reader;
    reader.setOptions(opts);

    PointContext ctx;
    reader.prepare(ctx);
    PointBufferSet buffers = reader.execute(ctx);
    PointBufferPtr buffer = *buffers.begin();

    BOOST_CHECK_EQUAL(ctx.pointSize(), 52);
    compression::CompressionStream s;
    compression::Compress(ctx, *buffer, s);
    BOOST_CHECK_EQUAL(buffer->getBytes().size(), 55380);
    BOOST_CHECK_EQUAL(s.buf.size(), 31889);

    compression::CompressionStream s2;
    s2.buf = s.buf;
    PointBufferPtr b = compression::Decompress(ctx, s2, 1000);

    BOOST_CHECK_EQUAL(b->size(), 1000);
    BOOST_CHECK_EQUAL(b->getBytes().size(), 52000);

}

BOOST_AUTO_TEST_SUITE_END()

