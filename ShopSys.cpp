#include "ShopSys.h"

/* Constructors and Destructors */

ShopSys::ShopSys()
{

}

ShopSys::~ShopSys()
{

}

/* Common Functions */

string ShopSys::input_command()
{
	string str_command;
	getline(cin,str_command);
	return str_command;
}

int ShopSys::cmd_productlist(vector<string> cmd_analysis)
{
	if (cmd_analysis.size() == 1)
	{
		cout << "ID\t\tProduct Name\t\tOrigin\t\tPrice" << endl;
		for (map<string, Goods>::iterator it = id_goods_map.begin(); it != id_goods_map.end(); ++it)
		{
			cout << it->first << "\t" 
					<< it->second.get_name() << "\t\t" 
					<< it->second.get_origin() << "\t\t" 
					<< it->second.get_price() << endl;
		}
		return 0;
	}
	else if (cmd_analysis.size() == 2)
	{
		if (regex_match(cmd_analysis[1], Is_Unsigned_Int_Pattern))
		{
			stringstream ss;
			u_int display_per_time;
			ss << cmd_analysis[1];
			ss >> display_per_time;

			u_int counter = 0;
			for (map<string, Goods>::iterator it = id_goods_map.begin(); it != id_goods_map.end(); ++it)
			{
				cout << it->first << "\t"
					<< it->second.get_name() << "\t"
					<< it->second.get_origin() << "\t"
					<< it->second.get_price() << endl;
				counter++;
				if (counter == display_per_time)
				{
					counter = 0;
					system("pause");
					cout << endl;
				}
			}
			return 0;
		}
		else
		{
			cout << "Please make sure you are entering an unsigned integer after \"ls\"." << endl;
			return 0;
		}
	}
	else
	{
		return 1;
	}
}

