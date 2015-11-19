#include <vector>
#include <string>
////////////
//agent.h //
////////////
/**
 * creates agent capable of possessing and trading assets
 */

class agent {                                      
	private:                                       
		long int ID;
		double wealth;                                 
	public:
		agent(long int id, double w) : ID(id), wealth(w){}
		agent(long int id) : ID(id){}
		long int getID() {return ID;}
		vector<string> assets{"money", "securities", "bonds"};       //array of asset types
		
		claim portfolio[3];                                          //array same length assets containing info about each asset
		virtual void createPortfolio(){}                             //create a portfolio of assets    

		virtual double networth() {}                        				//function that will return the total value of all assets held by the agent
		virtual void deposit_cash(agent* B, double amount){}       //function allowing an agent to deposit cash
		virtual void withdraw_cash(agent* B, double amount){}      //function allowing an agent to withdraw cash

		//if financial intermediary
		vector<account> accounts {};                               //vector of accounts held by financial intermediary
		virtual void createAccount(agent* A) {}                     //create an account for an agent at hand


};