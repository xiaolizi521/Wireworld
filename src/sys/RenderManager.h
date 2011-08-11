
#ifndef __RENDERMANAGER_H__
#define __RENDERMANAGER_H__

#include <string>
#include <map>
#include <boost/intrusive_ptr.hpp>
#include <SDL/SDL.h>

#include "util/Singleton.h"
#include "util/RefCount.h"

//***************************************************************************************************************

struct CSprite
{
	int top;
	int lft;
	int count;
};

//***************************************************************************************************************

class CPackage : public CRefCount
{
public:
	// associated typedefs:
	typedef boost::intrusive_ptr<CPackage> Ref;
	typedef std::map<std::string, CSprite> Hash;

public:
	// c-tor and d-tor:
	explicit CPackage();

	// refs management:
	int IncRef();
	int DecRef();

	// drawing operations:
	void DrawSprite (std::string sprite, int index);

private:
	int  m_refs;
	Hash m_hash;
};

//***************************************************************************************************************

class CRenderManager : public CSingleton <CRenderManager>
{
	friend class CSingleton<CRenderManager>;

public:
	// associated typedefs:
	typedef std::map<std::string, CPackage::Ref> Hash;

	// sprite packages:
	void Attach  (std::string package);
	void Release (std::string package);

	// drawing operations:
	void DrawSprite (std::string package, std::string sprite, int index);

private:
	explicit CRenderManager();
	virtual ~CRenderManager();

	Hash m_hash;
	SDL_Surface *m_disp;
};

//***************************************************************************************************************

namespace RMan
{
	inline void Attach(std::string package)
	{ return CRenderManager::Get()->Attach(package); }

	inline void Release(std::string package)
	{ return CRenderManager::Get()->Release(package); }

	inline void DrawSprite(std::string package, std::string sprite, int index)
	{ return CRenderManager::Get()->DrawSprite(package, sprite, index); }
}

//***************************************************************************************************************

#endif
