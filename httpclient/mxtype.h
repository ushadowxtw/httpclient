#pragma once
#include <string>
#include <map>

#include <utility>
#include <curl.h>
using namespace std;
class mxtype
{
public:
	mxtype(void);
	~mxtype(void);
};



struct CurlHolder {
    CURL* handle;
    struct curl_slist* chunk;
    struct curl_httppost* formpost;
    char error[CURL_ERROR_SIZE];
};

struct CaseInsensitiveCompare {
    bool operator()(const std::string& a, const std::string& b) ;
};

#define Header std::map<std::string, std::string>

#define CPR_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

#define Url string

