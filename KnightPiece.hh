#ifndef __KNIGHTPIECE_H__
#define __KNIGHTPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Knight chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class KnightPiece : public ChessPiece
    {
    public:
        KnightPiece(ChessBoard &board, Color color, int row, int column);
        virtual bool canMoveToLocation(int toRow, int toColumn) override;
        virtual const char *toString() override;
    };
}

#endif
