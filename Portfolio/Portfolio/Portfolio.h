#pragma once
#include <string>
#include <unordered_map>
#include "PortfolioExceptions.h"

using namespace std;

class Portfolio
{
public:
	//Portfolio(void);

	bool IsEmpty() const;
	void Purchase(const string& symbol, unsigned int shareCount);
	void Sell(const string& symbol, unsigned int shareCount);
	unsigned int ShareCount(const std::string& symbol) const;

	virtual ~Portfolio(void);

private:
	//unsigned int shareCount_;
	unordered_map<string, unsigned int> holdings_;
};

