#include <iostream>
#include "BankingSystem.h"

using namespace std;


//Mohamed's Part

void BankAccount::setID(int id)
{
	m_accountID  = id;
}

BankAccount::BankAccount(int intial_balance)
{
	m_balance = intial_balance;
}
BankAccount::BankAccount()
{
	m_balance = 0;
}
int BankAccount::getID()
{
	return m_accountID;
}
void BankAccount::setBalance(int balance)
{
	m_balance = balance;
}
int BankAccount::getBalance()
{
	return m_balance;
}

void  BankAccount::setClient(Client* ptr)
{
	m_owner = ptr;
}
Client* BankAccount:: client()
{
	return m_owner;
}
void BankAccount::withdraw(int amount)
{

}

void BankAccount::deposit(int amount)
{

}

string BankAccount::type()
{
	return "basic_account";
}
///saving bank account (Fadl's Part)

void SavingsBankAccount::setBalance(int balance)
{
    m_balance = balance;
}
void  SavingsBankAccount::setClient(Client* ptr)
{
	m_owner = ptr;

}
Client* SavingsBankAccount:: client()
{
	return m_owner;

}
SavingsBankAccount::SavingsBankAccount(int intial_balance, int minimumBalance) 
{
    setBalance(intial_balance);
    setMinimumBalance(minimumBalance);
}

void SavingsBankAccount::setMinimumBalance(int minimumBalance)
{
    m_minimumBalance = minimumBalance;
}

int SavingsBankAccount::getMinimumBalance()
{
    return m_minimumBalance;
}

void SavingsBankAccount::withdraw(int amount)
{   
    cout<<"Enter amount you want to withdraw: "<<endl;
    cin>>amount;
    while (amount < 100)
    {
        cout<<"please, it can not be less than 100 LE"<<endl;
        cout<<"Enter amount you want to withdraw: "<<endl;
        cin>>amount;
    }    
    while (m_balance < amount)
    {
        cout<<"sorry, it more than you have"<<endl;
        cout<<"Enter amount you want to withdraw: "<<endl;
        cin>>amount;
    }
    
    m_balance -= amount;    
}
void SavingsBankAccount::deposit(int amount)
{
    cout<<"please, enter amount you want to deposit: "<<endl;
    cin>>amount;
    m_balance += amount;
}


string SavingsBankAccount::type()
{
	return "savings_account";
}