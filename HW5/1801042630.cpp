#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>
#include<random>
#include<deque>
#include"AbstractHex.h"
#include"HexVector.h"
#include"HexAdapter.h"
#include"HexAdapter.cpp"
#include"Array.h"

using namespace std;

bool isValid(AbstractHex* abs,int size);	//the implementation is below tha main function.
int main(){
	vector<AbstractHex*> game;
	
	int gameSelection,menuSelection,compareSelection;
	int SelectData=0;
	while(SelectData!=1&&SelectData!=2&&SelectData!=3&&SelectData!=4){
		cout<<"Choose a Data Structure to play"<<endl
			<<"1) HexVector "<<endl
			<<"2) HexAdapter<vector>"<<endl
			<<"3) HexAdapter<deque>"<<endl
			<<"4) HexArray1D"<<endl;
		cin>>SelectData;
		if(SelectData==1){
			for(int i=1;i<7;i++){
				game.push_back(new HexVector);
			}
		}
		else if(SelectData==2){
			for(int i=1;i<7;i++){
				game.push_back(new HexAdapter<vector>);
			}
		}
		else if(SelectData==3){
			for(int i=1;i<7;i++){
				game.push_back(new HexAdapter<deque>);
			}
		}
		else if(SelectData==4){
			for(int i=1;i<7;i++){
				game.push_back(new HexArray);
			}
		}
		else
			cerr<<"Try Again!"<<endl;
	}
	while(1){
		cout<<endl
			<<"1) New Game"<<endl<<"2) Select a Game"<<endl<<"3) Test () Overloading"<<endl<<"4) Show the Last Move of Selected Game"<<endl
			<<"5) Show the Number of Moves of the Selected Game"<<endl<<"6) Check the Games are Equal or Not(Test == Overloading)"<<endl
			<<"7) Reset the Selected Game"<<endl<<"8) Exit"<<endl;
		cin>>menuSelection;
		if(menuSelection==1){
			cout<<"Please enter the game number which you want to play [1-5]: ";
			cin>>gameSelection;
			game[gameSelection]->playGame();
		}
		else if(menuSelection==2){
			cout<<"Please enter the game number which you want to continue [1-5]: ";
			cin>>gameSelection;
			game[gameSelection]->continuedGame();
		}
		else if(menuSelection==3){
			int tempRow,tempCol;
			try{
				cout<<"Please enter the game number which you want to check () overloading [1-5]: ";
				cin>>gameSelection;
				cout<<"Please enter the row and column number which you want to see the type: "<<endl;
				cin>>tempRow>>tempCol;
				cout<<"The selected type:\t"<<(char)(*game[gameSelection])(tempRow-1,tempCol-1).getType()<<endl;
			}
			catch(outOfRange){
				cout<<"Out of range error.Try Again.(coded with exception handling)\n";
			}
		}
		else if(menuSelection==4){
			try{
				cout<<"Please enter the game number which you want to see the last move [1-5]: ";
				cin>>gameSelection;
				game[gameSelection]->lastMove();
			}
			catch(noLastMove){
				cout<<"No Last Move.Try Again.(coded with exception handling)\n";
			}
		}
		else if(menuSelection==5){
				cout<<"Please enter the game number which you want to see the number of moves [1-5]: ";
				cin>>gameSelection;
				cout<<"\nNumber of Moves: ";
				cout<<game[gameSelection]->numberOfMoves()<<endl;
		}
		else if(menuSelection==6){
				cout<<"Please enter 2 game numbers which you want to compare [1-5]: \n";
				cin>>gameSelection>>compareSelection;
				if(game[gameSelection]==game[compareSelection]){
					cout<<"The chosen boards are equal.\n";
				}
				else{
					cout<<"The chosen boards are not equal.\n";
				}	
		}
		else if(menuSelection==7){
			cout<<"Please enter the game number which you want to reset [1-5]: ";
			cin>>gameSelection;
			game[gameSelection]->reset();
		}
		else if(menuSelection==8){
			cout<<"\n~~~Leaving the Game~~~\n\n\n";
			break;
		}
	}
	return 0;
}

bool isValid(AbstractHex* abs,int& size){		//this global functions must be checking that if a game is valid or not
	for(int i=0;i<abs->getSize();i++){			//but i dont know how and where to use it :))
		for(int j=0;j<abs->getSize();j++){
			if((*abs)(i,j).getType()!=player1&&(*abs)(i,j).getType()!=player2&&(*abs)(i,j).getType()!=empty) return false;
		}
	}
}
