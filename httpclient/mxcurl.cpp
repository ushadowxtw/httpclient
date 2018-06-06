#include "StdAfx.h"
#include "mxcurl.h"
#include "Cookies.h"
#include "Error.h"


Session::Session() {
    m_CurlHolder =newHolder();
    auto curl = m_CurlHolder->handle;
    if (curl) {
        // Set up some sensible defaults
        auto version_info = curl_version_info(CURLVERSION_NOW);
        auto version = std::string("curl/") + std::string(version_info->version);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, version.data());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, m_CurlHolder->error);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
#ifdef CPR_CURL_NOSIGNAL
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
#endif
#if LIBCURL_VERSION_MAJOR >= 7
#if LIBCURL_VERSION_MINOR >= 25
#if LIBCURL_VERSION_PATCH >= 0
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
#endif
#endif
#endif
    }
}
 Session:: ~Session()
 {
 
	 freeHolder(m_CurlHolder);
 }
Response Session::makeRequest(CURL* curl) {
  //  if (!parameters_.content.empty()) {
 //       Url new_url{url_ + "?" + parameters_.content};
   //     curl_easy_setopt(curl, CURLOPT_URL, new_url.data());
  //  } else {
        curl_easy_setopt(curl, CURLOPT_URL, m_Url.data());
   // }

 //   auto protocol = m_Url.substr(0, m_Url.find(':'));
  //  if (proxies_.has(protocol)) {
    //    curl_easy_setopt(curl, CURLOPT_PROXY, proxies_[protocol].data());
   // } else {
   //     curl_easy_setopt(curl, CURLOPT_PROXY, "");
    //}

    m_CurlHolder->error[0] = '\0';

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

    auto curl_error = curl_easy_perform(curl);

    char* raw_url;
    long response_code;
    double elapsed;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &raw_url);

    Cookies cookies;
    struct curl_slist* raw_cookies;
    curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &raw_cookies);
    for (struct curl_slist* nc = raw_cookies; nc; nc = nc->next) {
        auto tokens =split(nc->data, '\t');
        auto value = tokens.back();
        tokens.pop_back();
        cookies[tokens.back()] = value;
    }
    curl_slist_free_all(raw_cookies);

    return Response(static_cast<std::int32_t>(response_code),
                    std::move(response_string),
                    parseHeader(header_string),
                    std::move(raw_url),
                    elapsed,
                    std::move(cookies),
                    Error(curl_error, m_CurlHolder->error));
}
/*
//
void Session::init()
{



}
*/
CurlHolder* Session::newHolder() {
    CurlHolder* holder = new CurlHolder();
    holder->handle = curl_easy_init();
    holder->chunk = NULL;
    holder->formpost = NULL;
    return holder;
}

//释放资源
void Session::freeHolder(CurlHolder* holder) {

    curl_easy_cleanup(holder->handle);
    curl_slist_free_all(holder->chunk);
    curl_formfree(holder->formpost);
    delete holder;
}
//设置URL
void Session::SetUrl(const string & url) {
		m_Url = url;
}

void Session::SetHeader(const Header& header) {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        struct curl_slist* chunk = NULL;
        for (auto item = header.cbegin(); item != header.cend(); ++item) {
            auto header_string = std::string(item->first);
            if (item->second.empty()) {
                header_string += ";";
            } else {
                header_string += ": " + item->second;
            }

            auto temp = curl_slist_append(chunk, header_string.data());
            if (temp) {
                chunk = temp;
            }
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_slist_free_all(m_CurlHolder->chunk);
        m_CurlHolder->chunk = chunk;
    }
}

void Session::SetTimeout(const int& timeout) {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS,timeout);
    }
}

void Session::SetAuth(Authentication& auth) {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, auth.GetAuthString());
    }
}

void Session::SetPayload(string payload) {
//	payload=urlEncode(payload);
    auto curl = m_CurlHolder->handle;
    if (curl) {
		printf("%s\r\n",payload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, payload.length());
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, payload);
    }
}
void Session::SetCookies( Cookies& cookies) {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_COOKIELIST, "ALL");
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookies.GetEncoded().data());
    }
}


Response Session::Get() {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    }

    return makeRequest(curl);
}

Response Session::Head() {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, NULL);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    }

    return makeRequest(curl);
}

Response Session::Options() {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");
    }

    return makeRequest(curl);
}

Response Session::Patch() {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    }

    return makeRequest(curl);
}

Response Session::Post() {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    }

    return makeRequest(curl);
}

Response Session::Put() {
    auto curl = m_CurlHolder->handle;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    }

    return makeRequest(curl);
}



