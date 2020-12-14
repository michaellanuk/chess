#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

ChessBoard::ChessBoard() {
    newGame();
}

ChessBoard::~ChessBoard() {
    clearBoard();
}

void ChessBoard::newGame() {
    /*--------INITIALISE CHESS BOARD--------*/

    /* create empty middle 4 rows */
    for (int row = 2; row < 6; row++) {
        for (int column = 0; column < 8; column++) {
            board[row][column] = nullptr;
        }
    }

    /* create pawns */
    for (int column = 0; column < 8; column++) {
        board[1][column] = new Pawn("black");
        board[6][column] = new Pawn("white");
    }

    /* create rooks */
    board[0][0] = new Rook("black");
    board[0][7] = new Rook("black");
    board[7][0] = new Rook("white");
    board[7][7] = new Rook("white");

    /* create knights */
    board[0][1] = new Knight("black");
    board[0][6] = new Knight("black");
    board[7][1] = new Knight("white");
    board[7][6] = new Knight("white");

    /* create bishops */
    board[0][2] = new Bishop("black");
    board[0][5] = new Bishop("black");
    board[7][2] = new Bishop("white");
    board[7][5] = new Bishop("white");

    /* create queens */
    board[0][3] = new Queen("black");
    board[7][3] = new Queen("white");

    /* create kings */
    blackKing = new King("black");
    board[0][4] = blackKing;
    whiteKing = new King("white");
    board[7][4] = whiteKing;

    std::cout << "A new chess game has started!" << std::endl;

    attackingPieceCoordinates.clear();
    playerTurn = "white";
    printBoard();
}

void ChessBoard::clearBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

void ChessBoard::resetBoard() {
    clearBoard();
    newGame();
}

void ChessBoard::printBoard() {
    std::cout << "\n\n";

    /* print top column labels */
    std::cout << "    ";
    for (char columnLetter = 'A'; columnLetter < 'I'; columnLetter++) {
        std::cout << columnLetter << ' ';
    }
    std::cout << '\n';
    std::cout << "  +-----------------+" << std::endl;
    for (int row = 0, rowNum = 8; row < 8 && rowNum > 0; row++, rowNum--) {
        /* print left row numbers */
        std::cout << rowNum << " | ";
        for (int column = 0; column < 8; column++) {
            if (board[row][column] == nullptr) {
                std::cout << ". ";
                continue;
            }
            board[row][column]->printSymbol();
            std::cout << ' ';
        }
        /* print right row numbers */
        std::cout << "| " << rowNum;
        std::cout << "\n";
    }
    std::cout << "  +-----------------+" << std::endl;
    /* print bottom column labels */
    std::cout << "    ";
    for (char columnLetter = 'A'; columnLetter < 'I'; columnLetter++) {
        std::cout << columnLetter << ' ';
    }

    std::cout << "\n\n";
}

