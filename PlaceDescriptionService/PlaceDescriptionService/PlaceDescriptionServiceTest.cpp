#include "gmock/gmock.h"
//#include "Http.h"
#include "HttpStub.h"
#include "PlaceDescriptionService.h"
using namespace testing;
using namespace std;

class APlaceDescriptionService: public Test {
public:
	static const string ValidLatitude;
	static const string ValidLongitude;
	static const string DefaultAddress;
	//HttpStub httpStub;
	NiceMock<HttpStub> httpStub;
	PlaceDescriptionService service;// (&httpStub);
	string expectedUrl;

	APlaceDescriptionService()
	{
		//InSequence forceExpectationOrder; doesn't work in fixture
		string urlStart = "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&";
		expectedUrl = urlStart +
			"lat=" + APlaceDescriptionService::ValidLatitude + "&" +
			"lon=" + APlaceDescriptionService::ValidLongitude;
		service = PlaceDescriptionService(&httpStub);
	}
};

const string APlaceDescriptionService::ValidLatitude("38.005");
const string APlaceDescriptionService::ValidLongitude("-104.44");
const string APlaceDescriptionService::DefaultAddress("{ \"address\": {\"road\":\"Drury Ln\",\"city\":\"Fountain\",\"state\":\"CO\",\"country\":\"US\"}}");

//TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation) 
//{	//uses default expected result 
/* can't do this with the gmock - either you set an expectation in the FixtureConstructor which all tests must fulfill
	or you set the expectation in the test case. Could factor out the expected data to a const as has been done with ValidLaititude to reduce 
	duplication in the test. in fact, lets do that now
*/
//	auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
//	ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
//}

TEST_F(APlaceDescriptionService, ReturnsDescriptionForAnotherValidLocation) 
{	//uses a specific expected result for this test case
	EXPECT_CALL(httpStub, get(_)) .WillOnce
		(Return("{ \"address\": {\"road\":\"Drury Ln\",\"city\":\"London\",\"country\":\"UK\"}}"));
	auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
	ASSERT_THAT(description, Eq("Drury Ln, London, , UK"));
}

TEST_F(APlaceDescriptionService,MakesHttpRequestToObtainAddress)
{//the get here appears to conflict with one from the std library, but when called, the PlaceDescriptionservice method is called
	EXPECT_CALL(httpStub, get(expectedUrl));
	service.summaryDescription(ValidLatitude,ValidLongitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) 
{
	InSequence forceExpectationOrder;
	EXPECT_CALL(httpStub, initialize());
	EXPECT_CALL(httpStub, get(_)).WillOnce
		(Return(DefaultAddress));
	auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
	ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}