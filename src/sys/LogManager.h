
#ifndef __LOGMANAGER_H__
#define __LOGMANAGER_H__

#include <string>
#include <fstream>
#include "util/Singleton.h"

//***************************************************************************************************************

class CLogManager : public CSingleton <CLogManager>
{
	friend class CSingleton<CLogManager>;

public:
	void Log(std::string msg);
	void Err(std::string msg);

	// our test for critical errors:
	void Check(bool test, std::string msg);

private:
	explicit CLogManager();
	virtual ~CLogManager();

	// file for output:
	std::ofstream m_file;
};

//***************************************************************************************************************

namespace LMan
{
	inline void Log(std::string msg)
	{ CLogManager::Get()->Log(msg); }

	inline void Err(std::string msg)
	{ CLogManager::Get()->Err(msg); }

	inline void Check(bool test, std::string msg)
	{ CLogManager::Get()->Check(test, msg); }
}

//***************************************************************************************************************

#endif
