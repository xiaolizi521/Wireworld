
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <vector>
#include <boost/intrusive_ptr.hpp>

#include "util/RefCount.h"
#include "util/Singleton.h"

//***************************************************************************************************************

class CScene : public CRefCount
{
public:
	typedef boost::intrusive_ptr<CScene> Ptr;

public:
	virtual ~CScene() {}

	virtual void OnEnter()  = 0;
	virtual void OnLeave()  = 0;

	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
};

//***************************************************************************************************************

class CSceneManager : public CSingleton <CSceneManager>
{
public:
	void PushScene(CScene::Ptr scene);
	void PopScene();

	bool HasScenes() const;
	void RunGameLoop();

private:
	std::vector<CScene::Ptr> m_stack;
	CScene::Ptr GetTop();
};

//***************************************************************************************************************

namespace SMan
{
	inline void PushScene(CScene::Ptr scene)
	{ CSceneManager::Get()->PushScene(scene); }

	inline void PopScene()
	{ CSceneManager::Get()->PopScene(); }

	inline bool HasScenes()
	{ return CSceneManager::Get()->HasScenes(); }

	inline void RunGameLoop()
	{ CSceneManager::Get()->RunGameLoop(); }
}

//***************************************************************************************************************

#endif
