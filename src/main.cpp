#include <iostream>

#include "sys/LogManager.h"
#include "sys/SceneManager.h"
#include "sys/ConfigManager.h"
#include "sys/InputManager.h"
#include "sys/RenderManager.h"

//***************************************************************************************************************

int main()
{
	// create singletons:
	CLogManager::Guard    g_LMan;
	CConfigManager::Guard g_CMan;
	CRenderManager::Guard g_RMan;
	CSceneManager::Guard  g_SMan;
	CInputManager::Guard  g_IMan;

    LMan::Log("Start the game");

	CConfigSection screen = CMan::GetSection("screen");
	assert(screen.IsValid());

	int a = screen.GetInteger("a");
	int b = screen.GetInteger("b");
	float c = screen.GetFloat("c");
	bool d = screen.GetBoolean("d");

	screen.SetInteger("a", 100);
	screen.SetInteger("b", 300);

	CConfigSection sample = CMan::GetSection("sample");

	sample.SetInteger("a", 100);
	sample.SetInteger("b", 300);

	// enjoy the game:
	SMan::RunGameLoop();

	return 0;
}

//***************************************************************************************************************
