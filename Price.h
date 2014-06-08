#pragma once
#include "StdLibs.h"

class Price
{
public:
	/* Constructors & Destructors */
	/* Okay, three ways to init an instance : 
		For example : Price() or Price("1.23") or Price(1.23)*/
	Price();
	Price(string);
	Price(double);

	/* Set Fuctions */
	void set_int_part(int);
	void set_dec_part(double);

	/* Get Functions */
	int get_int_part() const;
	double get_dec_part() const;

	/* Overload Operators */
	friend istream& operator >> (istream& is, Price& price);
	friend ostream& operator << (ostream& os, const Price& price);
	Price operator+(Price);
	Price operator-(Price);
	Price operator+(double);
	Price operator-(double);
	Price operator*(double);
	bool operator>(double);
	bool operator<(double);
	bool operator==(Price);
	

private:
	int int_part;
	double dec_part;
};