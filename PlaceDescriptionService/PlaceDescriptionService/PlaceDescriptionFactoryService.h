#pragma once
#include <memory>
#include "Address.h"
#include "Http.h"
#include <string>
#include "AddressExtractor.h"
#include "CurlHttp.h"

class PlaceDescriptionFactoryService 
{
public:
	PlaceDescriptionFactoryService();
	PlaceDescriptionFactoryService(Http* http);
	//TODO:- create a Move Constructor so that when PlaceDescriptionFactoryService is created as a field it can be initialised without double creating a PDS
	virtual ~PlaceDescriptionFactoryService(void);

	string summaryDescription(const string& latitude, const string& longitude) const ;
	string summaryDescription(const string& response) const;
	string get(const string& requestUrl) const ;
	
protected:
	virtual std::shared_ptr<Http> httpService() const;

private:
	Http* _http;
	string createGetRequestUrl(const string& latitude, const string& longitude)const;
	string keyValue (const string& key, const string& value) const ;
};

