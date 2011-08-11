#include "LogManager.h"
#include <assert.h>
#include <stdlib.h>

//***************************************************************************************************************

CLogManager::CLogManager()
{
    m_file.open("wireworld.log");
    assert(m_file.is_open());
}

CLogManager::~CLogManager()
{
    m_file.close();
}

void CLogManager::Log(std::string msg)
{
    m_file << msg << std::endl;
}

void CLogManager::Err(std::string msg)
{
    assert(false);

    // write final log:
    m_file << msg << std::endl;
    m_file.close();

    // terminate app:
    exit(1);
}

// shortcut for writing errors:

void CLogManager::Check(bool test, std::string msg)
{
    if (!test)
    {
        Err(msg);
    }
}

//***************************************************************************************************************
