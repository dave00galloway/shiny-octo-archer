#pragma once
#include <string>
#include <unordered_map>
#include "PortfolioExceptions.h"
#include "boost\date_time\gregorian\gregorian_types.hpp"

using namespace std;
using namespace boost::gregorian;

struct PurchaseRecord
{
	unsigned int ShareCount;
	date Date;
};

class Portfolio
{
public:
	static const date FIXED_PURCHASE_DATE;

	bool IsEmpty() const;
	void Purchase(const string& symbol, unsigned int shareCount);
	void Sell(const string& symbol, unsigned int shareCount);
	unsigned int ShareCount(const string& symbol) const;
	vector<PurchaseRecord> Purchases(const string& symbol) const;

	virtual ~Portfolio(void);

private:
	//unsigned int shareCount_;
	unordered_map<string, unsigned int> holdings_;
	vector<PurchaseRecord> purchases_;
};

