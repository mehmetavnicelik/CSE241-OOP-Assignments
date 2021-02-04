//Mehmet Avni ÇELİK/1801042630
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include"lib.h"
using namespace std;
//enum part is in the header file.
//all the errors printed in cerr.
//decltype and auto is used for the last_word function
//player_x and player_o has default arguament for error detection.
//const parameter by reference is used for last_word function.
//parameter by reference is used for returning loaded values. Its for checking is the game loaded or not.
///////////////////////////////////////////////////////////////////////////////////////////
void fill_the_grid(int size,char grid[MAX][MAX]){
	int i,j;
	char c = 'a';

	for(i=0;i<size;i++){		//this loop fills the array with points
		for(j=0;j<size;j++){
			grid[i][j]=empty;
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
void player_x(int size, char grid[MAX][MAX],char selection,int& loaded,string& file_name,int flag){
	string str;
	int row,col;
	
	cout<<"Player A (x) \nPlease Pick a Cell (Example: C5)\n";				//gets inputs for player x
	while(1){
		getline(cin,str);
		if(str[0]=='S'&&str[1]=='A'&&str[2]=='V'&&str[3]=='E'){
			file_name=last_word(str);
			saving(grid,file_name,'x',selection,size);
		}
		else if(str[0]=='L'&&str[1]=='O'&&str[2]=='A'&&str[3]=='D'){
			file_name=last_word(str);
			loading(grid,file_name,size,'o',selection);				//seelction is for = the game is against user or computer
			print_the_grid(size,grid);
			loaded=1;												
			break;
		}
		else{		
			col=str[0]-65;
			if(str[3]>='0'&&str[3]<='9'){
				row=(((str[2]-48)*10)+(str[3]-48)-1);				//string conversion
			}
			else
				row=str[2]-49;
			if(row<size && row>-1 && col<size && col >-1 && grid[row][col]==empty){
				grid[row][col]=gamer1;
				break;
			}
			else if(flag!=0){
				cerr<< "Invalid Selection. Please Try Again\n";
				flag=1;
			}
			else
				flag=1;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void player_o(int size, char grid[MAX][MAX],char selection,int& loaded,string& file_name, int flag){	
	string str;
	int row,col;
	
	cout<<"Player B (o) \nPlease Pick a Cell (Example: C5)\n";				//gets inputs for player x
	while(1){
		getline(cin,str);
		if(str[0]=='S'&&str[1]=='A'&&str[2]=='V'&&str[3]=='E'){
			file_name=last_word(str);
			saving(grid,file_name,'o',selection,size);					//seelction is for = the game is against user or computer
		}
		else if(str[0]=='L'&&str[1]=='O'&&str[2]=='A'&&str[3]=='D'){
			file_name=last_word(str);
			loading(grid,file_name,size,'x',selection);
			loaded=1;
			print_the_grid(size,grid);
			break;
		}
		else{		
			col=str[0]-65;
			if(str[3]>='0'&&str[3]<='9'){
				row=(((str[2]-48)*10)+(str[3]-48)-1);				//string conversion
			}
			else
				row=str[2]-49;
			if(row<size && row>-1 && col<size && col >-1 && grid[row][col]==empty){
				grid[row][col]=gamer2;
				break;
			}
			else if(flag!=0){
				cerr<< "Invalid Selection. Please Try Again\n";
				flag=1;
			}
			else
				flag=1;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void player_ai(int size, char grid[MAX][MAX],int row,int col){
	
	cout<<"Player B (o) \nPlease Pick a Cell (Example: C5)\n";
	while(1){
		if(grid[row][col]==empty){							//it checks AI's incoming coordinates.
			grid[row][col]=gamer2;
			break;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
int first_x(char grid[MAX][MAX],int path[MAX][MAX],int size){
	int i;
	for(i=0;i<size;i++){
		if(grid[i][0]==gamer1){				//finds the first element of X in the first column
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
		if(grid[0][i]==gamer2){				//finds the first element of X in the first column
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
	if(grid[i][j]==gamer1){
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
	if(grid[i][j]==gamer2){
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
void saving(char grid[MAX][MAX], std::string& file_name,char whoseTurn, char againstWho,int size){
	ofstream myfile;
	myfile.open(file_name);
	myfile<<whoseTurn<<" " <<againstWho<<" "<<size<<"\n";		//first line of the file will be the "turn","against who" and "size"
	for(int i=0;i<MAX;i++){
		int k=0;
		while(k!=i){
			myfile<<" ";						//this funnction saves the game to the entered file.
			k++;
		}	
		for(int j=0;j<MAX;j++){
			myfile << grid[i][j];	
		}
		myfile << "\n";
	}
	myfile.close();
}
///////////////////////////////////////////////////////////////////////////////////////////
void loading(char grid[MAX][MAX], std::string& file_name,int size,char whoseTurn, char aganistWho){
	int i,row=0,col=0;
	string line;
	ifstream myfile(file_name);
	if (myfile.is_open()){
		getline(myfile,line);
	    while(getline(myfile,line)){
	    	whoseTurn=line[0];
	    	i=0;
	      	while(line[i]==' '){
	      		i++;											//loads the entered file to the game 
	      	}
	      	for(int j=0;j<size;j++){
	      		grid[row][col]=line[i];
	      		i++;
	      		col++;
	      	}
	      	row++;
	      	col=0;
	    }
	   	myfile.close();
	}
  	else
  		cerr << "The file is not able to open."; 
}
///////////////////////////////////////////////////////////////////////////////////////////
string last_word(const std::string& str){
    auto l = str.length();							//auto and dcltype
    decltype(l) i=l-1;
    while (i >= 0&&str[i]!=' '){
        i--;
    }
    string last_word;						//finds the last word of entered string
    for (int j = i + 1; j < l; j++){
        last_word += str[j];
    }
    return last_word;
}

///////////////////////////////////////////////////////////////////////////////////////////