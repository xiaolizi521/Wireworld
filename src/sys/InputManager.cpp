#include "InputManager.h"
#include <Windows.h>

//***************************************************************************************************************

CInputManager::CInputManager()
{
    m_codes[Key_Up]    = VK_UP;
	m_codes[Key_Down]  = VK_DOWN;
	m_codes[Key_Left]  = VK_LEFT;
	m_codes[Key_Right] = VK_RIGHT;
	m_codes[Key_Esc]   = VK_ESCAPE;
}

CInputManager::~CInputManager()
{
}

bool CInputManager::Pressed(Keys key)
{
    return (GetAsyncKeyState(m_codes[key]) != 0) ? true : false;
}

//***************************************************************************************************************
