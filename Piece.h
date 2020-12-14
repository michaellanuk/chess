#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>

class Piece {
    public:
        virtual std::string getTeam() = 0;
        virtual std::string getPieceName() = 0;
        virtual void printSymbol() = 0;
        virtual bool isMoveValid(const char sourceSquare[2], 
            const char destinationSquare[2], Piece* board[8][8]) = 0;
        virtual ~Piece() = default;

        bool checkDiagonals(int toRow, int toColumn, int fromRow, 
            int fromColumn);
        bool checkVerticalsAndHorizontals(int toRow, int toColumn, 
            int fromRow, int fromColumn);
        bool checkKnightsMove(int toRow, int toColumn, int fromRow, 
            int fromColumn);
        bool checkKingsMove(int toRow, int toColumn, int fromRow, 
            int fromColumn);

        bool isDiagonalPathClear(int toRow, int toColumn, int fromRow, 
            int fromColumn, Piece* board[8][8]);
        bool isHorizontalPathClear(int toColumn, int fromColumn, int row, 
            Piece* board[8][8]);
        bool isVerticalPathClear(int toRow, int fromRow, int column, 
            Piece* board[8][8]);
};

#endif