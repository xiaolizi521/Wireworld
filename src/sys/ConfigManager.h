
#ifndef __CONFIGMANAGER_H__
#define __CONFIGMANAGER_H__

#include <string>
#include <json/json.h>

#include "util/Singleton.h"

//***************************************************************************************************************

class CConfigSection
{
public:
	explicit CConfigSection(Json::Value &root, std::string name);
	bool IsValid() const;

	int   GetInteger(std::string key);
	bool  GetBoolean(std::string key);
	float GetFloat(std::string key);

	void  SetInteger(std::string key, int val);
	void  SetBoolean(std::string key, bool val);
	void  SetFloat(std::string key, float val);

private:
	std::string  m_name;
	Json::Value &m_root;
};

//***************************************************************************************************************

class CConfigManager : public CSingleton <CConfigManager>
{
	friend class CSingleton<CConfigManager>;

public:
	CConfigSection GetSection(std::string name);

private:
	explicit CConfigManager();
	virtual ~CConfigManager();

	// actual doc root:
	Json::Value  m_root;
};

//***************************************************************************************************************

namespace CMan
{
	inline CConfigSection GetSection(std::string name)
	{ return CConfigManager::Get()->GetSection(name); }
}

//***************************************************************************************************************

#endif
