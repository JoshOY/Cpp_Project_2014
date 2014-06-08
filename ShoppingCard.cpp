#include "ShoppingCard.h"

/*Constructors & Destructors*/

ShoppingCard::ShoppingCard() : card_number("N/A"), 
														balance(0)
{
	
}

ShoppingCard::ShoppingCard(string _number = "N/A", Price _balance = 0)
		: card_number(_number),
		balance(_balance)
{
	
}


int ShoppingCard::pay(Price& _payment, Price real_payment)
{
	if ( (real_payment - _payment) > 0)
	{
		cout << "You don't need to pay that so much. Please retry." << endl;
		return 0;
	}
	else
	{
		if ( (real_payment - balance) > 0)
		{
			cout << "Not enough balance in your shopping card." << endl;
			return 0;
		}
		else if (real_payment == _payment)
		{
			balance = balance - _payment;
			cout << "Payment Complete. Thank you and have a nice day!" << endl;
			return 1;
		}
		else //real_payment < _payment
		{
			balance = balance - real_payment;
			cout << "Payment Complete. Thank you and have a nice day!" << endl;
			_payment = _payment - real_payment;
			return 0;
		}
	}
}

