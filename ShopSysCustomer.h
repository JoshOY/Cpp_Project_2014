#pragma once
#include "ShopSys.h"

class ShopSysCostomer : public ShopSys
{
public:
	/* Constructors and Destructor */
	
	ShopSysCostomer();
	~ShopSysCostomer();

	/* User Interface */

	int receive_command(string);
	int cmd_add(vector<string>);
	int cmd_rmv(vector<string>);
	int cmd_chk(vector<string>);
	int cmd_login(vector<string>);
	int cmd_settle_account();

	/* Purchase Functions */

	void add_into_list(string, u_int);
	void remove_from_list(string, u_int);
	

	/* Login/Logout Functions */

	int login_action(string, string);
	int logout_action();

	string password_mem;
private:
	base_member *p_identity;
	map<Goods, u_int> shoppinglist;
	bool is_member;
	
};