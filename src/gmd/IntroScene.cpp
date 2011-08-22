#include "IntroScene.h"
#include "sys/InputManager.h"

//***************************************************************************************************************

CIntroScene::CIntroScene()
{
}

CIntroScene::~CIntroScene()
{
}

void CIntroScene::OnEnter()
{
}

void CIntroScene::OnLeave()
{
}

void CIntroScene::OnUpdate()
{
    if (IMan::Pressed(Key_Esc))
    {
        // leave when escape is hit:
        SMan::PopScene();
    }
}

void CIntroScene::OnRender()
{
}

//***************************************************************************************************************
