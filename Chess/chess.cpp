#include "chess.h"

using namespace std;

const std::string RESET = "\033[0m";
const std::string BOLD_WHITE = "\033[1;37m";
const std::string BOLD_RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";

Square::Square()
{
	this->piece = EMPTY;
	this->color = NONE;
}

void Square::setSpace(Square* space)
{
	this->color = space->getColor();
	this->piece = space->getPiece();
}

void Square::setEmpty()
{
	this->color = NONE;
	this->piece = EMPTY;
}

Piece Square::getPiece()
{
	return this->piece;
}

Color Square::getColor()
{
	return this->color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	this->piece = p;
	this->color = c;
}

void Board::printBoard() {
    cout << GREEN << "      0  1  2  3  4  5  6  7 " << RESET << endl;
    cout << GREEN << " " << RESET << endl;
    for (int i = 0; i < 8; i++) {
        cout << GREEN << " " << i << "   " << RESET;
        for (int j = 0; j < 8; j++) {
            Piece p = square[i][j].getPiece();
            Color c = square[i][j].getColor();

            string color_code = (c == WHITE) ? BOLD_WHITE : BOLD_RED;

            switch (p) {
                case KING:
                    cout << color_code << " K " << RESET;
                    break;
                case QUEEN:
                    cout << color_code << " Q " << RESET;
                    break;
                case BISHOP:
                    cout << color_code << " B " << RESET;
                    break;
                case KNIGHT:
                    cout << color_code << " N " << RESET;
                    break;
                case ROOK:
                    cout << color_code << " R " << RESET;
                    break;
                case PAWN:
                    cout << color_code << " P " << RESET;
                    break;
                case EMPTY:
                    cout << " " << "-" << " ";
                    break;
                default:
                    cout << "XXX";
                    break;
            }
        }
        cout << endl;
    }
}

bool Board::doMove() {
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
        (turn == WHITE) ? cout << "\nWhite's turn" << endl : cout << "\nBlack's turn" << endl;
        if (turn == WHITE) {
            if (is_in_check(this->WhiteKingX, this->WhiteKingY) != KING) {
                if (!is_checkmated(this->WhiteKingX, this->WhiteKingY)) {
                    cout<<"!!!Your king is in check!!!"<<endl;
                    static bool check = true;
                }
                else {
                    cout << "BLACK WINS" << endl;
			        return false;
                }
            }
        }
        else
            if (is_in_check(this->BlackKingX, this->BlackKingY) != KING) {
                if (!is_checkmated(this->BlackKingX, this->BlackKingY)) {
                    cout<<"!!!Your king is in check!!!"<<endl;
                    static bool check = true;
                }
                else if (is_checkmated(this->BlackKingX, this->BlackKingY)) {
                    cout << "WHITE WINS" << endl;
                    return false;
                }
            }
		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
        cout<<"White king is on "<<this->WhiteKingX<<" "<<this->WhiteKingY<<endl;
        cout<<"Black king is on "<<this->BlackKingX<<" "<<this->BlackKingY<<endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		if (getSquare(x1, y1)->getColor() == turn)
		{
			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << BOLD_RED << "Invalid move, try again." << RESET << endl;
			}
            else stop = true;
		}
		else
			cout << BOLD_RED << "That's not your piece. Try again." << RESET << endl;
	}

	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;
}

void Board::setBoard()
{
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[0][1].setPieceAndColor(KNIGHT, WHITE);
	square[0][2].setPieceAndColor(BISHOP, WHITE);
	square[0][3].setPieceAndColor(QUEEN, WHITE);
	square[0][4].setPieceAndColor(KING, WHITE);
	square[0][5].setPieceAndColor(BISHOP, WHITE);
	square[0][6].setPieceAndColor(KNIGHT, WHITE);
	square[0][7].setPieceAndColor(ROOK, WHITE);

	square[7][0].setPieceAndColor(ROOK, BLACK);
	square[7][1].setPieceAndColor(KNIGHT, BLACK);
	square[7][2].setPieceAndColor(BISHOP, BLACK);
	square[7][3].setPieceAndColor(QUEEN, BLACK);
	square[7][4].setPieceAndColor(KING, BLACK);
	square[7][5].setPieceAndColor(BISHOP, BLACK);
	square[7][6].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	this->BlackKingX = 7;
	this->BlackKingY = 4;
	this->WhiteKingX = 0;
	this->WhiteKingY = 4;

	for (int i = 0; i < 8; i++)
	{
		square[1][i].setPieceAndColor(PAWN, WHITE);
		square[6][i].setPieceAndColor(PAWN, BLACK);

	}

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[i][j].setPieceAndColor(EMPTY, NONE);
	}

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}
}

