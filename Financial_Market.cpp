#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include <random>
#include "utlis.h"

class agent;

#include "trader.h"
#include "financial_intermediary.h"

using namespace std;

//In this program, we will model a financial market


//PODs (Possibly fold into class for additional functionality?)

/**
 * Exchange wealth between two agents (know as the lender and lendee)
 * @param lender - the agent giving the wealth
 * @param lendee - the agent recieving the wealth
 */
void borrow_lend(agent* lender, agent* lendee);

/**
 * Better Random number generator
 * @param  fMin Minimum nmuber on the range of possible randomly generated numbers.
 * @param  fMax Maximum number on the range of possible randomly generated numbers.
 * @return      A random number on the range of (fMin, fMax).
 */
double dRand(double fMin, double fMax)         
{
	std::default_random_engine generator;
	std::uniform_real_distributon<double> distribution(fMin, fMax);
	return distribution(generator);
}


int main(){  
	cout.precision(3);                                  //set precision on output values....might need to retool this

	srand(time(NULL));                                  //generate new sequence of random variables for each loop

	int M, N;                                           //number of financial intermediaries, number of nodes, respectively

	cout << "Enter number of financial intermediaries: ";
	cin >> M;

	vector<agent*> fin_int_vec {};                      //placeholder for all financial intermediaries generated below

	cout << "Enter number of agents: ";
	cin >> N;

	vector<agent*> trader_vec {};                       //placeholder for all traders generated below
	
	for (int i = 0; i < M; i++){
		agent * bank = new financial_intermediary(i);     //create new financial intermediary
		fin_int_vec.push_back(bank);                      //add financial intermediary to storage vector
	}

	for (int i = 0; i < N; i++){                    
		agent * node = new trader(i);                     //create new trader
		node->createPortfolio();                          //create trader portfolio
		trader_vec.push_back(node);                       //add trader to storage vector
	}

	for (int i = 0; i < N; i++){
		fin_int_vec[0]->createAccount(trader_vec[i]);     //create account for all nodes interacting with particular financial intermediary
	}                                                   //leaving as separate loop so these values can change

	for (int i = 0; i < fin_int_vec[0]->accounts.size(); i++){             //loop through accounts

		cout << "Account pre-deposit " << fin_int_vec[0]->accounts[i].ID << ' ' << fin_int_vec[0]->accounts[i].value << '\n'; //display account information before deposit
		
		cout << "Portfolio pre-deposit" << '\n';

		for (int j = 0; j < trader_vec[i]->assets.size(); j++){              //loop through portfolio of account at hand
			cout << trader_vec[i]->portfolio[j].type << ' '                    //print out portfolio attribues
			<< trader_vec[i]->portfolio[j].ID << ' ' 
			<< trader_vec[i]->portfolio[j].title << ' ' 
			<< trader_vec[i]->portfolio[j].value << '\n';
		}
		
		trader_vec[i]->deposit_cash(fin_int_vec[0], utils::dRand(0, trader_vec[i]->portfolio[0].value));  //deposit cash into account

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

	for (int i = 0; i < M; i++){
		delete fin_int_vec[i];             //delete all objects
	}

	for (int i = 0; i < N; i++){
		delete trader_vec[i];              //delete all objects
	}
	
	return 0;
}
