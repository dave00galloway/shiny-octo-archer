#include "PlaceDescriptionService.h"

PlaceDescriptionService::PlaceDescriptionService(Http* http)
{
	_http = http;
}

PlaceDescriptionService::PlaceDescriptionService()
{
	_http = NULL;
};

string PlaceDescriptionService:: summaryDescription
	(const string& latitude,const string& longitude) const
{
	auto request = createGetRequestUrl(latitude,longitude);
	auto jsonResponse = get(request);
	return summaryDescription(jsonResponse);
}

string PlaceDescriptionService::summaryDescription(
	const string& response) const 
{
	AddressExtractor extractor;
	auto address = extractor.addressFrom(response);
	return address.road + ", " + address.city + ", " +
		address.state + ", " + address.country;
}

string PlaceDescriptionService::get
	(const string& requestUrl) const 
{
	 //auto r = _http->get(requestUrl);
	_http->initialize();
	return  _http->get(requestUrl);
	//throw exception();
}

string PlaceDescriptionService:: createGetRequestUrl
	(const string& latitude, const string& longitude)const
{
	string server("http://open.mapquestapi.com/");
	string document("nominatim/v1/reverse");
	return server + document + "?" +
		keyValue("format", "json") + "&" +
		keyValue("lat", latitude) + "&" +
		keyValue("lon", longitude);
}

string PlaceDescriptionService::keyValue 
	(const string& key, const string& value) const 
{
	return key + "=" + value;
}

PlaceDescriptionService::~PlaceDescriptionService(void)
{
}
