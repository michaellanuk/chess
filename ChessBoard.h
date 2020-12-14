#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

#include <iostream>
#include <vector>

class ChessBoard {
    private:
        Piece* board[8][8];
        std::string playerTurn;
        King* blackKing;
        King* whiteKing;
        std::vector<std::string> attackingPieceCoordinates;

    public:
        ChessBoard();
        ~ChessBoard();

        void newGame();
        void clearBoard();
        void resetBoard();

        void printBoard();
        void submitMove(const char sourceSquare[2], const char destinationSquare[2]);
        void hypotheticalMove(const char sourceSquare[2], 
            const char destinationSquare[2]);
        void switchTurn();

        int* getKingCoordinates(std::string team);
        bool isKingChecked(int row, int column, std::string kingsTeam);
        bool isKingCheckMate(std::string team);

        bool isSquareOffBoard(int row, int column);
};

#endif