bool Board::playGame()
{
	system("cls");
	printBoard();
	return doMove();
}

Piece Board::is_in_check(int kingX, int kingY)
{
    for (int i=kingX+1; i<8; i++) {
        if (square[i][kingY].color != square[kingX][kingY].color && square[i][kingY].color != NONE) {
            if (this->square[i][kingY].piece == QUEEN) return QUEEN;
            else if (this->square[i][kingY].piece == ROOK) return ROOK;
            else break;
        }
        if (square[i][kingY].color == square[kingX][kingY].color) break;

        if (square[kingY][i].color != square[kingX][kingY].color && square[kingY][i].color != NONE) {
            if (this->square[kingY][i].piece == QUEEN) return QUEEN;
            else if (this->square[kingY][i].piece == ROOK) return ROOK;
            else break;
        }
        if (square[kingY][i].color == square[kingX][kingY].color) break;
    }

    for (int i=kingX-1; i>=0; i--) {
        if (square[i][kingY].color != square[kingX][kingY].color && square[i][kingY].color != NONE) {
            if (square[i][kingY].piece == QUEEN) return QUEEN;
            else if (square[i][kingY].piece == ROOK) return ROOK;
            else break;
        }
        if (square[i][kingY].color == square[kingX][kingY].color) break;

        if (square[kingY][i].color != square[kingX][kingY].color && square[kingY][i].color != NONE) {
            if (square[kingY][i].piece == QUEEN) return QUEEN;
            else if (square[kingY][i].piece == ROOK) return ROOK;
            else break;
        }
        if (square[kingY][i].color == square[kingX][kingY].color) break;
    }

    for (int i=kingX-1, j=kingY-1; i>=0, j>=0; i--,j--) {
        if (square[i][j].color != square[kingX][kingY].color && square[i][j].color != NONE) {
           if (square[i][j].piece == BISHOP) return BISHOP;
           else if (square[i][j].piece == QUEEN) return QUEEN;
           else break;
        }
        if (square[i][j].color == square[kingX][kingY].color) break;
    }

    for (int i=kingX+1, j=kingY+1; i<8, j<8; i++,j++) {
        if (square[i][j].color != square[kingX][kingY].color && square[i][j].color != NONE) {
            if (square[i][j].piece == BISHOP) return BISHOP;
            else if (square[i][j].piece == QUEEN) return QUEEN;
            else break;
        }
        if (square[i][j].color == square[kingX][kingY].color && square[i][j].color != NONE) break;
    }

    for (int i=kingX, j=kingY; i>=0, j<8; i--,j++) {
        if (square[i][j].color != square[kingX][kingY].color && square[i][j].color != NONE) {
           if (square[i][j].piece == BISHOP) return BISHOP;
           else if (square[i][j].piece == QUEEN) return QUEEN;
           else break;
        }
        if (square[i][j].color == square[kingX][kingY].color) break;
    }

    for (int i=kingX, j=kingY; i<8, j>=0; i++,j--) {
        if (square[i][j].color != square[kingX][kingY].color && square[i][j].color != NONE) {
            if (square[i][j].piece == BISHOP) return BISHOP;
            else if (square[i][j].piece == QUEEN) return QUEEN;
            else break;
        }
        if (square[i][j].color == square[kingX][kingY].color) break;
    }

    if (square[kingX-1][kingY-1].piece == PAWN && square[kingX-1][kingY-1].color == WHITE && square[kingX][kingY].color == BLACK) return PAWN;
    if (square[kingX+1][kingY+1].piece == PAWN && square[kingX+1][kingY+1].color == WHITE && square[kingX][kingY].color == BLACK) return PAWN;
    if (square[kingX+1][kingY-1].piece == PAWN && square[kingX+1][kingY-1].color == BLACK && square[kingX][kingY].color == WHITE) return PAWN;
    if (square[kingX-1][kingY+1].piece == PAWN && square[kingX-1][kingY+1].color == BLACK && square[kingX][kingY].color == WHITE) return PAWN;

    if (square[kingX-2][kingY+1].color != square[kingX][kingY].color && square[kingX-2][kingY+1].piece == KNIGHT) return KNIGHT;
    if (square[kingX+2][kingY+1].color != square[kingX][kingY].color && square[kingX+2][kingY+1].piece == KNIGHT) return KNIGHT;
    if (square[kingX-2][kingY-1].color != square[kingX][kingY].color && square[kingX-2][kingY-1].piece == KNIGHT) return KNIGHT;
    if (square[kingX-1][kingY-2].color != square[kingX][kingY].color && square[kingX-1][kingY-2].piece == KNIGHT) return KNIGHT;
    if (square[kingX-1][kingY+2].color != square[kingX][kingY].color && square[kingX-1][kingY+2].piece == KNIGHT) return KNIGHT;
    if (square[kingX+1][kingY+2].color != square[kingX][kingY].color && square[kingX+1][kingY+2].piece == KNIGHT) return KNIGHT;
    if (square[kingX+1][kingY-2].color != square[kingX][kingY].color && square[kingX+1][kingY-2].piece == KNIGHT) return KNIGHT;
    if (square[kingX+2][kingY-1].color != square[kingX][kingY].color && square[kingX+2][kingY-1].piece == KNIGHT) return KNIGHT;

    return KING;
}

