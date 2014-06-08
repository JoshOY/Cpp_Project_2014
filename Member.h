#pragma once
#include "Price.h"

enum Gender
{
	male, 
	female 
};

class base_member
{
public:
	/* Constructor & Destructor */
	base_member();
	base_member(string, string, string, string, string);
	virtual ~base_member();

	/* Set Functions */

	void set_id(string);
	void set_id(long);
	void set_name(string);
	void set_gender(Gender);
	void set_gender(string);
	void set_points(string);
	void set_points(double);
	void set_points(Price);

	/* Get Functions */

	string get_name() const;
	string get_id() const;
	string get_gender() const;
	string get_phone() const;
	Price get_points() const;
	virtual string get_member_type();

	/* Other Functions */

	virtual Price settle_accounts(vector<Price>);
	virtual Price add_point(Price);

protected:
	string id;
	string name;
	Gender gender;
	string phone;
	Price points;
};

class normal_member : public base_member
{
public:
	normal_member();
	normal_member(string, string, string, string, string);

	string get_member_type();
	Price settle_accounts(vector<Price>);
	Price add_point(Price);
};

class silver_member : public base_member
{
public:
	silver_member();
	silver_member(string, string, string, string, string);

	string get_member_type();
	Price settle_accounts(vector<Price>);
	Price add_point(Price);
};

class gold_member : public base_member
{
public:
	gold_member();
	gold_member(string, string, string, string, string);

	string get_member_type();
	Price settle_accounts(vector<Price>);
	Price add_point(Price);
};

/* Return 0: no upgrade; return 1: uprade to silver; return 2: upgrade to gold */
int check_upgrade(base_member* &);