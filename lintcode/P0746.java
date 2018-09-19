// https://www.lintcode.com/problem/design-tic-tac-toe/description
// 746. Design Tic-Tac-Toe

class GameEndException extends Exception {
    public GameEndException() {
        super("Game has been ended, cannot make any more moves");
    }
}

class AlreadyTakenException extends Exception {
    public AlreadyTakenException() {
        super("This place has been taken");
    }
}

class TicTacToe {
    private int[][] board;
    private boolean win = false;
    private int counter = 0;

    public TicTacToe() {
        board = new int[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = -1;
            }
        }
    }

    public boolean move(int row, int col) throws AlreadyTakenException,
           GameEndException {
        if (win) throw new GameEndException();
        if (board[row][col] != -1) throw new AlreadyTakenException();
        board[row][col] = (counter++) % 2;
        win = check();
        return win;
    }

    private boolean check() {
        // check row
        for (int i = 0; i < 3; i++) {
            int tot = 0;
            boolean unmarked = false;
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == -1) {
                    unmarked = true;
                    break;
                }
                tot += board[i][j];
            }
            if (!unmarked && (tot % 3) == 0) return true;
        }
        // check col
        for (int j = 0; j < 3; j++) {
            int tot = 0;
            boolean unmarked = false;
            for (int i = 0; i < 3; i++) {
                if (board[i][j] == -1) {
                    unmarked = true;
                    break;
                }
                tot += board[i][j];
            }
            if (!unmarked && (tot % 3) == 0) return true;
        }

        int tot = 0;
        boolean unmarked = false;
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == -1) {
                unmarked = true;
                break;
            }
            tot += board[i][i];
        }
        if (!unmarked && (tot % 3) == 0) return true;

        tot = 0;
        unmarked = false;
        for (int i = 0; i < 3; i++) {
            if (board[i][2-i] == -1) {
                unmarked = true;
                break;
            }
            tot += board[i][2-i];
        }
        if (!unmarked && (tot % 3) == 0) return true;

        return false;
    }
}
