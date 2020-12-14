#include "Bishop.h"

Bishop::Bishop(std::string team) :
    team(team) {}

std::string Bishop::getTeam() {
    return team;
}

std::string Bishop::getPieceName() {
    return "Bishop";
}

void Bishop::printSymbol() {
    if (team == "white") {
        std::cout << "♗";
    } else {
        std::cout << "♝";
    }
}

bool Bishop::isMoveValid(const char sourceSquare[2], 
    const char destinationSquare[2], Piece* board[8][8]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    if (!checkDiagonals(toRow, toColumn, fromRow, fromColumn)) {
        return false;
    }

    if (!isDiagonalPathClear(toRow, toColumn, fromRow, fromColumn, board)) {
        return false;
    }
   
    return true;
}