
#include <fstream>

#include "ConfigManager.h"
#include "LogManager.h"

//***************************************************************************************************************

CConfigSection::CConfigSection(Json::Value &root, std::string name)
: m_name(name), m_root(root)
{
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

std::string CConfigSection::GetString(std::string key)
{
    return m_root[m_name][key].asString();
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

void CConfigSection::SetString(std::string key, std::string val)
{
	m_root[m_name][key] = val;
}

//***************************************************************************************************************

CConfigManager::CConfigManager()
{
	typedef std::istreambuf_iterator<char> Iterator;

	// get file content:
	std::ifstream ifs("config.json");
	Iterator beg = Iterator(ifs);
	Iterator end = Iterator();
	std::string str(beg, end);

    // parse json string:
	Json::Reader reader;
	bool result = reader.parse(str, m_root);
	LMan::Check(result, reader.getFormatedErrorMessages());
}

CConfigManager::~CConfigManager()
{
	std::ofstream ofs("config.json");

	Json::StyledWriter writer;
	ofs << writer.write(m_root);
}

CConfigSection CConfigManager::GetSection(std::string name)
{
    // ensure that our section exists:
    bool hasSect = !m_root[name].empty();
    LMan::Check(hasSect, "missing config section");

    // return actual config section:
	return CConfigSection(m_root, name);
}

//***************************************************************************************************************
