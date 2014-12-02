#include "gmock/gmock.h"
//#include "RetweetCollection.h"
#include "Tweet.h"
//#include <memory>

using namespace ::testing;

AssertionResult ContainsString(	const string& expected,const string& actual)
{
	size_t found = actual.find(expected,0);
	if (found == string::npos)
	{
		return AssertionFailure() << actual << " did not contain " << expected ;
	}
	return AssertionSuccess();
}

TEST(ATweet, RequiresUserToStartWithAtSign) {
	string invalidUser("notStartingWith@");
	ASSERT_ANY_THROW(Tweet tweet("msg", invalidUser));
}

TEST(ATweet, UserNameExceptionMessageContainsText_is_not_a_valid_user_) {
	string invalidUser("notStartingWith@");
	try {
		Tweet tweet("msg", invalidUser);
		FAIL();
	}
	catch (const InvalidUserException& exception) 
	{
		ASSERT_TRUE(ContainsString("is not a valid user",string(exception.what())));
		//could have used a matcher macro with Contains too apparently
	}
}