void ChessBoard::submitMove(const char sourceSquare[2], 
    const char destinationSquare[2]) {
    if (sourceSquare == destinationSquare) {
        std::cerr << "Selected destination square is same as source square!" 
        << std::endl;
        return;
    }

    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    /* check if square coordinates are out-of-range */
    if (isSquareOffBoard(toRow, toColumn)) {
        std::cerr << "Selected destination square is off the board!" 
        << std::endl;
        std::cerr << "Please select a column from A to H and a row from 1 to 8"
         << std::endl;
        return;
    }
    if (isSquareOffBoard(fromRow, fromColumn)) {
        std::cerr << "Selected source square is off the board!" 
        << std::endl;
        std::cerr << "Please select a column from A to H and a row from 1 to 8"
         << std::endl;
        return;
    }

    auto currentPiece = board[fromRow][fromColumn];
    /* check for empty square */
    if (currentPiece == nullptr) {
        std::cerr << "There is no piece at position " << sourceSquare[0] 
        << sourceSquare[1] << '!' << std::endl;
        return;
    }
    std::string currentTeam = currentPiece->getTeam();

    /* check if current player's King is in check */
    
    int* coordinates = getKingCoordinates(currentTeam);
    if (isKingChecked(coordinates[0], coordinates[1], currentTeam)) {
        // store temporary piece found in destination square
        auto tempPiece = board[toRow][toColumn];
        hypotheticalMove(sourceSquare, destinationSquare);
        // If King is still in check after hypotheticalMove(), put pieces
        // back to their original squares and return.
        // Otherwise, just put pieces back and continue.
        int* newCoordinates = getKingCoordinates(currentTeam);
        if (isKingChecked(newCoordinates[0], newCoordinates[1], currentTeam)) {
            board[toRow][toColumn] = tempPiece;
            board[fromRow][fromColumn] = currentPiece;
            std::cerr << "Cannot move, " << currentTeam 
            << "'s King is in check!" << std::endl;
            return;
        }
        delete [] newCoordinates;
        board[toRow][toColumn] = tempPiece;
        board[fromRow][fromColumn] = currentPiece;
    }
    delete [] coordinates;

    /* check for correct player's turn */
    if (currentTeam != playerTurn) {
        std::cerr << "It is not " << currentTeam << "'s turn to move!" 
        << std::endl;
        return;
    }

    /* check if move is valid */
    if (!currentPiece->isMoveValid(sourceSquare, destinationSquare, board)) {
        std::cerr << currentTeam << "'s " << currentPiece->getPieceName() 
        << " cannot move to " << destinationSquare[0] << destinationSquare[1] 
        << std::endl;
        return;
    }

    /* append capture message if player moved to take opponent's piece */
    std::string captureMessage = "";
    auto pieceToCapture = board[toRow][toColumn];
    if (pieceToCapture != nullptr) {
        captureMessage = " taking " + pieceToCapture->getTeam() + "'s " 
        + pieceToCapture->getPieceName();
    }

    /* move currentPiece if all checks passed */
    auto temp = board[toRow][toColumn];
    board[toRow][toColumn] = currentPiece;
    board[fromRow][fromColumn] = nullptr;

    /*
    if the current player's King wasn't in check before, make sure
    that after validating and moving currentPiece, the King is still
    not in check.
    */
    int* coordinatesPostMove = getKingCoordinates(currentTeam);
    if (isKingChecked(coordinatesPostMove[0], coordinatesPostMove[1], 
        currentTeam)) {
        /* move pieces back */
        board[toRow][toColumn] = temp;
        board[fromRow][fromColumn] = currentPiece;
        std::cerr << "Making that move will leave " << currentTeam 
        << "'s King in check!" << std::endl;
        return;
    }
    delete [] coordinatesPostMove;

    std::cout << currentPiece->getTeam() << "'s " 
    << currentPiece->getPieceName() << " moves from " << sourceSquare[0] 
    << sourceSquare[1] << " to " << destinationSquare[0] 
    << destinationSquare[1] << captureMessage << std::endl;

    /* check if player has now checked opponent's King */
    std::string opponentsTeam;
    if (currentTeam == "black") {
        opponentsTeam = "white";
    } else {
        opponentsTeam = "black";
    }
    int* opponentsKingsCoordinates = getKingCoordinates(opponentsTeam);
    if (isKingChecked(opponentsKingsCoordinates[0], 
        opponentsKingsCoordinates[1], opponentsTeam)) {
        std::cout << opponentsTeam << "'s King is now in check!" << std::endl;
    }
    delete [] opponentsKingsCoordinates;

    
    if (isKingCheckMate(opponentsTeam)) {
        std::cout << "Checkmate on " << opponentsTeam << "! " << currentTeam 
        << " wins!!!" << std::endl;
    }

    switchTurn();
    printBoard();
}

