#include "PlaceDescriptionFactoryService.h"

string PlaceDescriptionFactoryService::get(const string& url) const 
{
	auto http = httpService();
	http->initialize();
	return http->get(url);
}
shared_ptr<Http> PlaceDescriptionFactoryService::httpService() const 
{
	return make_shared<CurlHttp>();
	//throw exception("Not Implemented");
}

string PlaceDescriptionFactoryService:: summaryDescription
	(const string& latitude,const string& longitude) const
{
	auto request = createGetRequestUrl(latitude,longitude);
	auto jsonResponse = get(request);
	return summaryDescription(jsonResponse);
}

string PlaceDescriptionFactoryService::summaryDescription(
	const string& response) const 
{
	AddressExtractor extractor;
	auto address = extractor.addressFrom(response);
	return address.road + ", " + address.city + ", " +
		address.state + ", " + address.country;
}

string PlaceDescriptionFactoryService:: createGetRequestUrl
	(const string& latitude, const string& longitude)const
{
	string server("http://open.mapquestapi.com/");
	string document("nominatim/v1/reverse");
	return server + document + "?" +
		keyValue("format", "json") + "&" +
		keyValue("lat", latitude) + "&" +
		keyValue("lon", longitude);
}

string PlaceDescriptionFactoryService::keyValue 
	(const string& key, const string& value) const 
{
	return key + "=" + value;
}



PlaceDescriptionFactoryService::PlaceDescriptionFactoryService(void)
{
}


PlaceDescriptionFactoryService::~PlaceDescriptionFactoryService(void)
{
}
