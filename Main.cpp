#include "ShopSys.h"
#include "ShopSysCustomer.h"
//#include "ShopSysAdmin.h"

const int NORMAL = 0;
const int EXIT = 2;
const int INVALID = 1;


//IF YOU WANT TO COMPILE COSTUMER MODE

int main(int argc, char *argv[])
{
	//test
	system("dir /a-d /b goods\\*.txt >goods_list.txt");
	ShopSys* _sys_ = new ShopSysCostomer;
	cout << "***************************************" << endl;
	cout << "*         Welcome to our Shop!        *" << endl;
	cout << "***************************************" << endl;
	string cmd;
	while (1)
	{
		cout << endl <<">>> ";
		cmd = _sys_->input_command();
		int status =_sys_->receive_command(cmd);
		switch (status)
		{
		case NORMAL:
			break;
		case INVALID:
			cout << "Invalid Command." << endl;
			break;
		case EXIT:
			system("pause >nul");
			return 0;
		}
	}
	//done

	return 0;
}

/*
//ADMIN MODE
int main(int argc, char *argv[])
{
	cout << "Shop system administrator mode Logining... Done.";
	string command;
	while (1)
	{
		cout << endl << "$admin>>> ";
		cin >> command;
	}

	return 0;
}
*/