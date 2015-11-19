#include "agent.h"
///////////////////////////
//financial_intermediary //
///////////////////////////
/**
 * creates an agent capable of possessing and trading assets, will also serve as a storage node
 */
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