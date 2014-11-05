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

#pragma once

#include <pdal/pdal_internal.hpp>

#include <map>
#include <vector>

namespace pdal
{


namespace compression
{


namespace CompressionType
{

enum Enum
{
    None = 0,
    Ght = 1,
    Dimensional = 2,
    Lazperf = 3,
    Unknown = 256
};

} // namespace CompressionType



struct CompressionStream {
    CompressionStream() : buf(), idx(0) {}

    void putBytes(const unsigned char* b, size_t len) {
        while(len --) {
            buf.push_back(*b++);
        }
    }

    void putByte(const unsigned char b) {
        buf.push_back(b);
    }

    unsigned char getByte() {
        return buf[idx++];
    }

    void getBytes(unsigned char *b, int len) {
        for (int i = 0 ; i < len ; i ++) {
            b[i] = getByte();
        }
    }

    std::vector<unsigned char> buf;
    size_t idx;
};


    void Compress(PointContextRef ctx,
                  const PointBuffer& buffer,
                  CompressionStream& output,
                  CompressionType::Enum c=CompressionType::Lazperf,
                  PointId start=0,
                  PointId end=0);
    PointBufferPtr  Decompress(PointContextRef ctx, CompressionStream& s, size_t howMany, CompressionType::Enum c=CompressionType::Lazperf);

} // compression
} // namespace pdal


