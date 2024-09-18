#include "chessmethod.h"
#include <iostream>//remove for Workwi
#include <cmath>//remove for Workwi
#include <string>//remove for Workwi
#include <string>//remove for Workwi
using namespace std;
#include <vector>

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}


void Square::setupPiece(Piece t, Color c)
{
  piece = t;
  color = c;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

int Board:: getCol(){
  //get Column by having ARDUINO
  //for now, do interface or I/O with user using c>> to get int

  
}

int Board:: getRow(){
  //get Row by having ARDUINO
  //for now, do interface or I/O with user using c>> to get int
}

int Board:: getColUpdated(){
  //get Column by having ARDUINO
  //for now, do interface or I/O with user using c>> to get int

  
}

int Board:: getRowUpdated(){
  //get Row by having ARDUINO
  //for now, do interface or I/O with user using c>> to get int
}


bool Board::movePawn(int row, int col, int RowUpdated, int ColUpdated) {//Updated int is to know the position to put the piece to
    //Slightly updated the method as it did not properly updat ethe pawn position and take into account moving 2 squares at the start
    //Does not work for captures

    // en passant

    // normal pawn move
    int x = row;
    int y = col;

    Piece piece = square[x][y].getPiece();
    Color color = square[x][y].getColor();

    //If the piece is a black pawn
    if (color == BLACK && piece == PAWN) {
        int temp = RowUpdated - row; //to see if you move by 2 with ur pawn
        int temp1 = abs(ColUpdated - col); //horizontal movement
        
        //Check if it's the pawn's first move (can move 1 or 2 squares)
        if (x == 1 && (temp == 1 || temp == 2) && temp1 == 0) {
            //Check if the destination is empty
            Piece check = square[RowUpdated][ColUpdated].getPiece();
            if (check == EMPTY) {
                square[x][y].setupPiece(EMPTY, NONE);
                square[RowUpdated][ColUpdated].setupPiece(PAWN, BLACK);
                return true;
            }
        }

        //Normal one-square forward move
        if (temp == 1 && temp1 == 0) {
            Piece check = square[RowUpdated][ColUpdated].getPiece();
            if (check == EMPTY) {
                square[x][y].setupPiece(EMPTY, NONE);
                square[RowUpdated][ColUpdated].setupPiece(PAWN, BLACK);
                return true;
            }
        }

        //Capture move diagonal
        if (temp == 1 && temp1 == 1) {
            Piece check = square[RowUpdated][ColUpdated].getPiece();
            Color targetColor = square[RowUpdated][ColUpdated].getColor();
            if (check != EMPTY && targetColor == WHITE) {
                square[x][y].setupPiece(EMPTY, NONE);
                square[RowUpdated][ColUpdated].setupPiece(PAWN, BLACK);
                return true;
            }
        }
    }
    //If the piece is a white pawn
    else if (color == WHITE && piece == PAWN) {
        int temp = row - RowUpdated; // vertical movement
        int temp1 = abs(ColUpdated - col); // horizontal movement
        
        // Check if it's the pawn's first move (can move 1 or 2 squares)
        if (x == 6 && (temp == 1 || temp == 2) && temp1 == 0) {
            // Check if the destination is empty
            Piece check = square[RowUpdated][ColUpdated].getPiece();
            if (check == EMPTY) {
                square[x][y].setupPiece(EMPTY, NONE);
                square[RowUpdated][ColUpdated].setupPiece(PAWN, WHITE);
                return true;
            }
        }

        //Normal one-square forward move
        if (temp == 1 && temp1 == 0) {
            Piece check = square[RowUpdated][ColUpdated].getPiece();
            if (check == EMPTY) {
                square[x][y].setupPiece(EMPTY, NONE);
                square[RowUpdated][ColUpdated].setupPiece(PAWN, WHITE);
                return true;
            }
        }

        //Capture move diagonal
        if (temp == 1 && temp1 == 1) {//if u move by 1 on the row and 1 for col
        //check if piece to go has a piece which is not a king
            Piece check = square[RowUpdated][ColUpdated].getPiece();
            Color targetColor = square[RowUpdated][ColUpdated].getColor();
            if (check != EMPTY && targetColor == BLACK) {
                square[x][y].setupPiece(EMPTY, NONE);
                square[RowUpdated][ColUpdated].setupPiece(PAWN, WHITE);
                return true;
            }
        }
    }

    return false; // else invalid move
}

bool Board::moveRook(int row, int col, int RowUpdated, int ColUpdated) {
    int x = row;
    int y = col;

    Piece piece = square[x][y].getPiece();
    Color color = square[x][y].getColor();

    //Check if the piece is a Rook or Queen, and also since the queen method calls the rook method
    if (piece == ROOK || piece == QUEEN) {
        int temp = abs(ColUpdated - col);
        int temp1 = abs(RowUpdated - row);

        if (temp == 0) { // check column
            if (row > RowUpdated) { // ROOK is moving up
                for (int i = row - 1; i > RowUpdated; i--) {
                    Piece check = square[i][col].getPiece();//updated by Lalit
                    if (check != EMPTY) { // if there's a piece, there's an error
                        return false;
                    }
                }
            }
            if (row < RowUpdated) { // ROOK is moving down
                for (int i = row + 1; i < RowUpdated; i++) {
                    Piece check = square[i][col].getPiece();
                    if (check != EMPTY) { // if there's a piece, there's an error
                        return false;
                    }
                }
            }
        }

        if (temp1 == 0) { // check row
            if (col > ColUpdated) { // ROOK is moving to the left
                for (int i = col - 1; i > ColUpdated; i--) {
                    Piece check = square[row][i].getPiece();
                    if (check != EMPTY) { // if there's a piece, there's an error
                        return false;
                    }
                }
            }
            if (col < ColUpdated) { // ROOK is moving to the right
                for (int i = col + 1; i < ColUpdated; i++) {
                    Piece check = square[row][i].getPiece();
                    if (check != EMPTY) { // if there's a piece, there's an error
                        return false;
                    }
                }
            }
        }

        //Added: need to check if the destination square is occupied by a piece of the same color
        Piece targetPiece = square[RowUpdated][ColUpdated].getPiece();
        Color targetColor = square[RowUpdated][ColUpdated].getColor();

        if (targetPiece != EMPTY && targetColor == color) {
            return false; //the destination square is occupied by a piece of the same color
        }

        // If no error move the Rook to the destination square
        square[x][y].setupPiece(EMPTY, NONE);
        square[RowUpdated][ColUpdated].setupPiece(ROOK, color);
        return true;
    }

    return false; //if move is not vertical or horizontal then return false
}

bool Board::moveKnight(int row, int col, int RowUpdated, int ColUpdated) {
    //1. Get the coordinates of the current square (thisKnight) and the target square (thatSpace)
    //2.Calculate the differences in the x and y coordinates (dx and dy).
    //3. Check if the move follows the knight's L-shape pattern
    //4. Ensure the destination square is either empty or occupied by an opponent's piece
    //5. If all conditions are met, move the knight to the destination square and set the original square to empty
    //Reference logic: https://stackoverflow.com/questions/19372622/how-do-i-generate-all-of-a-knights-moves
    int startX = row;
    int startY = col;
    int endX = RowUpdated;
    int endY = ColUpdated;

    Piece piece = square[startX][startY].getPiece();
    Color color = square[startX][startY].getColor();

    //See if the piece being moved is a knight - edge case
    if (piece != KNIGHT) {
        return false; //Not a knight
    }
        // Ensure positions are within the bounds of the board
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 || endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false; // Move is out of bounds
    }

    //Calculate the differences in the coordinates
    //Using abs we don't need to do seperate logic for black and white color
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    //Ceck if the move follows the knight's L-shape pattern (still need to make sure)
    bool isValidMove = (dx == 2 && dy == 1) || (dx == 1 && dy == 2); // vertical and horizontal L

    if (!isValidMove) {
        return false; //Incorrect pattern
    }
    //Check if the destination square is either empty or occupied by an opponent's piece (not sure If i do captures here)
    Piece targetPiece = square[endX][endY].getPiece();
    Color targetColor = square[endX][endY].getColor();
    Color knightColor = square[endX][endY].getColor();

    if (targetPiece != EMPTY && targetColor == knightColor) {//Check if tile is empty and is occupied a same color piece
        return false; //The destination square is occupied by same color piece
    }
    //Move the knight to the destination square
    square[startX][startY].setupPiece(EMPTY, NONE);
    square[endX][endY].setupPiece(KNIGHT, color);

    return true; //The move is valid
}

