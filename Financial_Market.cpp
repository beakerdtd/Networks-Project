#include <iostream>            //probably don't need all of these headers
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <string>
#include "utils.h"

#include "node.h"

//In this program, we will model a financial market


int main(){  

	//cout.precision(3);                                  //set precision on output values....might need to retool this

	srand(time(NULL));                                  //generate new sequence of random variables for each loop

	//open for business

	vector<agent*> agent_vec {};                        //placeholder for all agents in network
	vector<agent*> fin_int_vec {};                      //placeholder for all financial intermediaries generated below
	vector<agent*> trader_vec {};                       //placeholder for all traders generated below

	int M, N;                                           //number of financial intermediaries, number of nodes, respectively

	cout << "Enter number of financial intermediaries: ";
	cin >> M;

	cout << "Enter number of traders: ";
	cin >> N;

	cout << '\n';
	
	for (int i = 0; i < M; i++){
		agent * bank = new financial_intermediary(i);     //create new financial intermediary
		bank->createPortfolio();                          //create financial intermediary portfolio
		fin_int_vec.push_back(bank);                      //add financial intermediary to storage vector
		agent_vec.push_back(bank);                        //add financial intermediary to grand storage vector
	}

	for (int i = 0; i < N; i++){                    
		agent * node = new trader(i);                     //create new trader
		node->createPortfolio();                          //create trader portfolio
		trader_vec.push_back(node);                       //add trader to storage vector
		agent_vec.push_back(node);                        //add financial intermediary to grand storage vector
	}

	if(M>0){
		for (int i = 0; i < N; i++){
			fin_int_vec[0]->createAccount(trader_vec[i]);     //create account for all nodes interacting with particular financial intermediary
		}    
	}                                               //leaving as separate loop so these values can change


	//create adjacency matrix for network
	int adj_mat[agent_vec.size()][agent_vec.size()];           //create NxN matrix, where N is the total number of agents in network 

	for (int i = 0; i<agent_vec.size(); i++){
		for (int j = 0; j<agent_vec.size(); j++){
			adj_mat[i][j] = rand() % 2;                            //randomly assign each component as 0 or 1
			//cout << adj_mat[i][j] << ' ';
		}
		//cout << '\n';
	}

	cout << '\n';

	for (int i = 0; i<agent_vec.size(); i++){
		for (int j = 0; j<agent_vec.size(); j++){
			adj_mat[j][i] = adj_mat[i][j];                         //make matrix symetric
			adj_mat[i][i] = 0;                                     //set diagonal to zerpo (set trace to zero)
			//cout << adj_mat[i][j] << ' ';
		}
		//cout << '\n';
	}

	cout << '\n';

	int number_of_functions = 4;                         //number of inter-agent functions

	int roll;

	for (int i = 0; i < agent_vec.size()-1; i ++){   //start from top and go all the way to second to last row (last component = 0)         
		for (int j = i+1; j < agent_vec.size(); j++){  //start from second column and go all the way to the end (first component = 0)  
			if(adj_mat[i][j] == 1){
				roll = rand() % number_of_functions;
				switch (roll)
					{
					  case 1:
					     trader_vec[i]->borrow(trader_vec[j], dRand(0, 100));
					     cout << '\n';
					     break;
					  case 2:
					     trader_vec[i]->lend(trader_vec[j], dRand(0, 100));
					     cout << '\n';
					     break;
					   case 3:
					     trader_vec[i]->trade(trader_vec[i]->portfolio[rand()%3].title, 
					     	trader_vec[j], trader_vec[j]->portfolio[rand()%3].title, dRand(0, 100));
					     cout << '\n';
					     break;
					  default:
					     trader_vec[i]->null_interaction(trader_vec[j]);
					     cout << '\n';
					     break;
					}
			}
		}
	}

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
