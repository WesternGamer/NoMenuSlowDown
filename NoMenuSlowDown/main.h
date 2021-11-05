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

//Imports functions from script hook.

#include <windows.h>

#define IMPORT __declspec(dllimport)

/* keyboard */

// DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow
typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

// Register keyboard handler
// must be called on dll attach
IMPORT void keyboardHandlerRegister(KeyboardHandler handler);

// Unregister keyboard handler
// must be called on dll detach
IMPORT void keyboardHandlerUnregister(KeyboardHandler handler);

/* scripts */

IMPORT void scriptWait(DWORD time);
IMPORT void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptUnregister(HMODULE module);
IMPORT void scriptUnregister(void(*LP_SCRIPT_MAIN)()); // deprecated

IMPORT void nativeInit(UINT64 hash);
IMPORT void nativePush64(UINT64 val);
IMPORT PUINT64 nativeCall();

static void WAIT(DWORD time) { scriptWait(time); }
static void TERMINATE() { WAIT(MAXDWORD); }

// Returns pointer to global variable
// make sure that you check game version before accessing globals because
// ids may differ between patches
IMPORT UINT64* getGlobalPtr(int globalId);

/* world */

// Get entities from internal pools
// return value represents filled array elements count
// can be called only in the same thread as natives
IMPORT int worldGetAllVehicles(int* arr, int arrSize);
IMPORT int worldGetAllPeds(int* arr, int arrSize);
IMPORT int worldGetAllObjects(int* arr, int arrSize);
IMPORT int worldGetAllPickups(int* arr, int arrSize);

/* misc */

// Returns base object pointer using it's script handle
// make sure that you check game version before accessing object fields because
// offsets may differ between patches
IMPORT BYTE* getScriptHandleBaseAddress(int handle);

enum eGameVersion : int
{
	VER_AUTO,
	VER_1_0_1207_60_RGS,
	VER_1_0_1207_69_RGS,

	VER_SIZE,
	VER_UNK = -1
};

IMPORT eGameVersion getGameVersion();

void Main();

void Update();

void Dispose();