bool Board::moveBishop(int row, int col, int RowUpdated, int ColUpdated) {
    // 1. Get Coordinates: Fetch the coordinates of the bishop's current and target positions
    // 2. Calculate Differences: Determine how far the bishop needs to move horizontally and vertically
    // 3. Check Move Pattern: Ensure the move is diagonal by comparing the differences in coordinates
    // 4. Determine Direction: Calculate the direction to move along the diagonal
    // 5. Check Path: Verify that no pieces are blocking the diagonal path
    // 6. Check Destination: Ensure the target square is either empty or occupied by an opponent's piece
    // 7. Execute Move: Move the bishop to the target square and clear the original square
    // 8. Return Result: Indicate whether the move was valid with bool

    // Reference logic: https://stackoverflow.com/questions/69523744/diagonal-bishop-moves-on-chess-board-with-python

    // Get the coordinates of the current square
    int startX = row;
    int startY = col;
    int endX = RowUpdated;
    int endY = ColUpdated;

    Piece piece = square[startX][startY].getPiece();
    if (piece != BISHOP && piece != QUEEN) { //check if not Bishop and Queen and also since Queen calls Bishop method
        return false;
    }

    // Calculate the differences in the x and y coordinates
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    //Check if the move is diagonal
    if (dx != dy) {
        return false;
    }

    //Determine the direction of movement along the diagonal
    int xDirection = (endX - startX) / dx;
    int yDirection = (endY - startY) / dy;

    //Check if all squares between the start and end positions are empty
    for (int i = 1; i < dx; ++i) {
        int intermediateX = startX + i * xDirection;
        int intermediateY = startY + i * yDirection;
        Piece intermediatePiece = square[intermediateX][intermediateY].getPiece();

        if (intermediatePiece != EMPTY) {
            return false; //There's a piece blocking the path
        }
    }

    //Get the piece and color at the target square
    Piece targetPiece = square[endX][endY].getPiece();
    Color targetColor = square[endX][endY].getColor();
    Color bishopColor = square[startX][startY].getColor();

    //Check if the destination square is either empty or occupied by same color piece
    if (targetPiece != EMPTY && targetColor == bishopColor) {
        return false; //the destination square is occupied by the same color piece
    }

    //Move the bishop to the destination square
    square[startX][startY].setupPiece(EMPTY, NONE); //Clear the original square
    square[endX][endY].setupPiece(BISHOP, bishopColor); //set the target square with the bishop

    return true;
}

