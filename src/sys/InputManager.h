
#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "util/Singleton.h"

//***************************************************************************************************************

enum Keys
{
	Key_Up,
	Key_Down,
	Key_Left,
	Key_Right,
	Key_Esc,
	Key_Count,
};

//***************************************************************************************************************

class CInputManager : public CSingleton <CInputManager>
{
	friend class CSingleton<CInputManager>;

public:
	bool Pressed(Keys key);

private:
	explicit CInputManager();
	virtual ~CInputManager();

	// keyboard mapping:
	int m_codes[Key_Count];
};

//***************************************************************************************************************

namespace IMan
{
	inline bool Pressed(Keys key)
	{ return CInputManager::Get()->Pressed(key); }
}

//***************************************************************************************************************

#endif
