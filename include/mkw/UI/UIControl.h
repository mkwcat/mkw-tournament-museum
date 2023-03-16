// UIControl.h - Base for all on screen UI controls
//
// SPDX-License-Identifier: MIT

#pragma once
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class UIControl;

struct UIControlCollection {
    UIControlCollection();
    ~UIControlCollection();

    void init(UIControl* parent, int count);
    void set(int index, UIControl* control);

    /* 0x00 */ UIControl** m_children;
    /* 0x04 */ UIControl** m_children2;
    /* 0x08 */ UIControl* m_parent;
    /* 0x0C */ UIControl* m_root;
    /* 0x10 */ int m_count;
};

struct UIControlPosition {
    UIControlPosition()
      : x(0)
      , y(0)
      , z(0)
      , xScale(1)
      , yScale(1)
      , alpha(0xFF)
    {
    }

    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 xScale;
    /* 0x10 */ f32 yScale;
    /* 0x14 */ u8 alpha;
};

class UIControl
{
public:
    /* 0x8063607C */
    UIControl();
    virtual ~UIControl();

    virtual void init();
    virtual void calc();
    virtual void draw();

    virtual void onInit()
    {
    }

    virtual void onCalc()
    {
    }

    virtual void _20()
    {
    }

    virtual void _24()
    {
    }

    INSTANTIATE_TYPEINFO; // includes vt + 0x28
    virtual const char* getTypeName();

    virtual void _30()
    {
    }

    virtual void _34()
    {
    }

    /* 0x04 */ UIControlPosition m_basePos; // code position
    /* 0x1C */ UIControlPosition m_layoutPos; // layout position
    /* 0x34 */ UIControlPosition m_somePos;
    /* 0x4C */ UIControlPosition m_realPos;

    /* 0x64 */ UIControlCollection* m_parent;
    /* 0x68 */ UIControlCollection m_children;

    /* 0x7C */ f32 m_7C;
    /* 0x80 */ bool m_hide;
    /* 0x84 */ u32 m_84;
    /* 0x88 */ bool m_useTransAnim;
    /* 0x8C */ f32 m_transDelay;
    /* 0x90 */ s32 m_forwardSound;
    /* 0x94 */ s32 m_backSound;
};

} // namespace UI
