#ifndef __QUEENPIECE_H__
#define __QUEENPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Queen chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class QueenPiece : public ChessPiece
    {
    public:
        QueenPiece(ChessBoard &board, Color color, int row, int column);
        virtual bool canMoveToLocation(int toRow, int toColumn) override;
        virtual const char *toString() override;
    };
}

#endif
