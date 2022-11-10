#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H
#include <iostream>
#include <string>
#include <vector>
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

public:
	int m_accountID;
	int m_balance;
	int m_clientID;
	Client* m_owner;
	virtual void setID(int id);
	BankAccount(int intial_balance);
	BankAccount();

	virtual int getID();

	virtual void setBalance(int balance);
	virtual int getBalance();

	virtual void setClient(Client*);
	virtual Client* client();

	virtual void withdraw(int amount);
	virtual void deposit(int amount);
	virtual string type();

};

class SavingsBankAccount: public BankAccount
{
private:
	int m_minimumBalance = 1000;
public:
	void setBalance(int balance);
	SavingsBankAccount(int intial_balance, int minimumBalance);
	void setMinimumBalance(int minimumBalance);
	int getMinimumBalance();

	void setClient(Client*);
	Client* client();

	void withdraw(int amount);
	void deposit(int amount);
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