#include "ShopSysAdmin.h"

ShopSysAdmin::ShopSysAdmin()
{
	system("dir /a-d /b goods\\*.txt >goods_list.txt");
	system("dir /a-d /b members\\*.txt >members_list.txt");
	system("dir /a-d /b shoppingcards\\*.txt >shoppingcards_list.txt");

	fstream filereader;

	//Read goods_list.txt
	filereader.open("goods_list.txt", ios::in);
	if (!filereader)
	{
		cerr << "Exception : Cannot Find File goods_list.txt. " << endl;
		filereader.close();
		system("pause");
		exit(1);
	}
	
}

ShopSysAdmin::~ShopSysAdmin()
{

}