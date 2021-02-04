#include <iostream>
#include <fstream>
#include"lib.h"
using namespace std;
int main(){
	int left,top,size,loaded=0;
	int is_win_x=0,is_win_o=0;
	int row,col,moveNumber=0;
	int path[MAX][MAX]={0};
	char turn='x',selection,grid[MAX][MAX];
	string file_name="",info;
	cout<< "Please Enter the Board Size: ";
	while(1){
		cin>> size;
		if(size>5 && size<13)
			break;
		else
			cerr<< "Please Enter a Number Between 6 and 12\n";
	}
	fill_the_grid(size,grid);
	print_the_grid(size,grid);
	cout<< "Please Make a selection\n"
		<< "a) Two Player Game?\n"
		<< "b) Player vs Computer?\n";
		cin>> selection;
	while(1){
		if(selection=='a'){
			while(1){
				cout<<"----------------------------------------------\n";
				if(turn=='x'){
					player_x(size,grid,selection,loaded,file_name);								//player x plays.
					if(loaded==0){
						turn='o';
					}
					if(loaded==1){								// if user enters load, program loads by the process below.
						ifstream myfile(file_name);				// it is also same process for the other movements.
						if (myfile.is_open()){
							getline(myfile,info);
							selection=info[2];					//is it againt ai or user
							turn=info[0];						// whose turn
							myfile.close();				
						}
						loaded=0;
						break;				
					}
				}
				print_the_grid(size,grid);									//prints the grid after player x played.
				left=first_x(grid,path,size);								//first_x function tries to find the first element of x in 0th column.
				if(find_path_x(grid,path,size,left,0,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
					is_win_x=1;
					convert2upper_case(grid,path,size,1);					//makes the correct paths uppercase.
					break;
				}
				cout<<"----------------------------------------------\n";
				if(turn=='o'){
					player_o(size,grid,selection,loaded,file_name);										//player o plays.
					if(loaded==0){
						turn='x';
					}
					if(loaded==1){
						ifstream myfile(file_name);
						if (myfile.is_open()){
							getline(myfile,info);
							selection=info[2];
							turn=info[0];
							myfile.close();				
						}
						loaded=0;
						break;
					}				
				}
				print_the_grid(size,grid);									//prints the grid after player o played.
				top=first_o(grid,path,size);								//first_o function tries to find the first element of o in 0th row.
				if(find_path_o(grid,path,size,0,top,0)==1){					//by starting the first element of o's, backtracking algorithm is used.
					is_win_o=1;
					convert2upper_case(grid,path,size,2);					//makes the correct paths uppercase.
					break;
				}
			}
			if(is_win_o==1||is_win_x==1) break;
		}
		else if (selection=='b'){
			while(1){
				cout<<"----------------------------------------------\n";
				print_the_grid(size,grid);						//prints the grid.
				player_x(size,grid,selection,loaded,file_name);								//player x plays.
					if(loaded==1){
						ifstream myfile(file_name);
						if (myfile.is_open()){
							getline(myfile,info);
							selection=info[2];
							turn=info[0];
							myfile.close();				
						}
						loaded=0;
						break;				
					}
				cout<<"----------------------------------------------\n";
				if(moveNumber==0){	
					col=random_generator(size);							//this statements for the first move of AI. it is randomly chosen in row 0.
					row=0;
					moveNumber++;										//to express that other moves will not be the first move of AI
				}
				else{
					if(grid[row+1][col]==empty) row=row+1;											//if AI'last position's down is empty it follows down. if not;
					else if(grid[row+1][col-1]==empty && col-1<size &&col-1>=0) row=row+1,col=col-1;	//if AI's last position's left-down is empty it follows that path. if not;
					else if(grid[row][col+1]==empty&&col+1<size&&col>0) col=col+1;					//
					else if(grid[row][col-1]==empty&& col-1<size&&col-1>=0) col=col-1;				// AI' path chosing algortihm by checking available coordinates.
					else if(grid[row-1][col+1]==empty&& col+1<size) row=row-1,col=col+1;				//
					else if(grid[row-1][col]==empty&& row<=0) row=row-1;
					else{
						col=random_generator(size);													//if all around the last position is full, AI assigns another random position.
						row=0;
					}
				}

				player_ai(size,grid,row,col);					//makes AI's move according to the incoming coordinates.
				//print_the_grid(size,grid);						//prints the grid.
				top=first_o(grid,path,size);					//first_o function tries to find the first element of AI in 0th row.
				if(find_path_o(grid,path,size,0,top,0)==1){
					is_win_o=1;
					convert2upper_case(grid,path,size,2);
					break;
				}
			}
			if(is_win_o==1||is_win_x==1) break;
		}
		else
			cerr<< "Try Again\n";	
	}
	cout<<"**********************************************\n";
	if(is_win_o==1) cout<<"~~~~~~~~~~'O' WON THE GAME~~~~~~~~~~\n";
	if(is_win_x==1) cout<<"~~~~~~~~~~'X' WON THE GAME~~~~~~~~~~\n";
	print_the_grid(size,grid);
	cout<<"**********************************************\n";
}
