
#include "RenderManager.h"
#include "LogManager.h"

//***************************************************************************************************************

CPackage::CPackage()
: m_refs(1)
{
}

int CPackage::IncRef()
{
	return ++ m_refs;
}

int CPackage::DecRef()
{
	return -- m_refs;
}

void CPackage::DrawSprite(std::string sprite, int index)
{
	Hash::iterator it = m_hash.find(sprite);
}

//***************************************************************************************************************

CRenderManager::CRenderManager()
{
    // perform SDL initialization:
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    LMan::Check((result == 0), "failed to initialize SDL");

    // create display surface:
    m_disp = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    LMan::Check((m_disp != 0), "failed to set video mode");
}

CRenderManager::~CRenderManager()
{
    SDL_FreeSurface(m_disp);
    SDL_Quit();
}

// package management:

void CRenderManager::Attach(std::string package)
{
	Hash::iterator iter = m_hash.find(package);
	if (iter == m_hash.end())
	{
		CPackage::Ref pack = new CPackage();
		assert(pack);

		m_hash.insert(Hash::value_type(package, pack));
	}
	else
	{
		CPackage::Ref pack = iter->second;
		assert(pack);

		pack->IncRef();
	}
}

void CRenderManager::Release(std::string package)
{
	Hash::iterator iter = m_hash.find(package);
	assert(iter != m_hash.end());

	CPackage::Ref pack = iter->second;
	assert(pack);

	if (!pack->DecRef())
	{
		m_hash.erase(package);
	}
}

// drawing operations:

void CRenderManager::DrawSprite(std::string package, std::string sprite, int index)
{
	Hash::iterator iter = m_hash.find(package);
	assert(iter != m_hash.end());

	CPackage::Ref pack = iter->second;
	assert(pack);

	pack->DrawSprite(sprite, index);
}

// loop operations:

void CRenderManager::BegFrame()
{

}

void CRenderManager::EndFrame()
{
    SDL_Flip(m_disp);
}

//***************************************************************************************************************
