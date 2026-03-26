#include "KingPiece.hh"

namespace Student {
    KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, King, row, column) {}

    bool KingPiece::canMoveToLocation(int toRow, int toColumn) {
        bool no_move = toRow == getRow() && toColumn == getColumn(); // piece didn't move == illegal
        bool in_row_bounds = (toRow <= getRow() + 1) && (toRow >= getRow() - 1); // row - 1 <= toRow <= row + 1
        bool in_col_bounds = (toColumn <= getColumn() + 1) && (toColumn >= getColumn() - 1); // col - 1 <= toCol <= col + 1
        return in_row_bounds && in_col_bounds && !no_move; // move is one square away from current position
    }

    const char* KingPiece::toString() {
        return (getColor() == Black) ? "\u265A" : "\u2654";
    }
}