#pragma once
#include "StdLibs.h"
#include "Price.h"

class Goods
{
public:
	/* Constructors & Destructors */
	Goods();
	Goods(string,string,string,string);
	~Goods();

	/* Set Functions */

	void set_name(string);
	void set_origin(string);
	void set_id(long);
	void set_id(string);

	/* Get Functions */

	string get_name() const;
	string get_origin() const;
	string get_id() const;
	Price get_price() const;

	/* Overload Operator */
	/* In order to enable class Goods be used as key of std::map */
	bool operator<(const Goods&) const;

private:
	string name;
	string origin;
	string id;
	Price price;
};