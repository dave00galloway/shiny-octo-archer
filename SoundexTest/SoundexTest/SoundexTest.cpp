// SoundexTest.cpp : Defines the entry point for the console application.
// http://stackoverflow.com/questions/14714877/crypto-mismatch-detected-for-runtimelibrary
// explanation of how to set the runtime settings

#include "gmock/gmock.h"
#include "Soundex.h"
using namespace std;
using namespace testing;

class SoundexEncoding :public Test
{
public:
	Soundex soundex;
};

TEST_F(SoundexEncoding,RetainsSoleLetterOfOneLetterWord)
{
	ASSERT_THAT(soundex.encode("A"),Eq("A000"));
}

TEST_F(SoundexEncoding,PadsWithZerosToEnsureThreeDigits)
{
	ASSERT_THAT(soundex.encode("I"),Eq("I000"));
}

TEST_F(SoundexEncoding,ReplacesConsonantsWithAppropriateDigits)
{
	// ASSERT_THAT(soundex.encode("Ab"),Eq("A100")); 
	/* rather than have multiple yests for differnt letter encodings
	will test multiple assertions here tht will all be run even if one of them fails, 
	using the EXPECT_THAT macro
	disagree with auhtor about elimnating the cases, instead pick one for each output partition
	*/
	EXPECT_THAT(soundex.encode("Ab"),Eq("A100")); 
	EXPECT_THAT(soundex.encode("Ac"),Eq("A200")); 
	EXPECT_THAT(soundex.encode("Ad"),Eq("A300"));
	EXPECT_THAT(soundex.encode("Al"),Eq("A400"));
	EXPECT_THAT(soundex.encode("Am"),Eq("A500"));
	EXPECT_THAT(soundex.encode("Ar"),Eq("A600"));
}

TEST_F(SoundexEncoding,IgnoresNonAlphabetics)
{
	ASSERT_THAT(soundex.encode("A#"),Eq("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
	ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) 
{
	ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) 
{
	ASSERT_THAT(soundex.encode("Baeiouhycdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLettersInUpperAndLowerCase)
{
	ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
	//precondition assertions
	ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
	ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
	ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));
	//assertion we are interested in
	ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter) 
{
	ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants)
{
	ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
	ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) 
{
	ASSERT_THAT(soundex.encode("Jbob"), Eq("J110"));
}

/*
Test list
what about upper case consonants?
*/