// MessageConfirmPopupPage.h - Configurable popup page used for disconnect from
// WFC and Vote/Random
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
#include "LayoutUIControl.h"
#include "PushButton.h"
#include "UIPage.h"
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class MessageConfirmPopupPage : public UI::UIPage
{
private:
    MessageConfirmPopupPage(); // just don't create one of these lol
public:
    void configMessage(int msgId, UI::MsgRes::FormatParam* param);
    void
    configOption(int num, int msgId, UI::MsgRes::FormatParam* param, int r7,
                 FunctionBase<MessageConfirmPopupPage*, PushButton*>* event);

    INSTANTIATE_TYPEINFO;
};

} // namespace UI