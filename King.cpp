#include "King.h"

King::King(std::string team) :
    team(team), checked(false) {}

std::string King::getTeam() {
    return team;
}

std::string King::getPieceName() {
    return "King";
}

bool King::getCheckedStatus() {
    return checked;
}

void King::setCheckedStatus(bool check) {
    checked = check;
}

void King::printSymbol() {
    if (team == "white") {
        std::cout << "♔";
    } else {
        std::cout << "♚";
    }
}

bool King::isMoveValid(const char sourceSquare[2], 
    const char destinationSquare[2], Piece* board[8][8]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    /* check if square is off board when calling isMoveValid()
    from isKingCheckMate() */
    if (toRow > 7 || toColumn > 7 || toRow < 0 || toColumn < 0) {
        return false;
    }
    if (fromRow > 7 || fromColumn > 7 || fromRow < 0 || fromColumn < 0) {
        return false;
    }

    /* check valid distance */
    if (!checkKingsMove(toRow, toColumn, fromRow, fromColumn)) {
        return false;
    }

    /* check if a piece on the same team is in the way */
    if (board[toRow][toColumn] != nullptr) {
        if (board[toRow][toColumn]->getTeam() == team) {
            return false;
        }
    }
    
    return true;
}