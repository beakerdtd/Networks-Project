#include <iostream>            //probably don't need all of these headers
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <vector>
#include <string>

using namespace std;           //especially with this guy down here

//In this program, we will model a financial market

struct account {
	string type;
	long int ID;                         //ID associated with holder
	double value;                        //value associated with asset
	int period;                          //track how long asset has been stored
};

struct claim {
	string title;                        //name of asset...not really necessary to include but could come in handy
	string type;
	long int ID;                         //ID associated with holder
	double value;                        //value associated with asset
	int period;                          //for bonds, determines repayment period; for stocks, does not apply
} money, stock, bond;

class agent {                                      //creates agent capable of possessing and trading assets
	protected:                                       //these probably don't need to be protected?
		long int ID;
		double wealth;                                 
	public:
		//agent(long int id, int w) : ID(id), wealth(w){}          //initialize ID and total value of all assets
		agent(long int id) : ID(id){}          //initialize ID and total value of all assets
		long int getID = ID;                           //return ID
		vector<string> assets{"money", "securities", "bonds", "loans"};       //array of asset types

		void borrow(agent* B, double amount) {
			double borrower_cash_init = portfolio[0].value;
			double borrower_loans_init = portfolio[3].value;
			double lender_cash_init = B->portfolio[0].value;                  //keep track of initial values
			double lender_loans_init = B->portfolio[3].value;

			if (lender_cash_init < amount) {                               //if the agent cannot lend desired amount
				cout << "Cannot borrow desired amount" << '\n';                //restrict it from going into the negative
				portfolio[0].value = borrower_cash_init;
				portfolio[3].value = borrower_loans_init;
				B->portfolio[0].value = lender_cash_init;
				B->portfolio[3].value = lender_loans_init;
			}
			else {
				portfolio[0].value = borrower_cash_init + amount;             	//subtract amount lent from agent wealth
				portfolio[3].value = borrower_loans_init + amount;
				B->portfolio[0].value = lender_cash_init - amount;          //add deposited amount to agent's account
				B->portfolio[3].value = lender_loans_init - amount;          //add deposited amount to agent's account
			}

		}

		void lend(agent* B, double amount) {
			double lender_cash_init = portfolio[0].value;                  //keep track of initial values
			double lender_loans_init = portfolio[3].value;
			double borrower_cash_init = B->portfolio[0].value;
			double borrower_loans_init = B->portfolio[3].value;

			if (lender_cash_init < amount) {                               //if the agent cannot lend desired amount
				cout << "Cannot lend desired amount" << '\n';                //restrict it from going into the negative
				portfolio[0].value = lender_cash_init;
				portfolio[3].value = lender_loans_init;
				B->portfolio[0].value = borrower_cash_init;
				B->portfolio[3].value = borrower_loans_init;
			}
			else {
				portfolio[0].value = lender_cash_init - amount;             	//subtract amount lent from agent wealth
				portfolio[3].value = lender_loans_init - amount;
				B->portfolio[0].value = borrower_cash_init + amount;          //add deposited amount to agent's account
				B->portfolio[3].value = borrower_loans_init + amount;          //add deposited amount to agent's account
			}

		}

		//if trader
		
		claim portfolio[4];                                          //array same length assets containing info about each asset
		virtual void createPortfolio(){}                             //create a portfolio of assets    

		virtual double networth() {}                        				//function that will return the total value of all assets held by the agent
		virtual void deposit_cash(agent* B, double amount){}       //function allowing an agent to deposit cash
		virtual void withdraw_cash(agent* B, double amount){}      //function allowing an agent to withdraw cash

		//if financial intermediary
		vector<account> accounts {};                               //vector of accounts held by financial intermediary
		virtual void createAccount(agent* A) {}                     //create an account for an agent at hand


};

class trader: public agent {
	public:
		trader(int id) : agent(id) {}
		//claim portfolio[3];
		void createPortfolio() {
			for (int j = 0; j < assets.size()-1; j++){       //assign values to the portfolio
				portfolio[j].type = "node";
				portfolio[j].ID = ID;
				portfolio[j].title = assets[j];
				portfolio[j].value = rand() % 100;
			}
			portfolio[3].type = "node";
			portfolio[3].ID = ID;
			portfolio[3].title = assets[3];
			portfolio[3].value = 0;
		}
		double networth() {                              //return total value of all assets held by trader
			double val = 0;
			for (int i = 0; i < assets.size(); i++){
				if (getID == portfolio[i].ID){
					val = val + portfolio[i].value;
				}
			}
			return val;
		}
		void deposit_cash(agent* B, double amount){       							//function allowing an agent to deposit cash
			double agent_cash_init = portfolio[0].value;                  //keep track of initial values
			double fin_cash_init = B->accounts[getID].value;

			if (agent_cash_init < amount) {                               //if the agent cannot deposit desired amount
				cout << "Insufficient funds" << '\n';                      	//restrict it from going into the negative
				portfolio[0].value = agent_cash_init;
				B->accounts[getID].value = fin_cash_init;
			}
			else {
				portfolio[0].value = agent_cash_init - amount;             	//subtract amount deposited from agent wealth
				B->accounts[getID].value = fin_cash_init + amount;          //add deposited amount to agent's account
			}

		}
		
