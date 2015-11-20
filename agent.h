#include <vector>
#include <string>
#include "utils.h";
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
	//name of asset...not really necessary to include but could come in handy
	string title;
	//claim type
	string type;
	//ID associated with holder
	long int ID;
	//value associated with asset
	double value;
	//for bonds, determines repayment period; for stocks, does not apply
	int period;
} money, stock, bond;

class agent {
	private:
		long int ID;
		double wealth;
	public:
		agent(long int id, double w) : ID(id), wealth(w){}
		agent(long int id) : ID(id){}
		long int getID() {return ID;}

		//array of asset types
		vector<string> assets{"money", "securities", "bonds"};     

		//array same length assets containing info about each asset
		claim portfolio[3];

		//create a portfolio of assets                           
		virtual void createPortfolio(){}

		//function that will return the total value of all assets held by the agent
		virtual double calculateNetworth() {return wealth;}

		//function allowing an agent to deposit cash
		virtual void depositCash(agent* B, double amount){}

		//function allowing an agent to withdraw cash
		virtual void withdrawCash(agent* B, double amount){}    

		//create an account for an agent at hand
		virtual void createAccount(agent* A) {}
};