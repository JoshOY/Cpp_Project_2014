#include "Price.h"

/* A simple class, not nessessary to private something */
class ShoppingCard
{
public:
	/*Constructors & Destructors*/
	ShoppingCard();
	ShoppingCard(string,Price);

	int pay(Price&, Price);

	/* Vars */
	Price balance;
	string card_number;
};