		void withdraw_cash(agent* B, double amount){                    //function allowing an agent to withdraw cash
			double agent_wealth_init = portfolio[0].value;                //keep track of initial values
			double fin_wealth_init = B->accounts[getID].value;                    

			if (fin_wealth_init <= amount) {                              //if the agent wants to withdraw more than it has stored
				cout << "Insufficient funds" << '\n';                       //restrict it from going into the negative
				portfolio[0].value = agent_wealth_init;
				B->accounts[getID].value = fin_wealth_init;
			}
			else{
				portfolio[0].value = agent_wealth_init + amount;            //add amount withdrawn to agent wealth
				B->accounts[getID].value = fin_wealth_init - amount;        //subtract withdrawn amount from agent's account
			}

		}

};

class financial_intermediary: public agent {
	public:
		financial_intermediary(int id) : agent(id) {}

		void createAccount(agent* A) {                                  //create new account
			account b;
			b.ID = A->getID;																							//assign ID
			b.value = 0;                                                  //assign initial account sum
			accounts.push_back(b);                                        //add account to list of accounts
		}
		double networth() {                                             //return total value of all assets held by agent
			double val = 0;                                               //in this case a financial intermediary
			for (int i = 0; i < assets.size(); i++){
				if (getID == accounts[i].ID){
					val = val + accounts[i].value;
				}
			}
			return val;
		}
};

double dRand(double fMin, double fMax)         //random double generator courtesy of stackoverflow
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(){  
	cout.precision(3);                                  //set precision on output values....might need to retool this

	srand(time(NULL));                                  //generate new sequence of random variables for each loop

	int M, N;                                           //number of financial intermediaries, number of nodes, respectively

	cout << "Enter number of financial intermediaries: ";
	cin >> M;

	vector<agent*> fin_int_vec {};                      //placeholder for all financial intermediaries generated below

	cout << "Enter number of agents: ";
	cin >> N;

	cout << '\n';

	vector<agent*> trader_vec {};                       //placeholder for all traders generated below
	
	for (int i = 0; i < M; i++){
		agent * bank = new financial_intermediary(i);     //create new financial intermediary
		fin_int_vec.push_back(bank);                      //add financial intermediary to storage vector
	}

	for (int i = 0; i < N; i++){                    
		agent * node = new trader(i);                     //create new trader
		node->createPortfolio();                          //create trader portfolio
		trader_vec.push_back(node);                       //add trader to storage vector
	}

	for (int i = 0; i < N; i++){
		fin_int_vec[0]->createAccount(trader_vec[i]);     //create account for all nodes interacting with particular financial intermediary
	}                                                   //leaving as separate loop so these values can change

/*
	for (int i = 0; i < fin_int_vec[0]->accounts.size(); i++){             //loop through accounts

		cout << "Account pre-deposit " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information before deposit
		
		cout << "Portfolio pre-deposit" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){              //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                    //print out portfolio attribues
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		
		trader_vec[i]->deposit_cash(fin_int_vec[0], dRand(0, trader_vec[i]->portfolio[0].value));  //deposit cash into account

		cout << "Account post-deposit " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information after deposit

		cout << "Portfolio post-deposit" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}

		trader_vec[i]->withdraw_cash(fin_int_vec[0], dRand(0, trader_vec[i]->portfolio[0].value)); //withdraw cash from account

		cout << "Account post-withdrawl " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information after withdrawl
		
		cout << "Portfolio post-withdrawl" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}

		cout << '\n';
		
	}
*/

	cout << "Trader portfolio pre-loan" << '\n' << '\n';

		for(int i = 0; i < 2; i++){
		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		cout << '\n';
	}

	cout << '\n';

	cout << "Trader portfolio pre-loan" << '\n' << '\n';

	//trader_vec[0]->borrow(trader_vec[1], 4);
	trader_vec[0]->lend(trader_vec[1], 4);

	for(int i = 0; i < 2; i++){
		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		cout << '\n';
	}

	cout << '\n';


	for (int i = 0; i < M; i++){
		delete fin_int_vec[i];             //delete all objects
	}

	for (int i = 0; i < N; i++){
		delete trader_vec[i];              //delete all objects
	}
	
	return 0;
}
