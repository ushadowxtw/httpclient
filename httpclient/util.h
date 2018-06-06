#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

#include "mxtype.h"



Header parseHeader(const std::string& headers);
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);
std::vector<std::string> split(const std::string& to_split, char delimiter);
std::string urlEncode(const std::string& response);


#endif
