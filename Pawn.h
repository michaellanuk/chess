#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    private:
        std::string team;
    public:
        Pawn(std::string team);
        std::string getTeam();
        std::string getPieceName();
        void printSymbol();
        virtual bool isMoveValid(const char sourceSquare[2], 
            const char destinationSquare[2], Piece* board[8][8]);
        bool checkPawnsMove(int toRow, int toColumn, int fromRow, 
            int fromColumn, Piece* board[8][8]);
};

#endif