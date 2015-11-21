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

		//return total value of all assets held by trader
		double wealth() {                              
			double val = 0;
			for (int i = 0; i < assets.size(); i++){
				if (getID == portfolio[i].ID){
					val = val + portfolio[i].value;
				}
			}
			return val;
		}

		//function allowing an agent to deposit cash
		void deposit_cash(agent* B, double amount){
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

		//function allowing an agent to withdraw cash
		void withdraw_cash(agent* B, double amount){
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

		//create new account
		void createAccount(agent* A) {                                  
			account b;
			b.ID = A->getID;																							//assign ID
			b.value = 0;                                                  //assign initial account sum
			accounts.push_back(b);                                        //add account to list of accounts
		}

		//return total value of all assets held by agent
		double wealth() {                                             
			if (!accounts.empty()){
				double val = 0;                                               
				for (int i = 0; i < assets.size(); i++){
					if (getID == accounts[i].ID){
						val = val + accounts[i].value;
					}
				}
				return val;
			}
			else {
				return 0;
			}
		}
}; 
