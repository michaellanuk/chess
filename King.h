#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    private:
        std::string team;
        bool checked;
    public:
        King(std::string team);
        std::string getTeam();
        std::string getPieceName();
        bool getCheckedStatus();
        void setCheckedStatus(bool check);
        void printSymbol();
        bool isMoveValid(const char sourceSquare[2], 
            const char destinationSquare[2], Piece* board[8][8]);
};

#endif