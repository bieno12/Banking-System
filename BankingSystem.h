#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

class Client;
class BankAccount;
class SavingsBankAccount;


class Client
{
public:
	string m_name;
	string m_address;
	string m_phoneNumber;
	int m_accountID;
	int m_clientID;
	BankAccount* m_account;
};


class BankAccount
{
private:
	int m_accountID;
	int m_balance;
public:
	int m_clientID;
	Client* m_owner;
	BankAccount(int intial_balance);
	BankAccount();

	void setID(int id);
	int getID();

	void setBalance(int balance);
	int getBalance();

	void setClient(Client*);
    Client* client();

	virtual void withdraw(int amount);
	void deposit(int amount);
	virtual string type();

};

class SavingsBankAccount: public BankAccount
{
private:
	int m_minimumBalance = 1000;
public:
	SavingsBankAccount(int intial_balance, int minimumBalance);
	void setMinimumBalance(int minimumBalance);
	int getMinimumBalance();

	void withdraw(int amount);
	string type();
};


class BankingApplication
{
	int account_counter = 0;
	int client_counter = 0;
	vector<BankAccount*> m_accounts;
	vector<Client*> m_clients; 
public:
	BankingApplication();
	void run();
private:
	void register_account();
	void list_data();
	void withdraw_money();
	void deposit_money();
	void load_data(string clients_file, string accounts_file);

	void save_data(string clients_file, string accounts_file);

};
#endif