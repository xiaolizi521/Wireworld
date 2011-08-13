
#include "SceneManager.h"
#include "RenderManager.h"

//***************************************************************************************************************

// stack modification:

void CSceneManager::PushScene(CScene::Ptr scene)
{
	assert(scene);

	scene->OnEnter();
	m_stack.push_back(scene);
}

void CSceneManager::PopScene()
{
	GetTop()->OnLeave();
	m_stack.pop_back();
}

// main game loop:

bool CSceneManager::HasScenes() const
{
	return (m_stack.size() > 0);
}

void CSceneManager::RunGameLoop()
{
	while (HasScenes())
	{
	    // pre-frame operations:
		RMan::BegFrame();

		CScene::Ptr top = GetTop();

		top->OnUpdate();
		top->OnRender();

	    // post-frame operations:
		RMan::EndFrame();
	}
}

// helpers:

CScene::Ptr CSceneManager::GetTop()
{
	assert(HasScenes());
	return m_stack.back();
}

//***************************************************************************************************************
