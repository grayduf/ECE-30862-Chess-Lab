#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "QueenPiece.hh"
#include "KnightPiece.hh"
#include "KingPiece.hh"

namespace Student {
    using Student::ChessBoard;

    ChessBoard::ChessBoard(int numRow, int numCol) : numRows(numRow), numCols(numCol)
    {
        board.resize(numRows);
        for (int i = 0; i < numRows; i++){
            board.at(i).resize(numCols, nullptr);
        }
    }

    ChessBoard::~ChessBoard() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (board.at(i).at(j) != nullptr) { // TODO: can all board.at(i).at(j) be changed to getPiece() ?
                    removePiece(i, j);
                }
            }
        }
    }

    void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
    {
        if (board.at(startRow).at(startColumn) != nullptr) {
            removePiece(startRow, startColumn);
        }

        ChessPiece* newPiece = nullptr;

        if (ty == Pawn) {
            newPiece = new PawnPiece(*this, col, startRow, startColumn);
        } else if (ty == Rook) {
            newPiece = new RookPiece(*this, col, startRow, startColumn);
        } else if (ty == Bishop) {
            newPiece = new BishopPiece(*this, col, startRow, startColumn);
        } else if (ty == Queen) {
            newPiece = new QueenPiece(*this, col, startRow, startColumn);
        } else if (ty == Knight) {
            newPiece = new KnightPiece(*this, col, startRow, startColumn);
        } else if (ty == King) {
            newPiece = new KingPiece(*this, col, startRow, startColumn);
            kingPieces.push_back(newPiece);
        } //else {
            // exit(1) // TODO: invalid piece type
        //}

        if(newPiece->getColor() == White) {
            whitePieces.push_back(newPiece);
        } else {
            blackPieces.push_back(newPiece);
        }

        board.at(startRow).at(startColumn) = newPiece;
    }

    bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
        ChessPiece* selectedPiece = getPiece(fromRow, fromColumn);
        if(isValidMove(fromRow, fromColumn, toRow, toColumn) && selectedPiece != nullptr && selectedPiece->getColor() == turn) {
            capturePiece(fromRow, fromColumn, toRow, toColumn);
            changeTurns();
            return true;
        } else {
            return false;
        }
    }

    bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
    {
        if(!isPossibleMove(fromRow, fromColumn, toRow, toColumn)) {
            return false;
        }

        if(willMoveCheckKing(fromRow, fromColumn, toRow, toColumn)) {
            return false;
        }

        return true;
    }

    bool ChessBoard::isPieceUnderThreat(int row, int column) {
        if(getPiece(row, column) != nullptr) {
            std::vector<ChessPiece *> enemyPieces = getPiece(row, column)->getColor() == White ? blackPieces : whitePieces;
            for (const auto& element : enemyPieces) {
                if(isPossibleMove(element->getRow(), element->getColumn(), row, column)) {
                    return true;
                }
            }
        }
        return false;
    }

    std::ostringstream ChessBoard::displayBoard()
    {
        std::ostringstream outputString;
        // top scale
        outputString << "  ";
        for (int i = 0; i < numCols; i++){
            outputString << i << " ";
        }
        outputString << std::endl << "  ";
        // top border
        for (int i = 0; i < numCols; i++){
            outputString << "– ";
        }
        outputString << std::endl;

        for (int row = 0; row < numRows; row++){
            outputString << row << "|";
            for (int column = 0; column < numCols; column++){
                ChessPiece *piece = board.at(row).at(column);
                outputString << (piece == nullptr ? " " : piece->toString()) << " ";
            }
            outputString << "|" << std::endl;
        }

        // bottom border
        outputString << "  ";
        for (int i = 0; i < numCols; i++){
            outputString << "– ";
        }
        outputString << std::endl << std::endl;

        return outputString;
    }

    bool ChessBoard::isPossibleMove(int fromRow, int fromColumn, int toRow, int toColumn) {
        if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols ||
            toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols) {
            return false;
        }

        ChessPiece* selectedPiece = board.at(fromRow).at(fromColumn);
        if (selectedPiece == nullptr) {
            return false;
        }

        if (fromRow == toRow && fromColumn == toColumn) {
            return false;
        }

        ChessPiece* targetPiece = board.at(toRow).at(toColumn);
        if (targetPiece != nullptr && targetPiece->getColor() == selectedPiece->getColor()) {
            return false;
        }

        if (!selectedPiece->canMoveToLocation(toRow, toColumn)) {
            return false;
        }

        if(selectedPiece->getType() != Knight) {
            int rowStep = 0; // stays zero if toRow == fromRow
            if (toRow > fromRow) rowStep = 1;
            else if (toRow < fromRow) rowStep = -1;

            int colStep = 0; // stays zero if toColumn == fromColumn
            if (toColumn > fromColumn) colStep = 1;
            else if (toColumn < fromColumn) colStep = -1;

            int currRow = fromRow + rowStep;
            int currColumn = fromColumn + colStep;

            if ((selectedPiece->getType() == Pawn && colStep == 0 && targetPiece != nullptr) ||
                (selectedPiece->getType() == Pawn && colStep != 0 && targetPiece == nullptr)) {
                // a pawn can't take a piece in front of it, and can't move diagonally if a piece isn't there
                return false;
            }

            while (currRow != toRow || currColumn != toColumn) {
                if (board.at(currRow).at(currColumn) != nullptr) {
                    return false;
                }
                currRow += rowStep; 
                currColumn += colStep;
            }
        }

        return true;
    }

    bool ChessBoard::willMoveCheckKing(int fromRow, int fromColumn, int toRow, int toColumn) {
        ChessPiece* movingPiece = board.at(fromRow).at(fromColumn);
        ChessPiece* targetPiece = board.at(toRow).at(toColumn);
        Color myColor = movingPiece->getColor();
        
        // manually simulate move on the board
        board.at(toRow).at(toColumn) = movingPiece;
        board.at(fromRow).at(fromColumn) = nullptr;

        // temp update the moving piece's pos 
        int origRow = fromRow;
        int origCol = fromColumn;
        movingPiece->setPosition(toRow, toColumn);

        bool isKingChecked = false;
        for (ChessPiece* king : kingPieces) {
            if (king->getColor() == myColor) {
                if (isPieceUnderThreat(king->getRow(), king->getColumn())) {
                    isKingChecked = true;
                    break;
                }
            }
        }

        //undo the simulated move
        board.at(origRow).at(origCol) = movingPiece;
        board.at(toRow).at(toColumn) = targetPiece;
        movingPiece->setPosition(origRow, origCol);

        return isKingChecked;
    }

    void ChessBoard::removePiece(int row, int column) {
        ChessPiece* p = board.at(row).at(column);
        if(p != nullptr) {
            // Manual vector removal to avoid <algorithm>
            auto& vec = (p->getColor() == White) ? whitePieces : blackPieces;
            for (auto it = vec.begin(); it != vec.end(); ) {
                if (*it == p) it = vec.erase(it);
                else ++it;
            }

            if(p->getType() == King) {
                for (auto it = kingPieces.begin(); it != kingPieces.end(); ) {
                    if (*it == p) it = kingPieces.erase(it);
                    else ++it;
                }
            }
            
            delete p;
            board.at(row).at(column) = nullptr;
        }
    }

    void ChessBoard::capturePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
        ChessPiece* selectedPiece = getPiece(fromRow, fromColumn);
        if(board.at(toRow).at(toColumn) != nullptr) {
            removePiece(toRow, toColumn);
        }
        if(selectedPiece != nullptr) {
            // check for pawn promotion
            if(selectedPiece->getType() == Pawn &&
               ((selectedPiece->getColor() == White && toRow == 0) || (selectedPiece->getColor() == Black && toRow == numRows - 1))) {
                createChessPiece(selectedPiece->getColor(), Queen, toRow, toColumn);
                removePiece(fromRow, fromColumn);
            } else {
                selectedPiece->setPosition(toRow, toColumn);
                board.at(toRow).at(toColumn) = selectedPiece;
            }
        }
        board.at(fromRow).at(fromColumn) = nullptr;
    }

    void ChessBoard::changeTurns() {
        turn = turn == White ? Black : White;
    }
}