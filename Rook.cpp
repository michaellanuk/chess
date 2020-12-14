#include <iostream>

#include "Rook.h"

Rook::Rook(std::string team) :
    team(team) {}

std::string Rook::getTeam() {
    return team;
}

std::string Rook::getPieceName() {
    return "Rook";
}

void Rook::printSymbol() {
    if (team == "white") {
        std::cout << "♖";
    } else {
        std::cout << "♜";
    }
}

bool Rook::isMoveValid(const char sourceSquare[2], 
    const char destinationSquare[2], Piece* board[8][8]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    if (!checkVerticalsAndHorizontals(toRow, toColumn, fromRow, fromColumn)) {
        return false;
    }

    /* if moving vertically */
    if (toColumn == fromColumn) {
        if (!isVerticalPathClear(toRow, fromRow, fromColumn, board)) {
            return false;
        }
    }

    /* if moving horizontally */
    if (toRow == fromRow) {
        if (!isHorizontalPathClear(toColumn, fromColumn, fromRow, board)) {
            return false;
        }
    }

    return true;
}