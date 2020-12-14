#ifndef BISHOP_H
#define BISHOP_H

#include <string>

#include "Piece.h"

class Bishop : public Piece {
    private:
        std::string team;
    public:
        Bishop(std::string team);
        std::string getTeam();
        std::string getPieceName();
        void printSymbol();
        bool isMoveValid(char const sourceSquare[2], 
            char const destinationSquare[2], Piece* board[8][8]);
};

#endif