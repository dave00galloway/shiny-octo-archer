#pragma once
#include "Address.h"
#include "Http.h"
#include <string>
#include "AddressExtractor.h"
using namespace std;

class PlaceDescriptionService
{
public:
	PlaceDescriptionService();
	PlaceDescriptionService(Http* http);
	//TODO:- create a Move Constructor so that when PlaceDescriptionService is created as a field it can be initialised without double creating a PDS
	virtual ~PlaceDescriptionService(void);

	string summaryDescription(const string& latitude, const string& longitude) const ;
	string summaryDescription(const string& response) const;
	string get(const string& requestUrl) const ;

private:
	Http* _http;
	string createGetRequestUrl(const string& latitude, const string& longitude)const;
	string keyValue (const string& key, const string& value) const ;
};

