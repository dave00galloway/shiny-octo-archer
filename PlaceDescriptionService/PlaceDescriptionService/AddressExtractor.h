#pragma once

#include <value.h>
#include <reader.h>
#include <string>
#include "Address.h"

using namespace std;
using namespace Json;

class AddressExtractor
{
public:
	AddressExtractor(void);
	Address addressFrom(const string& json) const;
	virtual ~AddressExtractor(void);

private:
   Value jsonAddressFrom(const string& json) const;
   void populate(Address& address, Value& jsonAddress) const;
   Value parse(const string& json) const;
   string getString(Value& result, const string& name) const;

};

