#include "AddressExtractor.h"

AddressExtractor::AddressExtractor(void)
{
}


Address AddressExtractor::addressFrom(const string& json) const {
	Address address;
	Value jsonAddress(jsonAddressFrom(json));
	populate(address, jsonAddress);
	return address; 
}

Value AddressExtractor::jsonAddressFrom(const string& json) const {
	auto location = parse(json);
	return location.get("address", Value::null);
}

void AddressExtractor::populate(Address& address, Value& jsonAddress) const {
	address.road = getString(jsonAddress, "road");
	address.city = getString(jsonAddress, "city");
	address.state = getString(jsonAddress, "state");
	address.country = getString(jsonAddress, "country");
}

Value AddressExtractor::parse(const string& json) const {
	Value root;
	Reader reader;
	reader.parse(json, root);
	return root; 
}

string AddressExtractor::getString(Value& result, const string& name) const {
	return result.get(name, "").asString();
}


AddressExtractor::~AddressExtractor(void)
{
}
