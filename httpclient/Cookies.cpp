#include "StdAfx.h"
#include "Cookies.h"
#include <algorithm> 

std::string Cookies::GetEncoded()  {
    std::stringstream stream;
	map<std::string, std::string>::iterator item;

	for (item=map_.begin(); item!=map_.end();item++) {
        stream <<urlEncode(item->first) << "=";
        // special case version 1 cookies, which can be distinguished by
        // beginning and trailing quotes
        if (!item->second.empty() && item->second.front() == '"' && item->second.back() == '"') {
            stream << item->second;
        } else {
            stream <<urlEncode(item->second);
        }
        stream << "; ";
    }
    return stream.str();
}

std::string& Cookies::operator[](const std::string& key) {
    return map_[key];
}
