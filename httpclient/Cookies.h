#pragma once
#include <map>
#include <sstream>
#include <string>
using namespace std;
#include "util.h"
class Cookies {
  public:
    Cookies() {}
    Cookies(const std::map<std::string, std::string>& map) : map_(map) {}

    std::string& operator[](const std::string& key);
    std::string GetEncoded() ;

  private:
    std::map<std::string, std::string> map_;
};


