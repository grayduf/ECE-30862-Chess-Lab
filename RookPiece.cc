#include "RookPiece.hh"

namespace Student {
    RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, Rook, row, column) {}

    bool RookPiece::canMoveToLocation(int toRow, int toColumn) {
        // Don't need XOR here because both would only be true if the piece did not move
        //      which is checked for in isValidMove().
        return (getRow() == toRow || getColumn() == toColumn);
    }

    const char* RookPiece::toString() {
        return (getColor() == Black) ? "\u265C" : "\u2656";
    }
}