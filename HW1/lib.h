const int MAX=12;
void fill_the_grid(int size,char grid[MAX][MAX]);
void print_the_grid(int size,char grid[MAX][MAX]);
void player_x(int size, char grid[MAX][MAX]);
void player_o(int size, char grid[MAX][MAX]);
void player_ai(int size, char grid[MAX][MAX],int col,int row);
int first_x(char grid[MAX][MAX],int path[MAX][MAX],int size);
int first_o(char grid[MAX][MAX],int path[MAX][MAX],int size);
bool find_path_x(char grid[MAX][MAX],int path[MAX][MAX],int size,int i,int j,int flag);
bool find_path_o(char grid[MAX][MAX],int path[MAX][MAX],int size,int i,int j,int flag);
void convert2upper_case(char grid[MAX][MAX],int path[MAX][MAX],int size,int picked);
int random_generator(int size);
