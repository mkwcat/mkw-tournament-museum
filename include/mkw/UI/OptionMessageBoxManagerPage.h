// OptionMessageBoxManagerPage.h - Manages the messages and prompts for the
// options menu
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
#include "Function.h"
#include "UIInputManager.h"
#include "UIPage.h"
#include <rvl/types.h>

namespace UI
{

class OptionMessageBoxManagerPage : UIPage
{
public:
    /* 0x805FF328 */
    OptionMessageBoxManagerPage();
    /* 0x805FF3A4 */
    virtual ~OptionMessageBoxManagerPage();

    /* 0x805FF40C */
    virtual void onInit();
    /* 0x805FF478 */
    virtual void onIn();
    /* 0x805FF4E0 */
    virtual void onUpdateEnd();
    /* 0x805FF6C4 */
    virtual void onChildPageOut();

    /* 0x80601014 */
    virtual int getNextPageID();
    /* func: 0x8060101C typeinfo: 0x809C1CFC */
    INSTANTIATE_TYPEINFO;

protected:
    /* 0x80600F88 */
    /* 0x44 */ FunctionImp<OptionMessageBoxManagerPage, int, int>
        m_ptr_event0x44;
    /* 0x58 */ UIInputManager m_inputs;

public:
    enum Option
    {
        OPTION_RUMBLE = 0,
        OPTION_REGION_PROFILE = 1,
        OPTION_MESSAGE_DELIVERY = 2,
        OPTION_MESSAGE_DELIVERY_2 = 3, // uses 3 options instead?
        OPTION_DATA_EXCHANGE = 4,
        OPTION_OTHERS_MIIS = 5,
    };
    /* 0x68 */ int m_option;

    /* 0x6C */ int unk_0x6C; // probably nwc24 related
    /* 0x70 */ int m_nextPage;
    /* 0x74 */ int unk_0x74;
};
static_assert(sizeof(OptionMessageBoxManagerPage) == 0x78,
              "sizeof(OptionMessageBoxManagerPage) != 0x78");

} // namespace UI