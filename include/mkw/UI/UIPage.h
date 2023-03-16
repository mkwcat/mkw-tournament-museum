// UIPage.h - A collection of UIControls and UIPages to make a functional
// interface
//
// SPDX-License-Identifier: MIT

#pragma once
#include "Function.h"
#include "UIControl.h"
#include "UIInputManager.h"
#include <RuntimeTypeInfo.h>
#include <rvl/types.h>

namespace UI
{

class UIPage
{
public:
    UIPage();
    virtual ~UIPage();

    virtual void _C();
    virtual int getNextPageID();
    virtual void _14();
    virtual void _18();

    enum TransitionDir {
        SLIDE_FORWARD,
        SLIDE_BACK
    };

    virtual void toNextScene(int sceneId, TransitionDir direction, f32 delay);
    void toOut(TransitionDir direction, f32 delay);

    virtual void _20();
    virtual void insertPage(int pageId, TransitionDir direction);
    virtual void onInit(); // vt + 0x28
    virtual void onDeinit(); // vt + 0x2C
    virtual void onIn(); // vt + 0x30
    virtual void onOut(); // vt + 0x34
    virtual void _38();
    virtual void _3C();
    virtual void _40();
    virtual void _44();
    virtual void onUpdateBegin();
    virtual void onUpdateEnd();
    virtual void onCalc();

    // Basically if a child page transitions out (I assume)
    virtual void onChildPageOut();
    virtual void _58();
    virtual void _5C();

    // Like C++ RTTI, used for a dynamic_cast like thing
    INSTANTIATE_TYPEINFO;

    void init(s32 id);
    void initControlGroup(int count);
    void setControl(int index, UIControl* control, int);

    void setInputManager(UIInputManager*);

    s32 m_pageId;
    u32 m_8;
    bool m_C;

    TransitionDir m_slideDir;
    u32 m_14;
    u32 m_18;
    u32 m_1C;
    u32 m_20;

    UIControlCollection m_children;
    UIInputManager* m_inputManager;

    /* 0x3C */ int m_forwardSound;
    /* 0x40 */ int m_backSound;
};

static_assert(sizeof(UIPage) == 0x44, "sizeof(UIPage) != 0x44");

} // namespace UI