bool Board::moveQueen(int row, int col, int RowUpdated, int ColUpdated) {
//1. ensure the piece being moved is a queen
//2. calculate the differences in the coordinates to determine the type of move
//3. Depending on the type of move call the respective moveRook or moveBishop method to handle the move.
//4. If the move is neither rook-like nor bishop-like return false to indicate an invalid move.
    int startX = row;
    int startY = col;
    int endX = RowUpdated;
    int endY = ColUpdated;

    Piece piece = square[startX][startY].getPiece();
    Color color = square[startX][startY].getColor();
    //Don;t need to check if piece is equal to Queen since we check in the Bishop and Rook methods

    //Calculate the differences in the coordinates
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    //See if the move is a rook-like or bishop-like move
    bool isRookMove = (dx == 0 || dy == 0); //Horizontal or vertical move
    bool isBishopMove = (dx == dy); //Diagonal move

    //Use the existing methods to handle the move
    if (isRookMove) {
        bool result = moveRook(startX, startY, endX, endY);
        if (result) {
            //Move and update the Queen to the destination square
            square[startX][startY].setupPiece(EMPTY, NONE);
            square[endX][endY].setupPiece(QUEEN, color);
            return true;
        } else {
            return false;
        }
    }
    if (isBishopMove) {
        bool result = moveBishop(startX, startY, endX, endY);
        if (result) {
            //Move and update the Queen to the destination square
            square[startX][startY].setupPiece(EMPTY, NONE);
            square[endX][endY].setupPiece(QUEEN, color);
            return true;
        } else {
            return false;
        }
    }

    return false; //If the move is neither rook-like nor bishop-like it's invalid
}

