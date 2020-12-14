#include "Queen.h"

Queen::Queen(std::string team) :
    team(team) {}

std::string Queen::getTeam() {
    return team;
}

std::string Queen::getPieceName() {
    return "Queen";
}

void Queen::printSymbol() {
    if (team == "white") {
        std::cout << "♕";
    } else {
        std::cout << "♛";
    }
}

bool Queen::isMoveValid(const char sourceSquare[2], 
    const char destinationSquare[2], Piece* board[8][8]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    /* if moving horizontally */
    if (toRow == fromRow) {
        if (!checkVerticalsAndHorizontals(toRow, toColumn, fromRow, 
            fromColumn)) {
            return false;
        }
        if (!isHorizontalPathClear(toColumn, fromColumn, fromRow, board)) {
            return false;
        }
    }

    /* if moving vertically */
    if (toColumn == fromColumn) {
        if (!checkVerticalsAndHorizontals(toRow, toColumn, fromRow, 
            fromColumn)) {
            return false;
        }
        if (!isVerticalPathClear(toRow, fromRow, fromColumn, board)) {
            return false;
        }
    }

    /* if moving diagonally */
    if (toRow != fromRow && toColumn != fromColumn) {
        if (!checkDiagonals(toRow, toColumn, fromRow, fromColumn)) {
            return false;
        }
        if (!isDiagonalPathClear(toRow, toColumn, fromRow, fromColumn, 
            board)) {
            return false;
        }
    }
    
    return true;
}