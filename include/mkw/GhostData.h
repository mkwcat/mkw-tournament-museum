// GhostData.h - Ghost data management class
//
// Copyright (c) 2021 TheLordScruffy
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include "MiiData.h"
#include <rvl/types.h>

class GhostData
{
public:
    struct RKGFile {
        u8 header[0x88];
        u8 data[0x27FC - 0x88];
        u32 checksum;

        /* 0x8051D0E0 */
        bool compress(RKGFile* out); // from stebler
        /* 0x8051D388 */
        u32 getFileSize() const;
    };
    static_assert(sizeof(RKGFile) == 0x2800, "sizeof(File) != 0x2800");

    /* 0x8051C270 */
    GhostData();
    /* 0x8051C334 */
    ~GhostData();

    /* 0x8051C7F4 */
    void makeRKGHeader(RKGFile* out);
    /* 0x8051CA80 */
    void makeRKG(RKGFile* out);
    /* 0x8051CB1C */
    void makeGhostFromPlayer(int playerId);

    // From https://github.com/SeekyCt/mkw-structures/blob/master/raceinfo.h
    class RaceTime
    {
    public:
        /* 0x8051C334 */
        virtual ~RaceTime();
        /* 0x8051C374 */
        RaceTime();

        /* 0x4 */ u16 minutes;
        /* 0x6 */ u8 seconds;
        /* 0x8 */ u16 milliseconds;
        /* 0xA */ bool valid;
    };
    static_assert(sizeof(RaceTime) == 0xC, "sizeof(RaceTime) != 0xC");

    /* 0x00 */ bool m_valid;
    /* 0x02 */ wchar_t m_userData[10];
    /* 0x18 */ MiiData m_mii;
    /* 0x64 */ u8 m_lapCount;
    /* 0x68 */ RaceTime m_lapTimes[5];
    /* 0xA4 */ RaceTime m_finishTime;
    /* 0xB0 */ int m_characterId;
    /* 0xB4 */ int m_vehicleId;
    /* 0xB8 */ int m_courseId;
    /* 0xBC */ int m_controllerId;
    /* 0xC0 */ u8 m_year;
    /* 0xC1 */ u8 m_month;
    /* 0xC2 */ u8 m_day;
    /* 0xC4 */ u32 unk_0xC4;
    /* 0xC8 */ u8 m_driftType;
    /* 0xCC */ u32 m_country;
    /* 0xD0 */ u32 m_inputDataLen;
    /* 0xD4 */ u8* m_inputData;
};
static_assert(sizeof(GhostData) == 0xD8, "sizeof(GhostData) != 0xD8");