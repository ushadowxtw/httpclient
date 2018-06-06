#pragma once

#include <curl.h>
#include "mxtype.h"
#include "Response.h"
class mxcurl
{
public:
	mxcurl(void);
	~mxcurl(void);
};


class Authentication {
  public:
    template <typename UserType, typename PassType>
    Authentication(UserType&& username, PassType&& password)
            : username_(CPR_FWD(username)), password_(CPR_FWD(password)),
              auth_string_(username_ + ":" + password_) {}

    const char* GetAuthString(){
		return auth_string_.c_str();
	};

  private:
    std::string username_;
    std::string password_;
    std::string auth_string_;
};

class Session {
  public:
    Session();
    ~Session();


public:
	void freeHolder(CurlHolder* holder) ;
	CurlHolder* newHolder();

public:
	void SetUrl(const string & url);
	void SetHeader(const Header& header);
	void SetTimeout(const int& timeout);
	void SetAuth( Authentication& auth) ;
	void SetPayload(string payload);
	void SetCookies(Cookies& cookies) ;

	Response Get() ;
	Response Head() ;
	Response Options() ;
	Response Patch() ;
	Response Post() ;
	Response Put();


	Response makeRequest(CURL* curl);


private:
	CurlHolder *m_CurlHolder;

private:
	string m_Url;

};