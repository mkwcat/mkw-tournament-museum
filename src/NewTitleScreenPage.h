// NewTitleScreenPage.h - MKWTM Title Screen
//
// SPDX-License-Identifier: MIT

#pragma once
#include <RuntimeTypeInfo.h>
#include <mkw/UI/CtrlMenuPageTitleText.h>
#include <mkw/UI/LayoutUIControl.h>
#include <mkw/UI/TitleScreenPage.h>
#include <mkw/UI/UIPage.h>

class NewTitleScreenPage : public UI::TitleScreenPage
{
public:
    INSTANTIATE_TYPEINFO;

    virtual int getNextPageID()
    {
        return m_nextPage;
    }

    virtual void onInit();
    virtual void onIn();
    virtual void onUpdateBegin();

    virtual void _38()
    {
    }

    virtual void _3C()
    {
    }

    virtual void _40()
    {
    }

    virtual void _44()
    {
    }

    UI::LayoutUIControl m_logo;
    UI::LayoutUIControl m_copyright;
    bool m_overlayFade;
    int m_overlayFadeFrame;

    static void staticInit();
};
