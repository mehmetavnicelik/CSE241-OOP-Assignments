#include <iostream>
#include"lib.h"
using namespace std;

int main(){
	int left,top,size;
	int is_win_x=0,is_win_o=0;
	int row,col,moveNumber=0;
	int path[MAX][MAX]={0};
	char selection,grid[MAX][MAX];
	cout<< "Please Enter the Board Size: ";
	while(1){
		cin>> size;
		if(size>5 && size<13)
			break;
		else
			cout<< "Please Enter a Number Between 6 and 12\n";
	}
	fill_the_grid(size,grid);
	print_the_grid(size,grid);
	cout<< "Please Make a selection\n"
		<< "a) Two Player Game?\n"
		<< "b) Player vs Computer?\n";
	while(1){
		cin>> selection;
		if(selection=='a'){
			while(1){
				cout<<"----------------------------------------------\n";
				player_x(size,grid);										//player x plays.
				print_the_grid(size,grid);									//prints the grid after player x played.
				left=first_x(grid,path,size);								//first_x function tries to find the first element of x in 0th column.
				if(find_path_x(grid,path,size,left,0,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
					is_win_x=1;
					convert2upper_case(grid,path,size,1);					//makes the correct paths uppercase.
					break;
				}
				cout<<"----------------------------------------------\n";
				player_o(size,grid);										//player o plays.
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
				player_x(size,grid);
				print_the_grid(size,grid);
				left=first_x(grid,path,size);								//same with the algorihm above for player x
				if(find_path_x(grid,path,size,left,0,0)==1){
					is_win_x=1;
					convert2upper_case(grid,path,size,1);
					break;
				}
				cout<<"----------------------------------------------\n";
				if(moveNumber==0){	
					col=random_generator(size);							//this statements for the first move of AI. it is randomly chosen in row 0.
					row=0;
					moveNumber++;										//to express that other moves will not be the first move of AI
				}
				else{
					if(grid[row+1][col]=='.') row=row+1;											//if AI'last position's down is empty it follows down. if not;
					else if(grid[row+1][col-1]=='.'&& col-1<size &&col-1>=0) row=row+1,col=col-1;	//if AI's last position's left-down is empty it follows that path. if not;
					else if(grid[row][col+1]=='.'&&col+1<size&&col>0) col=col+1;					//
					else if(grid[row][col-1]=='.'&& col-1<size&&col-1>=0) col=col-1;				// AI' path chosing algortihm by checking available coordinates.
					else if(grid[row-1][col+1]=='.'&& col+1<size) row=row-1,col=col+1;				//
					else if(grid[row-1][col]=='.'&& row<=0) row=row-1;
					else{
						col=random_generator(size);													//if all around the last position is full, AI assigns another random position.
						row=0;
					}
				}

				player_ai(size,grid,row,col);					//makes AI's move according to the incoming coordinates.
				print_the_grid(size,grid);						//prints the grid.
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
			cout<< "Try Again\n";	
	}
	cout<<"**********************************************\n";
	if(is_win_o==1) cout<<"~~~~~~~~~~'O' WON THE GAME~~~~~~~~~~\n";
	if(is_win_x==1) cout<<"~~~~~~~~~~'X' WON THE GAME~~~~~~~~~~\n";
	print_the_grid(size,grid);
	cout<<"**********************************************\n";
}
