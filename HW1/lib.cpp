//Mehmet Avni ÇELİK/1801042630
#include <iostream>
#include <chrono>
#include <random>
#include"lib.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
void fill_the_grid(int size,char grid[MAX][MAX]){
	int i,j;
	char c = 'a';

	for(i=0;i<size;i++){		//this loop fills the array with points
		for(j=0;j<size;j++){
			grid[i][j]='.';
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void print_the_grid(int size,char grid[MAX][MAX]){
	int i,j,k;
	char c = 'a';
	
	for(i=0;i<size;i++){		//this loop prints the column letters.
		cout<<"  "<<c<<" ";
		c++;
	}
	cout<<"\n";
	for(i=0;i<size;i++){		//this loop prints the game board
		cout<<i+1<<" ";			//this statement prints the row numbers.
		for(j=0;j<i;j++){
			cout<<"  ";
		}
		for(k=0;k<size;k++){
			cout<<grid[i][k]<<"   ";
		}
		cout<<"\n";
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void player_x(int size, char grid[MAX][MAX]){
	char colC;
	int row,col;
	
	cout<<"Player A (x) \nPlease Pick a Cell (Example: C5)\n";					//gets inputs for player x
	while(1){
		cin>>colC>>row;
		col=colC-65;
		row=row-1;
		if(row<size && row>-1 && col<size && col >-1 && grid[row][col]=='.'){
			grid[row][col]='x';
			break;
		}
		else
			cout<< "Invalid Selection. Please Try Again\n";
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void player_o(int size, char grid[MAX][MAX]){	
	char colC;
	int row,col;
	
	cout<<"Player B (o) \nPlease Pick a Cell (Example: C5)\n";			//gets input for player o
	while(1){
		cin>>colC>>row;
		col=colC-65;
		row=row-1;
		if(row<size && row>-1 && col<size && col >-1 && grid[row][col]=='.'){
			grid[row][col]='o';
			break;
		}
		else
			cout<< "Invalid Selection. Please Try Again\n";
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void player_ai(int size, char grid[MAX][MAX],int row,int col){
	
	cout<<"Player B (o) \nPlease Pick a Cell (Example: C5)\n";
	while(1){
		if(grid[row][col]=='.'){							//it checks AI's incoming coordinates.
			grid[row][col]='o';
			break;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
int first_x(char grid[MAX][MAX],int path[MAX][MAX],int size){
	int i;
	for(i=0;i<size;i++){
		if(grid[i][0]=='x'){				//finds the first element of X in the first column
			path[i][0]=1;					//and assign them as 1's to another map which is made up of integers
			break;
		}
	}
	if(path[i][0]==1) return i;
	else return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
int first_o(char grid[MAX][MAX],int path[MAX][MAX],int size){
	int i;
	for(i=0;i<size;i++){
		if(grid[0][i]=='o'){				//finds the first element of X in the first column
			path[0][i]=2;					//and assign them as 2's to another map which is made up of integers
			break;
		}
	}
	if(path[0][i]==2) return i;
	else return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool find_path_x(char grid[MAX][MAX],int path[MAX][MAX],int size,int i,int j,int flag){

	if(j==size){
		path[i][j]==1;							//back tracking algorithm by recursive function.
		return 1;								//the path is followed by seeking 1's on the path map
	}
	if(grid[i][j]=='x'){
		path[i][j]=1;							//assigns 1 to the x parts of map.
		if(flag!=6&&path[i][j+1]!=1)			if(find_path_x(grid,path,size,i,j+1,1)==1) 		return 1;
		if(flag!=5&&path[i+1][j]!=1)			if(find_path_x(grid,path,size,i+1,j,2)==1) 		return 1;
		if(i>=1 && flag!=4&&path[i-1][j+1]!=1) 	if(find_path_x(grid,path,size,i-1,j+1,3)==1) 	return 1;
		if(j>=1&&flag!=3&&path[i+1][j-1]!=1)	if(find_path_x(grid,path,size,i+1,j-1,4)==1) 	return 1;
		if(i>=1&&flag!=2&&path[i-1][j]!=1)		if(find_path_x(grid,path,size,i-1,j,5)==1) 		return 1;
		if(j>=1&&flag!=1&&path[i][j-1]!=1)		if(find_path_x(grid,path,size,i,j-1,6)==1) 		return 1;
		path[i][j]=0;							//if a path which is followed does not lead to the ending, then all of the path will be 0 again.
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
bool find_path_o(char grid[MAX][MAX],int path[MAX][MAX],int size,int i,int j,int flag){

	if(i==size){
		path[i][j]==2;							//back tracking algorithm by recursive function.
		return 1;								//the path is followed by seeking 2's on the path map
	}
	if(grid[i][j]=='o'){
		path[i][j]=2;							//assigns 2 to the x parts of map.
		if(flag!=6&&path[i][j+1]!=2)			if(find_path_o(grid,path,size,i,j+1,1)==1) 		return 1;
		if(flag!=5&&path[i+1][j]!=2)			if(find_path_o(grid,path,size,i+1,j,2)==1) 		return 1;
		if(i>=1 && flag!=4&&path[i-1][j+1]!=2) 	if(find_path_o(grid,path,size,i-1,j+1,3)==1) 	return 1;
		if(j>=1&&flag!=3&&path[i+1][j-1]!=2)	if(find_path_o(grid,path,size,i+1,j-1,4)==1) 	return 1;
		if(i>=1&&flag!=2&&path[i-1][j]!=2)		if(find_path_o(grid,path,size,i-1,j,5)==1)		return 1;
		if(j>=1&&flag!=1&&path[i][j-1]!=2)		if(find_path_o(grid,path,size,i,j-1,6)==1) 		return 1;
		path[i][j]=0;							//if a path which is followed does not lead to the ending, then all of the path will be 0 again.
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
void convert2upper_case(char grid[MAX][MAX],int path[MAX][MAX],int size,int picked){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(path[i][j]==picked)	grid[i][j]=grid[i][j]-32;    //converts the winner path to the uppercase letters.
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
int random_generator(int size){
	int rand;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator (seed);				//random number generator
	rand=generator()%(size);
	return rand;
}
///////////////////////////////////////////////////////////////////////////////////////////

