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
		vector<account> accounts {};
		/**
		 * Create new account to add to total accounts of financial intermediary
		 * @param newAccount the acconut to be created.
		 */
		void createAccount(agent* newAccount) {
			account temp;
			temp.ID = A->getID();
			temp.value = 0;
			accounts.push_back(temp);
		}
		/**
		 * calculate the networth of the finacial_intermediary
		 * @return [description]
		 */
		double calculateNetworth() {
			wealth = 0;
			//in this case a financial intermediary
			for (int i = 0; i < assets.size(); i++){
				if (getID == accounts[i].ID){
					wealth += accounts[i].value;
				}
			}
			return wealth;
		}
};