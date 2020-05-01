#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

const int EMPTY = 0;
const int ELEVEN_DIGITS = 11;
const char FIRST_DIGIT = '0', SECOND_DIGIT = '9';
const char DOT = '.', DASH = '-', END_LINE = '\n';
const string COMMA(",");
const string AT_SIGN("@");

struct Contact
{
	string first_name;
	string last_name;
	string phone_number;
	string email_address;
	string address;
	int identity_document;

	Contact(string first, string last, string phone, string email, string address_constructor, int id)
	{
		identity_document = id;
		first_name = first;
		last_name = last;
		phone_number = phone;
		email_address = email;
		address = address_constructor;
	}
};

int ID = 0;

int convert_string_to_integer(string id_string)
{
	int id_int = 0;
	for(int i = 0; i < id_string.size(); i++)
	{
		id_int += ((int)id_string[i])-'0';
		id_int *= 10;
	}
	id_int /= 10;
	return id_int;
}

bool check_info_existance(vector<string> input_vector)
{
	for(int i = 0; i < input_vector.size() - 1; i++)
	{
		if(input_vector[i].size() == 0)
		{
			return false;
		}  
	}
	return true;
}

bool check_input(vector<string> input_vector, vector<Contact> contacts, int ignore_index = -1)
{
	string firstname, lastname, phonenumber, emailaddress, address_string;
	firstname = input_vector[0];
	lastname = input_vector[1];
	phonenumber = input_vector[2];
	emailaddress = input_vector[3];
	address_string = input_vector[4];

	for(int k = 0; k < contacts.size(); k++)
	{
		if(k == ignore_index)
			continue;
		if (((contacts[k].first_name == firstname) && (contacts[k].last_name == lastname)) || (contacts[k].phone_number == phonenumber) || (contacts[k].email_address == emailaddress))
		{
			return false;
		}
	}
	
	for (int j = 0; j < phonenumber.size(); j++) 
	{
		if (phonenumber[j] >= '0' && phonenumber[j] <= '9')
		{
			continue;
		}
		else 
		{
			return false;
		}
	}

	if((phonenumber.size() == ELEVEN_DIGITS) && (phonenumber.at(0) == FIRST_DIGIT) && (phonenumber.at(1) == SECOND_DIGIT) && (emailaddress.find(COMMA)==string::npos) && (emailaddress.find(AT_SIGN) != string::npos))
	{
		return true;
	}
	return false;
}

vector<string> make_vector(string firstname, string lastname, string phonenumber, string emailaddress, string address_string)
{
	vector<string> input_vector;
	input_vector.push_back(firstname);
	input_vector.push_back(lastname);
	input_vector.push_back(phonenumber);
	input_vector.push_back(emailaddress);
	input_vector.push_back(address_string);
	return input_vector;
}

vector<string> get_input(string line)
{
	string firstname, lastname, phonenumber, emailaddress, address_string;
	string parameter;
	int id;
	bool success = true;
	vector<string> input_vector;
	string token;
	stringstream split(line);

	while(split >> token)
	{
		parameter = token;
		if(parameter == "-f")
		{
			split >> token;
			firstname = token;
		}
		else if(parameter == "-l")
		{
			split >> token;
			lastname = token;
		}
		else if(parameter == "-e")
		{
			split >> token;
			emailaddress = token;
		}
		else if(parameter == "-p")
		{
			split >> token;
			phonenumber = token;
		}
		else if(parameter == "-a")
		{
			getline(split, token, '-');
			if(token[token.size() - 1] == '\n')
			{
				token = token.substr(0,token.size()-1);
			}
		}
		else
		{
			success = false;
			break;
		}
	}

	if(success == false)
	{
		cout << "Command Failed" << endl;
	}

	input_vector = make_vector(firstname, lastname, phonenumber, emailaddress, address_string);

	return input_vector;
}

void add(string line, vector<Contact>& contacts)
{
	string firstname, lastname, phonenumber, emailaddress, address_string;
	vector<string> input_vector;
	string token;
	stringstream ss(line);
	ss >> token;
	getline(ss, line);
	input_vector = get_input(line);

	if(check_info_existance(input_vector) == true && check_input(input_vector, contacts) == true)
	{
		firstname = input_vector[0];
		lastname = input_vector[1];
		phonenumber = input_vector[2];
		emailaddress = input_vector[3];
		address_string = input_vector[4];

		contacts.push_back(Contact(firstname, lastname, phonenumber, emailaddress, address_string, ID));
		ID++;
		cout << "Command Ok" << endl;
	}
	else 
	{
		cout << "Command Failed" << endl;
	}
}

