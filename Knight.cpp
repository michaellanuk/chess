#include "Knight.h"

Knight::Knight(std::string team) :
    team(team) {}
    
std::string Knight::getTeam() {
    return team;
}

std::string Knight::getPieceName() {
    return "Knight";
}

void Knight::printSymbol() {
    if (team == "white") {
        std::cout << "♘";
    } else {
        std::cout << "♞";
    }
}

bool Knight::isMoveValid(const char sourceSquare[2], 
    const char destinationSquare[2], Piece* board[8][8]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    if (!checkKnightsMove(toRow, toColumn, fromRow, fromColumn)) {
        return false;
    }

    /* do not need to check clear path as Knight can jump over other pieces */

    return true;
}