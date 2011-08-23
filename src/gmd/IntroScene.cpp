#include "IntroScene.h"
#include "sys/InputManager.h"
#include "sys/RenderManager.h"

//***************************************************************************************************************

CIntroScene::CIntroScene()
{
}

CIntroScene::~CIntroScene()
{
}

void CIntroScene::OnEnter()
{
    RMan::Attach("pack");
}

void CIntroScene::OnLeave()
{
    RMan::Release("pack");
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
    RMan::DrawSprite("pack", "player", 1);
}

//***************************************************************************************************************
