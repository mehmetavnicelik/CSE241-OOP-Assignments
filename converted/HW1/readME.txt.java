import java.util.*;

public class HexGame {

    static final int SIZE = 8;
    static char[][] board = new char[SIZE][SIZE];
    static boolean[][] visited = new boolean[SIZE][SIZE];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read the board (expects SIZE lines each with SIZE characters: '.', 'x', 'o')
        for (int i = 0; i < SIZE; i++) {
            String line = scanner.nextLine();
            String[] tokens = line.trim().split("\\s+");
            for (int j = 0; j < SIZE && j < tokens.length; j++) {
                board[i][j] = tokens[j].charAt(0);
            }
        }

        String winner = findWinner();
        System.out.println(winner);
    }

    // X goes from left to right, O goes from up to down.
    // The game searches for the minimum indexes (first found coordinates).
    static String findWinner() {
        // Check X: must connect leftmost column (j == 0) to rightmost column (j == SIZE-1)
        for (int i = 0; i < SIZE; i++) {
            if (board[i][0] == 'x') {
                clearVisited();
                if (dfsX(i, 0)) {
                    return "x wins";
                }
            }
        }

        // Check O: must connect top row (i == 0) to bottom row (i == SIZE-1)
        for (int j = 0; j < SIZE; j++) {
            if (board[0][j] == 'o') {
                clearVisited();
                if (dfsO(0, j)) {
                    return "o wins";
                }
            }
        }

        return "No winner";
    }

    static boolean dfsX(int row, int col) {
        if (col == SIZE - 1) {
            return true;
        }
        visited[row][col] = true;

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int nr = row + dr[k];
            int nc = col + dc[k];
            if (isValid(nr, nc) && !visited[nr][nc] && board[nr][nc] == 'x') {
                if (dfsX(nr, nc)) {
                    return true;
                }
            }
        }
        return false;
    }

    static boolean dfsO(int row, int col) {
        if (row == SIZE - 1) {
            return true;
        }
        visited[row][col] = true;

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        for (int k = 0; k < 4; k++) {
            int nr = row + dr[k];
            int nc = col + dc[k];
            if (isValid(nr, nc) && !visited[nr][nc] && board[nr][nc] == 'o') {
                if (dfsO(nr, nc)) {
                    return true;
                }
            }
        }
        return false;
    }

    static boolean isValid(int r, int c) {
        return r >= 0 && r < SIZE && c >= 0 && c < SIZE;
    }

    static void clearVisited() {
        for (int i = 0; i < SIZE; i++) {
            Arrays.fill(visited[i], false);
        }
    }
}