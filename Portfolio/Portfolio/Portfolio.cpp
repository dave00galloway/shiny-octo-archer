#include "Portfolio.h"

const date Portfolio::FIXED_PURCHASE_DATE(date(2014, Jan, 1));

bool Portfolio::IsEmpty() const 
{
	return holdings_.size() == 0;
}

void Portfolio::Purchase(const string& symbol, unsigned int shareCount) 
{
	if (0 == shareCount) throw InvalidPurchaseException();
	holdings_[symbol] = shareCount + ShareCount(symbol);
}

void Portfolio::Sell(const string& symbol, unsigned int shareCount) 
{
	if (IsEmpty() || shareCount > ShareCount(symbol)) throw InvalidSellException();
	holdings_[symbol] = ShareCount(symbol) - shareCount;
}

unsigned int Portfolio::ShareCount(const string& symbol) const 
{
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
	
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const 
{
   return purchases_;
}

Portfolio::~Portfolio(void)
{
}
