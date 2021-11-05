/*Copyright (c) 2021 WesternGamer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#pragma once

#include "main.h"

template <typename T>
static inline void nativePush(T val)
{
	UINT64 val64 = 0;
	if (sizeof(T) > sizeof(UINT64))
	{
		throw "error, value size > 64 bit";
	}
	*reinterpret_cast<T*>(&val64) = val; // &val + sizeof(dw) - sizeof(val)
	nativePush64(val64);
}

static inline void pushArgs()
{
}

template <typename T>
static inline void pushArgs(T arg)
{
	nativePush(arg);
}

template <typename T, typename... Ts>
static inline void pushArgs(T arg, Ts... args)
{
	nativePush(arg);
	pushArgs(args...);
}

template <typename R, typename... Ts>
static inline R invoke(UINT64 hash, Ts... args)
{
	nativeInit(hash);
	pushArgs(args...);
	return *reinterpret_cast<R*>(nativeCall());
}