#pragma once
#include "ShopSys.h"

class ShopSysAdmin : public ShopSys
{
public:
	ShopSysAdmin();
	~ShopSysAdmin();
	
private:
	/* id - member map, use member id to get member info */
	map<string, base_member*> id_member_map;
	/* id - member map, use member id to get shopping card info */
	map<string, vector<ShoppingCard> > id_card_map;
	/* id - member map, use good id to get goods info */
	map<string, vector<Goods> > id_good_map;
};