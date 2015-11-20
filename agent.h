#include <iostream>
#include <vector>
#include <string>

using namespace std;
////////////
//agent.h //
////////////
/**
 * creates agent capable of possessing and trading assets
 */

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
				portfolio[3].value = borrower_loans_init - amount;
				B->portfolio[0].value = lender_cash_init - amount;          //add deposited amount to agent's account
				B->portfolio[3].value = lender_loans_init + amount;          //add deposited amount to agent's account
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
				portfolio[3].value = lender_loans_init + amount;
				B->portfolio[0].value = borrower_cash_init + amount;          //add deposited amount to agent's account
				B->portfolio[3].value = borrower_loans_init - amount;          //add deposited amount to agent's account
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

//return the quantity of money in the network
double money_supply(vector<agent*>& A){
	double sum = 0;
	for (int i = 0; i < A.size(); i++){
		sum = sum + A[i]->networth();
	}
	return sum;
}