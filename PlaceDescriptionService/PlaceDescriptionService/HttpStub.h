#pragma once
#include "Http.h"
#include "gmock/gmock.h"
// not importing the entire testing namespace here avoids a conflict between testing::Value and Json::Value in the AddressExtractor.h
using testing::Eq; 
using namespace std;

//GMOCK
class HttpStub : public Http
{
public:

	HttpStub(void)
	{
	}
	MOCK_METHOD0(initialize,void());
	MOCK_CONST_METHOD1(get,string(const string&));

	virtual ~HttpStub(void)
	{
	}
};

//manually created mock
//class HttpStub : public Http
//{
//public:
//
//	HttpStub(void)
//	{
//	}
//
//	string returnResponse;
//	string expectedUrl;
//	void initialize() override {}
//	string get(const string& url) const override 
//	{
//		verify(url);
//		return returnResponse;
//	}
//	void verify(const string& url) const
//	{
//		ASSERT_THAT(url,Eq(expectedUrl));
//	}
//
//	virtual ~HttpStub(void)
//	{
//	}
//};