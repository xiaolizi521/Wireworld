#ifndef __JSONUTILS_H__
#define __JSONUTILS_H__

#include <string>
#include <json/json.h>

//***************************************************************************************************************

// get root element, given a file path:
bool JsonFromFile(std::string path, Json::Value &root);

//***************************************************************************************************************

#endif
