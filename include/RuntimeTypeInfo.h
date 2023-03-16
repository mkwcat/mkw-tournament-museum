// RuntimeTypeInfo.h - Reimplementation of NW4R's RuntimeTypeInfo class
//
// SPDX-License-Identifier: MIT

#pragma once

// A TypeInfo system for downcasting, used by MKW's UI system. It's actually
// from NW4R, but we don't have NW4R!

class RuntimeTypeInfo
{
public:
    // Constructor invoked by sinit
    RuntimeTypeInfo(const RuntimeTypeInfo* parent)
      : m_parent(parent)
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
  virtual const RuntimeTypeInfo* getRuntimeTypeInfo()                          \
  {                                                                            \
    return &typeInfo;                                                          \
  }                                                                            \
  static const RuntimeTypeInfo typeInfo

#define TYPEINFO_DERIVED(obj, base)                                            \
  const RuntimeTypeInfo obj::typeInfo(&base::typeInfo)
#define TYPEINFO_ROOT(obj) const RuntimeTypeInfo obj::typeInfo(nullptr)
