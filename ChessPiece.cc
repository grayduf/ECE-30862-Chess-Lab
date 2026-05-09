#include "ChessPiece.hh"
#include "ChessBoard.hh"

namespace Student {
    ChessPiece::ChessPiece(ChessBoard &board, Color color, Type type, int row, int column)
        : board(board), color(color), type(type), row(row), column(column), pieceMoved(false) {}
    
        Color ChessPiece::getColor() {
            return color;
        }

        Type ChessPiece::getType() {
            return type;
        }

        int ChessPiece::getRow() {
            return row;
        }

        int ChessPiece::getColumn() {
            return column;
        }

        bool ChessPiece::getPieceMoved() {
            return pieceMoved;
        }

        void ChessPiece::setPieceMovedTrue() {
            pieceMoved = true;
        }

        void ChessPiece::setPosition(int row, int column) {
            this->row = row;
            this->column = column;
        }
}

