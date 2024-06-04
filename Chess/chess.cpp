#include "chess.h"

const std::string RESET = "\033[0m";
const std::string BOLD_WHITE = "\033[1;37m";
const std::string BOLD_RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;
}


enPassant::enPassant(){
    coord_x = -1;
    coord_y = -1;
    permitted = false;
}

void enPassant::setX(int x) {
    coord_x = x;
}


void enPassant::setY(int y) {
    coord_y = y;
}

void enPassant::setPermitted(bool perm) {
    permitted = perm;
}

int enPassant::getX() {
    return coord_x;
}


int enPassant::getY() {
    return coord_y;
}

bool enPassant::getPermitted() {
    return permitted;
}




void Board::printBoard() {
    using namespace std;

    cout << GREEN << "   y: 0  1  2  3  4  5  6  7 " << RESET << endl;
    cout << GREEN << " x:" << RESET << endl;
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
                    cout << color_code << " H " << RESET;
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


Color Board::getTurn() {
    return turn;
}


bool Board::doMove() {
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
        (turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		if (getSquare(x1, y1)->getColor() == turn)
		{
			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "Invalid move, try again." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	/*if (getSquare(x2, y2)->getPiece() == KING)
		if (getSquare(x1, y1)->getColor() == WHITE)
		{
			cout << "WHITE WINS" << endl;
			return false;
		}
		else
		{
			cout << "BLACK WINS" << endl;
			return false;
		}
*/

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


void Board::setBoard_EnPassant() {





    for (int i = 0; i < 8; i++)
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

    square[1][4].setPieceAndColor(PAWN,WHITE);
    square[1][7].setPieceAndColor(PAWN,WHITE);
    square[4][2].setPieceAndColor(PAWN,WHITE);
    square[4][3].setPieceAndColor(PAWN,WHITE);


    square[3][6].setPieceAndColor(PAWN,BLACK);
    square[3][4].setPieceAndColor(PAWN,BLACK);
    square[3][5].setPieceAndColor(PAWN,BLACK);
    square[6][1].setPieceAndColor(PAWN,BLACK);
    square[6][4].setPieceAndColor(PAWN,BLACK);

}


void Board::setBoard_Castling() {
    square[0][0].setPieceAndColor(ROOK, WHITE);
    square[0][1].setPieceAndColor(EMPTY, NONE);
    square[0][2].setPieceAndColor(EMPTY, NONE);
    square[0][3].setPieceAndColor(EMPTY, NONE);
    square[0][4].setPieceAndColor(KING, WHITE);
    square[0][5].setPieceAndColor(EMPTY, NONE);
    square[0][6].setPieceAndColor(EMPTY, NONE);
    square[0][7].setPieceAndColor(ROOK, WHITE);

    square[7][0].setPieceAndColor(ROOK, BLACK);
    square[7][1].setPieceAndColor(EMPTY, NONE);
    square[7][2].setPieceAndColor(EMPTY, NONE);
    square[7][3].setPieceAndColor(EMPTY, NONE);
    square[7][4].setPieceAndColor(KING, BLACK);
    square[7][5].setPieceAndColor(EMPTY, NONE);
    square[7][6].setPieceAndColor(EMPTY, NONE);
    square[7][7].setPieceAndColor(ROOK, BLACK);

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

bool Board::moveKing(Square* thisKing, Square* thatSpace) {
    //off board inputs should be handled elsewhere (before this)
    //squares with same color should be handled elsewhere (before this)
    int kingX = thisKing->getX();
    int kingY = thisKing->getY();
    int thatX = thatSpace->getX();
    int thatY = thatSpace->getY();

    //Castle verify
    //Create flag for castling? Rn it can do it multiple times if conditions are met
    //for white

    if ((getTurn() == WHITE && (kingX == 0 && kingY == 4))) {
        //Right side ROOK
        if ((thatX == 0 && thatY == 6) && getSquare(0, 7)->getPiece() == ROOK) {
            if (getSquare(0, 5)->getColor() == NONE && getSquare(0, 6)->getColor() == NONE) {

                thatSpace->setSpace(thisKing);
                thisKing->setEmpty();
                getSquare(0, 5)->setPieceAndColor(ROOK, WHITE);
                getSquare(0, 7)->setEmpty();
                return true;
            }

        }
        //Left side ROOK
        if ((thatX == 0 && thatY == 2) && getSquare(0, 0)->getPiece() == ROOK) {
            if (getSquare(0, 3)->getColor() == NONE && getSquare(0, 2)->getColor() == NONE &&
                getSquare(0, 1)->getColor() == NONE) {

                thatSpace->setSpace(thisKing);
                thisKing->setEmpty();
                getSquare(0, 3)->setPieceAndColor(ROOK, WHITE);
                getSquare(0, 0)->setEmpty();
                return true;
            }

        }
    }
            //for Black side
    else if ((getTurn() == BLACK && (kingX == 7 && kingY == 4))) {
        //Right side ROOK
        if ((thatX == 7 && thatY == 6) && getSquare(7, 7)->getPiece() == ROOK) {
            if (getSquare(7, 5)->getColor() == NONE && getSquare(7, 6)->getColor() == NONE) {

                thatSpace->setSpace(thisKing);
                thisKing->setEmpty();
                getSquare(7, 5)->setPieceAndColor(ROOK, BLACK);
                getSquare(7, 7)->setEmpty();
                return true;
            }

        }
        //Left side ROOK
        if ((thatX == 7 && thatY == 2) && getSquare(7, 0)->getPiece() == ROOK) {
            if (getSquare(7, 3)->getColor() == NONE && getSquare(7, 2)->getColor() == NONE &&
                getSquare(7, 1)->getColor() == NONE) {

                thatSpace->setSpace(thisKing);
                thisKing->setEmpty();
                getSquare(7, 3)->setPieceAndColor(ROOK, BLACK);
                getSquare(7, 0)->setEmpty();
                return true;
            }

        }


}

    if ((abs(kingX - thatX) == 1 && abs(kingY - thatY) == 0) ||
        (abs(kingX - thatX) == 0 && abs(kingY - thatY) == 1) ||
        (abs(kingX - thatX) == 1 && abs(kingY - thatY) == 1)) {
        thatSpace->setSpace(thisKing);
        thisKing->setEmpty();
        return true;
    } else {
        return false;
    }
}
bool Board::moveQueen(Square* thisQueen, Square* thatSpace) { //there might be problems with numbers of brackets
													   //off board inputs should be handled elsewhere (before this)
													   //squares with same color should be handled elsewhere (before this)

	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	std::cout << "this";
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
				else
					return false;
	}

	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
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
	Square *s;

	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
			if (square[bishopX][bishopY].getColor() == square[thatX][thatY].getColor())
				return false;
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
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
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
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

	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
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
	using namespace std;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
//If EnPassant == True
    //If Move is for enpassant, take piece or smth.
        //En passant == False
//Save Move Here in "EnPassant->LastPawnMove"

    if(abs(pawnX - thatX)==2){


    }
//Check difference between endPos and startPos
    //If difference == 2
        //If endPos.y +1 or endPos.y -1 are opposing collor pawns
            // Position endPos is EnPassantable






	if (thisPawn->getColor() == WHITE)
	{
        //Verify EnPassant Move
        if(EnPassant.getPermitted()){
            if(thatX == EnPassant.getX()+1 && thatY == EnPassant.getY()){
                if(abs(EnPassant.getY() - pawnY) == 1 && pawnX == EnPassant.getX()){
                    thatSpace->setSpace(thisPawn);
                    thisPawn->setEmpty();
                    getSquare(EnPassant.getX(),EnPassant.getY())->setEmpty();
                    return true;

                }
            }
        }
        EnPassant.setPermitted(false);

        //First move (2 steps)
        if(pawnX == 1 && thatX == 3 && getSquare(2,pawnY)->getColor() == NONE && thatSpace->getColor() == NONE){
            thatSpace->setSpace(thisPawn);
            thisPawn->setEmpty();
            if(getSquare(thatX,thatY+1)->getColor()==BLACK || getSquare(thatX,thatY-1)->getColor()==BLACK){
                if(getSquare(thatX,thatY+1)->getPiece() == PAWN || getSquare(thatX,thatY-1)->getPiece() == PAWN){
                    EnPassant.setPermitted(true);
                    EnPassant.setX(thatX);
                    EnPassant.setY(thatY);
                }
            }
            return true;
        }

        //Step
		if (pawnX == thatX - 1 && thatY == pawnY && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);
			thisPawn->setEmpty();
			return true;
		}
		else
            //Capture
			if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX + 1 == thatX  && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
            //verify EnPassant Move

            if(EnPassant.getPermitted()){
                if(thatX == EnPassant.getX()-1 && thatY == EnPassant.getY()){
                    if(abs(EnPassant.getY() - pawnY) == 1 && pawnX == EnPassant.getX()){
                        thatSpace->setSpace(thisPawn);
                        thisPawn->setEmpty();
                        getSquare(EnPassant.getX(),EnPassant.getY())->setEmpty();
                        return true;

                    }
                }
            }
            EnPassant.setPermitted(false);

            if(pawnX == 6 && thatX == 4 && getSquare(5,pawnY)->getColor() == NONE && thatSpace->getColor() == NONE){
                thatSpace->setSpace(thisPawn);
                thisPawn->setEmpty();
                if(getSquare(thatX,thatY+1)->getColor()==WHITE || getSquare(thatX,thatY-1)->getColor()==WHITE){
                    if(getSquare(thatX,thatY+1)->getPiece() == PAWN || getSquare(thatX,thatY-1)->getPiece() == PAWN){
                        EnPassant.setPermitted(true);
                        EnPassant.setX(thatX);
                        EnPassant.setY(thatY);
                    }
                }
                return true;
            }
			if (pawnX == thatX + 1 && thatY == pawnY && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX - 1 == thatX  && thatSpace->getColor() == WHITE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
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

    //Save the move Somewhere
    //LastMove


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
