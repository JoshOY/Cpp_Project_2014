#include "ShopSysCustomer.h"
extern int check_upgrade(base_member* & p_member);

vector<string> str_Split_not_add_zero(string _buffer)
{
	vector<string> strvec;
	string strbuf;

	if (_buffer == "")
	{
		strvec.push_back("");
		return strvec;
	}

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

	return strvec;
}

vector<string> str_Split_file(string _buffer)
{
	vector<string> strvec;
	string strbuf;

	u_int index_rec = 0;
	for (u_int index = 0; index < _buffer.length() - 1; index++)
	{
		if (SPLCHARS_FILE.find(_buffer[index]) != string::npos)
		{
			strvec.push_back(_buffer.substr(index_rec, index - index_rec));
			index_rec = index + 1;
		}
	}
	strvec.push_back(_buffer.substr(index_rec, _buffer.length() - index_rec));
	return strvec;
}

/* Constructors and Destructor */

ShopSysCostomer::ShopSysCostomer() :is_member(false), p_identity(NULL)
{
	/* Firstly the system should import goods info */
	fstream fgoods_list, fgoods;
	u_int read_line_num = 0;
	string goods_file_name, goods_info;
	
	fgoods_list.open("goods_list.txt",ios::in);
	if (!fgoods_list)
	{
		cerr << "Exception : Cannot Find File goods_list.txt. " << endl;
		fgoods_list.close();
		system("pause");
		exit(1);
	}
	while (!fgoods_list.eof())
	{
		read_line_num++;
		getline(fgoods_list, goods_file_name);

		/* Read Each Goods File */
		if (goods_file_name == "")
			break;
		fgoods.open((".\\goods\\"+goods_file_name),ios::in);

		if (!fgoods_list)
		{
			cerr << "Exception : Cannot Find File \"" << goods_file_name << "\" in folder goods\\. " << endl;
			fgoods.close();
			system("pause");
			exit(1);
		}

		getline(fgoods, goods_info);
		if ( regex_match(goods_info, Id_Goods_File_Pattern) )
		{
			vector<string> info = str_Split_file(goods_info);
			id_goods_map[(info[0])] = Goods(info[1],info[2],info[0],info[3]);
		}
		else
		{
			cerr << "Exception : Product information file format does not conform regex. " << endl;
			fgoods.close();
			system("pause");
			exit(1);
		}

		fgoods.close();
	}
	fgoods_list.close();
}

ShopSysCostomer::~ShopSysCostomer()
{
	if (p_identity != NULL)
	{
		delete p_identity;
	}
}

/* User Interface */

