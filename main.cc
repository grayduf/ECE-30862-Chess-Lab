#include <assert.h>
#include <iostream>
#include <string>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

void isValidScan(Student::ChessBoard &sBoard) {
    for(int i = 0; i < sBoard.getNumRows(); i++) {
        for(int j = 0; j < sBoard.getNumCols(); j++) {
            for(int x = 0; x < sBoard.getNumRows(); x++) {
                for(int y = 0; y < sBoard.getNumCols(); y++) {
                    bool valid = sBoard.isValidMove(i, j, x, y);
                    if(valid) {
                        std::cout << i << ", " << j << " -> " << x << ", " << y << std::endl;
                    }
                }
            }
        }
    }
}

void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    std::cout << sBoard.displayBoard().str() << std::endl;

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    isValidScan(sBoard);

    return;
}

void test_part3_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // b k 0 0
    // w k 3 0
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(Black, King, 0, 0);
    sBoard.createChessPiece(White, King, 3, 0);

    std::cout << sBoard.displayBoard().str() << std::endl;

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    //isValidScan(sBoard);

    return;
}

int main()
{
    //test_part1_4x4_1();
    test_part3_4x4_1();
    return EXIT_SUCCESS;
}
