#include <iostream>            //probably don't need all of these headers
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include "utils.h"

//class agent;

#include "node.h"

//#include "trader.h"
//#include "financial_intermediary.h"

//using namespace std;           //especially with this guy down here

//In this program, we will model a financial market


int main(){  
	cout.precision(3);                                  //set precision on output values....might need to retool this

	srand(time(NULL));                                  //generate new sequence of random variables for each loop

	//open for business

	vector<agent*> agent_vec {};                        //placeholder for all agents in network
	vector<agent*> fin_int_vec {};                      //placeholder for all financial intermediaries generated below
	vector<agent*> trader_vec {};                       //placeholder for all traders generated below

	int M, N;                                           //number of financial intermediaries, number of nodes, respectively

	cout << "Enter number of financial intermediaries: ";
	cin >> M;

	cout << "Enter number of agents: ";
	cin >> N;

	cout << '\n';
	
	for (int i = 0; i < M; i++){
		agent * bank = new financial_intermediary(i);     //create new financial intermediary
		fin_int_vec.push_back(bank);                      //add financial intermediary to storage vector
		agent_vec.push_back(bank);                        //add financial intermediary to grand storage vector
	}

	for (int i = 0; i < N; i++){                    
		agent * node = new trader(i);                     //create new trader
		node->createPortfolio();                          //create trader portfolio
		trader_vec.push_back(node);                       //add trader to storage vector
		agent_vec.push_back(node);                        //add financial intermediary to grand storage vector
	}

	for (int i = 0; i < N; i++){
		fin_int_vec[0]->createAccount(trader_vec[i]);     //create account for all nodes interacting with particular financial intermediary
	}                                                   //leaving as separate loop so these values can change

/*
	for (int i = 0; i < fin_int_vec[0]->accounts.size(); i++){             //loop through accounts

		cout << "Account pre-deposit " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information before deposit
		
		cout << "Portfolio pre-deposit" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){              //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                    //print out portfolio attribues
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		
		trader_vec[i]->deposit_cash(fin_int_vec[0], dRand(0, trader_vec[i]->portfolio[0].value));  //deposit cash into account

		cout << "Account post-deposit " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information after deposit

		cout << "Portfolio post-deposit" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}

		trader_vec[i]->withdraw_cash(fin_int_vec[0], dRand(0, trader_vec[i]->portfolio[0].value)); //withdraw cash from account

		cout << "Account post-withdrawl " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information after withdrawl
		
		cout << "Portfolio post-withdrawl" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}

		cout << '\n';
		
	}
*/

/*
	cout << "Trader portfolio pre-loan" << '\n' << '\n';

		for(int i = 0; i < 2; i++){
		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		cout << '\n';
	}

	cout << '\n';

	cout << "Trader portfolio pre-loan" << '\n' << '\n';

	trader_vec[0]->borrow(trader_vec[1], 4);
	//trader_vec[0]->lend(trader_vec[1], 4);

	for(int i = 0; i < 2; i++){
		for (int j = 0; j < trader_vec[i]->assets.size(); j++){            //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                  //print out portfolio attributes
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		cout << '\n';
	}

	*/

/*
	for (int i = 0; i < fin_int_vec.size(); i++){
		cout << fin_int_vec[i]->networth() << '\n';
	}

	cout << '\n';

	for (int i = 0; i < trader_vec.size(); i++){
		cout << trader_vec[i]->networth() << '\n';
	}

	cout << '\n';

	for (int i = 0; i < agent_vec.size(); i++){
		cout << agent_vec[i]->networth() << '\n';
	}

	cout << '\n';

	cout << money_supply(agent_vec) << '\n';
*/

	cout << '\n';

	cout << "More to come, stay tuned." << '\n' << '\n';

	//close up shop

	for (int i = 0; i < agent_vec.size(); i++){
		delete agent_vec[i];
	}

	agent_vec.clear(); 
	fin_int_vec.clear(); 
	trader_vec.clear();

	return 0;
	
}