bool Board::is_checkmated(int kingX, int kingY)
{
    if (!KingPossibleMoves(kingX, kingY) && !PawnPossibleMoves(kingX, kingY) &&
        !QueenPossibleMoves(kingX, kingY) && !KnightPossibleMoves(kingX, kingY) &&
        !BishopPossibleMoves(kingX, kingY) && !RookPossibleMoves(kingX, kingY)) return true;

    return false;
}

void Board::swap_pieces(Square *A, Square *B)
{
    Square C;
    C.setPieceAndColor(A->getPiece(), A->getColor());
    A->setSpace(B);
    B->setSpace(&C);
}

bool Board::KingPossibleMoves(int kingX, int kingY)
{
    int ok=0;

        Square *thisPiece = getSquare(kingX, kingY);

        Square *thatSpace = getSquare(kingX+1, kingY);
        if (square[kingX][kingY].getColor() != square[kingX+1][kingY].getColor() && kingX+1<8) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX+1, kingY) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX+1, kingY+1);
        if (square[kingX][kingY].getColor() != square[kingX+1][kingY+1].getColor() && kingX+1<8 && kingY+1<8) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX+1, kingY+1) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX+1, kingY-1);
        if (square[kingX][kingY].getColor() != square[kingX+1][kingY-1].getColor() && kingX+1<8 && kingY-1>=0) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX+1, kingY-1) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX, kingY+1);
        if (square[kingX][kingY].getColor() != square[kingX][kingY+1].getColor() && kingY+1<8) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX, kingY+1) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX, kingY-1);
        if (square[kingX][kingY].getColor() != square[kingX][kingY-1].getColor() && kingY-1>=0) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX, kingY-1) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX-1, kingY+1);
        if (square[kingX][kingY].getColor() != square[kingX-1][kingY+1].getColor()&& kingY+1<8 && kingX-1>=0) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX-1, kingY+1) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX-1, kingY-1);
        if (square[kingX][kingY].getColor() != square[kingX-1][kingY-1].getColor() && kingY-1>=0 && kingX-1>=0) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX-1, kingY-1) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

        thatSpace = getSquare(kingX-1, kingY);
        if (square[kingX][kingY].getColor() != square[kingX-1][kingY].getColor() && kingX-1>=0) {
            swap_pieces(thisPiece, thatSpace);
            if (is_in_check(kingX-1, kingY) == KING) ok=1;
            swap_pieces(thisPiece, thatSpace);
        }

    if (ok) return true;
    return false;
}

bool Board::PawnPossibleMoves(int kingX, int kingY)
{
    int ok=0;

        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if ((square[i][j].getColor() == square[kingX][kingY].getColor() && square[kingX][kingY].getColor() == WHITE && square[i][j].getPiece() == PAWN)){
                    Square *thisPiece = getSquare(i, j);
                    Square *thatSpace = getSquare(i+1, j);
                    if (square[i][j].getColor() != square[i+1][j].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                }
                else if ((square[i][j].getColor() == square[kingX][kingY].getColor() && square[kingX][kingY].getColor() == BLACK && square[i][j].getPiece() == PAWN)){
                    Square *thisPiece = getSquare(i, j);
                    Square *thatSpace = getSquare(i-1, j);
                    if (square[i][j].getColor() != square[i-1][j].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                }
            }
        }

    if (ok) return true;
    return false;
}

