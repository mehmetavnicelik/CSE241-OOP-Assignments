#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>
#include<random>
#include"lib.h"

using namespace std;

int main(){
	Hex game[6];
	int gameSelection,menuSelection,compareSelection;
	while(1){
		cout<<"\n1) New Game\n2) Select a Game\n3) Compare 2 Game\n4) See the Amount of All Marked Cells\n"
			<<"5) is Equal?(== overloading)\n6) See the Score of Selected Game\n7) Exit\n";
		cin>>menuSelection;
		if(menuSelection==1){
			cout<<"Please enter the game number which you want to play [1-5]: ";
			cin>>gameSelection;
			game[gameSelection].playGame();
		}
		else if(menuSelection==2){
			cout<<"Please enter the game number which you want to continue [1-5]: ";
			cin>>gameSelection;
			game[gameSelection].continuedGame();
		}
		else if(menuSelection==3){
			cout<<"Please enter the game numbers which you want to compare [1-5]:\n";
			cout<<"First Number:";
			cin>>gameSelection;
			cout<<"Second Number:";
			cin>>compareSelection;
			cout<<"('1' means first game has more marked celss. '0' means other)\n"<<game[gameSelection].compare(game[compareSelection])<<"\n";
		}
		else if(menuSelection==4){
			cout<<"The amount of all the marked cells: "<<game[0].getAllMarked()-1<<"\n"; 
		}
		else if(menuSelection==5){
			cout<<"Please enter the game numbers which you want to know the equality [1-5]:\n";
			cout<<"First Game:";
			cin>>gameSelection;
			cout<<"Second Game:";
			cin>>compareSelection;
			if(game[gameSelection]==game[compareSelection]){
				cout<<"There are SAME Amount of Marked Cells.\n";
			}
			else{
				cout<<"There are DIFFERENT Amount of Marked Cells.\n";
			}
		}
		else if(menuSelection==6){
			cout<<"Please enter the game numbers which you want to know the score [1-5]:\n";
			cin>>gameSelection;
			game[gameSelection].userScore();
			cout<<"Efficient move of X:  "<<game[gameSelection].getScore()<<endl;
			cout<<"Efficient move of ai: "<<game[gameSelection].get_ai_score()<<endl;
			if(game[gameSelection].getScore()>game[gameSelection].get_ai_score()){
				cout<<"User is in a better position. USER POINT: 50"<<endl;
			}
			if(game[gameSelection].getScore()==game[gameSelection].get_ai_score()){
				cout<<"DRAW!! Score is 0 for now."<<endl;
			}
			else if(game[gameSelection].get_is_winx()==gameSelection){
				cout<<"User won the game. USER POINT: 100"<<endl;
			}
			else{
				cout<<"AI is in a better position. AI POINT: 50"<<endl;
			}
		}
		else if(menuSelection==7){
			cout<<"\n~~~Leaving the Game~~~\n\n\n";
			break;
		}
	}
	return 0;
}