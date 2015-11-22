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

struct claim {
	string type;                         //type of agent entitled to claim
	long ID;                             //ID associated with holder
	string title;                        //name of asset...not really necessary to include but could come in handy
	double value;                        //value associated with asset
	int period;                          //for bonds, determines repayment period; for stocks, does not apply
} currency, stock, bond;

struct account {
	long ID;                             //ID associated with account holder
	vector<claim> asset {};              //elements of account
	int period;                          //track how long asset has been stored
};

class agent {                                      //creates agent capable of possessing and trading assets
	protected:                                       //these probably don't need to be protected?
		long ID;                               
	public:
		agent(long id) : ID(id){}                      //initialize ID and total value of all assets

		long getID = ID;                               //return ID

		vector<string> assets{"currency", "stocks", "bonds", "loans"};       //array of asset types
		
		claim portfolio[4];                                          //array same length assets containing info about each asset
		virtual void createPortfolio(){}                             //create a portfolio of assets 

		//allow agent to borrow currency from another agent
		void borrow(agent* B, double amount) {
			double borrower_cash_init = portfolio[0].value;
			double borrower_loans_init = portfolio[3].value;
			double lender_cash_init = B->portfolio[0].value;                  //keep track of initial values
			double lender_loans_init = B->portfolio[3].value;

			cout << "Agent " << ID << " attempted to borrow " << amount << " from agent " << B->getID << '\n';  

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

				cout << "Agent " << ID << " borrowed " << amount << " from agent " << B->getID << '\n'; 
			}

		}

		//allow agent to lend currency to another agent
		void lend(agent* B, double amount) {
			double lender_cash_init = portfolio[0].value;                  //keep track of initial values
			double lender_loans_init = portfolio[3].value;
			double borrower_cash_init = B->portfolio[0].value;
			double borrower_loans_init = B->portfolio[3].value;

			cout << "Agent " << ID << " attempted to lend " << amount << " to agent " << B->getID << '\n';

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

				cout << "Agent " << ID << " lent out " << amount << " to agent " << B->getID << '\n';
			}

		}

		//a function allowing for the possibility of no interaction upon coupling
		void null_interaction(agent* B){                             
			cout << "Nothing happened" << '\n';
		}

		//if trader   

		virtual void deposit_cash(agent* B, double amount){}       //function allowing an agent to deposit cash
		virtual void withdraw_cash(agent* B, double amount){}      //function allowing an agent to withdraw cash

		//allow agent to trade one financial instrument for another with another agent
		void trade(string asset_A, agent* B, string asset_B, double amount){

			double traderA_assetA_init;                                       
			double traderB_assetB_init;

			cout << "Agent " << ID << " attempted to trade " << amount << " to agent " << B->getID << '\n';

			for (int i = 0; i < assets.size()-1; i++){
				for (int j = 0; j < assets.size()-1; j++){
					if (asset_A == portfolio[i].title && asset_B == portfolio[j].title){
						traderA_assetA_init = portfolio[i].value;                      				//keep track of initial values
						traderB_assetB_init = B->portfolio[j].value; 
						if (traderA_assetA_init < amount) {                            				//if the agent cannot lend desired amount
							cout << "Cannot trade desired asset" << '\n';                				//restrict it from going into the negative
							portfolio[i].value = traderA_assetA_init;
							B->portfolio[j].value = traderB_assetB_init;
						}
						else {
							portfolio[i].value = traderA_assetA_init - amount;             			//subtract amount lent from agent wealth
							B->portfolio[j].value = traderB_assetB_init + amount;          			//add deposited amount to agent's account

							cout << "Agent " << ID << " traded " << asset_A << " with a value of " 
							<< amount << " to agent " << B->getID << " in exchange for " << asset_B << " of the same value." << '\n';
						}
					}
				}
			}
		}

		//if financial intermediary
		vector<account> accounts {};                               	//vector of accounts held by financial intermediary
		virtual void createAccount(agent* A) {}                     //create an account for an agent at hand

		//return total value of all assets held by agent
		double wealth() {                              
			double val = 0;
			for (int i = 0; i < assets.size(); i++){
				if (getID == portfolio[i].ID){
					val = val + portfolio[i].value;
				}
			}
			return val;
		}

};

//return the quantity of money in the network
double money_supply(vector<agent*>& A){
	double sum = 0;
	for (int i = 0; i < A.size(); i++){
		sum = sum + A[i]->wealth();
	}
	return sum;
}