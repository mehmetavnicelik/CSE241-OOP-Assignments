#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>
#include<random>
#include"lib.h"
int Hex::markedCell=0;
void Hex:: playGame(){
	do{
		cout<<"Please Enter a Board Size: ";
		cin>>size;
	}while(size<6||size>26);
	createBoard();
	cout<<"Make a selection: \n1)User vs User\n2)User vs Computer\n";
	cin>>selection;
	while(1){
		//printBoard();
		cout<<*this;
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
			//printBoard();
			cout<<*this;
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
			left=first_x();
			if(find_path_x(left,0,0)==1){				//by starting the first element of x's, backtracking algorithm is used.
				is_win_x=1;
				convert2upper_case(1);					//makes the correct paths uppercase.
				break;
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
					else break;
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
	//printBoard();
	cout<<*this;
	cout<<"**********************************************\n";
}
bool operator ==(const Hex& game1, const Hex& game2){

	return game1.getCompareMarked() == game2.getCompareMarked();
}
ostream& operator<<(ostream& outputStream,const Hex& game1){ //operation overloading for printing to the screen.
	int i,j,k;
	char c = 'a';
	for(i=0;i<game1.size;i++){		//this loop prints the column letters.
		cout<<"  "<<c<<" ";
		c++;
	}
	cout<<"\n";
	for(i=0;i<game1.size;i++){		//this loop prints the game board
		cout<<i+1<<" ";			//this statement prints the row numbers.
		for(j=0;j<i;j++){
			cout<<"  ";
		}
		for(k=0;k<game1.size;k++){
			cout<<(char)game1.hexCells[i][k].getType()<<"   ";
		}
		cout<<"\n";
	}
	return outputStream;
}
ofstream& operator<<(ofstream& outputStream, Hex& game1){	//operation overloading for saving to the file.	
	ofstream myfile;
	string file=game1.file_name;
	myfile.open(file);
	myfile<<game1.whoseTurn<<" " <<game1.selection<<" "<<game1.size<<"\n";
	for(int i=0;i<game1.size;i++){
		int k=0;
		while(k!=i){
			myfile<<" ";
			k++;
		}	
		for(int j=0;j<game1.size;j++){
			myfile <<(char)game1.hexCells[i][j].getType();	
		}
		myfile << "\n";
	}
	myfile.close();	
	return outputStream;
}
ifstream& operator>>(ifstream& inputStream, Hex& game1){	//operation overloading for loading from the file.
	int i;
	char fromFile;
	game1.row=0,game1.col=0;
	ifstream myfile(game1.file_name);
	if (myfile.is_open()){
		getline(myfile,game1.line);
		if(game1.line[5]>='0'&&game1.line[5]<='9'){
				game1.size=((game1.line[4]-48)*10)+(game1.line[5]-48);				//string conversion
			}
			else
				game1.size=game1.line[4]-48;
	    while(getline(myfile,game1.line)){
	    	game1.whoseTurn=game1.line[0]-48;
	    	i=0;
	      	while(game1.line[i]==' '){
	      		i++;
	      	}
	      	for(int j=0;j<game1.size;j++){
	      		fromFile=game1.line[i];
	      		if(fromFile=='x') 		game1.hexCells[game1.row][game1.col].setType(player1);
	      		else if(fromFile=='o')	game1.hexCells[game1.row][game1.col].setType(player2);
	      		else if(fromFile=='.')	game1.hexCells[game1.row][game1.col].setType(empty);
	      		i++;
	      		game1.col++;
	      	}
	      	game1.row++;
	      	game1.col=0;
	    }
	   	myfile.close();
	}
  	else{
		cerr << "The file is not able to open.\n"; 
  	}
  	return inputStream;	
}
Hex Hex:: operator--(){										//prefix operator overloading
	undo();
	return *this;
}
Hex Hex:: operator--(int){									//postfix operator overloading
	undo();
	return *this;
}
void Hex:: continuedGame(){
	while(1){
		//printBoard();
		cout<<*this;
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
			//printBoard();
			cout<<*this;
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
	//printBoard();
	cout<<*this;
	cout<<"**********************************************\n";	
}
void Hex:: createBoard(){
	int MAX=26;					//because of the max number of the letters
	hexCells =new Cell* [size+1];
	for(int i=0;i<size+1;i++){
		hexCells[i]= new Cell[size+1];
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			hexCells[i][j].setType(empty);
		}
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
			whoseTurn=1;				//file_name,whoseTurn(1=x,2=o),selection(1=uvsu 2=uvsai)
			cout<<*this;
		}
		else if(str[0]=='L'&&str[1]=='O'&&str[2]=='A'&&str[3]=='D'){
			file_name=last_word(str);
			whoseTurn=2;
			ifstream obj;
			obj>> *this;
			loaded=1;												
			break;
		}
		else if(str[0]=='M'&&str[1]=='E'&&str[2]=='N'&&str[3]=='U'){
			callMenu=1;
			break;
		}
		else if(str[0]=='U'&&str[1]=='N'&&str[2]=='D'&&str[3]=='O'){
				--(*this);											//prefix overloading
				break;
		}
		else{		
			col=str[0]-65;
			if(str[3]>='0'&&str[3]<='9'){
				row=(((str[2]-48)*10)+(str[3]-48)-1);				//string conversion
			}
			else{
				row=str[2]-49;
			}
			moveRow[getCurrentIndex()]=row;		//we keep the last played row here.
			moveCol[getCurrentIndex()]=col;		//we keep the last played col here.
			increaseCurrentIndex();

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
			whoseTurn=2;
			cout<<*this;
		}
		else if(str[0]=='L'&&str[1]=='O'&&str[2]=='A'&&str[3]=='D'){
			file_name=last_word(str);
			whoseTurn=1;
			ifstream obj;
			obj>> *this;
			loaded=1;												
			break;
		}
		else if(str[0]=='M'&&str[1]=='E'&&str[2]=='N'&&str[3]=='U'){
			callMenu=1;
			break;
		}
		else if(str[0]=='U'&&str[1]=='N'&&str[2]=='D'&&str[3]=='O'){
			--(*this);
			break;
		}
		else{		
			col=str[0]-65;
			if(str[3]>='0'&&str[3]<='9'){
				row=(((str[2]-48)*10)+(str[3]-48)-1);				//string conversion
			}
			else{
				row=str[2]-49;
			}
			moveRow[getCurrentIndex()]=row;
			moveCol[getCurrentIndex()]=col;
			increaseCurrentIndex();

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
int Hex:: randomGenerator(){
	int rand;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator (seed);				//random number generator
	rand=generator()%(size);
	return rand;
}
Hex:: Cell Hex:: play(){
	while(1){
		if(hexCells[rowAI][colAI].getType()==empty){							//it checks AI's incoming coordinates.
			hexCells[rowAI][colAI].setType(player2);
			break;
		}
		else break;
	}
	moveRow[getCurrentIndex()]=rowAI;
	moveCol[getCurrentIndex()]=colAI;
	increaseCurrentIndex();
	cout<<"Computer's move: "<<row<<"'th row"<<col<<"'th columnn\n";
	ai_score++;
	return hexCells[rowAI][colAI];												//plays the ai and returns the cell where it made a change as wanted in assignment.
}
bool Hex:: isEnded(){
	if(is_win_o==1||is_win_x==1) return true;
	else return false;
}
bool Hex:: compare(Hex& other)const{
	if(getCompareMarked()>other.getCompareMarked()) return true;
	else return false;
}
bool Hex:: find_path_score(int i,int j,int flag){
	if(j==size){
		path2[i][j]==1;							//back tracking algorithm by recursive function.
		return 1;								//the path is followed by seeking 1's on the path map
	}
	if(hexCells[i][j].getType()==player1){
		path2[i][j]=1;							//assigns 1 to the x parts of map.
		if(flag!=6&&path2[i][j+1]!=1)			if(find_path_score(i,j+1,1)==1) 		return 1;
		if(flag!=5&&path2[i+1][j]!=1)			if(find_path_score(i+1,j,2)==1) 		return 1;
		if(i>=1 && flag!=4&&path2[i-1][j+1]!=1) if(find_path_score(i-1,j+1,3)==1) 	return 1;
		if(j>=1&&flag!=3&&path2[i+1][j-1]!=1)	if(find_path_score(i+1,j-1,4)==1) 	return 1;
		if(i>=1&&flag!=2&&path2[i-1][j]!=1)		if(find_path_score(i-1,j,5)==1) 		return 1;
		if(j>=1&&flag!=1&&path2[i][j-1]!=1)		if(find_path_score(i,j-1,6)==1) 		return 1;
	}
	return 0;
}
int Hex:: userScore(){
	score=0;
	int left=first_x();
	find_path_score(left,0,0);	
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(path2[i][j]==1){
				increaseScore();
			}
		}
	}
	int score;
}
int Hex:: undo(){
	if(current_index<=1){
		return 0;
	}
	hexCells[moveRow[current_index-1]][moveCol[current_index-1]].setType(empty);
	current_index--;
	return 0;
}
void Hex:: removePointers(){
	if(hexCells!=nullptr){
		for(int i=0;i<size;i++){
			delete hexCells[i];
		}
		delete []	hexCells;
		hexCells=nullptr;
	}
	if(moveRow!=nullptr){
		delete []	moveRow;
		moveRow=nullptr;
	}
	if(moveCol!=nullptr){
		delete []	moveCol;
		moveCol=nullptr;
	}			// this is also a destructor 
}
Hex:: ~Hex(){								//destructor;
	//delete []	hexCells;
	//removePointers();
}
Hex::Hex(const Hex &copy){					//copy constructor		
	/*	
	removePointers();
	createBoard();
	for(int cx=0;cx<26;cx++){
		for(int cy=0;cy<26;cy++){
			path[cx][cy]=copy.path[cx][cy];
			path2[cx][cy]=copy.path2[cx][cy];
			hexCells[cx][cy]=copy.hexCells[cx][cy];
		}
	}			
	moveRow=new int[750];
	moveCol=new int[750];
	for(int og=0;og<copy.current_index;og++){
		moveRow[og]=copy.moveRow[og];
		moveCol[og]=copy.moveCol[og];
	}

	size=copy.size;
	selection=copy.selection;
	whoseTurn=copy.whoseTurn;
	current_index=copy.current_index;
	flag=copy.flag;
	callMenu=copy.callMenu;
	left=copy.left;
	top=copy.top;
	loaded=copy.loaded;
	is_win_x=copy.is_win_x;
	is_win_o=copy.is_win_o;
	row=copy.row;
	col=copy.col;
	moveNumber=copy.moveNumber;
	rowAI=copy.rowAI;
	colAI=copy.colAI;
	turn=copy.turn;
	compareMarked=copy.compareMarked;
	score=copy.score;
	ai_score=copy.ai_score;
	file_name=copy.file_name;
	info=copy.info;
	str=copy.str;
	line=copy.line;
	*/
}
Hex& Hex:: operator=(const Hex& copy){		//assignment operator		
	/*
	removePointers();
	createBoard();
	for(int cx=0;cx<26;cx++){
		for(int cy=0;cy<26;cy++){
			path[cx][cy]=copy.path[cx][cy];
			path2[cx][cy]=copy.path2[cx][cy];
			hexCells[cx][cy]=copy.hexCells[cx][cy];
		}
	}			
	moveRow=new int[750];
	moveCol=new int[750];
	for(int og=0;og<copy.current_index;og++){
		moveRow[og]=copy.moveRow[og];
		moveCol[og]=copy.moveCol[og];
	}

	size=copy.size;
	selection=copy.selection;
	whoseTurn=copy.whoseTurn;
	current_index=copy.current_index;
	flag=copy.flag;
	callMenu=copy.callMenu;
	left=copy.left;
	top=copy.top;
	loaded=copy.loaded;
	is_win_x=copy.is_win_x;
	is_win_o=copy.is_win_o;
	row=copy.row;
	col=copy.col;
	moveNumber=copy.moveNumber;
	rowAI=copy.rowAI;
	colAI=copy.colAI;
	turn=copy.turn;
	compareMarked=copy.compareMarked;
	score=copy.score;
	ai_score=copy.ai_score;
	file_name=copy.file_name;
	info=copy.info;
	str=copy.str;
	line=copy.line;
	return *this;
	*/
}