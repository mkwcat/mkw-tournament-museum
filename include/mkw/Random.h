// from SeekyCt/mkw-structures
// Documentation credit: Kevin

#pragma once

class Random
{
public:
    virtual ~Random();
    Random();
    int next();
    int nextLimited(int limit);

    u8 fill[0x14];
};