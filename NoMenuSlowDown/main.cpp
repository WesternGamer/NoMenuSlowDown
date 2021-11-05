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

#include "main.h"
#include <string>
#include <vector>
#include "natives.h"
#include "enums.h"
#include "types.h"

/// <summary>
/// Main entry point of ASI script.
/// </summary>
/// <param name="hInstance">Handle to DLL module.</param>
/// <param name="reason">Reason for calling function</param>
/// <param name="lpReserved">Reserved.</param>
/// <returns></returns>
BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, Main);
		break;
	case DLL_PROCESS_DETACH:
		Dispose();
		scriptUnregister(hInstance);
		break;
	}
	return TRUE;
}

void Main() 
{

#pragma region DoNotTouch
	// Add your code above this code.
	srand(GetTickCount64());
	while (true)
	{
		Update();
		WAIT(0);
	}
#pragma endregion
}

void Update() 
{
	//Is called on Update() just in case the ingame scripts call _ENABLE_REDUCE_TIME_SCALE_WHILE_MENU_IS_OPEN().
	HUD::_DISABLE_REDUCE_TIME_SCALE_WHILE_MENU_IS_OPEN();
}

void Dispose() 
{

}