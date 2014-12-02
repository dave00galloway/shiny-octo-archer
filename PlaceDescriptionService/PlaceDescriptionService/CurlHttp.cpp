#include "CurlHttp.h"

string CurlHttp::response_;

CurlHttp::CurlHttp(void)
	: curl(NULL)
{
}

void CurlHttp::initialize() 
{
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlHttp::writeCallback);
}

string CurlHttp::get(const string& url) const 
{
	response_ = "invalid request"; // TODO test
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	return CurlHttp::Response();
}

string CurlHttp::Response() {
	return response_;
}

size_t CurlHttp::writeCallback(const char* buf, size_t size, size_t nMemb, void*) 
{
	for (auto i = 0u; i < size * nMemb; i++) 
		response_.push_back(buf[i]);
	return size * nMemb;
}



CurlHttp::~CurlHttp(void)
{
	curl_global_cleanup();
}