bool Board::moveKing(int row, int col, int RowUpdated, int ColUpdated) {
    //https://stackoverflow.com/questions/58075207/python-code-for-validating-chess-king-movement
    int startX = row;
    int startY = col;
    int endX = RowUpdated;
    int endY = ColUpdated;

    Piece piece = square[startX][startY].getPiece();
    Color color = square[startX][startY].getColor();

    //Check if the piece is King
    if (piece != KING) {
        return false;
    }

    //Ensure the move is within one square in any direction
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);
    if (dx > 1 || dy > 1) {
        return false;
    }

    //check if the destination square is either empty or occupied by an opponent's piece
    Piece targetPiece = square[endX][endY].getPiece();
    Color targetColor = square[endX][endY].getColor();
    if (targetPiece != EMPTY && targetColor == color) {
        return false; //destination square is occupied by a piece of the same color
    }

    //Temporarily move the king to the destination square to check for checks
    square[startX][startY].setupPiece(EMPTY, NONE);
    square[endX][endY].setupPiece(KING, color);

    //Need to check if the move puts the king in check


    return true; //The move is valid
}

int* Board::ShowAllKnightMoves(int row, int col) {
    static int moves[8];  
    vector<int> validMoves;

    int possibleMoves[8][2] = {
        {row + 2, col + 1}, {row + 2, col - 1},
        {row - 2, col + 1}, {row - 2, col - 1},
        {row + 1, col + 2}, {row + 1, col - 2},
        {row - 1, col + 2}, {row - 1, col - 2}
    };
  
    Color ogColor = square[row][col].getColor();

    for (int i = 0; i < 8; i++) {
        int newRow = possibleMoves[i][0];
        int newCol = possibleMoves[i][1];

        // Correct the board boundary checks
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            Piece piece = square[newRow][newCol].getPiece();
            Color targetColor = square[newRow][newCol].getColor();
            
            if (piece == EMPTY || targetColor != ogColor) {
                validMoves.push_back(IndexConverter(newRow, newCol));
            }
    }

    int moveIndex = 0;
    for (size_t i = 0; i < validMoves.size(); i++) {
        moves[moveIndex++] = validMoves[i];
    }

    // Fill remaining elements with -1 to mark the end
    for (int i = moveIndex; i < 8; i++) {
        moves[i] = -1;
    }
    }
    return moves;
}

int* Board::ShowAllBishopMoves(int row, int col) {
    static int moves[13];  //bishop can have a maximum of 13 possible moves
    vector<int> validMoves;

    Color ogColor = square[row][col].getColor();

    // Diagonal top-right
    for (int i = 1; row + i < 8 && col + i < 8; i++) {
        Piece piece = square[row + i][col + i].getPiece();
        Color targetColor = square[row + i][col + i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row + i, col + i));
            if (piece != EMPTY) break;
        } else {
            break;  //Blocked by a piece of the same color
        }
    }

    // Diagonal top-left
    for (int i = 1; row + i < 8 && col - i >= 0; i++) {
        Piece piece = square[row + i][col - i].getPiece();
        Color targetColor = square[row + i][col - i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row + i, col - i));
            if (piece != EMPTY) break; //stop if capturing a piece
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    // Diagonal bottom-right
    for (int i = 1; row - i >= 0 && col + i < 8; i++) {
        Piece piece = square[row - i][col + i].getPiece();
        Color targetColor = square[row - i][col + i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row - i, col + i));
            if (piece != EMPTY) break;//stop if capturing a piece
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    // Diagonal bottom-left
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        Piece piece = square[row - i][col - i].getPiece();
        Color targetColor = square[row - i][col - i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row - i, col - i));
            if (piece != EMPTY) break;//Stop if capturing a piece
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    //Copy valid moves to the static array
    int moveIndex = 0;
    for (size_t i = 0; i < validMoves.size(); i++) {
        moves[moveIndex++] = validMoves[i];
    }

    //Fill remaining elements with -1 to mark the end
    for (int i = moveIndex; i < 13; i++) {
        moves[i] = -1;
    }

    return moves;
}

