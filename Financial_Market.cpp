#include <iostream>

using namespace std;

//In this program, we will model a financial market

class agent {                                      //creates agent capable of possessing and trading assets
		double wealth;                                 
	public:
		agent(double x) : wealth(x){}                  //so far just has one public variable denoting total value of all assets
		//double networth() { return wealth;}
		double networth = wealth;                      //return wealth

};

class financial_intermediary {                     //creates an agent capable of possessing and trading assets, will also serve as a storage node
		double wealth;                                 //with more abilities down the line
	public:
		financial_intermediary(double x) : wealth(x){}
		double networth = wealth;

};

void deposit(agent& A, financial_intermediary& B, double amount){       //function allowing an agent to deposit cash
	double agent_wealth_init = A.networth;
	double fin_wealth_init = B.networth;

	A.networth = agent_wealth_init - amount;
	B.networth = fin_wealth_init + amount;

}

void withdraw(agent& A, financial_intermediary& B, double amount){      //function allowing an agent to deposit cash
	double agent_wealth_init = A.networth;
	double fin_wealth_init = B.networth;

	A.networth = agent_wealth_init + amount;
	B.networth = fin_wealth_init - amount;

}

int main(){                                                             //tests for me

	agent spender(3.0);
	financial_intermediary bank(30000.0);

	cout << spender.networth << '\n';
	cout << spender.networth + 20 << '\n';
	cout << bank.networth << '\n';

	deposit(spender, bank, 1);

	cout << spender.networth << '\n';
	cout << bank.networth << '\n';

	withdraw(spender, bank, 1);

	cout << spender.networth << '\n';
	cout << bank.networth << '\n';




	return 0;
}