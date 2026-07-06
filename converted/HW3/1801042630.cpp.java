import java.util.*;
import java.io.*;

enum EnumType {
	player1('x'),
	player1w('X'),
	player2('o'),
	player2w('O'),
	empty('.');

	final char value;
	EnumType(char v) { this.value = v; }
}

public class Hex {

	private static class Cell {
		private EnumType type;
		private int row;
		private int column;

		public EnumType getType() { return type; }
		public int getRow() { return row; }
		public int getCol() { return column; }
		public void setType(EnumType player) { type = player; }
		public void setRow(int rowInput) { row = rowInput; }
		public void setCol(int colInput) { column = colInput; }
	}

	private int getSize() { return size; }
	private String getFileName() { return file_name; }
	private void setCompareMarked() { compareMarked++; }
	private int getCompareMarked() { return compareMarked; }

	private static int markedCell = 0;
	private ArrayList<ArrayList<Cell>> hexCells = new ArrayList<ArrayList<Cell>>();
	private int size, selection, flag = 0, callMenu;
	private int left, top, loaded = 0;
	private int is_win_x = 0, is_win_o = 0;
	private int row, col, moveNumber = 0;
	private int rowAI, colAI;
	private int[][] path = new int[27][27];
	private int turn = 1;
	private int compareMarked = 0;
	private String file_name = "", info, str, line;

	static Scanner scanner = new Scanner(System.in);

	static int readInt() { return Integer.parseInt(scanner.nextLine().trim()); }
	static String readLine() { return scanner.nextLine(); }

	private static char ch(String s, int i) {
		return (s != null && i < s.length() && i >= 0) ? s.charAt(i) : '\0';
	}

	public Hex() { size = 6; selection = 1; createBoard(); }
	public Hex(int tempSize) { size = tempSize; selection = 1; createBoard(); }
	public Hex(int tempSize, int againstWho) { size = tempSize; selection = againstWho; createBoard(); }

	public static int getAllMarked() { markedCell++; return markedCell; }

	public static void main(String[] args) {
		Hex[] game = new Hex[6];
		for (int i = 0; i < 6; i++) game[i] = new Hex();
		int gameSelection, menuSelection, compareSelection;
		while (true) {
			System.out.print("\n1) New Game\n2) Select a Game\n3) Compare 2 Game\n4) See the Amount of All Marked Cells\n5) Exit\n");
			menuSelection = readInt();
			if (menuSelection == 1) {
				System.out.print("Please enter the game number which you want to play [1-5]: ");
				gameSelection = readInt();
				game[gameSelection].playGame();
			} else if (menuSelection == 2) {
				System.out.print("Please enter the game number which you want to continue [1-5]: ");
				gameSelection = readInt();
				game[gameSelection].continuedGame();
			} else if (menuSelection == 3) {
				System.out.print("Please enter the game numbers which you want to compare [1-5]:\n");
				System.out.print("First Number:");
				gameSelection = readInt();
				System.out.print("Second Number:");
				compareSelection = readInt();
				System.out.print("('1' means first game has more marked celss. '0' means other)\n" + (game[gameSelection].compare(game[compareSelection]) ? 1 : 0) + "\n");
			} else if (menuSelection == 4) {
				System.out.print("The amount of all the marked cells: " + (getAllMarked() - 1) + "\n");
			} else if (menuSelection == 5) {
				System.out.print("\n~~~Leaving the Game~~~\n\n\n");
				break;
			}
		}
	}

	public void playGame() {
		do {
			System.out.print("Please Enter a Board Size: ");
			size = readInt();
		} while (size < 6 || size > 26);
		hexCells.clear();
		createBoard();
		System.out.print("Make a selection: \n1)User vs User\n2)User vs Computer\n");
		selection = readInt();
		while (true) {
			printBoard();
			if (selection == 1) {
				System.out.print("----------------------------------------------\n");
				if (turn == 1) {
					player_x();
					if (callMenu == 1) {
						break;
					}
					getAllMarked();
					setCompareMarked();
					if (loaded == 0) {
						turn = 2;
					}
					if (loaded == 1) {
						try (BufferedReader myfile = new BufferedReader(new FileReader(file_name))) {
							info = myfile.readLine();
							selection = ch(info, 2) - 48;
							turn = ch(info, 0) - 48;
						} catch (IOException e) { }
						loaded = 0;
					}
				}
				printBoard();
				left = first_x();
				if (find_path_x(left, 0, 0)) {
					is_win_x = 1;
					convert2upper_case(1);
					break;
				}
				System.out.print("----------------------------------------------\n");