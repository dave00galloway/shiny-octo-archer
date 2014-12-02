#pragma once
#include <string>
using namespace std;
class Http
{
public:

	virtual ~Http() {}
	virtual void initialize() = 0;
	virtual string get(const string& url) const = 0;

};