/* 
following function makes move without checking validity so as to see if King
will still be in check after making the "hypothetical" move 
*/
void ChessBoard::hypotheticalMove(const char sourceSquare[2], 
    const char destinationSquare[2]) {
    int toRow = abs((destinationSquare[1] - '8'));
    int toColumn = (destinationSquare[0] - 'A');
    int fromRow = abs((sourceSquare[1] - '8'));
    int fromColumn = (sourceSquare[0] - 'A');

    auto piece = board[fromRow][fromColumn];

    board[toRow][toColumn] = piece;
    board[fromRow][fromColumn] = nullptr;
}

void ChessBoard::switchTurn() {
    if (playerTurn == "white") {
        playerTurn = "black";
    } else {
        playerTurn = "white";
    }
}

int* ChessBoard::getKingCoordinates(std::string team) {
    int* coordinates = new int[2];
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == nullptr) {
                continue;
            } else {
                if (board[i][j]->getPieceName() == "King" 
                && board[i][j]->getTeam() == team) {
                    coordinates[0] = i;
                    coordinates[1] = j;
                }
            }
        }
    }
    return coordinates;
}

/* check if any pieces of the opposing team can attack the King */
bool ChessBoard::isKingChecked(int row, int column, std::string kingsTeam) {
    char kingsRow = '8' - row;
    char kingsColumn = column + 'A';
    std::string kingsSquare;
    kingsSquare.push_back(kingsColumn);
    kingsSquare.push_back(kingsRow);
    const char* king = kingsSquare.c_str();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char sourceRow = '8' - i;
            char sourceColumn = j + 'A';
            std::string sourceSquare;
            sourceSquare.push_back(sourceColumn);
            sourceSquare.push_back(sourceRow);
            const char* piece = sourceSquare.c_str();
            if (board[i][j] != nullptr) {
                if(board[i][j]->isMoveValid(piece, king, board)
                && board[i][j]->getTeam() != kingsTeam
                && board[i][j]->getPieceName() != "King") {
                    attackingPieceCoordinates.push_back(sourceSquare);
                    return true;
                }
            }
        }
    }
    attackingPieceCoordinates.clear();

    return false;
}

bool ChessBoard::isKingCheckMate(std::string team) {
    
    int* coordinates = getKingCoordinates(team);
    int row = coordinates[0];
    int column = coordinates[1];
    auto currentKing = board[row][column];
    
    if (isKingChecked(row, column, team)) {
        char kingsRow = '8' - row;
        char kingsColumn = column + 'A';
        std::string kingsSquare;
        kingsSquare.push_back(kingsColumn);
        kingsSquare.push_back(kingsRow);
        const char* king = kingsSquare.c_str();

        /*
        check if King can move anywhere and, if it can, that
        it won't be in check 
        */
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) { // avoid checking against own square
                    continue;
                }
                char destRow = kingsRow + i;
                char destColumn = kingsColumn + j;
                std::string destination;
                destination.push_back(destColumn);
                destination.push_back(destRow);
                const char* piece = destination.c_str();
                if (currentKing->isMoveValid(king, piece, board)
                && !isKingChecked(row + i, column + j, team)) {
                    return false;
                }
            }
        }
        delete [] coordinates;

        /* can attacking piece be taken? */
        std::string destination = attackingPieceCoordinates[0];
        const char* destinationSquare = destination.c_str();

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                char sourceRow = '8' - i;
                char sourceColumn = j + 'A';
                std::string source;
                source.push_back(sourceColumn);
                source.push_back(sourceRow);
                const char* sourceSquare = source.c_str();
                if (board[i][j] != nullptr) {
                    if (board[i][j]->isMoveValid(sourceSquare, 
                    destinationSquare, board)
                    && board[i][j]->getTeam() == team) {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }

    return false;
}

/* check square exists to avoid segmentation fault */
bool ChessBoard::isSquareOffBoard(int row, int column) {
    if (row > 7 || column > 7 || row < 0 || column < 0) {
        return true;
    }
    return false;
}