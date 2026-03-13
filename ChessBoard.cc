#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol) : numRows(numRow), numCols(numCol)
{
    board.resize(numRows);
    for (int i = 0; i < numRows; i++){
        board.at(i).resize(numCols, nullptr);
    }
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

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
    if (board.at(startRow).at(startColumn) != nullptr) {
        delete board.at(startRow).at(startColumn);
        board.at(startRow).at(startColumn) = nullptr;
    }

    ChessPiece* newPiece = nullptr;

    if (ty == Pawn) {
        newPiece = new PawnPiece(*this, col, startRow, startColumn);
    } else if (ty == Rook) {
        newPiece = new RookPiece(*this, col, startRow, startColumn);
    } else if (ty == Bishop) {
        newPiece = new BishopPiece(*this, col, startRow, startColumn);
    } else if (ty == King) {
        newPiece = new KingPiece(*this, col, startRow, startColumn);
    }

    board.at(startRow).at(startColumn) = newPiece;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
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

    return true;
}