bool Board::QueenPossibleMoves(int kingX, int kingY)
{
    int ok=0;

        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if (square[i][j].getColor() == square[kingX][kingY].getColor() && square[i][j].getPiece() == QUEEN) {
                    Square *thisPiece = getSquare(i, j);
                    for (int k=0; k<8; k++) {
                        Square *thatSpace = getSquare(i, k);
                        if (square[i][j].getColor() != square[i][k].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=0; k<8; k++) {
                        Square *thatSpace = getSquare(k, j);
                        if (square[i][j].getColor() != square[k][j].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k<8,l<8; k++,l++) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k>=0,l<8; k--,l++) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k<8,l>=0; k++,l--) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k>=0,l>=0; k--,l--) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                }
            }
        }

    if (ok) return true;
    return false;
}

bool Board::RookPossibleMoves(int kingX, int kingY)
{
    int ok=0;

        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if (square[i][j].getColor() == square[kingX][kingY].getColor() && square[i][j].getPiece() == ROOK) {
                    Square *thisPiece = getSquare(i, j);
                    for (int k=0; k<8; k++) {
                        Square *thatSpace = getSquare(i, k);
                        if (square[i][j].getColor() != square[i][k].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=0; k<8; k++) {
                        Square *thatSpace = getSquare(k, j);
                        if (square[i][j].getColor() != square[k][j].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                }
            }
        }

    if (ok) return true;
    return false;
}

bool Board::BishopPossibleMoves(int kingX, int kingY)
{
    int ok=0;

        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if (square[i][j].getColor() == square[kingX][kingY].getColor() && square[i][j].getPiece() == BISHOP) {
                    Square *thisPiece = getSquare(i, j);
                    for (int k=i, l=j; k<8,l<8; k++,l++) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k>=0,l<8; k--,l++) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k<8,l>=0; k++,l--) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                    for (int k=i, l=j; k>=0,l>=0; k--,l--) {
                        Square *thatSpace = getSquare(k, l);
                        if (square[i][j].getColor() != square[k][l].getColor()) {
                            swap_pieces(thisPiece, thatSpace);
                            if (is_in_check(kingX, kingY) == KING) ok=1;
                            swap_pieces(thisPiece, thatSpace);
                        }
                        else break;
                    }
                }
            }
        }

    if (ok) return true;
    return false;
}

bool Board::KnightPossibleMoves(int kingX, int kingY)
{
    int ok=0;

        for (int i=0; i<8; i++) {
            for (int j=0; j<8; j++) {
                if (square[i][j].getColor() == square[kingX][kingY].getColor() && square[i][j].getPiece() == KNIGHT) {
                    Square *thisPiece = getSquare(i, j);

                    Square *thatSpace = getSquare(i+2, j+1);
                    if (square[i][j].getColor() != square[i+2][j+1].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i-2, j+1);
                    if (square[i][j].getColor() != square[i-2][j+1].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i-2, j-1);
                    if (square[i][j].getColor() != square[i-2][j-1].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i-1, j-2);
                    if (square[i][j].getColor() != square[i-1][j-2].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i-1, j+2);
                    if (square[i][j].getColor() != square[i-1][j+2].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i+1, j+2);
                    if (square[i][j].getColor() != square[i+1][j+2].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i+1, j-2);
                    if (square[i][j].getColor() != square[i+1][j-2].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }

                    thatSpace = getSquare(i+2, j-1);
                    if (square[i][j].getColor() != square[i+2][j-1].getColor()) {
                        swap_pieces(thisPiece, thatSpace);
                        if (is_in_check(kingX, kingY) == KING) ok=1;
                        swap_pieces(thisPiece, thatSpace);
                    }
                }
            }
        }

    if (ok) return true;
    return false;
}

bool Board::moveKing(Square* thisKing, Square* thatSpace) {
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
    int kingX = thisKing->getX();
	int kingY = thisKing->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(kingX - thatX) == 1 && abs(kingY - thatY) == 0) || (abs(kingX - thatX) == 0 && abs(kingY - thatY) == 1) || (abs(kingX - thatX) == 1 && abs(kingY - thatY) == 1))
	{
	    if (is_in_check(kingX, kingY) == false) {
            thatSpace->setSpace(thisKing);
            thisKing->setEmpty();
            if (turn == WHITE) {
                this->WhiteKingX = thatX;
                this->WhiteKingY = thatY;
            }
            else {
                this->BlackKingX = thatX;
                this->BlackKingY = thatY;
            }
            return true;
	    }
	}
	else
	{
		return false;
	}
}