int ShopSysCostomer::receive_command(string _cmd)
{
	vector<string> cmd_analysis = str_Split_not_add_zero(_cmd);

	/* add command */
	if (cmd_analysis[0] == "add")
	{
		return cmd_add(cmd_analysis);
	}
	else if (cmd_analysis[0] == "rmv")
	{
		return cmd_rmv(cmd_analysis);
	}
	else if (cmd_analysis[0] == "chk")
	{
		return cmd_chk(cmd_analysis);
	}
	else if (cmd_analysis[0] == "ls")
	{
		return cmd_productlist(cmd_analysis);
	}
	else if (cmd_analysis[0] == "login")
	{
		return cmd_login(cmd_analysis);
	}
	else if ((cmd_analysis[0] == "logout") && (cmd_analysis.size() == 1))
	{
		return logout_action();
	}
	else if ((cmd_analysis[0] == "pay") && (cmd_analysis.size() == 1))
	{
		return cmd_settle_account();
	}
	else if (cmd_analysis[0] == "")
	{
		return 0;
	}
	else if ((cmd_analysis[0] == "exit") && (cmd_analysis.size() == 1))
	{
		if (is_member)
		{
			fstream fmember;
			fmember.open(".\\members\\" + p_identity->get_id() + ".txt", ios::trunc | ios::out);
			fmember << p_identity->get_id() << ','
				<< p_identity->get_name() << ','
				<< p_identity->get_gender() << ','
				<< p_identity->get_phone() << ','
				<< p_identity->get_points() << ','
				<< password_mem;
			fmember.close();
			//Refresh file done
			delete p_identity;
			p_identity = NULL;
			is_member = false;
		}
		cout << endl << "Bye!";
		return 2;
	}
	else if ((cmd_analysis[0] == "help") && (cmd_analysis.size() == 1))
	{
		cout << "Command mannual : " << endl;
		cout << "ls [number each page] : List all the goods." << endl;
		cout << "add <Goods ID> [number] : add [number(default 1)] goods into your cart." << endl;
		cout << "rmv <Goods ID> [number] : remove [number(default all of this ID)] goods from your cart." << endl;
		cout << "login : Log in command." << endl;
		cout << "logout : Log out command." << endl;
		cout << "chk : Check your carts of goods." << endl;
		cout << "pay : Settle account." << endl;
		cout << "info : (Only used when logged in)Check member info." << endl;
		return 0;
	}
	else if ((cmd_analysis[0] == "info") && (cmd_analysis.size() == 1))
	{
		if (!is_member)
		{
			cout << "You have to login first." << endl;
			return 0;
		}

		cout << "Your info : " << endl;
		cout << "Member ID : " << p_identity->get_id() << endl;
		cout << "Name : " << p_identity->get_name() << endl;
		cout << "Gender : " << p_identity->get_gender() << endl;
		cout << "Phone : " << p_identity->get_phone() << endl;
		cout << "Member type : " << p_identity->get_member_type() << endl;
		cout << "Points : " << p_identity->get_points() << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

int ShopSysCostomer::cmd_add(vector<string> cmd_analysis)
{
	if (cmd_analysis.size() == 2)
	{
		add_into_list(cmd_analysis[1], 1);
		return 0;
	}
	else if (cmd_analysis.size() == 3)
	{
		if (regex_match(cmd_analysis[2], Is_Unsigned_Int_Pattern))
		{
			stringstream ss;
			u_int num;
			ss << cmd_analysis[2];
			ss >> num;
			add_into_list(cmd_analysis[1], num);
			return 0;
		}
		else
		{
			cout << "Please make sure you are entering an unsigned integer larger than 0 after ID." << endl;
			return 0;
		}
	}
	else if (cmd_analysis.size() == 1)
	{
		cout << "\"add\" Expression:" << endl;
		cout << "add <Product ID> [Number of items]\tAdd Product to shoppinglist. (Default number of items is 1)." << endl;
		return 0;
	}
	else
		return 1;
}

int ShopSysCostomer::cmd_rmv(vector<string>cmd_analysis)
{
	if (cmd_analysis.size() == 2)
	{
		remove_from_list(cmd_analysis[1], 0);
		return 0;
	}
	else if (cmd_analysis.size() == 3)
	{
		if (regex_match(cmd_analysis[2], Is_Unsigned_Int_Pattern))
		{
			stringstream ss;
			u_int num;
			ss << cmd_analysis[2];
			ss >> num;
			remove_from_list(cmd_analysis[1], num);
			return 0;
		}
		else
		{
			cout << "Please make sure you are entering an unsigned integer larger than 0 after ID." << endl;
			return 0;
		}
	}
	else if (cmd_analysis.size() == 1)
	{
		cout << "\"rmv\" Expression:" << endl;
		cout << "rmv <Product ID> [Number of items]\tRemove Product in shoppinglist. (Default number of items is total)." << endl;
		return 0;
	}
	else
		return 1;
}

int ShopSysCostomer::cmd_chk(vector<string>cmd_analysis)
{
	if (cmd_analysis.size() == 1)
	{
		cout << "ID\t\tProduct Name\tOrigin\t\tPrice\tNum\tTotal" << endl;
		Price sum(0);
		cout << "==============================================================================" << endl;
		for (map<Goods, u_int>::iterator it = shoppinglist.begin(); it != shoppinglist.end(); ++it)
		{
			cout << (it->first.get_id()) << "\t"
				<< (it->first.get_name()) << "\t"
				<< (it->first.get_origin()) << "\t\t"
				<< (it->first.get_price()) << "\t"
				<< (it->second) << "\t"
				<< (it->first.get_price() * (it->second))<< endl;
			sum = sum + ((it->first.get_price()) * (it->second));
		}
		cout << "==============================================================================" << endl;
		cout << "TOTAL : " << sum << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

int ShopSysCostomer::cmd_login(vector<string> cmd_analysis)
{
	if (cmd_analysis.size() == 1)
	{
		if (is_member)
		{
			cout << "You've already login. Type \"logout\" to logout and retry. " << endl;
			return 0;
		}
		string input_id, input_pw;
		cout << "Enter your ID : "; cin >> input_id;
		cout << "Enter your Password : "; cin >> input_pw;
		if (!regex_match(input_pw, Password_Pattern))
		{
			cout << "Invalid Password. (0-9 or a-z or A-Z, 8-16 digits)" << endl;
			return 0;
		}
		if (login_action(input_id, input_pw))
		{
			cout << "Login Failed.";
			return 0;
		}
		password_mem = input_pw;
		return 0;
	}
	else
		return 1;
}

int ShopSysCostomer::cmd_settle_account()
{
	Price sum(0);
	cout << "==============================================================================" << endl;
	for (map<Goods, u_int>::iterator it = shoppinglist.begin(); it != shoppinglist.end(); ++it)
	{
		cout << (it->first.get_id()) << "\t"
			<< (it->first.get_name()) << "\t"
			<< (it->first.get_origin()) << "\t\t"
			<< (it->first.get_price()) << "\t"
			<< (it->second) << "\t"
			<< (it->first.get_price() * (it->second)) << endl;
		sum = sum + ((it->first.get_price()) * (it->second));
	}
	cout << "==============================================================================" << endl;
	cout << "TOTAL : " << sum << endl;
	/* Case : member of shop */

	if (is_member)
	{
		cout << "You are a member of our shop. Your adjusted payment: $";
		vector<Price> vecshoppingls;
		for (map<Goods, u_int>::iterator it = shoppinglist.begin(); it != shoppinglist.end(); ++it)
		{
			for (int i = 0; i < (it->second); i++)
				vecshoppingls.push_back((it->first).get_price());
		}
		sum = p_identity->settle_accounts(vecshoppingls);
		cout << sum << endl << endl;
	}

	/* Case : member of shop END */

	// This boolean var is used as a flag of end
	bool still_need_to_pay_flag = true;
	//This boolean var is used as a flag of payment done
	bool payment_complete = false;
	//This boolean var is used as a flag of payment cannot cancel.
	bool cancelable = true;

	ShoppingCard *card = NULL;
	// Start to settle account
	while (still_need_to_pay_flag) // loop 1
	{
		cout << "Please select your payment method:" << endl
			<< "1. Cash" << endl
			<< "2. Member Card" << endl
			<< "3. Credit Card" << endl
			<< "0. Cancel" << endl;
		char selection;
		string payment;
		// This boolean var is used as a flag of end
		bool still_using_this_method = true;
		selection = getch();

		while (1)	//loop 2
		{
			if (still_using_this_method)
			{
				switch (selection)	//loop 3
				{
				//
				//Pay by cash
				//
				PLACE_SELECTION:
				case '1':
					cout << "Enter cash (enter 0 to try other payment method) : $"; cin >> payment;
					if (!regex_match(payment, Is_Number_Pattern))
					{
						cout << "Input is not available. Please retry." << endl;
						still_using_this_method = true;
						goto PLACE_SELECTION; // to loop 3
					}
					if ((Price(payment) - sum) > 0)
					{
						cout << "You don't need to pay that so much. Please retry." << endl;
						still_using_this_method = true;
						goto PLACE_SELECTION;; // to loop 3
					}
					else if ((sum - Price(payment)) == 0)
					{
						shoppinglist.clear();	//Clear everything in your list after account settled.
						cout << "Payment Complete. Thank you and have a nice day!" << endl;
						still_need_to_pay_flag = false;
						still_using_this_method = false;
						payment_complete = true;
						cancelable = false;
						break; //to loop 2
					}
					else
					{
						sum = sum - Price(payment);
						cout << "Payment Complete. But you still need to pay : $" << sum << endl;
						cout << "You can try to pay by other methods." << endl;
						still_need_to_pay_flag = true;
						still_using_this_method = false;
						cancelable = false;
						break; //to loop 2
					}
					break; // to loop 1

				//Pay by shoppingcard
				case '2':
					if (is_member == false)
					{
						cout << "Only members can pay by member card. Please login and retry." << endl;
						still_using_this_method = false;
						break;
					}
					else
					{
						cout << "Enter cash (enter 0 to try other payment method) : $";
						cin >> payment;
						if (!regex_match(payment, Is_Number_Pattern))
						{
							cout << "Input is not available. Please retry." << endl;
							still_using_this_method = true;
							goto PLACE_SELECTION; // to loop 3
						}
						if ((Price(payment) - sum) > 0)
						{
							cout << "You don't need to pay that so much. Please retry." << endl;
							still_using_this_method = true;
							goto PLACE_SELECTION;; // to loop 3
						}
						else
						{
							string shopping_card_id_input;
							cout << "Input your shopping card ID:"; cin >> shopping_card_id_input;
							fstream cardfile;
							cardfile.open(".\\shoppingcards\\" + shopping_card_id_input + ".txt", ios::in);
							if (!cardfile)
							{
								cout << "Cannot find this ID. Make sure your input is correct." << endl;
								still_using_this_method = true;
								cardfile.close();
								goto PLACE_SELECTION;; // to loop 3
							}
							//If File found
							string cardid, cardbalance;
							cardfile >> cardid;
							cardfile >> cardbalance;
							card = new ShoppingCard(cardid, Price(cardbalance));
							if (Price(payment) - (card->balance) > 0)
							{
								cout << "Insufficient balance. You only have $" << (card->balance) << " remain." << endl;
								cardfile.close();
								still_using_this_method = false;
								delete card;
								break;
							}
							else
							{
								cardfile.close();
								cardfile.open(".\\shoppingcards\\" + shopping_card_id_input + ".txt", ios::trunc | ios::out);
								(card->balance) = (card->balance) - payment;
								cardfile << (card->card_number) << endl << (card->balance);
								if ((sum - Price(payment)) == 0)
								{
									shoppinglist.clear();	//Clear everything in your list after account settled.
									cout << "Payment Complete. Thank you and have a nice day!" << endl;
									cardfile.close();
									delete card;
									still_need_to_pay_flag = false;
									still_using_this_method = false;
									payment_complete = true;
									cancelable = false;
									break; //to loop 2
								}
								else
								{
									sum = sum - Price(payment);
									cout << "Payment Complete. But you still need to pay : $" << sum << endl;
									cout << "You can try to pay by other methods." << endl;
									cardfile.close();
									delete card;
									still_need_to_pay_flag = true;
									still_using_this_method = false;
									cancelable = false;
									break; //to loop 2
								}

							}
							
						}
						break; // to loop 1
					}

				//Pay by creditcard
				case '3':
					cout << "Enter your bank card ID: "; cin >> payment;
					if (!regex_match(payment, Bank_Card_Pattern))
					{
						cout << "Invalid bank account. Should be a 19 digit number." << endl;
						still_using_this_method = false;
						break;
					}

					cout << "Enter cash (enter 0 to try other payment method) : $"; cin >> payment;
					
					if (!regex_match(payment, Is_Number_Pattern))
					{
						cout << "Input is not available. Please retry." << endl;
						still_using_this_method = true;
						goto PLACE_SELECTION; // to loop 3
					}
					if ((Price(payment) - sum) > 0)
					{
						cout << "You don't need to pay that so much. Please retry." << endl;
						still_using_this_method = true;
						goto PLACE_SELECTION;; // to loop 3
					}
					else if ((sum - Price(payment)) == 0)
					{
						shoppinglist.clear();	//Clear everything in your list after account settled.
						cout << "Payment Complete. Thank you and have a nice day!" << endl;
						still_need_to_pay_flag = false;
						still_using_this_method = false;
						payment_complete = true;
						cancelable = false;
						break; //to loop 2
					}
					else
					{
						sum = sum - Price(payment);
						cout << "Payment Complete. But you still need to pay : $" << sum << endl;
						cout << "You can try to pay by other methods." << endl;
						still_need_to_pay_flag = true;
						still_using_this_method = false;
						cancelable = false;
						break; //to loop 2
					}
					break; // to loop 1

				//Cancel
				case '0':
					if (!cancelable)
					{
						cout << "Sorry, you can't cancel this transaction after paid a part of the list." << endl
								<<"Contact us to get other methods." << endl;
						still_using_this_method = false;
						payment_complete = false;
						still_need_to_pay_flag = true;
						break; // to loop 3
					}
					still_need_to_pay_flag = false;
					still_using_this_method = false;
					payment_complete = false;
					cout << "Payment operation cancelled." <<endl;
					break;

				default:
					break;
				}
			}
			else
				break;
		}
	} 

	//Member Promote
	if (is_member && payment_complete)
	{
		p_identity->set_points(p_identity->get_points() + p_identity->add_point(sum));
		int promotion = check_upgrade(p_identity);
		if (promotion != 0)
		{
			cout << "Congratuation! Now your level is: " << p_identity->get_member_type() << "." << endl;
		}
		cout << "Your current point is: "<< p_identity->get_points() << endl;
	}
	//Member Promote end

	return 0;
}

/* Purchase Functions */

void ShopSysCostomer::add_into_list(string _id, u_int _num = 1)
{
	if (id_goods_map.count(_id))
	{
		Goods tmpobj = id_goods_map[_id];
		if (shoppinglist.count(tmpobj) == 0)
		{
			shoppinglist[tmpobj] = _num;
		}
		else
		{
			shoppinglist[tmpobj] += _num;
		}
		cout << "Adding " << _num <<" product(s) complete." << endl;
	}
	else
	{
		cout << ("Cannot find product ID : " + _id) << endl;
	}
}

void ShopSysCostomer::remove_from_list(string _id, u_int _num = 0)
{
	Goods tmpobj = id_goods_map[_id];
	if (shoppinglist.count(tmpobj) != 0)
	{
		if (_num == 0)
		{
			u_int tmp_num = shoppinglist[tmpobj];
			shoppinglist.erase(tmpobj);
			cout << "Removing " << tmp_num << " product(s) complete." << endl;
		}
		else if (_num > shoppinglist[tmpobj])
		{
			cout << "Unable to execute : Required number is more than the number in your list. ( Maximum : " << shoppinglist[tmpobj] <<" )"<< endl;
		}
		else if (_num == shoppinglist[tmpobj])
		{
			shoppinglist.erase(tmpobj);
			cout << "Removing " << _num << " product(s) complete." << endl;
		}
		else
		{
			shoppinglist[tmpobj] -= _num;
			cout << "Removing " << _num << " product(s) complete." << endl;
		}
	}
	else
	{
		cout << "You didn't add this product in your list or wrong ID is entered." << endl;
	}
		
}

/* Login/Logout Functions */

//return 0 normal; return 1 failed.
int ShopSysCostomer::login_action(string _id, string _password)
{
	fstream file;
	file.open(".\\members\\"+_id+".txt");
	if (!file)
	{
		cout << "Cannot find ID : " << _id << ". Please enter a proper ID." << endl;
		return 1;
	}

	string info_read;
	getline(file, info_read);
	if (!regex_match(info_read, Id_Member_File_Pattern))
	{
		cout << "Read Member Info Error. Please contact our server." << endl;
		return 1;
	}

	vector<string> infovec = str_Split_file(info_read);
	//[0]:ID   [1]:Name   [2]:Gender   [3]:Phone    [4]:Points    [5]:Password
	if (_password != infovec[5])
	{
		cout << "Wrong Password!" << endl;
		return 1;
	}

	is_member = true;
	p_identity = new normal_member(infovec[1], infovec[0], infovec[2], infovec[3], infovec[4]);
	check_upgrade(p_identity);

	cout << "Welcome, "<<p_identity->get_member_type() <<": "<< infovec[1] << "!" <<endl;
	cout << "Your current point is: " << p_identity->get_points() << endl;
	return 0;
}

int ShopSysCostomer::logout_action()
{
	if (p_identity == NULL)
	{
		cout << "You haven't login yet. Operation cancelled." << endl;
		return 0;
	}
	cout << "Sure to logout? (y/n)";
	while (1)
	{
		char presskey;
		presskey = getch();
		if (presskey == 'y')
		{
			//Refresh file
			fstream fmember;
			fmember.open(".\\members\\"+p_identity->get_id()+".txt", ios::trunc|ios::out);
			fmember << p_identity->get_id() << ',' 
				<< p_identity->get_name() << ','
				<< p_identity->get_gender() << ','
				<< p_identity->get_phone() << ','
				<< p_identity->get_points() << ','
				<< password_mem;
			fmember.close();
			//Refresh file done
			delete p_identity;
			p_identity = NULL;
			cout << endl << "Bye!";
			is_member = false;
			return 0;
		}
		else if (presskey == 'n')
		{
			cout << endl << "Cancelled.";
			return 0;
		}
	}
	
}

