#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <chrono>
#include <random>

enum enumType{
	player1 = 'x',
	player1w = 'X',
	player2 = 'o',
	player2w = 'O',
	//computer= 'o',
	empty = '.'
};
using namespace std;

class Hex{
	private:
		class Cell{
			public:
				inline enumType getType(){return type;}
				int getRow();
				int getCol();
				inline void setType(enumType player){type=player;}
				void setRow(int rowInput);
				void setCol(int colInput);
			private:
				enumType type;
				int row;
				int column;
		};
		inline int getSize() 		{return size;}								//returns the board's size.
		inline string getFileName()	{return file_name;}							//returns files name to save the game.
		inline void setCompareMarked() {compareMarked++;}						//increase the marked cells for each game seperately.
		inline int getCompareMarked() const { return compareMarked;}			//keeps the marked cells for each game seperately.
		void player_x();														//makes move for player-x.Also play function is in this function too.		
		void player_o();														//makes move for player-o.Also play function is in this function too.
		void play();															//plays for AI.
		void printBoard();														//prints the board.
		void convert2upper_case(int picked);									//makes the winning path uppercase.
		void saving(const string& file_name,int againstWho,int selection);		//save the game to the file.
		void loading(const string& file_name,int whoseTurn, int aganistWho);	//load a game from the file.
		void resizeBoard(vector<vector<Cell> > hexCells);						//resizes the board in order to new size input. 
		void play(int row,int col,enumType who);								//makes an assignment to hexCells indexes.
		void createBoard();														//fills the board.	
		int randomGenerator();													//generates random number for computer player.		
		int first_x();															//finds the first index of x.															
		int first_o();															//finds the first index of o.
		bool find_path_x(int i,int j,int flag);									//follows the winning path for x.
		bool find_path_o(int i,int j,int flag);									//follows the winning path for o.			
		bool isEnded();															//checks the game is ended or still continues.	
		string last_word(string& str)const ;									//finds the file name that is going to be saved.
		
		static int markedCell;
		vector<vector<Cell> > hexCells;
		int size,selection,flag=0,callMenu;
		int left,top,loaded=0;
		int is_win_x=0,is_win_o=0;
		int row,col,moveNumber=0;
		int rowAI,colAI;
		int path[26][26]={0};
		int turn=1;
		int compareMarked=0;
		string file_name="",info,str,line;

	public:
		inline Hex()							{size=6; selection=1; createBoard();}
		inline Hex(int tempSize)				{size=tempSize; selection=1; createBoard();}
		inline Hex(int tempSize,int againstWho)	{size=tempSize; selection=againstWho; createBoard();}
		inline static int getAllMarked(){markedCell++; return markedCell;}
		void playGame();
		void continuedGame();
		bool compare(Hex& other)const;
};

int Hex:: markedCell=0;

