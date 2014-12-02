//reworked examples using the OverrideFactoryMethod
#include "gmock/gmock.h"
//#include "Http.h"
#include "HttpStub.h"
#include "PlaceDescriptionFactoryService.h"
#include <memory>
using namespace testing;
using namespace std;

class PlaceDescriptionService_StubHttpService: public PlaceDescriptionFactoryService 
{
public:
	PlaceDescriptionService_StubHttpService(shared_ptr<HttpStub> httpStub)
		: httpStub_(httpStub) {}
	shared_ptr<Http> httpService() const override { return httpStub_; }
	shared_ptr<Http> httpStub_;
};

class APlaceDescriptionFactoryService: public Test {
public:
	static const string ValidLatitude;
	static const string ValidLongitude;
	static const string DefaultAddress;
	//HttpStub httpStub;
	NiceMock<HttpStub> httpStub;
	PlaceDescriptionFactoryService service;// (&httpStub);
	string expectedUrl;

	APlaceDescriptionFactoryService()
	{
		//InSequence forceExpectationOrder; doesn't work in fixture
		string urlStart = "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&";
		expectedUrl = urlStart +
			"lat=" + APlaceDescriptionFactoryService::ValidLatitude + "&" +
			"lon=" + APlaceDescriptionFactoryService::ValidLongitude;
		//	service = PlaceDescriptionFactoryService(&httpStub);
	}
};

const string APlaceDescriptionFactoryService::ValidLatitude("38.005");
const string APlaceDescriptionFactoryService::ValidLongitude("-104.44");
const string APlaceDescriptionFactoryService::DefaultAddress("{ \"address\": {\"road\":\"Drury Ln\",\"city\":\"Fountain\",\"state\":\"CO\",\"country\":\"US\"}}");

TEST_F(APlaceDescriptionFactoryService, MakesHttpRequestToObtainAddressViaFactory) {
	InSequence forceExpectationOrder;
	shared_ptr<HttpStub> httpStub(new HttpStub);
	string urlStart(
		"http://open.mapquestapi.com/nominatim/v1/reverse?format=json&");
	auto expectedURL = urlStart +
		"lat=" + APlaceDescriptionFactoryService::ValidLatitude + "&" +
		"lon=" + APlaceDescriptionFactoryService::ValidLongitude;
	EXPECT_CALL(*httpStub, initialize());
	EXPECT_CALL(*httpStub, get(expectedURL));
	PlaceDescriptionService_StubHttpService service(httpStub);
	service.summaryDescription(ValidLatitude, ValidLongitude);
}

TEST_F(APlaceDescriptionFactoryService, DISABLED_ReturnsDescriptionForAnotherValidLocation) 
{	//uses a specific expected result for this test case
	EXPECT_CALL(httpStub, get(_)) .WillOnce
		(Return("{ \"address\": {\"road\":\"Drury Ln\",\"city\":\"London\",\"country\":\"UK\"}}"));
	/*	auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
	ASSERT_THAT(description, Eq("Drury Ln, London, , UK"));
	*/
}

TEST_F(APlaceDescriptionFactoryService,DISABLED_MakesHttpRequestToObtainAddress)
{//the get here appears to conflict with one from the std library, but when called, the PlaceDescriptionFactoryService method is called
	EXPECT_CALL(httpStub, get(expectedUrl));
	//service.summaryDescription(ValidLatitude,ValidLongitude);
}

TEST_F(APlaceDescriptionFactoryService, DISABLED_FormatsRetrievedAddressIntoSummaryDescription) 
{
	InSequence forceExpectationOrder;
	EXPECT_CALL(httpStub, initialize());
	EXPECT_CALL(httpStub, get(_)).WillOnce
		(Return(DefaultAddress));
	//auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
	//ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}