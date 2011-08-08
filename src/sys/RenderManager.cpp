
#include "RenderManager.h"

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
}

CRenderManager::~CRenderManager()
{
}

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

void CRenderManager::DrawSprite(std::string package, std::string sprite, int index)
{
	Hash::iterator iter = m_hash.find(package);
	assert(iter != m_hash.end());

	CPackage::Ref pack = iter->second;
	assert(pack);

	pack->DrawSprite(sprite, index);
}

//***************************************************************************************************************
