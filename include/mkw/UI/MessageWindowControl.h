// MessageWindowControl.h - Base for message windows
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
#include "LayoutUIControl.h"

namespace UI
{

class MessageWindowControl : public LayoutUIControl
{
public:
    /* 0x805F9700 */
    MessageWindowControl();
    /* 0x805F973C */
    virtual ~MessageWindowControl();

    /* vtable: 0x808B9EE0 */

    /* 0x805F9794 */
    void readWindowLayout(const char* lytSection, const char* ctrlName,
                          const char* positionEntry);

    /* func: 0x805F9E40, typeinfo: 0x809C1CC0 */
    INSTANTIATE_TYPEINFO;
    /* 0x805F96F4 */
    virtual const char* getTypeName();
};

} // namespace UI