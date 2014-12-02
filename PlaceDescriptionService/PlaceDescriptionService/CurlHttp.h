#pragma once
#include "http.h"
#include <curl/curl.h>
#include <string>
using namespace std;

class CurlHttp : public Http
{
public:
	CurlHttp(void);
	virtual ~CurlHttp(void);

	void initialize();
	virtual string get(const std::string& url) const;
	static string Response();
	static size_t writeCallback(const char* buf, size_t size, size_t nMemb, void*);

private:
   CURL* curl;

   static std::string response_;
};

