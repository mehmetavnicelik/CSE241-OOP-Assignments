import java.util.Scanner;

public class Main {
	static final int MAX = 12;

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int left, top, size;
		int is_win_x = 0, is_win_o = 0;
		int row = 0, col = 0, moveNumber = 0;
		int[][] path = new int[MAX][MAX];
		char selection;
		char[][] grid = new char[MAX][MAX];
		System.out.print("Please Enter the Board Size: ");
		while (true) {
			size = scanner.nextInt();
			if (size > 5 && size < 13)
				break;
			else
				System.out.print("Please Enter a Number Between 6 and 12\n");
		}
		fill_the_grid(size, grid);
		print_the_grid(size, grid);
		System.out.print("Please Make a selection\n"
				+ "a) Two Player Game?\n"
				+ "b) Player vs Computer?\n");
		while (true) {
			selection = scanner.next().charAt(0);
			if (selection == 'a') {
				while (true) {
					System.out.print("----------------------------------------------\n");
					player_x(size, grid);										//player x plays.
					print_the_grid(size, grid);									//prints the grid after player x played.
					left = first_x(grid, path, size);								//first_x function tries to find the first element of x in 0th column.
					if (find_path_x(grid, path, size, left, 0, 0) == 1) {				//by starting the first element of x's, backtracking algorithm is used.
						is_win_x = 1;
						convert2upper_case(grid, path, size, 1);					//makes the correct paths uppercase.
						break;
					}
					System.out.print("----------------------------------------------\n");
					player_o(size, grid);										//player o plays.
					print_the_grid(size, grid);									//prints the grid after player o played.
					top = first_o(grid, path, size);								//first_o function tries to find the first element of o in 0th row.
					if (find_path_o(grid, path, size, 0, top, 0) == 1) {					//by starting the first element of o's, backtracking algorithm is used.
						is_win_o = 1;
						convert2upper_case(grid, path, size, 2);					//makes the correct paths uppercase.
						break;
					}
				}
				if (is_win_o == 1 || is_win_x == 1) break;
			} else if (selection == 'b') {
				while (true) {
					System.out.print("----------------------------------------------\n");
					player_x(size, grid);
					print_the_grid(size, grid);
					left = first_x(grid, path, size);								//same with the algorihm above for player x
					if (find_path_x(grid, path, size, left, 0, 0) == 1) {
						is_win_x = 1;
						convert2upper_case(grid, path, size, 1);
						break;
					}
					System.out.print("----------------------------------------------\n");
					if (moveNumber == 0) {
						col = random_generator(size);							//this statements for the first move of AI. it is randomly chosen in row 0.
						row = 0;
						moveNumber++;										//to express that other moves will not be the first move of AI
					} else {
						if (grid[row + 1][col] == '.') row = row + 1;											//if AI'last position's down is empty it follows down. if not;
						else if (grid[row + 1][col - 1] == '.' && col - 1 < size && col - 1 >= 0) { row = row + 1; col = col - 1; }	//if AI's last position's left-down is empty it follows that path. if not;
						else if (grid[row][col + 1] == '.' && col + 1 < size && col > 0) col = col + 1;					//
						else if (grid[row][col - 1] == '.' && col - 1 < size && col - 1 >= 0) col = col - 1;				// AI' path chosing algortihm by checking available coordinates.
						else if (grid[row - 1][col + 1] == '.' && col + 1 < size) { row = row - 1; col = col + 1; }				//
						else if (grid[row - 1][col] == '.' && row <= 0) row = row - 1;
						else {
							col = random_generator(size);													//if all around the last position is full, AI assigns another random position.
							row = 0;
						}
					}

					player_ai(size, grid, row, col);					//makes AI's move according to the incoming coordinates.
					print_the_grid(size, grid);						//prints the grid.
					top = first_o(grid, path, size);					//first_o function tries to find the first element of AI in 0th row.
					if (find_path_o(grid, path, size, 0, top, 0) == 1) {
						is_win_o = 1;
						convert2upper_case(grid, path, size, 2);
						break;
					}
				}
				if (is_win_o == 1 || is_win_x == 1) break;
			} else
				System.out.print("Try Again\n");
		}
		System.out.print("**********************************************\n");
		if (is_win_o == 1) System.out.print("~~~~~~~~~~'O' WON THE GAME~~~~~~~~~~\n");
		if (is_win_x == 1) System.out.print("~~~~~~~~~~'X' WON THE GAME~~~~~~~~~~\n");
		print_the_grid(size, grid);
		System.out.print("**********************************************\n");
	}
}