bool Board::check = false;

bool Board::moveQueen(Square* thisQueen, Square* thatSpace) { //there might be problems with numbers of brackets
													   //off board inputs should be handled elsewhere (before this)
													   //squares with same color should be handled elsewhere (before this)

	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{
		if (queenX == thatX)
		{
			if (square[thatX][thatY].getColor() == square[queenX][queenY].getColor())
					return false;
		}
		else
			if (queenY == thatY)
			{
				if (square[thatX][thatY].getColor() == square[queenX][queenY].getColor())
						return false;
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						std::cout << "It got here somehow";
						if (square[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
							return false;

					}
				}
				else return false;
	}

    bool isStraightMove = (queenX == thatX || queenY == thatY);
    bool isDiagonalMove = (abs(queenX - thatX) == abs(queenY - thatY));

    if (!isStraightMove && !isDiagonalMove) {
        return false;
    }

    if (isStraightMove) {
        if (queenX == thatX) {
            int stepY = (thatY > queenY) ? 1 : -1;
            for (int y = queenY + stepY; y != thatY; y += stepY) {
                if (square[queenX][y].getPiece() != EMPTY) {
                    return false;
                }
            }
        } else {
            int stepX = (thatX > queenX) ? 1 : -1;
            for (int x = queenX + stepX; x != thatX; x += stepX) {
                if (square[x][queenY].getPiece() != EMPTY) {
                    return false;
                }
            }
        }
    } else if (isDiagonalMove) {
        int stepX = (thatX > queenX) ? 1 : -1;
        int stepY = (thatY > queenY) ? 1 : -1;
        for (int i = 1; i < abs(queenX - thatX); ++i) {
            if (square[queenX + i * stepX][queenY + i * stepY].getPiece() != EMPTY) {
                return false;
            }
        }
    }

	if (invalid == false)
	{
        if (this->check == true) {
            thatSpace->setSpace(thisQueen);
		    thisQueen->setEmpty();

		    if (this->turn == WHITE)
                if (is_in_check(this->WhiteKingX, this->WhiteKingY) != KING) {
                    thisQueen->setSpace(thatSpace);
                    thatSpace->setEmpty();
                    return false;
                }
            else
                if (is_in_check(this->BlackKingX, this->BlackKingY) != KING) {
                thisQueen->setSpace(thatSpace);
                thatSpace->setEmpty();
                return false;
            }
            check = false;
        }
        else {
            thatSpace->setSpace(thisQueen);
            thisQueen->setEmpty();
            return true;
        }
	}
	else
	{
		return false;
	}
}

bool Board::moveBishop(Square* thisBishop, Square* thatSpace) { //there might be problems with number of brackets
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;

	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
        if (square[bishopX][bishopY].getColor() == square[thatX][thatY].getColor())
            return false;
	}
	else
		return false;

    int stepX = (thatX > bishopX) ? 1 : -1;
    int stepY = (thatY > bishopY) ? 1 : -1;
    for (int i = 1; i < abs(bishopX - thatX); ++i) {
            if (square[bishopX + i * stepX][bishopY + i * stepY].getPiece() != EMPTY) {
                return false;
            }
    }

	if (invalid == false)
	{
		if (this->check == true) {
            thatSpace->setSpace(thisBishop);
		    thisBishop->setEmpty();
		    if (this->turn == WHITE)
                if (is_in_check(this->WhiteKingX, this->WhiteKingY) != KING) {
                    thisBishop->setSpace(thatSpace);
                    thatSpace->setEmpty();
                    return false;
                }
            else
                if (is_in_check(this->BlackKingX, this->BlackKingY) != KING) {
                thisBishop->setSpace(thatSpace);
                thatSpace->setEmpty();
                return false;
            }
            check = false;
        }
        else {
            thatSpace->setSpace(thisBishop);
            thisBishop->setEmpty();
            return true;
        }
	}
	else
	{
		return false;
	}
}

