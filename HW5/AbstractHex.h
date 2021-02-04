#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>
#include<random>
enum enumType{
	player1 = 'x',
	player1w = 'X',
	player2 = 'o',
	player2w = 'O',
	//computer= 'o',
	empty = '.'
};
#pragma once
using namespace std;
class outOfRange{};		//Exception Class
class noLastMove{};		//Exception Class

class AbstractHex{					//abstract class. you can not create this kind of objects
	protected:
		class Cell{
			public:
				inline enumType getType(){return type;}
				int getRow(){return row;}
				int getCol(){return column;}
				inline void setType(enumType player){type=player;}
				void setRow(int rowInput);
				void setCol(int colInput);																
			private:
				enumType type;
				int row;
				int column;
		};
		int lastRow=-1;
		int lastCol=-1;
	public:
		//pure virtual functions.those are implemented in the derived classın implementation files.
		virtual void playGame()=0;
		virtual void reset()=0;
		virtual void continuedGame()=0;
		virtual void createBoard()=0;						//PURE VIRTUAL FUNCTION
		virtual bool operator ==(AbstractHex& game2)=0;		//operator overloading for checking the equality.
		virtual Cell operator ()(int r,int c)=0;			//operrator overloading	for checking the type
		virtual void lastMove()=0;							//this functions shows the last played room.
		virtual int getSize()=0;
		virtual int numberOfMoves()=0;
		inline int getLastRow(){return lastRow;}			//if it is -1 it throws noLastMove exception
};