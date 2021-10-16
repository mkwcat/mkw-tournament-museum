// Function.h - UI member function pointers
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

namespace UI
{

template <class P1, class P2>
class FunctionBase
{
public:
    virtual void call(P1 param1, P2 param2) = 0;
};

template <class P1, class P2>
class Function
{
    FunctionBase<P1, P2>* m_function;

public:
    void operator()(P1 param1, P2 param2)
    {
        m_function->call(param1, param2);
    }

    void operator=(FunctionBase<P1, P2>* function)
    {
        m_function = function;
    }
};

template <class O, class P1, class P2>
class FunctionImp : public FunctionBase<P1, P2>
{
    O* m_object;
    void (O::*m_function)(P1, P2);

public:
    FunctionImp(O* object, void (O::*function)(P1, P2))
    {
        m_object = object;
        m_function = function;
    }

    virtual void call(P1 param1, P2 param2)
    {
        (m_object->*m_function)(param1, param2);
    }
};

} // namespace UI
