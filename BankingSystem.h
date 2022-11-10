#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Client;

class BankAccount
{
private:
	int m_accountID;
	int m_balance;
	Client* m_owner;
	virtual void setID(int id);
public:
	BankAccount(int intial_balance);
	BankAccount();

	virtual int getID();

	virtual void setBalance(int balance);
	virtual int getBalance();
	
	virtual void withdraw(int amount);
	virtual void deposit(int amount);


};

class SavingsBankAccount
{
private:
	int m_minimumBalance;
public:
	SavingsBankAccount(int intial_balance, int minimumBalance);
	void setMinimumBalance(int minimumBalance);
	int getMinimumBalance();

	void withdraw();
	void deposit();
};

class Client
{
	string m_name;
	string m_address;
	string m_phoneNumber;
	BankAccount* m_account;

};

class BankingApplication
{
	vector<BankAccount> m_accounts;
	vector<Client> m_clients; 
public:
	BankingApplication();
	void run();
};
#endif