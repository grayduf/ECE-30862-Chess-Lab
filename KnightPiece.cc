#include "KnightPiece.hh"

namespace Student {
    KnightPiece::KnightPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, Knight, row, column) {}

    bool KnightPiece::canMoveToLocation(int toRow, int toColumn) {
        bool twoRows = (((getRow() - toRow) == 2) || ((getRow() - toRow) == -2)); // abs(row change) = 2
        bool oneRow = (((getRow() - toRow) == 1) || ((getRow() - toRow) == -1)); // abs(row change) = 1
        bool twoCols = (((getColumn() - toColumn) == 2) || ((getColumn() - toColumn) == -2)); // abs(col change) = 2
        bool oneCol = (((getColumn() - toColumn) == 1) || ((getColumn() - toColumn) == -1)); // abs(col change) = 1

        return (twoRows && oneCol) || (twoCols && oneRow);
    }

    const char* KnightPiece::toString() {
        return (getColor() == Black) ? "\u265E" : "\u2658";
    }
}