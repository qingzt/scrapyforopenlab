// currency class using three data members
// (sign, dollars, and cents) to
// represent an instance/object

#ifndef currency_
#define currency_

#include <iostream>
#include "myExceptions.h"

using namespace std;

enum signType {plus_, minus_};

class currency 
{
   public:
      // constructor
      currency(signType theSign = plus_,
               unsigned long theDollars = 0,
               unsigned int theCents = 0);
      // destructor
      ~currency() {}
      void setValue(signType, unsigned long, unsigned int);
      void setValue(double);
      signType getSign() const {return sign;}
      unsigned long getDollars() const {return dollars;}
      unsigned int getCents() const {return cents;}
      currency add(const currency&) const;
      currency& increment(const currency&);
      void output() const;
      void input();
      currency subtract(const currency& x) const;
      currency percent(double x);
      currency multiply(double x);
      currency devide(double x);
   private:
      signType sign;           // sign of object
      unsigned long dollars;   // number of dollars
      unsigned int cents;      // number of cents
};

currency::currency(signType theSign, unsigned long theDollars,
                                     unsigned int theCents)
{// Create a currency object.
   setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars,
                                          unsigned int theCents)
{// Set currency value.
   if (theCents > 99)
       // too many cents
       throw illegalParameterValue("Cents should be < 100");

   sign = theSign;
   dollars = theDollars;
   cents = theCents;
}
   
void currency::setValue(double theAmount)
{// Set currency value.
   if (theAmount < 0) {sign = minus_;
                       theAmount = -theAmount;}
   else sign = plus_;

   dollars = (unsigned long) theAmount;
             // extract integer part
   cents = (unsigned int) ((theAmount + 0.001 - dollars) * 100);
             // get two decimal digits
}

currency currency::add(const currency& x) const
{// Add x and *this.
   long a1, a2, a3;
   currency result;
   // convert invoking object to signed integers
   a1 = dollars * 100 + cents;
   if (sign == minus_) a1 = -a1;
   
   // convert x to signed integer
   a2 = x.dollars * 100 + x.cents;
   if (x.sign == minus_) a2 = -a2;
   
   a3 = a1 + a2;
    
   // convert to currency representation
   if (a3 < 0) {result.sign = minus_; a3 = -a3;}
   else result.sign = plus_;
   result.dollars = a3 / 100;
   result.cents = a3 - result.dollars * 100;
   
   return result;
}

currency& currency::increment(const currency& x)
{// Increment by x.
   *this = add(x);
   return *this;
}

void currency::output() const
{// Output currency value.
   if (sign == minus_) cout << '-';
   cout << '$' << dollars << '.';
   if (cents < 10) cout << '0';
   cout << cents;
}

void currency::input()
{
	int a;
	cin>>a;
	if(a==0)
		sign=minus_;
	else
		sign=plus_;
	cin>>dollars;
	cin>>cents;
}

currency currency::subtract(const currency &x) const
{
	long a1, a2, a3;
   currency result;
   a1 = dollars * 100 + cents;
   if (sign == minus_) a1 = -a1;
   a2 = x.dollars * 100 + x.cents;
   if (x.sign == minus_) a2 = -a2;
   a3 = a1 - a2;
   if (a3 < 0) {result.sign = minus_; a3 = -a3;}
   else result.sign = plus_;
   result.dollars = a3 / 100;
   result.cents = a3 - result.dollars * 100;
   return result;
}

currency currency::percent(double x)
{
	currency result;
	double value=x/100.0;
	double money=dollars+cents/100.0;
	if(sign==minus_)
		money=-money;
	money=money*value;
	if(money<0)
		result.sign=minus_;
	else
		result.sign=plus_;
	result.dollars=money;
	result.cents=(money-result.dollars)*100;
	return result;
}

currency currency::multiply(double x)
{
	currency result;
	double value=x;
	double money=dollars+cents/100.0;
	if(sign==minus_)
		money=-money;
	money=money*value;
	if(money<0)
		result.sign=minus_;
	else
		result.sign=plus_;
	result.dollars=money;
	result.cents=(money-result.dollars)*100;
	return result;
}

currency currency::devide(double x)
{
	currency result;
	double value=x;
	double money=dollars+cents/100.0;
	if(sign==minus_)
		money=-money;
	money=money/value;
	if (money<0)
		result.sign=minus_;
	else
		result.sign=plus_;
	result.dollars=money;
	result.cents=(money-result.dollars)*100;
	return result;
}

#endif

int main()
{
   currency a(plus_,8,8);
   a.output();
   currency b;
   b.input();
   b.output();
   currency c;
   c=a.subtract(b);
   c.output();
   currency d;
   d=a.percent(90);
   d.output();
   currency e;
   e=d.multiply(2);
   e.output();
   currency f;
   f=a.devide(2);
   f.output();
}

