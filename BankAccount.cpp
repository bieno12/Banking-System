#include "BankingSystem.h"

using namespace std;

int integer_in()
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
    while(m_balance < amount){
        cout<<"this is bigger than you have\n";
        cout<<"plese enter amount: ";
        cin >> amount;
    }
    m_balance -= amount;
}

void BankAccount::deposit(int amount)
{
    m_balance += amount;
}

string BankAccount::type()
{
	return "basic_account";
}
///saving bank account (Fadl's Part)

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
    while (amount < 100)
    {
        cout<<"please, it can not be less than 100 LE"<<endl;
        cout<<"Enter amount you want to withdraw: "<<endl;
        amount = integer_in();
    }    
    while (getBalance() - amount < m_minimumBalance)
    {
        cout<<"sorry, it more than you have"<<endl;
        cout<<"Enter amount you want to withdraw: "<<endl;
        amount = integer_in();
    }
    int b = getBalance();
    setBalance(b -= amount);    
}

string SavingsBankAccount::type()
{
	return "savings_account";
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
	bool running = true;
	cout << "Welcome to FCAI Banking Application\n";
	while(running)
	{
		cout << "1. Create a New Account\n";
		cout << "2. List Clients and Accounts\n";
		cout << "3. Withdraw Money\n";
		cout << "4. Deposit Money \n";
		cout << "5. Exit\n";


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
			case 5:
				running = false;
				break;
		}
		save_data("clients.txt", "accounts.txt");
	}

	for(auto c : m_clients)
	{
		delete c;

	}
	for(auto a : m_accounts)
	{
		delete a;
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

			new_account->setID(stoi(line));
			getline(accounts_file, line);
			new_account->setBalance(stoi(line));
			m_accounts.push_back(new_account);
		}
	}
	for(Client* c : m_clients)
	{
		for(BankAccount* acc : m_accounts)
		{
			if(c->m_accountID == acc->getID())
			{
				c->m_account = acc;
				acc->setClient(c);
			}
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
		if(c->m_account->type() == "savings_account")
			cout << "minimum Balance: " << static_cast<SavingsBankAccount*>(c->m_account)->getMinimumBalance() << endl;
	}
}	

void BankingApplication::withdraw_money()
{
	cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
	int id = integer_in();
	bool found = false;
	for(auto acc : m_accounts)
	{
		if(id == acc->getID())
		{
			found = true; 
			cout << "Account ID: " << id <<endl;
			cout << "Acocunt Type: " << acc->type() << endl;
			cout << "Balance: " << acc->getBalance() << endl;
			cout << "Please Enter The Amount to Withdraw =========> " ;
			unsigned int amount = integer_in();
			acc->withdraw(amount);

			cout << "Account ID: " << id <<endl;
			cout << "Balance: " << acc->getBalance() << endl;

			break;
		}
	}
	if(!found)
	{
		cout << "there is no such account\n";
	}

}
void BankingApplication::deposit_money()
{

	cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
	int id = integer_in();
	bool found = false;
	for(auto acc : m_accounts)
	{
		if(id == acc->getID())
		{
			found = true; 
			cout << "Account ID: " << id <<endl;
			cout << "Acocunt Type: " << acc->type() << endl;
			cout << "Balance: " << acc->getBalance() << endl;
			cout << "Please Enter The Amount to Deposit =========> " ;
			unsigned int amount = integer_in();
			acc->deposit(amount);

			cout << "Account ID: " << id <<endl;
			cout << "Balance: " << acc->getBalance() << endl;
			break;
		}
	}
	if(!found)
	{
		cout << "there is no such account\n";
	}
}
