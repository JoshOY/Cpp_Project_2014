#pragma once
#include "Goods.h"
#include "Member.h"
#include "ShoppingCard.h"

class ShopSys
{
public:
	/* Constructors and Destructor */

	ShopSys();
	virtual ~ShopSys();
	
	/* Common Functions */
	string input_command();
	virtual int receive_command(string) = 0;

	int cmd_productlist(vector<string>);
	

protected:
	/* id - member map, use member id to get goods info */
	map<string, Goods> id_goods_map;
};

