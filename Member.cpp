#include "Member.h"

/* Constructor & Destructor */

base_member::base_member(){}

base_member::base_member(	string _name, 
													string _id, 
													string _gender,
													string _phone, 
													string _points	)
{
	name = _name;
	id = _id;
	set_gender(_gender);
	phone = _phone;
	Price tmp_points(_points);
	points = _points;
}

base_member::~base_member()
{
	
}

/* Set Functions */

void base_member::set_id(string _id)
{
	id = _id;
}

void base_member::set_id(long _id)
{
	stringstream ss;
	ss << _id;
	ss >> id;
}

void base_member::set_name(string _name)
{
	name = _name;
}

void base_member::set_gender(Gender _gender)
{
	gender = _gender;
}

void base_member::set_gender(string _gender)
{
	if ((_gender == "Female")
		|| (_gender == "female")
		|| (_gender == "f")
		|| (_gender == "F"))
	{
		gender = female;
	}
	else
	{
		gender = male;
	}
}

void base_member::set_points(string _points)
{
	Price tmp_points(_points);
	points = tmp_points;
}

void base_member::set_points(double _points)
{
	Price tmp_points(_points);
	points = tmp_points;
}

void base_member::set_points(Price _points)
{
	points = _points;
}

/* Get Functions */

string base_member::get_name() const
{
	return name;
}

string base_member::get_id() const
{
	return id;
}

string base_member::get_gender() const
{
	if (gender == male)
		return "male";
	else
		return "female";
}

string base_member::get_phone() const
{
	return phone;
}

Price base_member::get_points() const
{
	return points;
}

string base_member::get_member_type()
{
	return "Base Member";
}

/* Other Functions */

Price base_member::settle_accounts(vector<Price> _list)
{
	Price total(0);
	for (vector<Price>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		total = total + (*it);
	}
	return total;
}

Price base_member::add_point(Price _cash)
{
	Price tmp_points("0");
	tmp_points = (_cash * 0.5);
	return tmp_points;
}

//normal

normal_member::normal_member(){}

string normal_member::get_member_type()
{
	return "Normal Member";
}

normal_member::normal_member(	string _name,
															string _id,
															string _gender,
															string _phone,
															string _points)
{
	name = _name;
	id = _id;
	set_gender(_gender);
	phone = _phone;
	Price tmp_points(_points);
	points = _points;
}

Price normal_member::settle_accounts(vector<Price> _list)
{
	Price total(0);
	for (vector<Price>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		total = total + (*it);
	}
	if (total < 2000)
	{
		return total;
	}
	else if (total < 5000)
	{
		total = ((total - 2000) * 0.95)+ 2000;
		return total;
	}
	else
	{
		total = ((total - 5000) * 0.9) + 4850;
	}
}

Price normal_member::add_point(Price _cash)
{
	return (_cash * 0.5);
}

//silver

silver_member::silver_member(){}

silver_member::silver_member(		string _name,
														string _id,
														string _gender,
														string _phone,
														string _points)
{
	name = _name;
	id = _id;
	set_gender(_gender);
	phone = _phone;
	Price tmp_points(_points);
	points = _points;
}

string silver_member::get_member_type()
{
	return "Silver Member";
}

Price silver_member::settle_accounts(vector<Price> _list)
{
	Price total(0);
	for (vector<Price>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		total = total + (*it);
	}
	if (total < 1000)
	{
		return ( total * 0.95);
	}
	else if (total < 2000)
	{
		total = ((total - 1000) * 0.9) + 950;
		return total;
	}
	else
	{
		total = ((total - 2000) * 0.85 ) + 950 + 900;
	}
	return total;
}

Price silver_member::add_point(Price _cash)
{
	if (_cash < 2000)
	{
		return (_cash * 1.2);
	}
	else if (_cash < 5000)
	{
		return ( ((_cash-2000) * 1.5 ) + 2400);
	}
	else
	{
		return (((_cash - 5000) * 1.8 ) + 2400 + 4500 );
	}
}

//Tu Hao Gold

gold_member::gold_member(){}

gold_member::gold_member(	string _name,
													string _id,
													string _gender,
													string _phone,
													string _points)
{
	name = _name;
	id = _id;
	set_gender(_gender);
	phone = _phone;
	Price tmp_points(_points);
	points = _points;
}

string gold_member::get_member_type()
{
	return "Gold Member";
}

Price gold_member::settle_accounts(vector<Price> _list)
{
	Price total(0);
	for (vector<Price>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		if (((*it) < 10) || ((*it) == 10))
		{
			total = total + (*it);
		}
		else if (((*it) < 20) || ((*it) == 20))
		{
			total = total + ((*it) * 0.95 );
		}
		else
		{
			total = total + ((*it) * 0.9);
		}
	}
	return total;
}

Price gold_member::add_point(Price _cash)
{
	if (_cash < 1000)
	{
		return (_cash * 1.5);
	}
	else if (_cash < 5000)
	{
		return (((_cash - 1000) * 1.8) + 1500);
	}
	else
	{
		return (((_cash - 5000) * 2.0) + 1500 + 7200);
	}
}

//Check Upgrade
/* Return 0: no upgrade; return 1: uprade to silver; return 2: upgrade to gold */
int check_upgrade(base_member* & p_member)
{
	string type = typeid(*p_member).name();
	if (type == "class gold_member")
	{
		//Well, Tu Hao don't need any upgrade anymore !
		return 0; 
	}
	else if (type == "class silver_member")
	{
		if ((p_member->get_points() > 50000) || (p_member->get_points() == 50000))
		{
			string tmp_id = p_member->get_id();
			string tmp_name = p_member->get_name();
			string tmp_gender = p_member->get_gender();
			string tmp_phone = p_member->get_phone();
			Price tmp_points = p_member->get_points();

			stringstream ss;
			ss << tmp_points;
			string tmp_points_str;
			ss >> tmp_points_str;

			delete p_member;
			p_member = new gold_member(tmp_name, tmp_id, tmp_gender, tmp_phone, tmp_points_str);
			return 2;
		}
		else
			return 0;
	}
	else if (type == "class normal_member")
	{
		if ((p_member->get_points() > 50000) || (p_member->get_points() == 50000))
		{
			string tmp_id = p_member->get_id();
			string tmp_name = p_member->get_name();
			string tmp_gender = p_member->get_gender();
			string tmp_phone = p_member->get_phone();
			Price tmp_points = p_member->get_points();

			stringstream ss;
			ss << tmp_points;
			string tmp_points_str;
			ss >> tmp_points_str;

			delete p_member;
			p_member = new gold_member(tmp_name, tmp_id, tmp_gender, tmp_phone, tmp_points_str);
			return 2;
			}
		else if ((p_member->get_points() > 10000) || (p_member->get_points() == 10000))
		{
			string tmp_id = p_member->get_id();
			string tmp_name = p_member->get_name();
			string tmp_gender = p_member->get_gender();
			string tmp_phone = p_member->get_phone();
			Price tmp_points = p_member->get_points();

			stringstream ss;
			ss << tmp_points;
			string tmp_points_str;
			ss >> tmp_points_str;

			delete p_member;
			p_member = new silver_member(tmp_name, tmp_id, tmp_gender, tmp_phone, tmp_points_str);
			return 1;
		}
		else
			return 0;
		}
		else
		{
			return -1;
		}
}