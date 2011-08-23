#include "JsonUtils.h"
#include <fstream>

//***************************************************************************************************************

bool JsonFromFile(std::string path, Json::Value &root)
{
	typedef std::istreambuf_iterator<char> Iterator;

	// get file content:
	std::ifstream ifs("config.json");
	Iterator beg = Iterator(ifs);
	Iterator end = Iterator();
	std::string str(beg, end);

    // parse json string:
	Json::Reader reader;
	return reader.parse(str, root);
}

//***************************************************************************************************************
