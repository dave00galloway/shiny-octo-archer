#include "gmock/gmock.h"
#include <string>
#include "CurlHttp.h"

using namespace ::testing;
using namespace std;

TEST(Http, WriteCallback) 
{
   string buffer("123456789012");
   size_t size(12);
   size_t numberOfMembers(1);
   CurlHttp::writeCallback("123456789012", size, numberOfMembers, NULL);
   ASSERT_THAT(CurlHttp::Response(), Eq("123456789012"));
}

TEST(HttpIntegration, DISABLED_Get) 
{
   CurlHttp http;
   http.initialize();
   auto response = http.get("http://langrsoft.com");
   ASSERT_THAT(response, HasSubstr("Jeff Langr"));
}

