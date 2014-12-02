#pragma once
#include <exception>
using namespace std;

class InvalidPurchaseException: public exception 
{
};

class InvalidSellException: public exception 
{
};