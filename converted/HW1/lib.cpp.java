//Mehmet Avni ÇELİK/1801042630
import java.util.Scanner;

public class Lib {
	static final int MAX = 100;
	static Scanner scanner = new Scanner(System.in);

	///////////////////////////////////////////////////////////////////////////////////////////
	static void fill_the_grid(int size, char grid[][]) {
		int i, j;
		char c = 'a';

		for (i = 0; i < size; i++) {		//this loop fills the array with points
			for (j = 0; j < size; j++) {
				grid[i][j] = '.';
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static void print_the_grid(int size, char grid[][]) {
		int i, j, k;
		char c = 'a';

		for (i = 0; i < size; i++) {		//this loop prints the column letters.
			System.out.print("  " + c + " ");
			c++;
		}
		System.out.print("\n");
		for (i = 0; i < size; i++) {		//this loop prints the game board
			System.out.print((i + 1) + " ");			//this statement prints the row numbers.
			for (j = 0; j < i; j++) {
				System.out.print("  ");
			}
			for (k = 0; k < size; k++) {
				System.out.print(grid[i][k] + "   ");
			}
			System.out.print("\n");
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static void player_x(int size, char grid[][]) {
		char colC;
		int row, col;

		System.out.print("Player A (x) \nPlease Pick a Cell (Example: C5)\n");					//gets inputs for player x
		while (true) {
			String token = scanner.next();
			colC = token.charAt(0);
			row = Integer.parseInt(token.substring(1).trim().isEmpty() ? scanner.next() : token.substring(1));
			col = colC - 65;
			row = row - 1;
			if (row < size && row > -1 && col < size && col > -1 && grid[row][col] == '.') {
				grid[row][col] = 'x';
				break;
			} else
				System.out.print("Invalid Selection. Please Try Again\n");
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static void player_o(int size, char grid[][]) {
		char colC;
		int row, col;

		System.out.print("Player B (o) \nPlease Pick a Cell (Example: C5)\n");			//gets input for player o
		while (true) {
			String token = scanner.next();
			colC = token.charAt(0);
			row = Integer.parseInt(token.substring(1).trim().isEmpty() ? scanner.next() : token.substring(1));
			col = colC - 65;
			row = row - 1;
			if (row < size && row > -1 && col < size && col > -1 && grid[row][col] == '.') {
				grid[row][col] = 'o';
				break;
			} else
				System.out.print("Invalid Selection. Please Try Again\n");
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static void player_ai(int size, char grid[][], int row, int col) {

		System.out.print("Player B (o) \nPlease Pick a Cell (Example: C5)\n");
		while (true) {
			if (grid[row][col] == '.') {							//it checks AI's incoming coordinates.
				grid[row][col] = 'o';
				break;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static int first_x(char grid[][], int path[][], int size) {
		int i;
		for (i = 0; i < size; i++) {
			if (grid[i][0] == 'x') {				//finds the first element of X in the first column
				path[i][0] = 1;					//and assign them as 1's to another map which is made up of integers
				break;
			}
		}
		if (i < size && path[i][0] == 1) return i;
		else return 0;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static int first_o(char grid[][], int path[][], int size) {
		int i;
		for (i = 0; i < size; i++) {
			if (grid[0][i] == 'o') {				//finds the first element of X in the first column
				path[0][i] = 2;					//and assign them as 2's to another map which is made up of integers
				break;
			}
		}
		if (i < size && path[0][i] == 2) return i;
		else return 0;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static boolean find_path_x(char grid[][], int path[][], int size, int i, int j, int flag) {

		if (j == size) {
			return true;								//the path is followed by seeking 1's on the path map
		}
		if (grid[i][j] == 'x') {
			path[i][j] = 1;							//assigns 1 to the x parts of map.
			if (flag != 6 && path[i][j + 1] != 1)			if (find_path_x(grid, path, size, i, j + 1, 1)) 		return true;
			if (flag != 5 && path[i + 1][j] != 1)			if (find_path_x(grid, path, size, i + 1, j, 2)) 		return true;
			if (i >= 1 && flag != 4 && path[i - 1][j + 1] != 1) 	if (find_path_x(grid, path, size, i - 1, j + 1, 3)) 	return true;
			if (j >= 1 && flag != 3 && path[i + 1][j - 1] != 1)	if (find_path_x(grid, path, size, i + 1, j - 1, 4)) 	return true;
			if (i >= 1 && flag != 2 && path[i - 1][j] != 1)		if (find_path_x(grid, path, size, i - 1, j, 5)) 		return true;
			if (j >= 1 && flag != 1 && path[i][j - 1] != 1)		if (find_path_x(grid, path, size, i, j - 1, 6)) 		return true;
			path[i][j] = 0;							//if a path which is followed does not lead to the ending, then all of the path will be 0 again.
		}
		return false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static boolean find_path_o(char grid[][], int path[][], int size, int i, int j, int flag) {

		if (i == size) {
			return true;								//the path is followed by seeking 2's on the path map
		}
		if (grid[i][j] == 'o') {
			path[i][j] = 2;							//assigns 2 to the x parts of map.
			if (flag != 6 && path[i][j + 1] != 2)			if (find_path_o(grid, path, size, i, j + 1, 1)) 		return true;
			if (flag != 5 && path[i + 1][j] != 2)			if (find_path_o(grid, path, size, i + 1, j, 2)) 		return true;
			if (i >= 1 && flag != 4 && path[i - 1][j + 1] != 2) 	if (find_path_o(grid, path, size, i - 1, j + 1, 3)) 	return true;
			if (j >= 1 && flag != 3 && path[i + 1][j - 1] != 2)	if (find_path_o(grid, path, size, i + 1, j - 1, 4)) 	return true;
			if (i >= 1 && flag != 2 && path[i - 1][j] != 2)		if (find_path_o(grid, path, size, i - 1, j, 5))		return true;
			if (j >= 1 && flag != 1 && path[i][j - 1] != 2)		if (find_path_o(grid, path, size, i, j - 1, 6)) 		return true;
			path[i][j] = 0;							//if a path which is followed does not lead to the ending, then all of the path will be 0 again.
		}
		return false;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static void convert2upper_case(char grid[][], int path[][], int size, int picked) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (path[i][j] == picked)	grid[i][j] = (char) (grid[i][j] - 32);    //converts the winner path to the uppercase letters.
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	static int random_generator(int size) {
		int rand;
		long seed = System.currentTimeMillis();
		java.util.Random generator = new java.util.Random(seed);				//random number generator
		rand = generator.nextInt(size);
		return rand;
	}
	///////////////////////////////////////////////////////////////////////////////////////////
}