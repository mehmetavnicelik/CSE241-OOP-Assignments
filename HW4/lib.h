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
	public:
		//BIG THREE IMPLEMENTED AS FOLLOWS
		~Hex();								//destructor 
		Hex(const Hex &copy);				//copy constructor
		Hex& operator=(const Hex &copy);	//assignment operator

		friend bool operator ==(const Hex& game1, const Hex& game2);		////<<operator overloading for checking the equality.
		friend ostream& operator<<(ostream& outputStream,const Hex& game1);	//<< operator overloading for printing to the screen.
		friend ofstream& operator<<(ofstream& outputStream, Hex& game1);	//<< operation overloading for saving to the file. 	
		friend ifstream& operator>>(ifstream& inputStream, Hex& game1);		//>> operation overloading for loading from the file.
		Hex operator--();													//prefix operator overloading for undo operation.
		Hex operator--(int);												//postfix operator overloading for undo operation.

		inline Hex()							{size=6; selection=1; createBoard();}
		inline Hex(int tempSize)				{size=tempSize; selection=1; createBoard();}
		explicit inline Hex(int tempSize,int againstWho)	{size=tempSize; selection=againstWho; createBoard();}
		inline static int getAllMarked(){markedCell++; return markedCell;}
		inline int getScore(){return score;}
		inline int get_ai_score(){return ai_score;}
		inline int get_is_winx(){return is_win_x;}
		inline void increaseScore(){score++;}
		inline int getCurrentIndex(){return current_index;};					//indexs operations for undo process.
		inline void decreaseCurrentIndex(){current_index--;}					//indexs operations for undo process.
		inline void increaseCurrentIndex(){current_index++;}					//indexs operations for undo process.
		void playGame();
		void continuedGame();
		bool compare(Hex& other)const;
		int userScore();
		void removePointers();
		
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
		
	private:
		inline int getSize() 		{return size;}								//returns the board's size.
		inline string getFileName()	{return file_name;}							//returns files name to save the game.
		inline void setCompareMarked() {compareMarked++;}						//increase the marked cells for each game seperately.
		inline int getCompareMarked() const { return compareMarked;}			//keeps the marked cells for each game seperately.
		void player_x();														//makes move for player-x.Also play function is in this function too.		
		void player_o();														//makes move for player-o.Also play function is in this function too.
		Cell play();															//plays for AI.
		void convert2upper_case(int picked);									//makes the winning path uppercase.
		void play(int row,int col,enumType who);								//makes an assignment to hexCells indexes.
		void createBoard();														//fills the board.	
		int randomGenerator();													//generates random number for computer player.		
		int first_x();															//finds the first index of x.															
		int first_o();															//finds the first index of o.
		bool find_path_x(int i,int j,int flag);									//follows the winning path for x.
		bool find_path_score(int i,int j,int flag);								//follows the winning path for x.
		bool find_path_o(int i,int j,int flag);									//follows the winning path for o.			
		bool isEnded();															//checks the game is ended or still continues.	
		int undo();
		string last_word(string& str)const ;									//finds the file name that is going to be saved.

		static int markedCell;
		Cell ** hexCells=nullptr;												//Dynamic memory techniques instead of vectors.
		int *moveRow=new int[750];												//For Keeping all the played row number.
		int *moveCol=new int[750];												//For Keeping all the played col number.		
		int current_index=0;
		int size,selection,flag=0,callMenu;
		int left,top,loaded=0;
		int is_win_x=0,is_win_o=0;
		int row,col,moveNumber=0;
		int rowAI,colAI;
		int path[26][26]={0};													//for finding the winnnig path.
		int path2[26][26]={0};													//for finding the scores.
		int turn=1,whoseTurn;
		int compareMarked=0;
		int score=0,ai_score=0;
		string file_name="",info,str,line;
};


