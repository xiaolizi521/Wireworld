
#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "sys/SceneManager.h"

//***************************************************************************************************************

class CIntroScene : public CScene
{
public:
    explicit CIntroScene();
    virtual ~CIntroScene();

	virtual void OnEnter();
	virtual void OnLeave();

	virtual void OnUpdate();
	virtual void OnRender();
};

//***************************************************************************************************************

#endif
