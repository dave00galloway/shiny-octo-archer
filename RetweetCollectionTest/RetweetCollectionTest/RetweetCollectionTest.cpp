// RetweetCollectionTest.cpp : Defines the entry point for the console application.
// contains 2 test fixtures, 1 of which adds a default valid tweet. The test cases are listed in the order that best makes sense, and are not grouped by the test fixture that they use
#include "gmock/gmock.h"
#include "RetweetCollection.h"
#include "Tweet.h"
#include <memory>

using namespace ::testing;

class ARetweetCollection : public Test
{
public:
	RetweetCollection collection;
};

class ARetweetCollectionWithOneTweet: public Test {
public:
	RetweetCollection collection;
	shared_ptr<Tweet> tweet;
	void SetUp() override 
	{
		tweet = shared_ptr<Tweet> ( new Tweet("msg", "@user"));
		collection.add(*tweet);
	}

	void TearDown() override
	{
		tweet = nullptr;
	}
};

MATCHER_P(HasSize,expected,"")
{
	return
		arg.size() == expected && arg.isEmpty() == ( 0 == expected);
}

TEST_F(ARetweetCollection, IsEmptyWhenCreated) 
{
	ASSERT_TRUE(collection.isEmpty());
}

TEST_F(ARetweetCollection, HasSizeZeroWhenCreated)
{
	ASSERT_THAT(collection.size(), Eq(0u));
}

TEST_F(ARetweetCollectionWithOneTweet, IsNoLongerEmptyAfterTweetAdded) 
{
	ASSERT_FALSE(collection.isEmpty());
}
TEST_F(ARetweetCollectionWithOneTweet, HasSizeOfOneAfterTweetAdded)
{
	ASSERT_THAT(collection.size(), Eq(1u));
}

TEST_F(ARetweetCollectionWithOneTweet, DecreasesSizeAfterRemovingTweet) 
{
	collection.remove(*tweet);
	ASSERT_THAT(collection, HasSize(0u)); // uses matcher
}

TEST_F(ARetweetCollection, IsEmptyWhenItsSizeIsZero) 
{
	ASSERT_THAT(collection.size(), Eq(0u)); //explicit documentation using precondition  assertion
	ASSERT_TRUE(collection.isEmpty());
}

TEST_F(ARetweetCollectionWithOneTweet, IsNotEmptyWhenItsSizeIsNonZero) 
{
	ASSERT_THAT(collection.size(), Gt(0u));
	ASSERT_FALSE(collection.isEmpty());
}

TEST_F(ARetweetCollectionWithOneTweet, IsNoLongerEmpty) {
	ASSERT_FALSE(collection.isEmpty());
}
TEST_F(ARetweetCollectionWithOneTweet, HasSizeOfOne) {
	ASSERT_THAT(collection.size(), Eq(1u));
}

TEST_F(ARetweetCollectionWithOneTweet, IgnoresDuplicateTweetAdded) {
	Tweet duplicate(*tweet);
	collection.add(duplicate);
	ASSERT_THAT(collection.size(), Eq(1u));
}
