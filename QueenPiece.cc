#include "QueenPiece.hh"

namespace Student {
    QueenPiece::QueenPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, Queen, row, column) {}

    bool QueenPiece::canMoveToLocation(int toRow, int toColumn) {
        return (((getRow() - toRow) == (getColumn() - toColumn)) ||
                ((getRow() - toRow) == (toColumn - getColumn())) ||
                (getColumn() == toColumn) ||
                (getRow() == toRow));
    }

    const char* QueenPiece::toString() {
        return (getColor() == Black) ? "\u265B" : "\u2655";
    }
}