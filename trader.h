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
		void createPortfolio() {
			for (int j = 0; j < assets.size(); j++){       //assign values to the portfolio
				portfolio[j].type = "node";
				portfolio[j].ID = ID;
				portfolio[j].title = assets[j];
				portfolio[j].value = utils::dRand(0.0,1.0) % 100;
				wealth += 
			}
		}
		/**
		 * return total value of all assets held by trader
		 * @return total networth.
		 */
		double calculateNetworth() {                              //return total value of all assets held by trader
			wealth = 0;
			for (int i = 0; i < assets.size(); i++){
				if (getID == portfolio[i].ID){
					wealth += portfolio[i].value;
				}
			}
			return wealth;
		}
		//function allowing an agent to deposit cash
		void depositCash(agent* B, double amount){
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
		void withdrawCash(agent* B, double amount){
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