int* Board::ShowRook(int row, int col) {
    Piece piece = square[row][col].getPiece();
    Color color = square[row][col].getColor();
    static int moves[14];
    vector<int> validMoves;

    if (piece == ROOK) {
        //Upwards check
        for (int i = row - 1; i >= 0; i--) { //Move upwards from the current position
            Piece CheckPiece = square[i][col].getPiece();
            Color CheckColor = square[i][col].getColor();
            if (CheckPiece == EMPTY) {
                validMoves.push_back(IndexConverter(i, col));
            } else if (CheckColor != color) {
                validMoves.push_back(IndexConverter(i, col)); 
                break;
            } else {
                break;//Same color piece is blocking
            }
        }

        //Downwards check
        for (int i = row + 1; i < 8; i++) { //Move downwards from the current position
            Piece CheckPiece = square[i][col].getPiece();
            Color CheckColor = square[i][col].getColor();
            if (CheckPiece == EMPTY) {
                validMoves.push_back(IndexConverter(i, col));
            } else if (CheckColor != color) {
                validMoves.push_back(IndexConverter(i, col)); // Capture opponent piece
                break;
            } else {
                break;//Same color piece is blocking
            }
        }

        // Leftwards check
        for (int j = col - 1; j >= 0; j--) { //Move leftwards from the current position
            Piece CheckPiece = square[row][j].getPiece();
            Color CheckColor = square[row][j].getColor();
            if (CheckPiece == EMPTY) {
                validMoves.push_back(IndexConverter(row, j));
            } else if (CheckColor != color) {
                validMoves.push_back(IndexConverter(row, j));  
                break;
            } else {
                break;//Same color piece is blocking
            }
        }

        // Rightwards check
        for (int j = col + 1; j < 8; j++) { //Move rightwards from the current position
            Piece CheckPiece = square[row][j].getPiece();
            Color CheckColor = square[row][j].getColor();
            if (CheckPiece == EMPTY) {
                validMoves.push_back(IndexConverter(row, j));
            } else if (CheckColor != color) {
                validMoves.push_back(IndexConverter(row, j));  
                break;
            } else {
                break;//Same color piece is blocking
            }
        }
    }

    //Copy valid moves to the static array
    int moveIndex = 0;
    for (size_t i = 0; i < validMoves.size(); i++) {
        moves[moveIndex++] = validMoves[i];
    }

    //Fill remaining elements with -1 to mark the end
    for (int i = moveIndex; i < 14; i++) {
        moves[i] = -1;
    }
    return moves;
}

