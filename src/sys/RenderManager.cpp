
#include "RenderManager.h"
#include "LogManager.h"
#include "ConfigManager.h"
#include "util/JsonUtils.h"
#include <SDL/SDL_image.h>

//***************************************************************************************************************

// c-tor and d-tor:

CPackage::CPackage(std::string name)
: m_refs(1), m_surf(NULL)
{
    // resolve file path:
    CConfigSection cfg  = CMan::GetSection("path");
    std::string sprRoot = cfg.GetString("sprites");

    std::string imgPath = sprRoot + name + ".png";
    std::string dscPath = sprRoot + name + ".json";

    // load and check:
    LoadSurf(imgPath);
    LoadDesc(dscPath);

    LMan::Check(m_surf != NULL, "failed to load surface");
    LMan::Check(m_hash.size(),  "failed to load descriptor");
}

CPackage::~CPackage()
{
    if (m_surf) { SDL_FreeSurface(m_surf); }
}

// ref management:

int CPackage::IncRef()
{
	return ++ m_refs;
}

int CPackage::DecRef()
{
	return -- m_refs;
}

// drawing:

void CPackage::DrawSprite(std::string sprite, int index)
{
	Hash::iterator it = m_hash.find(sprite);
}

// loaders:

void CPackage::LoadSurf(std::string path)
{
	if (SDL_Surface *res = IMG_Load(path.c_str()))
	{
		m_surf = SDL_DisplayFormatAlpha(res);
        SDL_FreeSurface(res);
	}
}

void CPackage::LoadDesc(std::string path)
{
    Json::Value root;
    JsonFromFile(path, root);

    Json::Value list = root["sprites"];
    for (size_t index = 0; index < list.size(); ++ index)
    {
        Json::Value desc = list[index];
        std::string name = desc["name"].asString();

        CSprite sprite;
        sprite.count  = desc["count"].asInt();
        sprite.orig.x = desc["left"].asInt();
        sprite.orig.y = desc["top"].asInt();
        sprite.size.x = desc["wid"].asInt();
        sprite.size.y = desc["hgt"].asInt();

        m_hash.insert(Hash::value_type(name, sprite));
    }
}

//***************************************************************************************************************

CRenderManager::CRenderManager()
{
    // perform SDL initialization:
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    LMan::Check((result == 0), "failed to initialize SDL");

    // read display configuration:
    CConfigSection cfg = CMan::GetSection("window");

    const int wid = cfg.GetInteger("width");
    const int hgt = cfg.GetInteger("height");

    Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
    flags |= cfg.GetBoolean("full") ? SDL_FULLSCREEN : SDL_NOFRAME;

    // create display surface:
    m_disp = SDL_SetVideoMode(wid, hgt, 32, flags);
    LMan::Check((m_disp != 0), "failed to set video mode");
}

CRenderManager::~CRenderManager()
{
    SDL_FreeSurface(m_disp);
    SDL_Quit();
}

// package management:

void CRenderManager::Attach(std::string name)
{
	Hash::iterator iter = m_hash.find(name);
	if (iter == m_hash.end())
	{
		CPackage::Ref pack = new CPackage(name);
		assert(pack);

		m_hash.insert(Hash::value_type(name, pack));
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

    SDL_Rect rc = {0,0,100,100};
    SDL_FillRect(m_disp, &rc, 0xFFFFFF00);
}

void CRenderManager::EndFrame()
{
    SDL_Flip(m_disp);
}

//***************************************************************************************************************
