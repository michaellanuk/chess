#ifndef ROOK_H
#define ROOK_H

#include <string>

#include "Piece.h"

class Rook : public Piece{
    private:
        std::string team;
    public:
        Rook(std::string team);
        std::string getTeam();
        std::string getPieceName();
        void printSymbol();
        bool isMoveValid(const char sourceSquare[2], 
            const char destinationSquare[2], Piece* board[8][8]);
};

#endif