int* Board::ShowPawn(int row, int col) {
    static int moves[4];  //pawn can have maximum of 4 possible moves (2 forward and 2 diagonally)
    vector<int> validMoves;

    Piece piece = square[row][col].getPiece();
    Color color = square[row][col].getColor();

    if (color == BLACK && piece == PAWN) {
        // Move forward
        if (square[row + 1][col].getPiece() == EMPTY) {
            validMoves.push_back(IndexConverter(row + 1, col));

            // Double move from starting position
            if (row == 1 && square[row + 2][col].getPiece() == EMPTY) {
                validMoves.push_back(IndexConverter(row + 2, col));
            }
        }

        // Capture diagonally
        if (col > 0) { //capture to the left
            Piece CheckPiece1 = square[row + 1][col - 1].getPiece();
            Color CheckColor1 = square[row + 1][col - 1].getColor();
            if (CheckPiece1 != EMPTY && CheckColor1 == WHITE) {
                validMoves.push_back(IndexConverter(row + 1, col - 1));
            }
        }
        if (col < 7) {//capture to the right
            Piece CheckPiece2 = square[row + 1][col + 1].getPiece();
            Color CheckColor2 = square[row + 1][col + 1].getColor();
            if (CheckPiece2 != EMPTY && CheckColor2 == WHITE) {
                validMoves.push_back(IndexConverter(row + 1, col + 1));
            }
        }
    } else if (color == WHITE && piece == PAWN) {
        // Move forward
        if (square[row - 1][col].getPiece() == EMPTY) {
            validMoves.push_back(IndexConverter(row - 1, col));

            //Double move from starting position
            if (row == 6 && square[row - 2][col].getPiece() == EMPTY) {
                validMoves.push_back(IndexConverter(row - 2, col));
            }
        }

        // Capture diagonally
        if (col > 0) { //capture to the left
            Piece CheckPiece3 = square[row - 1][col - 1].getPiece();
            Color CheckColor3 = square[row - 1][col - 1].getColor();
            if (CheckPiece3 != EMPTY && CheckColor3 == BLACK) {
                validMoves.push_back(IndexConverter(row - 1, col - 1));
            }
        }
        if (col < 7) {//capture to the right
            Piece CheckPiece4 = square[row - 1][col + 1].getPiece();
            Color CheckColor4 = square[row - 1][col + 1].getColor();
            if (CheckPiece4 != EMPTY && CheckColor4 == BLACK) {
                validMoves.push_back(IndexConverter(row - 1, col + 1));
            }
        }
    }

    // Copy valid moves to the static array
    int moveIndex = 0;
    for (size_t i = 0; i < validMoves.size(); i++) {
        moves[moveIndex++] = validMoves[i];
    }

    // Fill remaining elements with -1 to mark the end
    for (int i = moveIndex; i < 4; i++) {
        moves[i] = -1;
    }

    return moves;
}

int* Board::ShowAllQueenMoves(int row, int col) {
    static int moves[27];  //queen has 27 possible moves
    vector<int> validMoves;

    Color ogColor = square[row][col].getColor();

    //Rook-like movement (vertical and horizontal)
    //Upwards check
    for (int i = row - 1; i >= 0; i--) {
        Piece CheckPiece = square[i][col].getPiece();
        Color CheckColor = square[i][col].getColor();
        if (CheckPiece == EMPTY) {
            validMoves.push_back(IndexConverter(i, col));
        } else if (CheckColor != ogColor) {
            validMoves.push_back(IndexConverter(i, col)); 
            break;
        } else {
            break; //Blocked by a piece of the same color
        }
    }

    //Downwards check
    for (int i = row + 1; i < 8; i++) {
        Piece CheckPiece = square[i][col].getPiece();
        Color CheckColor = square[i][col].getColor();
        if (CheckPiece == EMPTY) {
            validMoves.push_back(IndexConverter(i, col));
        } else if (CheckColor != ogColor) {
            validMoves.push_back(IndexConverter(i, col)); 
            break;
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    //Leftwards check
    for (int j = col - 1; j >= 0; j--) {
        Piece CheckPiece = square[row][j].getPiece();
        Color CheckColor = square[row][j].getColor();
        if (CheckPiece == EMPTY) {
            validMoves.push_back(IndexConverter(row, j));
        } else if (CheckColor != ogColor) {
            validMoves.push_back(IndexConverter(row, j)); 
            break;
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    //Rightwards check
    for (int j = col + 1; j < 8; j++) {
        Piece CheckPiece = square[row][j].getPiece();
        Color CheckColor = square[row][j].getColor();
        if (CheckPiece == EMPTY) {
            validMoves.push_back(IndexConverter(row, j));
        } else if (CheckColor != ogColor) {
            validMoves.push_back(IndexConverter(row, j)); 
            break;
        } else {
            break; //Blocked by a piece of the same color
        }
    }

    //Bishop-like movement (diagonals)
    // Diagonal top-right
    for (int i = 1; row + i < 8 && col + i < 8; i++) {
        Piece piece = square[row + i][col + i].getPiece();
        Color targetColor = square[row + i][col + i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row + i, col + i));
            if (piece != EMPTY) break;
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    //Diagonal top-left
    for (int i = 1; row + i < 8 && col - i >= 0; i++) {
        Piece piece = square[row + i][col - i].getPiece();
        Color targetColor = square[row + i][col - i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row + i, col - i));
            if (piece != EMPTY) break;
        } else {
            break;//Blocked by a piece of the same color
        }
    }

    //Diagonal bottom-right
    for (int i = 1; row - i >= 0 && col + i < 8; i++) {
        Piece piece = square[row - i][col + i].getPiece();
        Color targetColor = square[row - i][col + i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row - i, col + i));
            if (piece != EMPTY) break;
        } else {
            break; //Blocked by a piece of the same color
        }
    }

    //Diagonal bottom-left
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        Piece piece = square[row - i][col - i].getPiece();
        Color targetColor = square[row - i][col - i].getColor();

        if (piece == EMPTY || targetColor != ogColor) {
            validMoves.push_back(IndexConverter(row - i, col - i));
            if (piece != EMPTY) break;
        } else {
            break; //Blocked by a piece of the same color
        }
    }

    // Copy valid moves to the static array
    int moveIndex = 0;
    for (size_t i = 0; i < validMoves.size(); i++) {
        moves[moveIndex++] = validMoves[i];
    }

    // Fill remaining elements with -1 to mark the end
    for (int i = moveIndex; i < 27; i++) {
        moves[i] = -1;
    }

    return moves;
}

