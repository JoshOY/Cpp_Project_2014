#include "Goods.h"

/* Constructors & Destructors */

Goods::Goods() : name("N/A"), origin("N/A"), id("N/A")
{
	price = Price("0");
}

Goods::Goods(string _name = "N/A",
										string _origin = "N/A",
										string _id = "N/A",
										string _price = "0")
{
	name = _name;
	origin = _origin;
	id = _id;
	Price tmp_price(_price);
	price = tmp_price;
}

Goods::~Goods()
{
	
}

/* Set Functions */

void Goods::set_name(string _name)
{
	name = _name;
}

void Goods::set_origin(string _origin)
{
	origin = _origin;
}

void Goods::set_id(string _id)
{
	id = _id;
}

void Goods::set_id(long _id)
{
	stringstream ss;
	ss << _id;
	ss >> id;
}

/* Get Functions */

string Goods::get_name() const 
{
	return name;
}

string Goods::get_origin() const
{
	return origin;
}

string Goods::get_id() const
{
	return id;
}

Price Goods::get_price() const 
{
	return price;
}

/* Overload Operator */

bool Goods::operator<(const Goods& _rhs) const
{
	return (this->get_id() < _rhs.get_id() );
}