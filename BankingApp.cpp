#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include "BankingSystem.h"

using namespace std;




static int integer_in()
{
	string str;
	getline(cin, str);
	try
	{
		return stoi(str);
	}
	catch(...)
	{
		cout << "invalid integer!\n";
		return integer_in();
	}
}


BankingApplication::BankingApplication()
{

}
void BankingApplication::run()
{
	load_data("clients.txt", "accounts.txt");
	for(Client* c : m_clients)
		client_counter = max(c->m_accountID, client_counter); 
	for(BankAccount* a : m_accounts)
		account_counter = max(a->getID(), client_counter); 

	cout << "Welcome to FCAI Banking Application\n";
	while(true)
	{
		cout << "1. Create a New Account\n";
		cout << "2. List Clients and Accounts\n";
		cout << "3. Withdraw Money\n";
		cout << "4. Deposit Money \n";


		cout << "Please Enter Choice =========> ";
		int command = integer_in();
		while(command < 1 && command > 4)
		{
			cout << "enter a valid choice ========> ";
			command = integer_in();
		}
		switch (command)
		{
			case 1:
				register_account();
			break;
	

			case 2:
				list_data();
			break;

			case 3:
				withdraw_money();
			break;

			case 4:
				deposit_money();
			break;
		}
		save_data("clients.txt", "accounts.txt");
	}

}

//additional functions
void BankingApplication::load_data(string clients_filename, string accounts_filename)
{
	ifstream clients_file(clients_filename);
	ifstream accounts_file(accounts_filename);

	//load clients;
	if(clients_file.is_open())
	{
		string line;
		while(getline(clients_file, line))
		{
			Client* new_client = new Client();
			getline(clients_file, line); 
			new_client->m_name = line;
			getline(clients_file, line);

			new_client->m_address = line;
			getline(clients_file, line);

			new_client->m_phoneNumber = line;
			getline(clients_file, line);

			new_client->m_accountID = stoi(line);
			getline(clients_file, line);

			new_client->m_clientID = stoi(line);
			m_clients.push_back(new_client);
		}
	}

	//load accounts
	if(accounts_file.is_open())
	{
		string line;
		while(getline(accounts_file, line))
		{
			cout << line << endl;
			BankAccount* new_account;
			if(line == "savings_account")
			{

				new_account = new SavingsBankAccount(0,0);
				getline(accounts_file, line);
				static_cast<SavingsBankAccount*>(new_account)->setMinimumBalance(stoi(line));
			}
			else if(line == "basic_account")
			{
				new_account = new BankAccount(0);
			}

			getline(accounts_file, line);
			cout << line << endl;

			new_account->setID(stoi(line));
			getline(accounts_file, line);
			cout << line << endl;
			new_account->setBalance(stoi(line));
			m_accounts.push_back(new_account);
		}
	}

}


void BankingApplication::save_data(string clients_filename, string accounts_filename)
{
	ofstream clients_file(clients_filename);
	ofstream accounts_file(accounts_filename);

	//save clients;
	if(clients_file.is_open())
	{
		for(Client* client: m_clients)
		{
			clients_file << endl;
			clients_file << client->m_name << endl;
			clients_file << client->m_address << endl;
			clients_file << client->m_phoneNumber << endl;
			clients_file << client->m_accountID<< endl;
			clients_file << client->m_clientID << endl;
		}
	}

	//saves accounts
	if(accounts_file.is_open())
	{
		for(BankAccount* account : m_accounts)
		{
			accounts_file << account->type() << endl;
			if(account->type() == "savings_account")
			{

				accounts_file << static_cast<SavingsBankAccount*>(account)->getMinimumBalance() << endl;
			}
			accounts_file << account->getID() << endl;
			accounts_file << account->getBalance() << endl;
		}
	}
	
}

void BankingApplication::register_account()
{
	m_clients.push_back(new Client);
	m_clients.back()->m_clientID = ++client_counter;
	cout << "Please Enter Client Name =========> ";
	getline(cin, m_clients.back()->m_name);
	cout << "Please Enter Client Address ======> ";
	getline(cin, m_clients.back()->m_address);
	cout << "Please Enter Client Phone ========> ";
	getline(cin, m_clients.back()->m_phoneNumber);
	cout << "What Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2\n";
	cout << "Please Enter your Choice =========> ";
	int type = integer_in();
	while(type > 2 && type < 1)
	{
		cout << "enter  a valid type :";
		type = integer_in();
	}
	cout << "Please Enter the Starting Balance ==> ";
	int balance = integer_in();
	if(type == 1)
	{
		m_accounts.push_back(new BankAccount(balance));
	}
	else
	{
		cout << "Please Enter the minimum Balance ==> ";
		int minimumBalance = integer_in();
		m_accounts.push_back(new SavingsBankAccount(balance, minimumBalance));
	}

	m_accounts.back()->setID(++account_counter);
	m_accounts.back()->setClient(m_clients.back());
	m_accounts.back()->m_clientID = m_accounts.back()->client()->m_clientID;


	m_clients.back()->m_account = m_accounts.back();
	m_clients.back()->m_accountID = m_accounts.back()->getID();
	cout << "An account was created with ID " << m_accounts.back()->getID() <<  "and Starting Balance "<< balance <<" L.E.\n";
}

void BankingApplication::list_data()
{
	for(Client* c : m_clients)
	{
		cout << setw(40) << setfill('-') <<  c->m_name <<  endl;
		cout << "Address: " << c->m_address << endl; 
		cout << "Phone Number: " << c->m_phoneNumber << endl; 
		cout << "Account ID: " << c->m_accountID << " (" << c->m_account->type() << ")\n"; 
		cout << "Balance: " << c->m_account->getBalance() << endl; 
	}
}	

void BankingApplication::withdraw_money()
{


}
void BankingApplication::deposit_money()
{


}
