#include "BishopPiece.hh"

namespace Student {
    BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, Bishop, row, column) {}

    bool BishopPiece::canMoveToLocation(int toRow, int toColumn) {
        return (((getRow() - toRow) == (getColumn() - toColumn)) ||
                ((getRow() - toRow) == (toColumn - getColumn())));
    }

    const char* BishopPiece::toString() {
        return (getColor() == Black) ? "\u265D" : "\u2657";
    }
}