void Board::createChessBoard(){

  square[0][0].setupPiece(ROOK, BLACK);
  square[0][1].setupPiece(KNIGHT, BLACK);
  square[0][2].setupPiece(BISHOP, BLACK);
  square[0][3].setupPiece(QUEEN, BLACK);
  square[0][4].setupPiece(KING, BLACK);
  square[0][5].setupPiece(BISHOP, BLACK);
  square[0][6].setupPiece(KNIGHT, BLACK);
  square[0][7].setupPiece(ROOK, BLACK);

  square[1][0].setupPiece(PAWN, BLACK);
  square[1][1].setupPiece(PAWN, BLACK);
  square[1][2].setupPiece(PAWN, BLACK);
  square[1][3].setupPiece(PAWN, BLACK);
  square[1][4].setupPiece(PAWN, BLACK);
  square[1][5].setupPiece(PAWN, BLACK);
  square[1][6].setupPiece(PAWN, BLACK);
  square[1][7].setupPiece(PAWN, BLACK);

  square[6][0].setupPiece(PAWN, WHITE);
  square[6][1].setupPiece(PAWN, WHITE);
  square[6][2].setupPiece(PAWN, WHITE);
  square[6][3].setupPiece(PAWN, WHITE);
  square[6][4].setupPiece(PAWN, WHITE);
  square[6][5].setupPiece(PAWN, WHITE);
  square[6][6].setupPiece(PAWN, WHITE);
  square[6][7].setupPiece(PAWN, WHITE);

  square[7][0].setupPiece(ROOK, WHITE);
  square[7][1].setupPiece(KNIGHT, WHITE);
  square[7][2].setupPiece(BISHOP, WHITE);
  square[7][3].setupPiece(QUEEN, WHITE);
  square[7][4].setupPiece(KING, WHITE);
  square[7][5].setupPiece(BISHOP, WHITE);
  square[7][6].setupPiece(KNIGHT, WHITE);
  square[7][7].setupPiece(ROOK, WHITE);

  for(int y = 2; y < 6; y++){ //rest of pieces are empty
    for(int x = 0; x < 8; x++ ){
      square[y][x].setupPiece(EMPTY, NONE);
    }
  }
 

}

void Board:: testing(){

  Piece piece = square[0][1].getPiece();
  Color color = square[0][1].getColor();

  if(piece == KNIGHT || color == BLACK){
        //Serial Print
   }

}

int Board:: IndexConverter(int row, int col){

  

  
    int temp = 0;
    int temp1 = 0;

    if (row % 2 == 0){ // even
      temp = row*8;

      for(int x = 1; x < col + 1; x++){
        temp += 1;
      }
      return temp;
    }
    else if (row % 2 != 0){//odd
      temp1 = row*8;
      for(int y = 6; y > col - 1; y--){
        temp1 += 1;
      }
      return temp1;
    
  }
  
}


