#include <fstream>
#include "ConfigManager.h"


//***************************************************************************************************************

CConfigSection::CConfigSection(Json::Value &root, std::string name)
: m_name(name), m_root(root)
{
}

bool CConfigSection::IsValid() const
{
	return !m_root[m_name].empty();
}

// getters:

int CConfigSection::GetInteger(std::string key)
{
	return m_root[m_name][key].asInt();
}

bool CConfigSection::GetBoolean(std::string key)
{
	return m_root[m_name][key].asBool();
}

float CConfigSection::GetFloat(std::string key)
{
	return (float)m_root[m_name][key].asDouble();
}

// setters:

void CConfigSection::SetInteger(std::string key, int val)
{
	m_root[m_name][key] = val;
}

void CConfigSection::SetBoolean(std::string key, bool val)
{
	m_root[m_name][key] = val;
}

void CConfigSection::SetFloat(std::string key, float val)
{
	m_root[m_name][key] = val;
}

//***************************************************************************************************************

CConfigManager::CConfigManager()
{
	typedef std::istreambuf_iterator<char> Iterator;

	std::ifstream ifs("config.json");
	Iterator beg = Iterator(ifs);
	Iterator end = Iterator();

	std::string str(beg, end);
	Json::Reader reader;

	reader.parse(str, m_root);
}

CConfigManager::~CConfigManager()
{
	std::ofstream ofs("config.json");

	Json::StyledWriter writer;
	ofs << writer.write(m_root);
}

CConfigSection CConfigManager::GetSection(std::string name)
{
	return CConfigSection(m_root, name);
}

//***************************************************************************************************************
