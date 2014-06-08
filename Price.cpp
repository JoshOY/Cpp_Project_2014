#include "Price.h"

/* A Split fucniton for spliting strings, split chars are recorded in a const string SPLCHARS in StdLibs.h*/
vector<string> str_Split(string _buffer)
{
	vector<string> strvec;
	string strbuf;

	u_int index_rec = 0;
	for (u_int index = 0; index < _buffer.length() - 1; index++)
	{
		if (SPLCHARS.find(_buffer[index]) != string::npos)
		{
			strvec.push_back(_buffer.substr(index_rec, index - index_rec));
			index_rec = index + 1;
		}
	}
	strvec.push_back(_buffer.substr(index_rec, _buffer.length() - index_rec));
	if (strvec.size() == 1)
		strvec.push_back("0");
	return strvec;
}


/* Constructors & Destructors */

Price::Price()
{
	int_part = 0;
	dec_part = 0;
}

Price::Price(string _init)
{
	stringstream ss;
	ss << _init;
	ss >> (*this);
}

Price::Price(double _init)
{
	int_part = 0;
	set_dec_part(_init);
}

/* Set Functions */

void Price::set_int_part(int _intpart)
{
	int_part = _intpart;
}

void Price::set_dec_part(double _decpart)
{
	int floor_part = floor(_decpart);
	/* I can't make sure that you are inputing a number larger than 1 */
	if (floor_part != 0)
	{
		int_part += floor_part;
	}
	dec_part = (_decpart - floor_part);
}

/* Get Functions */

int Price::get_int_part() const
{
	return int_part;
}

double Price::get_dec_part() const
{
	return dec_part;
}

/* Overload Operators */

Price Price::operator+(Price _add)
{
	Price tmp;
	tmp.set_int_part((this)->get_int_part() + _add.get_int_part());
	tmp.set_dec_part((this)->get_dec_part() + _add.get_dec_part());

	return tmp;
}

Price Price::operator+(double _add)
{
	Price tmp = (*this);
	tmp.int_part += (int)_add;
	if (_add >= 0)
	{
		_add -= floor(_add);
		tmp.set_dec_part(tmp.dec_part + _add);
	}
	else
	{
		_add -= floor(_add);
		_add *= (-1);
		if ((tmp.get_dec_part() + _add) >= 0)
			tmp.set_dec_part(tmp.dec_part + _add); 
		else
		{
			tmp.int_part--;
			tmp.dec_part = tmp.dec_part + 1 + _add;
		}
	}
	
	return tmp;
}

Price Price::operator-(Price _minus)
{
	Price tmp = (*this);
	tmp.set_int_part( tmp.get_int_part() - _minus.get_int_part() );
	tmp.set_dec_part( tmp.get_dec_part() - _minus.get_dec_part() );

	return tmp;
}

Price Price::operator-(double _minus)
{
	return (this->operator+(-_minus));
}

Price Price::operator*(double _multi)
{

	Price tmp;
	tmp.set_int_part((this)->get_int_part());
	tmp.set_dec_part((this)->get_dec_part());

	/* 大概方法是这样滴：例如_multi = 0.123，乘以4次10之后才能被10整除且大于1，也就是说：
	将Price类中的整数部分整体位移3位到小数部分后，乘以某个“整型”数即可。 */

	double mult = _multi;
	int displacement_num = 0;
	while ((mult <= 1) || ((int)mult % 10 != 0))
	{
		mult *= 10;
		displacement_num++;
	}
	displacement_num--;

	if (displacement_num < 0)		//考虑到有10的倍数之类的bug
	{
		tmp.set_int_part(tmp.get_int_part() * (int)_multi);
		tmp.set_dec_part(tmp.get_dec_part() * _multi);
		return tmp;
	}
	else
	{
		mult /= 10;
		/* 将Price类中的整数部分整体位移displacement_num位到小数部分 */
		for (int i = 0; i < displacement_num; ++i)
		{
			int c = (tmp.int_part % 10);
			tmp.int_part = (tmp.int_part - c) / 10;
			tmp.dec_part = (tmp.dec_part / 10) + (((double)c) * 0.1);
		}
	}
	/* 然后乘以mult */
	tmp.int_part *= (int)mult;
	tmp.set_dec_part((tmp.get_dec_part()) * mult);
	return tmp;
}

bool Price::operator>(double _rhs)
{
	if (this->get_int_part() > (int)_rhs){ return true; }
	else if (this->get_int_part() < (int)_rhs){ return false; }
	else 
	{
		if (this->get_dec_part() > (_rhs - (int)_rhs)){ return true; }
		else { return false; }
	}
}

bool Price::operator<(double _rhs)
{
	return !(this->operator>(_rhs));
}

bool Price::operator==(Price _rhs)
{
	if ((this->int_part == _rhs.get_int_part()) && (this->dec_part == _rhs.get_dec_part()))
		return true;
	else
		return false;
}

istream& operator >> (istream& is, Price& price)
{
	string price_str;
	is >> price_str;
	vector<string> price_vec(str_Split(price_str));
	/* price_vec[0] is int part, price_vec[1] is decimal part */
	stringstream ss;
	ss << price_vec[0];
	ss >> price.int_part;
	ss.clear();
	ss << ("0." + price_vec[1]);
	ss >> price.dec_part;

	return is;
}

ostream& operator << (ostream& os, const Price& price)
{
	stringstream ss;
	string dec_str;

	os << price.int_part;
	ss << price.dec_part;
	ss >> dec_str;
	if (dec_str.length() == 1)
	{
		dec_str += ".00";
	}
	else if (dec_str.length() == 3)
	{
		dec_str += "0";
	}

	os << dec_str.substr(1, dec_str.length() - 1);

	return os;
}