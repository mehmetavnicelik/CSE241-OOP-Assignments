const int MAX=12;
enum cell{
	gamer1 = 'x',
	gamer2 = 'o',
	empty = '.'
};
void fill_the_grid(int size,char grid[MAX][MAX]);
void print_the_grid(int size,char grid[MAX][MAX]);
void player_x(int size, char grid[MAX][MAX],char selection,int& loaded,std::string& file_name, int flag=0);
void player_o(int size, char grid[MAX][MAX],char selection,int& loaded,std::string& file_name, int flag=0);
void player_ai(int size, char grid[MAX][MAX],int col,int row);
int first_x(char grid[MAX][MAX],int path[MAX][MAX],int size);
int first_o(char grid[MAX][MAX],int path[MAX][MAX],int size);
bool find_path_x(char grid[MAX][MAX],int path[MAX][MAX],int size,int i,int j,int flag);
bool find_path_o(char grid[MAX][MAX],int path[MAX][MAX],int size,int i,int j,int flag);
void convert2upper_case(char grid[MAX][MAX],int path[MAX][MAX],int size,int picked);
int random_generator(int size);
std::string last_word(const std::string& str);
void saving(char grid[MAX][MAX], std::string& file_name, char whoseTurn,char againstWho,int size);
void loading(char grid[MAX][MAX], std::string& file_name,int size,char whoseTurn,char againstWho);