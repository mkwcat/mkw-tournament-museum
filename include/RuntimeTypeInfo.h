// RuntimeTypeInfo.h - Reimplementation of NW4R's RuntimeTypeInfo class
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

// A TypeInfo system for downcasting, used by MKW's UI system. It's actually
// from NW4R, but we don't have NW4R!

class RuntimeTypeInfo
{
public:
    // Constructor invoked by sinit
    RuntimeTypeInfo(const RuntimeTypeInfo* parent) : m_parent(parent)
    {
    }

    const RuntimeTypeInfo* m_parent;

protected:
    bool isValidCast(const RuntimeTypeInfo* cast) const
    {
        for (const RuntimeTypeInfo* info = this; info != nullptr;
             info = info->m_parent) {
            if (info == cast)
                return true;
        }
        return false;
    }

    template <class T>
    static const RuntimeTypeInfo* __getObjTypeInfo(T* obj)
    {
        return &T::typeInfo;
    }

public:
    template <class Derived, class Base>
    static Derived cast(Base* base)
    {
        if (base != nullptr && base->getRuntimeTypeInfo()->isValidCast(
                                   __getObjTypeInfo((Derived) nullptr))) {
            return reinterpret_cast<Derived>(base);
        }
        return nullptr;
    }
};

#define INSTANTIATE_TYPEINFO                                                   \
    virtual const RuntimeTypeInfo* getRuntimeTypeInfo()                        \
    {                                                                          \
        return &typeInfo;                                                      \
    }                                                                          \
    static const RuntimeTypeInfo typeInfo

#define TYPEINFO_DERIVED(obj, base)                                            \
    const RuntimeTypeInfo obj::typeInfo(&base::typeInfo)
#define TYPEINFO_ROOT(obj) const RuntimeTypeInfo obj::typeInfo(nullptr)