bool Board::moveKnight(Square* thisKnight, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		if (this->check == true) {
            thatSpace->setSpace(thisKnight);
		    thisKnight->setEmpty();
		    if (this->turn == WHITE)
                if (is_in_check(this->WhiteKingX, this->WhiteKingY) != KING) {
                    thisKnight->setSpace(thatSpace);
                    thatSpace->setEmpty();
                    return false;
                }
            else
                if (is_in_check(this->BlackKingX, this->BlackKingY) != KING) {
                thisKnight->setSpace(thatSpace);
                thatSpace->setEmpty();
                return false;
            }
            check = false;
        }
        else {
            thatSpace->setSpace(thisKnight);
            thisKnight->setEmpty();
            return true;
        }
	}
	else
	{
		return false;
	}
}

bool Board::moveRook(Square* thisRook, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;

	if (rookX != thatX || rookY != thatY)
	{
		if (rookX == thatX)
		{
			if (square[thatX][thatY].getColor() == square[rookX][rookY].getColor())
					return false;
		}
		else
			if (rookY == thatY)
			{
                if (square[thatX][thatY].getColor() == square[rookX][rookY].getColor())
						return false;
			}
			else return false;
	}

    if (rookX == thatX) {
        // Moving vertically
        int stepY = (thatY > rookY) ? 1 : -1;
        for (int y = rookY + stepY; y != thatY; y += stepY) {
            if (square[rookX][y].getPiece() != EMPTY) {
                return false;
            }
        }
    } else {
        // Moving horizontally
        int stepX = (thatX > rookX) ? 1 : -1;
        for (int x = rookX + stepX; x != thatX; x += stepX) {
            if (square[x][rookY].getPiece() != EMPTY) {
                return false;
            }
        }
    }

	if (invalid == false)
	{
		if (this->check == true) {
            thatSpace->setSpace(thisRook);
		    thisRook->setEmpty();
		    if (this->turn == WHITE)
                if (is_in_check(this->WhiteKingX, this->WhiteKingY) != KING) {
                    thisRook->setSpace(thatSpace);
                    thatSpace->setEmpty();
                    return false;
                }
            else
                if (is_in_check(this->BlackKingX, this->BlackKingY) != KING) {
                thisRook->setSpace(thatSpace);
                thatSpace->setEmpty();
                return false;
            }
            check = false;
        }
        else {
            thatSpace->setSpace(thisRook);
            thisRook->setEmpty();
            return true;
        }
	}
	else
	{
		std::cout << "That is an invalid move for rook";
		return false;
	}
}

bool Board::movePawn(Square* thisPawn, Square* thatSpace) {
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	bool valid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if (thisPawn->getColor() == WHITE)
	{
		if (pawnX == thatX - 1 && thatY == pawnY && thatSpace->getColor() == NONE)
		{
			valid = true;
		}
		else
			if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX + 1 == thatX  && thatSpace->getColor() == BLACK)
			{
				valid = true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
			if (pawnX == thatX + 1 && thatY == pawnY && thatSpace->getColor() == NONE)
			{
				valid = true;
			}
			else
				if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX - 1 == thatX  && thatSpace->getColor() == WHITE)
				{
					valid = true;
				}
				else
					return false;
		}
		else
			return false;
    if (valid) {
        if (this->check == true) {
            thatSpace->setSpace(thisPawn);
		    thisPawn->setEmpty();
		    if (this->turn == WHITE)
                if (is_in_check(this->WhiteKingX, this->WhiteKingY) != KING) {
                    thisPawn->setSpace(thatSpace);
                    thatSpace->setEmpty();
                    return false;
                }
            else
                if (is_in_check(this->BlackKingX, this->BlackKingY) != KING) {
                thisPawn->setSpace(thatSpace);
                thatSpace->setEmpty();
                return false;
            }
            check = false;
        }
        else {
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            return true;
        }
    }
}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "One of your inputs was out of bounds" << std::endl;
		return false;
	}
	Square* src = getSquare(x1, y1);
	Square* dest = getSquare(x2, y2);

	if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
	{
		std::cout << "Invalid move: cannot land on your own piece" << std::endl;
		return false;
	}

	switch (src->getPiece())
	{
	case KING: return moveKing(src, dest);
		break;
	case QUEEN: return moveQueen(src, dest);
		break;
	case BISHOP: return moveBishop(src, dest);
		break;
	case KNIGHT: return moveKnight(src, dest);
		break;
	case ROOK: return moveRook(src, dest);
		break;
	case PAWN: return movePawn(src, dest);
		break;
	case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
		break;
	default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
		break;
	}
	return false;
}
