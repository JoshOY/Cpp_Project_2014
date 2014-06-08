/******************************************
*      Standard Libraries or Headfiles        *
*      (with some const values defined)     *
*******************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <typeinfo>
#include <algorithm>
#include <iomanip>
#include <regex>			//with C++11
#include <conio.h>

using namespace std;

typedef unsigned int u_int;
 
/* chars for spliting strings */
const string SPLCHARS = "., \t\n";
const string SPLCHARS_FILE = ",";

/* Use Regular Expression to make sure you are entering an unsigned int */
const regex Is_Unsigned_Int_Pattern("[123456789][0-9]*");

/* Use Regular Expression to make sure you are entering a number >= 0 */
const regex Is_Number_Pattern("[0-9]+(.[0-9]+)?");

/* Use Regular Expression to make sure you are entering a valid bank card number (19 digits)*/
const regex Bank_Card_Pattern("[0-9]{19}");

/*
Use Regular Expression to make sure the correct input of a password
RE: [password(0-9 or a-z or A-Z)]
*/
const regex Password_Pattern("[a-z0-9A-Z]{8,16}");

/*
Use Regular Expression to make sure the correct input of id-member file 
RE: [id(8 digits)],[name(allow space)],[male/female],[phone(several digits)],[points(a number, eg: 14234.5)],[password(0-9 or a-z or A-Z)]
*/
const regex Id_Member_File_Pattern("(\\d{8}),([^,0123456789]+),([Ff]e)?[Mm]ale,(\\d+),([0-9]+(.[0-9]+)?),([a-z0-9A-Z]{8,16})");

/*
Use Regular Expression to make sure the correct input of id-goods file
RE: [id(several digits)],[name],[origin],[price(a number, eg: 49.9)]
*/
const regex Id_Goods_File_Pattern("([0-9]+),([^,]+),([^,]+),([0-9]+(.[0-9]+)?)");