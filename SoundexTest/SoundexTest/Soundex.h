#pragma once
#include <string>
#include <unordered_map>
using namespace std;
/*Really don't like that this is still in the same project as the test. 
Should be a seperate library really
*/

static const string NotADigit = "*";

class Soundex
{
public:
	Soundex(void)
	{
	}

	string encode(const string& word) const 
	{
		return zeroPad(
			upperFront(head(word)) + 
			tail(encodedDigits(word)));
	}

	string encodedDigit(char letter)const
	{
		//http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2756.htm - not supported
		//const unordered_map<char,string> encodings
		//{
		//	{'b',"1"},
		//	{'c',"2"},
		//	{'d',"3"}
		//};
		//should this be a (lazy)  class field instead?
		unordered_map<char,string> encodings; //can't be const as need to add pairs in seperate steps
		//1
		encodings.insert(make_pair('b',"1"));
		encodings.insert(make_pair('f',"1"));
		encodings.insert(make_pair('p',"1"));
		encodings.insert(make_pair('v',"1"));
		//2
		encodings.insert(make_pair('c',"2"));
		encodings.insert(make_pair('g',"2"));
		encodings.insert(make_pair('j',"2"));
		encodings.insert(make_pair('k',"2"));
		encodings.insert(make_pair('q',"2"));
		encodings.insert(make_pair('s',"2"));
		encodings.insert(make_pair('x',"2"));
		encodings.insert(make_pair('z',"2"));
		//3
		encodings.insert(make_pair('d',"3"));
		encodings.insert(make_pair('t',"3"));
		//4
		encodings.insert(make_pair('l',"4"));
		//5
		encodings.insert(make_pair('m',"5"));
		encodings.insert(make_pair('n',"5"));
		//6
		encodings.insert(make_pair('r',"6"));

		auto it = encodings.find(lower(letter));
		return it == encodings.end() ? NotADigit : it->second;
	}

	static const size_t MaxCodeLength = 4;

	virtual ~Soundex(void)
	{
	}

private:
	string upperFront(const string& word) const
	{
		//(The casting in upperFront() avoids potential problems with handling EOF.)
		return string(1,toupper(static_cast<unsigned char>(word.front())));
	}

	char lower(char c) const
	{
		return tolower(static_cast<unsigned char>(c));
	}

	string head(const string& word) const
	{
		return word.substr(0,1);
	}

	string tail(const string& word) const
	{
		return word.substr(1);
	}

	string encodedDigits(const string& word) const
	{
		string encoding;
		encodeHead(encoding,word);
		encodeTail(encoding,word);
		return encoding;
	}

	void encodeHead(string& encoding, const string& word) const
	{
		encoding += encodedDigit(word.front());
	}

	//void encodeTail(string& encoding, const string& word) const
	//{
	//	for (auto letter:word)
	//	{
	//		if (isComplete(encoding))
	//		{
	//			break; //book suggests inverting this if and not breaking, but that could waste cycles if the string to be encoded is very long
	//		}
	//		encodeLetter(encoding,letter);
	//	}
	//}

	void encodeTail(std::string& encoding, const std::string& word) const {
		for (auto i = 1u; i < word.length(); i++)
			if (!isComplete(encoding))
				encodeLetter(encoding, word[i], word[i - 1]);
	}

	void encodeLetter(string& encoding, char letter, char lastLetter) const
	{
		auto digit = encodedDigit(letter);
		if (digit != NotADigit && (digit != lastDigit(encoding)||isVowel(lastLetter)))
		{
			encoding+=digit;
		}	
	}

	bool isVowel(char letter) const
	{
		return string("aeiouy").find(lower(letter))  != string::npos;
	}

	string lastDigit(const string& encoding)const
	{
		//return string(1,encoding.back()); //not sure how the author got away with this! doesn't work if encoding is zero length!
		string digit = NotADigit;
		if (!encoding.empty())
		{
			digit = string(1,encoding.back());
		}
		return digit;
	}

	bool isComplete(const string& encoding) const
	{
		return encoding.length() == MaxCodeLength;
	}

	string zeroPad(const string& word) const 
	{
		auto zerosNeeded = MaxCodeLength -word.length();
		return word + string(zerosNeeded,'0');
	}

};
