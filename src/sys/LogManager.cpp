#include "LogManager.h"
#include <assert.h>
#include <stdlib.h>

//***************************************************************************************************************

CLogManager::CLogManager()
{
    m_file.open("wireworld.log");
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

//***************************************************************************************************************
