#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Contact
{
	string first_name;
	string last_name;
	string phone_number;
	string email;
	int id;
	Contact(string f, string l, string p, string e, int idd)
	{
		id = idd;
		first_name = f;
		last_name = l;
		phone_number = p;
		email = e;
	}
}; // end struct

vector<Contact>contacts;
int ID = 0;

/*=========================================ADD==============================================*/

bool add()
{
	char c1 = '@';
	char c2 = '.';
	string str2(",");
	char c;
	bool f, l, p, e;
	string firstName, lastName, phoneNumber, emailAddress;

	while (cin.peek() != '\n')
	{

		if (cin.get() == '-')
		{
			c = cin.get();
			switch (c)
			{
			case 'f':
				f = true;
				cin >> firstName;
				break;
			case 'l':
				l = true;
				cin >> lastName;
				break;
			case 'p':
				p = true;
				cin >> phoneNumber;
				break;
			case 'e':
				e = true;
				cin >> emailAddress;
				break;
			default:
				getline(cin, firstName);
				return false;
			}//end switch
		}//end if
	}//end while
	for(int k=0; k<contacts.size();k++)
	{
		if (((contacts[k].first_name==firstName)&&(contacts[k].last_name==lastName)) || (contacts[k].phone_number==phoneNumber) || (contacts[k].email==emailAddress))
		{
			return false;
		}
	}//endfor
	
	if (!(f && l && e && p))
		return false;

	for (int j = 0; j < phoneNumber.size(); j++) 
	{
		if (phoneNumber[j] >= '0' && phoneNumber[j] <= '9')
			continue;
		else return false;
	}//end for

	if ((phoneNumber.at(0) == '0') && (phoneNumber.at(1) == '9') && (phoneNumber.size() == 11)&& (emailAddress.find(str2)==string::npos) && (emailAddress.find(c1) != string::npos))
	{
		contacts.push_back(Contact(firstName, lastName, phoneNumber, emailAddress, ID));
		ID++;
		return true;
	}
	else return false;

}//end add

/*=======================================SEARCH=======================================*/

void search()
{
int	index=-1;
	string keyword;
	cin >> keyword;
	for (int i = 0; i < contacts.size(); i++)
	{
		if ((contacts[i].first_name.find(keyword) != string::npos) || (contacts[i].last_name.find(keyword) != string::npos) || (contacts[i].phone_number.find(keyword) != string::npos) || (contacts[i].email.find(keyword) != string::npos))
			cout << contacts[i].id << " " << contacts[i].first_name << " " << contacts[i].last_name << " " << contacts[i].phone_number << " " << contacts[i].email << endl;
	index=1;
	}//end for
if (index==-1)
	cout << "Command Failed" << endl;
}//end search

/*=========================================END==========================================*/

bool remove()
{ 
	int index=-1;
	int iddd;
	cin >> iddd;
	for(int i=0; i<contacts.size();i++)
	{
		if(contacts[i].id==iddd){
			index=1;
	contacts.erase(contacts.begin(), contacts.begin() + iddd);
	return true;}
	}

		if(index==-1)
			return false;
}//remove end

/*========================================EDIT==========================================*/

bool edit()
{
	char c;
	int iddd;
	cin >> iddd;
	int index = -1;
	string firstName, lastName, phoneNumber, emailAddress;
	for (int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i].id == iddd)
		{
			index = i;
			firstName = contacts[i].first_name;
			lastName = contacts[i].last_name;
			emailAddress = contacts[i].email;
			phoneNumber = contacts[i].phone_number;
		}//end if
	}//end for
	if (index == -1)
		return false;
	while (cin.peek() != '\n')
	{
		if (cin.get() == '-')
		{
			c = cin.get();
			switch (c)
			{
			case 'f':
				cin >> firstName;
				break;
			case 'l':
				cin >> lastName;
				break;
			case 'p':
				cin >> phoneNumber;
				break;
			case 'e':
				cin >> emailAddress;
				break;
			default:
				getline(cin, firstName);
				return false;
			}//end switch
		}//end if
	}//end while
	int thing=-1;
	for(int k=0;k<contacts.size();k++)
	{
		if(((contacts[k].first_name==firstName)&&(contacts[k].last_name==lastName)) || (contacts[k].phone_number==phoneNumber) || (contacts[k].email==emailAddress)) return false;
	}//endfor		
	contacts[index].first_name = firstName;
	contacts[index].last_name = lastName;
	contacts[index].phone_number = phoneNumber;
	contacts[index].email = emailAddress;
	return true;

}//end edit

/*============================================MAIN===========================================*/

int main()
{
	string command;
	int i;
	while (cin >> command)
	{
		if (command == "add")
		{
			if (add() == true)
				cout << "Command Ok" << endl;
			else cout << "Command Failed" << endl;
		}

		else if (command == "search")
		{
			search();
		}

		else if (command == "delete")
		{
			if (remove() == true)
				cout << "Command Ok" << endl;
			else cout << "Command Failed" << endl;
		}

		else if (command == "update")
		{
			if (edit() == true)
				cout << "Command Ok" << endl;
			else cout << "Command Failed" << endl;
		}
	}//end while
	return 0;
}//end main
