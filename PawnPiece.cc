#include "PawnPiece.hh"
#include "ChessBoard.hh"

namespace Student {
    PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column)
        : ChessPiece(board, color, Pawn, row, column) {}

    bool PawnPiece::canMoveToLocation(int toRow, int toColumn) {
        int rowDirection = (getColor() == Black) ? 1 : -1;
        int rowChange = toRow - getRow();
        bool doubleMoveValid = ((getColor() == Black && getRow() == 1) ||
                                (getColor() == White && getRow() == 6));

        if(toColumn == getColumn() && rowChange == rowDirection) {
            // Regular move forward by 1
            // toRow - getRow is positive 1 for Black
            return true;
        } 
        else if(doubleMoveValid && toColumn == getColumn() && (2 * rowDirection) == rowChange) {
                // moves two squares the first time the piece is moved
                return true;
        }
        else if(((toColumn - getColumn() == 1) || (toColumn - getColumn() == -1)) && rowChange == rowDirection) {
                // moves diagonally to capture enemy piece
                // isValidMove() checks if enemy piece is present
                return true;
        }
        else {
            return false;
        }
    }
    
    const char* PawnPiece::toString() {
        return (getColor() == Black) ? "\u265F" : "\u2659";
    }
}