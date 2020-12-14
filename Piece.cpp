#include "Piece.h"

bool Piece::checkDiagonals(int toRow, int toColumn, int fromRow, 
    int fromColumn) {
    if (abs(toRow - fromRow) == abs(toColumn - fromColumn)) {
        return true;
    }
    return false;
}

bool Piece::checkVerticalsAndHorizontals(int toRow, int toColumn, 
    int fromRow, int fromColumn) {
    if (toRow == fromRow || toColumn == fromColumn) {
        return true;
    }
    return false;
}

bool Piece::checkKnightsMove(int toRow, int toColumn, int fromRow, 
    int fromColumn) {
    if (abs(toRow - fromRow) == 2) {
        if (abs(toColumn - fromColumn) == 1) {
            return true;
        }
    }

    if (abs(toRow - fromRow) == 1) {
        if (abs(toColumn - fromColumn) == 2) {
            return true;
        }
    } 

    return false;
}

bool Piece::checkKingsMove(int toRow, int toColumn, int fromRow, 
    int fromColumn) {
    if (abs(toRow - fromRow) > 1 || abs(toColumn - fromColumn) > 1) {
        return false;
    }

    return true;
}

bool Piece::isDiagonalPathClear(int toRow, int toColumn, int fromRow, 
    int fromColumn, Piece* board[8][8]) {
    /* check upper right diagonal path */
    if (toRow < fromRow && toColumn > fromColumn) {
        for (int i = fromRow - 1, j = fromColumn + 1; i > toRow 
            && j < toColumn; i--, j++) {
            if (board[i][j] != nullptr) {
                return false;
            }
        }
    }
    /* check upper left diagonal path */
    if (toRow < fromRow && toColumn < fromColumn) {
        for (int i = fromRow - 1, j = fromColumn - 1; i > toRow 
            && j > toColumn; i--, j--) {
            if (board[i][j] != nullptr) {
                return false;
            }
        }
    }
    /* check lower right diagonal path */
    if (toRow > fromRow && toColumn > fromColumn) {
        for (int i = fromRow + 1, j = fromColumn + 1; i < toRow 
            && j < toColumn; i++, j++) {
            if (board[i][j] != nullptr) {
                return false;
            }
        }
    }
    /* check lower left diagonal path */
    if (toRow > fromRow && toColumn < fromColumn) {
        for (int i = fromRow + 1, j = fromColumn - 1; i < toRow 
            && j > toColumn; i++, j--) {
            if (board[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
}

bool Piece::isHorizontalPathClear(int toColumn, int fromColumn, int row, 
    Piece* board[8][8]) {
    if (toColumn > fromColumn) {
        for (int i = fromColumn + 1; i < toColumn; i++) {
            if (board[row][i] != nullptr) {
                return false;
            }
        }
    }

    if (fromColumn > toColumn) {
        for (int i = toColumn + 1; i < fromColumn; i++) {
            if (board[row][i] != nullptr) {
                return false;
            }
        }
    }

    return true;
}

bool Piece::isVerticalPathClear(int toRow, int fromRow, int column, 
    Piece* board[8][8]) {
    if (toRow > fromRow) {
        for (int i = fromRow + 1; i < toRow; i++) {
            if (board[i][column] != nullptr) {
                return false;
            }
        }
    }

    if (toRow < fromRow) {
        for (int i = fromRow - 1; i > toRow; i--) {
            if (board[i][column] != nullptr) {
                return false;
            }
        }
    }
    
    return true;
}