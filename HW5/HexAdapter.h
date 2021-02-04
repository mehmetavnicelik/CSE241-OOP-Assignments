#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>
#include<random>
#include<deque>
#include"AbstractHex.h"
#include"HexVector.h"
#pragma once

template<template<typename...> class T>
class HexAdapter :public AbstractHex{
public:
	void createBoard() 						override;
	bool operator ==(AbstractHex& game2)	override;
	Cell operator ()(int r,int c) 			override;
	void lastMove() 						override;
	inline int getSize() 					override{return size;}	//returns the board's size.
	inline int numberOfMoves() 				override{return markedCell4Board_Template;}
	void reset()							override;
	inline HexAdapter()						{size=6; selection=1; createBoard();}
	inline HexAdapter(int tempSize)			{size=tempSize; selection=1; createBoard();}
	inline HexAdapter(int tempSize,int againstWho)	{size=tempSize; selection=againstWho; createBoard();}
	inline void setCompareMarked() {compareMarked++;}						//increase the marked cells for each game seperately.
	inline int getCompareMarked() const {return compareMarked;}			//keeps the marked cells for each game seperately.
	void playGame();
	void continuedGame();
	bool compare(HexAdapter<T>& other)const;
	inline void increaseMarkedCell4Board() {markedCell4Board_Template++;}	

private:
	T <T<Cell>> hexCells;
	void resizeBoard(T <T<Cell>> hexCells);
	void printBoard();
	string last_word(string& str)const ;							//finds the file name that is going to be saved.
	void saving(const string& file_name,int againstWho,int selection);		//save the game to the file.
	void loading(const string& file_name,int whoseTurn, int aganistWho);	//load a game from the file.
	bool isEnded();													//checks the game is ended or still continues.	
	int randomGenerator();											//generates random number for computer player.
	void convert2upper_case(int picked);									//makes the winning path uppercase.
	void player_x();														//makes move for player-x.Also play function is in this function too.		
	void player_o();														//makes move for player-o.Also play function is in this function too.
	void play();															//plays for AI.
	void play(int row,int col,enumType who);								//makes an assignment to hexCells indexes.
	int first_x();															//finds the first index of x.															
	int first_o();															//finds the first index of o.
	bool find_path_x(int i,int j,int flag);									//follows the winning path for x.
	bool find_path_o(int i,int j,int flag);									//follows the winning path for o.			
	inline string getFileName()	{return file_name;}							//returns files name to save the game.
	int selection,flag=0,callMenu;
	int left,top,loaded=0;
	int is_win_x=0,is_win_o=0;
	int row,col,moveNumber=0;
	int rowAI,colAI;
	int size;
	int path[26][26]={{0}};
	int turn=1;
	int compareMarked=0;
	string file_name="",info,str,line;
	int markedCell4Board_Template=0;
};