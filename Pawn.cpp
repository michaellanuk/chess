#include "Pawn.h"

Pawn::Pawn(std::string team) :
    team(team) {}

std::string Pawn::getTeam() {
    return team;
}

std::string Pawn::getPieceName() {
    return "Pawn";
}

void Pawn::printSymbol() {
    if (team == "white") {
        std::cout << "♙";
    } else {
        std::cout << "♟";
    }
}

bool Pawn::isMoveValid(const char sourceSquare[2], 
    const char destinationSquare[2], Piece* board[8][8]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    if (!checkPawnsMove(toRow, toColumn, fromRow, fromColumn, board)) {
        return false;
    }
    
    return true;
}

bool Pawn::checkPawnsMove(int toRow, int toColumn, int fromRow, 
    int fromColumn, Piece* board[8][8]) {
    if (abs(toRow - fromRow) > 2) {
                return false;
    }
    
    if (team == "black") {
        /* check if black's pawn tries to move backwards or sideways */
        if (toRow <= fromRow) {
            return false;
        }
        /* check if a piece is blocking the pawn's path */
        if (toRow == fromRow + 1 && toColumn == fromColumn 
            && board[toRow][toColumn] != nullptr) {
            return false;
        }
        /* check if black's pawn's first move is valid */
        if (fromRow == 1 && toColumn == fromColumn 
            && abs(toRow - fromRow) == 2) {
            return true;
        }
        /* check if pawn can take opponent's piece diagonally */
        if (abs(toRow - fromRow) == 1 && abs(toColumn - fromColumn) == 1) {
            if (board[toRow][toColumn] != nullptr) {
                return true;
            }
            return false;
        }
        if (abs(toRow - fromRow) > 1 || abs(toColumn - fromColumn) > 1) {
            return false;
        }
    }

    if (team == "white") {
        /* check if white's pawn tries to move backwards or sideways */
        if (toRow >= fromRow) {
            return false;
        }
        /* check if a piece is blocking the pawn's path */
        if (toRow == fromRow - 1 && toColumn == fromColumn 
            && board[toRow][toColumn] != nullptr) {
            return false;
        }
        /* check if white's pawn's first move is valid */
        if (fromRow == 6 && toColumn == fromColumn 
            && abs(toRow - fromRow) == 2) {
            return true;
        }
        /* check if pawn can take opponent's piece diagonally */
        if (abs(toRow - fromRow) == 1 && abs(toColumn - fromColumn) == 1) {
            if (board[toRow][toColumn] != nullptr) {
                return true;
            }
            return false;
        }
        if (abs(toRow - fromRow) > 1 || abs(toColumn - fromColumn) > 1) {
            return false;
        }
    }

    return true;
}