int main(){
	Hex game[6];
	int gameSelection,menuSelection,compareSelection;
	while(1){
		cout<<"\n1) New Game\n2) Select a Game\n3) Compare 2 Game\n4) See the Amount of All Marked Cells\n5) Exit\n";
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
			cout<<"\n~~~Leaving the Game~~~\n\n\n";
			break;
		}
	}
	return 0;
}
void Hex:: playGame(){
	do{
		cout<<"Please Enter a Board Size: ";
		cin>>size;
	}while(size<6||size>26);
	hexCells.clear();
	createBoard();
	cout<<"Make a selection: \n1)User vs User\n2)User vs Computer\n";
	cin>>selection;
	while(1){
		printBoard();
		if(selection==1){
			cout<<"----------------------------------------------\n";
			if(turn==1){
				player_x();
				if(callMenu==1){
					break;
				}
				getAllMarked();
				setCompareMarked();
				if(loaded==0){
					turn=2;
				}
				if(loaded==1){
					ifstream myfile(file_name);				// it is also same process for the other movements.
					if (myfile.is_open()){
						getline(myfile,info);
						selection=info[2]-48;					//is it againt ai or user
						turn=info[0]-48;						// whose turn						myfile.close();				
						myfile.close();	
					}
					loaded=0;				
				}
			}
			printBoard();
			left=first_x();
			if(find_path_x(left,0,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_x=1;
				convert2upper_case(1);					//makes the correct paths uppercase.
				break;
			}
			cout<<"----------------------------------------------\n";
			if(turn==2){	
				player_o();
				if(callMenu==1){
					break;
				}
				getAllMarked();
				setCompareMarked();
				if(loaded==0){
					turn=1;
				}
				if(loaded==1){
					ifstream myfile(file_name);
					if (myfile.is_open()){
						getline(myfile,info);
						selection=info[2]-48;
						turn=info[0]-48;
						myfile.close();				
					}
					loaded=0;
				}						
			}
			top=first_o();
			if(find_path_o(0,top,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_o=1;
				convert2upper_case(2);					//makes the correct paths uppercase.
				break;
			}				
			if(isEnded()==true) break;	
		}
		else if(selection==2){
			player_x();
			if(callMenu==1){
				break;
			}
			getAllMarked();
			setCompareMarked();
			if(loaded==0){
				turn=2;
			}
			if(loaded==1){
				ifstream myfile(file_name);				// it is also same process for the other movements.
				if (myfile.is_open()){
					getline(myfile,info);
					selection=info[2]-48;					//is it againt ai or user
					turn=info[0]-48;						// whose turn						myfile.close();				
					myfile.close();	
				}
				loaded=0;			
			}
			cout<<"----------------------------------------------\n";
			if(moveNumber==0){	
				while(1){
					colAI=randomGenerator();							//this statements for the first move of AI. it is randomly chosen in row 0.
					rowAI=0;
					moveNumber++;										//to express that other moves will not be the first move of AI
					if(hexCells[rowAI][colAI].getType()!=empty){
						if(colAI+1<size) colAI=colAI+1;
						else colAI=colAI-1;
						break;
					}
				}
			}
			else{
				if(hexCells[rowAI+1][colAI].getType()==empty) rowAI=rowAI+1;											//if AI'last position's down is empty it follows down. if not;
				else if(hexCells[rowAI+1][colAI-1].getType()==empty && colAI-1<size &&colAI-1>=0) rowAI=rowAI+1,colAI=colAI-1;	//if AI's last position's left-down is empty it follows that path. if not;
				else if(hexCells[rowAI][colAI+1].getType()==empty&&colAI+1<size&&colAI>0) colAI=colAI+1;//
				else if(hexCells[rowAI][colAI-1].getType()==empty&& colAI-1<size&&colAI-1>=0) colAI=colAI-1;				// AI' path chosing algortihm by checking available coordinates.
				else if(hexCells[rowAI-1][colAI+1].getType()==empty&& colAI+1<size) rowAI=rowAI-1,colAI=colAI+1;				//
				else if(hexCells[rowAI-1][colAI].getType()==empty&& rowAI<=0) rowAI=rowAI-1;
				else{
					colAI=randomGenerator();													//if all around the last position is full, AI assigns another random position.
					rowAI=0;
				}				
			}
			play();
			getAllMarked();
			setCompareMarked();
			top=first_o();		
			if(find_path_o(0,top,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_o=1;
				convert2upper_case(2);					//makes the correct paths uppercase.
				break;
			}				
			if(isEnded()==true) break;	
		}
		else
			cerr<< "Try Again\n";
	}
	cout<<"**********************************************\n";
	if(is_win_o==1) cout<<"~~~~~~~~~~'O' WON THE GAME~~~~~~~~~~\n";
	if(is_win_x==1) cout<<"~~~~~~~~~~'X' WON THE GAME~~~~~~~~~~\n";
	printBoard();
	cout<<"**********************************************\n";
}
void Hex:: continuedGame(){
	while(1){
		printBoard();
		if(selection==1){
			cout<<"----------------------------------------------\n";
			if(turn==1){
				player_x();
				if(callMenu==1){
					break;
				}
				getAllMarked();
				setCompareMarked();
				if(loaded==0){
					turn=2;
				}
				if(loaded==1){
					ifstream myfile(file_name);				// it is also same process for the other movements.
					if (myfile.is_open()){
						getline(myfile,info);
						selection=info[2]-48;					//is it againt ai or user
						turn=info[0]-48;						// whose turn						myfile.close();				
						myfile.close();	
					}
					loaded=0;				
				}
			}
			printBoard();
			left=first_x();
			if(find_path_x(left,0,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_x=1;
				convert2upper_case(1);					//makes the correct paths uppercase.
				break;
			}
			cout<<"----------------------------------------------\n";
			if(turn==2){	
				player_o();
				if(callMenu==1){
					break;
				}
				getAllMarked();
				setCompareMarked();
				if(loaded==0){
					turn=1;
				}
				if(loaded==1){
					ifstream myfile(file_name);
					if (myfile.is_open()){
						getline(myfile,info);
						selection=info[2]-48;
						turn=info[0]-48;
						myfile.close();				
					}
					loaded=0;
				}						
			}
			top=first_o();
			if(find_path_o(0,top,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_o=1;
				convert2upper_case(2);					//makes the correct paths uppercase.
				break;
			}				
			if(isEnded()==true) break;	
		}
		else if(selection==2){
			player_x();
			if(callMenu==1){
				break;
			}
			getAllMarked();
			setCompareMarked();
			if(loaded==0){
				turn=2;
			}
			if(loaded==1){
				ifstream myfile(file_name);				// it is also same process for the other movements.
				if (myfile.is_open()){
					getline(myfile,info);
					selection=info[2]-48;					//is it againt ai or user
					turn=info[0]-48;						// whose turn						myfile.close();				
					myfile.close();	
				}
				loaded=0;			
			}
			cout<<"----------------------------------------------\n";
			if(moveNumber==0){	
				while(1){
					colAI=randomGenerator();							//this statements for the first move of AI. it is randomly chosen in row 0.
					rowAI=0;
					moveNumber++;										//to express that other moves will not be the first move of AI
					if(hexCells[rowAI][colAI].getType()!=empty){
						colAI=randomGenerator();
						break;
					}
				}
			}
			else{
				if(hexCells[rowAI+1][colAI].getType()==empty) rowAI=rowAI+1;											//if AI'last position's down is empty it follows down. if not;
				else if(hexCells[rowAI+1][colAI-1].getType()==empty && colAI-1<size &&colAI-1>=0) rowAI=rowAI+1,colAI=colAI-1;	//if AI's last position's left-down is empty it follows that path. if not;
				else if(hexCells[rowAI][colAI+1].getType()==empty&&colAI+1<size&&colAI>0) colAI=colAI+1;//
				else if(hexCells[rowAI][colAI-1].getType()==empty&& colAI-1<size&&colAI-1>=0) colAI=colAI-1;				// AI' path chosing algortihm by checking available coordinates.
				else if(hexCells[rowAI-1][colAI+1].getType()==empty&& colAI+1<size) rowAI=rowAI-1,colAI=colAI+1;				//
				else if(hexCells[rowAI-1][colAI].getType()==empty&& rowAI<=0) rowAI=rowAI-1;
				else{
					colAI=randomGenerator();													//if all around the last position is full, AI assigns another random position.
					rowAI=0;
				}				
			}
			play();
			getAllMarked();
			setCompareMarked();
			top=first_o();		
			if(find_path_o(0,top,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_o=1;
				convert2upper_case(2);					//makes the correct paths uppercase.
				break;
			}				
			if(isEnded()==true) break;	
		}
		else
			cerr<< "Try Again\n";
	}
	cout<<"**********************************************\n";
	if(is_win_o==1) cout<<"~~~~~~~~~~'O' WON THE GAME~~~~~~~~~~\n";
	if(is_win_x==1) cout<<"~~~~~~~~~~'X' WON THE GAME~~~~~~~~~~\n";
	printBoard();
	cout<<"**********************************************\n";	
}
void Hex:: createBoard(){
	int MAX=26;					//because of the max number of the letters
	Cell tempCell;
	vector<Cell> tempVector;
	for(int i=0;i<MAX+1;i++){
		for(int j=0;j<MAX+1;j++){
			tempCell.setType(empty);
			tempVector.push_back(tempCell);
		}
		hexCells.push_back(tempVector);
		tempVector.clear();
	}
}
void Hex:: resizeBoard(vector<vector<Cell> > hexCells){
	hexCells.resize(size);
	for (int i = 0; i < size; ++i){
    	hexCells[i].resize(size);
	}
}
void Hex:: printBoard(){
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
			cout<<(char)hexCells[i][k].getType()<<"   ";
		}
		cout<<"\n";
	}
}
void Hex:: play(int row,int col,enumType who){
	
	hexCells[row][col].setType(who);
}
void Hex:: player_x(){
	callMenu=0;
	cout<<"Player A (x) \nPlease Pick a Cell (Example: C5)\n";				//gets inputs for player x
	while(1){
		getline(cin,str);
		if(str[0]=='S'&&str[1]=='A'&&str[2]=='V'&&str[3]=='E'){
			file_name=last_word(str);
			saving(file_name,1,selection);//file_name,whoseTurn(1=x,2=o),selection(1=uvsu 2=uvsai)
		}
		else if(str[0]=='L'&&str[1]=='O'&&str[2]=='A'&&str[3]=='D'){
			file_name=last_word(str);
			loading(file_name,2,selection);				//seelction is for = the game is against user or computer
			loaded=1;												
			break;
		}
		else if(str[0]=='M'&&str[1]=='E'&&str[2]=='N'&&str[3]=='U'){
			callMenu=1;
			break;
		}
		else{		
			col=str[0]-65;
			if(str[3]>='0'&&str[3]<='9'){
				row=(((str[2]-48)*10)+(str[3]-48)-1);				//string conversion
			}
			else
				row=str[2]-49;
			if(row<size && row>-1 && col<size && col >-1 && hexCells[row][col].getType()==empty){
				play(row,col,player1);
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
void Hex:: player_o(){
	callMenu=0;	
	cout<<"Player B (o) \nPlease Pick a Cell (Example: C5)\n";				//gets inputs for player x
	while(1){
		getline(cin,str);
		if(str[0]=='S'&&str[1]=='A'&&str[2]=='V'&&str[3]=='E'){
			file_name=last_word(str);
			saving(file_name,2,selection);
		}
		else if(str[0]=='L'&&str[1]=='O'&&str[2]=='A'&&str[3]=='D'){
			file_name=last_word(str);
			loading(file_name,1,selection);						//seelction is for = the game is against user or computer
			loaded=1;												
			break;
		}
		else if(str[0]=='M'&&str[1]=='E'&&str[2]=='N'&&str[3]=='U'){
			callMenu=1;
			break;
		}
		else{		
			col=str[0]-65;
			if(str[3]>='0'&&str[3]<='9'){
				row=(((str[2]-48)*10)+(str[3]-48)-1);				//string conversion
			}
			else
				row=str[2]-49;
			if(row<size && row>-1 && col<size && col >-1 && hexCells[row][col].getType()==empty){
				play(row,col,player2);
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
string Hex:: last_word(string& str)const{
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
int Hex:: first_x(){
	int i;
	for(i=0;i<size+1;i++){
		if(hexCells[i][0].getType()==player1){				//finds the first element of X in the first column
			path[i][0]=1;					//and assign them as 1's to another map which is made up of integers
			break;
		}
	}
	if(path[i][0]==1) return i;
	else return 0;
}
int Hex:: first_o(){
	int i;
	for(i=0;i<size;i++){
		if(hexCells[0][i].getType()==player2){				//finds the first element of X in the first column
			path[0][i]=2;					//and assign them as 1's to another map which is made up of integers
			break;
		}
	}
	if(path[0][i]==2) return i;
	else return 0;
}
void Hex:: convert2upper_case(int picked){
	enumType tempPath;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(path[i][j]==picked&&picked==1){
				hexCells[i][j].setType(player1w);    //converts the winner path to the uppercase letters.
			}
			else if(path[i][j]==picked&&picked==2){
				hexCells[i][j].setType(player2w);    //converts the winner path to the uppercase letters.
			}
		}
	}
}
bool Hex:: find_path_x(int i,int j,int flag){
	if(j==size){
		path[i][j]==1;							//back tracking algorithm by recursive function.
		return 1;								//the path is followed by seeking 1's on the path map
	}
	if(hexCells[i][j].getType()==player1){
		path[i][j]=1;							//assigns 1 to the x parts of map.
		if(flag!=6&&path[i][j+1]!=1)			if(find_path_x(i,j+1,1)==1) 		return 1;
		if(flag!=5&&path[i+1][j]!=1)			if(find_path_x(i+1,j,2)==1) 		return 1;
		if(i>=1 && flag!=4&&path[i-1][j+1]!=1) 	if(find_path_x(i-1,j+1,3)==1) 	return 1;
		if(j>=1&&flag!=3&&path[i+1][j-1]!=1)	if(find_path_x(i+1,j-1,4)==1) 	return 1;
		if(i>=1&&flag!=2&&path[i-1][j]!=1)		if(find_path_x(i-1,j,5)==1) 		return 1;
		if(j>=1&&flag!=1&&path[i][j-1]!=1)		if(find_path_x(i,j-1,6)==1) 		return 1;
		path[i][j]=0;							//if a path which is followed does not lead to the ending, then all of the path will be 0 again.
	}
	return 0;
}
bool Hex:: find_path_o(int i,int j,int flag){

	if(i==size){
		path[i][j]==2;							//back tracking algorithm by recursive function.
		return 1;								//the path is followed by seeking 2's on the path map
	}
	if(hexCells[i][j].getType()==player2){
		path[i][j]=2;							//assigns 2 to the x parts of map.
		if(flag!=6&&path[i][j+1]!=2)			if(find_path_o(i,j+1,1)==1)		return 1;
		if(flag!=5&&path[i+1][j]!=2)			if(find_path_o(i+1,j,2)==1) 	return 1;
		if(i>=1 && flag!=4&&path[i-1][j+1]!=2) 	if(find_path_o(i-1,j+1,3)==1) 	return 1;
		if(j>=1&&flag!=3&&path[i+1][j-1]!=2)	if(find_path_o(i+1,j-1,4)==1) 	return 1;
		if(i>=1&&flag!=2&&path[i-1][j]!=2)		if(find_path_o(i-1,j,5)==1)		return 1;
		if(j>=1&&flag!=1&&path[i][j-1]!=2)		if(find_path_o(i,j-1,6)==1) 	return 1;
		path[i][j]=0;							//if a path which is followed does not lead to the ending, then all of the path will be 0 again.
	}
	return 0;
}
void Hex:: saving(const string& file_name,int whoseTurn,int againstWho){
	ofstream myfile;
	myfile.open(file_name);
	myfile<<whoseTurn<<" " <<selection<<" "<<size<<"\n";
	for(int i=0;i<size;i++){
		int k=0;
		while(k!=i){
			myfile<<" ";
			k++;
		}	
		for(int j=0;j<size;j++){
			myfile <<(char)hexCells[i][j].getType();	
		}
		myfile << "\n";
	}
	myfile.close();
}
void Hex:: loading(const std::string& file_name,int whoseTurn, int aganistWho){
	int i;
	char fromFile;
	row=0,col=0;
	ifstream myfile(file_name);
	if (myfile.is_open()){
		getline(myfile,line);
		if(line[5]>='0'&&line[5]<='9'){
				size=((line[4]-48)*10)+(line[5]-48);				//string conversion
			}
			else
				size=line[4]-48;
			resizeBoard(hexCells);
	    while(getline(myfile,line)){
	    	whoseTurn=line[0]-48;
	    	i=0;
	      	while(line[i]==' '){
	      		i++;
	      	}
	      	for(int j=0;j<size;j++){
	      		fromFile=line[i];
	      		if(fromFile=='x') 		hexCells[row][col].setType(player1);
	      		else if(fromFile=='o')	hexCells[row][col].setType(player2);
	      		else if(fromFile=='.')	hexCells[row][col].setType(empty);
	      		i++;
	      		col++;
	      	}
	      	row++;
	      	col=0;
	    }
	   	myfile.close();
	}
  	else
  		cerr << "The file is not able to open.\n"; 
}		
int Hex:: randomGenerator(){
	int rand;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator (seed);				//random number generator
	rand=generator()%(size);
	return rand;
}
void Hex:: play(){
	while(1){
		if(hexCells[rowAI][colAI].getType()==empty){							//it checks AI's incoming coordinates.
			hexCells[rowAI][colAI].setType(player2);
			break;
		}
	}
	cout<<"Computer's move: "<<row<<"'th row"<<col<<"'th columnn\n";
}
bool Hex:: isEnded(){
	if(is_win_o==1||is_win_x==1) return true;
	else return false;
}
bool Hex:: compare(Hex& other)const{
	if(getCompareMarked()>other.getCompareMarked()) return true;
	else return false;
}