#include <random>
#include "agent.h"

//////////////
// trader.h //
//////////////
/**
 * 
 */

class trader: public agent {
	public:
		trader(int id) : agent(id) {}

		//create new portfolio
		void createPortfolio() {
			for (int i = 0; i < assets.size(); i++){         //assign values to the portfolio
				portfolio[i].type = "node";
				portfolio[i].ID = ID;
				portfolio[i].title = assets[i];
				portfolio[i].value = rand() % 100;             //randomize intial values of assets
			}
			portfolio[assets.size()-1].value = 0;            //set intial loans to zero
		}

		//function allowing an agent to deposit cash
		void deposit_cash(agent* B, double amount){
			double trader_cash_init = portfolio[0].value;                              //keep track of initial values
			double account_cash_init = B->accounts[getID].asset[0].value;
			double fin_cash_init = B->portfolio[0].value;

			cout << "Agent attempted to deposited: " << amount << '\n';

			if (trader_cash_init < amount) {                               						 //if the agent cannot deposit desired amount
				cout << "Insufficient funds" << '\n';                      							 //restrict it from going into the negative
				portfolio[0].value = trader_cash_init;
				B->accounts[getID].asset[0].value = account_cash_init;
				B->portfolio[0].value = fin_cash_init;
			}
			else {
				portfolio[0].value = trader_cash_init - amount;             	           //subtract amount deposited from agent wealth
				B->accounts[getID].asset[0].value = account_cash_init + amount;          //add deposited amount to agent's account
				B->portfolio[0].value = fin_cash_init + amount;                          //and to financial intermediary's portfolio
				
				cout << "Agent deposited: " << amount << '\n';
			}

		}

		//function allowing an agent to withdraw cash
		void withdraw_cash(agent* B, double amount){
			double trader_cash_init = portfolio[0].value;                              //keep track of initial values
			double account_cash_init = B->accounts[getID].asset[0].value;
			double fin_cash_init = B->portfolio[0].value;
 

			cout << "Agent attempted to withdraw: " << amount << '\n';                 

			if (account_cash_init <= amount) {                              					 //if the agent wants to withdraw more than it has stored
				cout << "Insufficient funds" << '\n';                      							 //restrict it from going into the negative
				portfolio[0].value = trader_cash_init;
				B->accounts[getID].asset[0].value = account_cash_init;
				B->portfolio[0].value = fin_cash_init;
			}
			else{
				portfolio[0].value = trader_cash_init + amount;           						   //add amount withdrawn to agent wealth
				B->accounts[getID].asset[0].value = account_cash_init - amount;          //subtract withdrawn amount from agent's account
				B->portfolio[0].value = fin_cash_init - amount;                          //and from financial intermediary's portfolio

				cout << "Agent withdrew: " << amount << '\n';
			}
		}
};

class financial_intermediary: public agent {
	public:
		financial_intermediary(int id) : agent(id) {}

		//create new account
		void createAccount(agent* A) {                                  
			account b;
			b.ID = A->getID;																							//assign ID
		
			for (int i = 0; i < assets.size(); i++){
				b.asset.push_back(A->portfolio[i]);                         //add asset to portfolio
				b.asset[i].type = A->portfolio[i].type;                     //and assign types
				b.asset[i].ID = A->portfolio[i].ID;
				b.asset[i].title = A->portfolio[i].title;
				b.asset[i].value = 0;
			}          
			                                     
			accounts.push_back(b);                                        //add account to list of accounts
		}

		void createPortfolio() {
			double val = 0;

			for (int i = 0; i < assets.size(); i++){                      //assign values to the portfolio

				portfolio[i].type = "financial intermediary";
				portfolio[i].ID = ID;
				portfolio[i].title = assets[i];
				if (!accounts.empty()){
					for (int j = 0; j < accounts.size(); j++) {
					val = val + accounts[j].asset[i].value;
					}
				portfolio[i].value = val;
				}
				else {
					portfolio[i].value = 0;
				}
			}
		}
}; 