void update(string line, vector<Contact>& contacts)
{
	string firstname, lastname, phonenumber, emailaddress, address_string;
	int found = -1;
	int id;	
	string token;
	stringstream ss(line);
	ss >> token;
	ss >> id;

	getline(ss, line);
	vector<string> input_vector;
	input_vector = get_input(line);

	for (int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i].identity_document == id)
		{
			found = i;
			if(input_vector[0].size() == EMPTY)
			{
				input_vector[0] = contacts[i].first_name;
			}

			if(input_vector[1].size() == EMPTY)
			{
				input_vector[1] = contacts[i].last_name;
			}

			if(input_vector[2].size() == EMPTY)
			{
				input_vector[2] = contacts[i].phone_number;
			}

			if(input_vector[3].size() == EMPTY)
			{
				input_vector[3] = contacts[i].email_address;
			}

			if(input_vector[4].size() == EMPTY)
			{
				input_vector[4] = contacts[i].address;
			}
		}
	}

	if (found == -1 || check_input(input_vector, contacts, found) == false)
	{
		cout << "Command Failed" << endl;
		return;
	}

	contacts[found].first_name = input_vector[0];
	contacts[found].last_name = input_vector[1];
	contacts[found].phone_number = input_vector[2];
	contacts[found].email_address = input_vector[3];
	contacts[found].address = input_vector[4];

	cout << "Command Ok" << endl;
}

bool search(string line, vector<Contact>& contacts)
{
	string keyword;
	stringstream token(line);
	token >> keyword;
	token >> keyword;
	bool success = false;

	for (int i = 0; i < contacts.size(); i++)
	{
		if ((contacts[i].first_name.find(keyword) != string::npos) || (contacts[i].last_name.find(keyword) != string::npos) || (contacts[i].phone_number.find(keyword) != string::npos) || (contacts[i].email_address.find(keyword) != string::npos) || (contacts[i].address.find(keyword) != string::npos))
		{
			cout << contacts[i].identity_document << " " << contacts[i].first_name << " " << contacts[i].last_name << " " << contacts[i].phone_number << " " << contacts[i].email_address << contacts[i].address << endl;
			success = true;
		}
	}
	
	if (success == false)
	{
	    return false;
	}
	else 
	{
		return true;
	}
}

void remove(string line, vector<Contact>& contacts)
{ 
	bool was_removed = false;
	int id;
	string dummy;
	stringstream token(line);
	token >> dummy;	
	token >> id;

	for(int i = 0; i < contacts.size(); i++)
	{
		if(contacts[i].identity_document == id)
		{
			was_removed = true;
			contacts.erase(contacts.begin() + i);
		}
	}

	if(was_removed == false)
	{
		cout << "Command Failed" << endl;
	}
}

string get_command(string input)
{
	stringstream token(input);
	string command;
	token >> command;
	return command;
}

bool check_command(string command)
{  
	if(command == "add" || command == "delete" || command == "search" || command == "update")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void test_get_command()
{
	string test1("add -f Mahsa -e mahsa@gmail.com -p 09215796657 -l Eskandari -a Iran, Tehran");
	string test2("search Hedie");
	string test3("dkdkdkd kdkdkdk");

	if(get_command(test1) == "add")
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(get_command(test2) == "search")
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(get_command(test3) == "dkdkdkd")
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
}

void test_check_command()
{
	string test1("add");
	string test2("delete");
	string test3("lksajlaj");

	if(check_command(test1) == true)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(check_command(test2) == true)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(check_command(test3) == false)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
}

void test_check_info_existance()
{
	vector<string> test1;
	vector<string> test2;
	string firstname_test("Mahsa");
	string lastname_test("Eskandari");
	string phone_number_test("09215796657");
	string email_address_test("mahsa@gmail.com");
	string address_test("Iran, Tehran");

	test1.push_back(firstname_test);
	test1.push_back(lastname_test);
	test1.push_back(phone_number_test);
	test1.push_back(email_address_test);
	test1.push_back(address_test);

	test2.push_back(firstname_test);
	test2.push_back(lastname_test);
	test2.push_back(phone_number_test);
	test2.push_back(email_address_test);

	if(check_info_existance(test1) == true)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(check_info_existance(test2) == false)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
}

void test_convert_string_to_integer()
{
	string test1("0");
	string test2("4657860");
	string test3("65465464687886768");

	if(convert_string_to_integer(test1) == 0)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(convert_string_to_integer(test2) == 4657860)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
	if(convert_string_to_integer(test3) == 65465464687886768)
	{
		cout << "CORRECT ANSWER" << endl;
	}
	else 
	{
		cout << "WRONG ANSWER" << endl;
	}
}

int main()
{
	string text, command;
	vector<Contact> contacts;
	while(getline(cin, text))
	{
		command = get_command(text);
		if(check_command(command) == false)
		{
			cout << "Command Failed" << endl;
			continue;
		}
		else
		{
			if (command == "add")
			{
				add(text, contacts);
			}

			if (command == "search")
			{
				if(search(text, contacts) == false)
				{
					cout << "Command Failed" << endl;
				}
			
			}

			if (command == "delete")
			{
				remove(text, contacts);
			}

			if (command == "update")
			{
				update(text, contacts);
			}
		}
		for(int i = 0; i < contacts.size(); i++)
		{
			cout << contacts[i].identity_document << " " << contacts[i].first_name << " " << contacts[i].last_name << " " << contacts[i].phone_number << " " << contacts[i].email_address << contacts[i].address << endl;
		}
	}
	return 0;
}
