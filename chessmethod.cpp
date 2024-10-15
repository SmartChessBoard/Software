#include <FastLED.h>
#include "chessmethod.h"
#include <Arduino.h>
#include <vector>
#define NUM_LEDS    64
extern CRGB leds[NUM_LEDS];

void Board::LightUpLedMoves(int* moveIndexes, int maxMoves, CRGB* leds) {
  int index = 0;

  while (moveIndexes != nullptr && moveIndexes[index] != -1 && index < maxMoves) {
    int moveIndex = moveIndexes[index];

    leds[moveIndex] = CRGB::Blue; // Set the LED to blue for valid move
    FastLED.show();
    delay(960);

    Serial.print("Valid move LED at index: ");
    Serial.println(moveIndex);

    index++;
  }
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

// Array containing last move, [piece, color, initial row, initial col, final row, final col]
int LastMoveArray[6];

int InitialRow = 0; //global variables
int InitialCol = 0;


bool Board:: ShiftRegisterConverter(int** ShiftRegisterOutput) {
  //need shift register reference


  int ComparaisonArray[8][8]; //empty 8x8 array
  bool result = false;


  for (int i = 0; i < 8; i++) {


    for (int j = 0; j < 8; j++) {


      Piece piece = square[i][j].getPiece();
      Color color = square[i][j].getColor();

      if (piece != EMPTY && color != NONE) {
        ComparaisonArray[i][j] = 1;
      }
    }
  }
  for (int i = 0; i < 8; i++) {


    for (int j = 0; j < 8; j++) {
      if (ComparaisonArray[i][j] != ShiftRegisterOutput[i][j]) {
        int InitialRow = i;
        int InitialCol = j;


        result = true;
      }
    }
  }
  return result;
}
int Board:: getCol() {
  //get Column by having ARDUINO
  //for now, do interface or I/O with user using c>> to get int
  return InitialCol;

}


int Board:: getRow() {
  //get Row by having ARDUINO
  //for now, do interface or I/O with user using c>> to get int
  return InitialRow;
}






//1. Call ShiftRegisterArray(code is in To do list google doc) to have what the SR read
//2. Polling => Make an if statement that checks whether the board is the same as the SR array. If its not the same it means we have movement
// We use the ShiftRegisterConverter method. This method will also set global variables InitialRow and InitialCol to tell you which square has been lifted
//3. The rest of the code is going to be inside the if statement of the polling
//4. Get the piece and the color of the square where the piece was lifted using the InitialROW and InitialCol. Those variables can be obtained using the getCol and getRow methods
//5. Depending on piece, call the ShowPiece method and LightUpMethods
//6. Do a while loop to do another polling awaiting the move to be done.
// While(ShiftRegisterConverter = false) => Inside while you call ShiftRegister array to get the SR output. Call ShiftRegisterConverter to check movement of the board
//7. Call MovePiece according to piece to change the board state
//8. Checkmate method


// int Board:: getColUpdated(){
//   //get Column by having ARDUINO
//   //for now, do interface or I/O with user using c>> to get int


// }

// int Board:: getRowUpdated(){
//   //get Row by having ARDUINO
//   //for now, do interface or I/O with user using c>> to get int
// }

bool Board::movePawn(int row, int col, int RowUpdated, int ColUpdated) {}
//     int x = row;
//     int y = col;

//     Piece piece = square[x][y].getPiece();
//     Color color = square[x][y].getColor();
//     Piece destinationPiece = square[RowUpdated][ColUpdated].getPiece();
//     Color destinationColor = square[RowUpdated][ColUpdated].getColor();

//     int temp = abs(RowUpdated - row); // Difference in rows
//     int temp1 = abs(ColUpdated - col); // Difference in columns

//     Serial.print("Moving from ("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(")");
//     Serial.print("Trying to move to ("); Serial.print(RowUpdated); Serial.print(", "); Serial.print(ColUpdated); Serial.println(")");
//     Serial.print("temp: "); Serial.println(temp);
//     Serial.print("temp1: "); Serial.println(temp1);
//     // Serial.print("Piece at destination: "); Serial.println(destinationPiece);
//     // Serial.print("Destination color: "); Serial.println(destinationColor);

//     if (color == BLACK && piece == PAWN) {
//         // Black Pawn first move, 2 squares forward
//         if (x == 1 && temp == 2 && temp1 == 0) {
//             if (destinationPiece == EMPTY) {
//                 square[x][y].setupPiece(EMPTY, NONE);
//                 square[RowUpdated][ColUpdated].setupPiece(PAWN, BLACK);
//                 Serial.println("First move: 2 squares forward");
//                 return true;
//             }
//         }

//         // Black Pawn regular 1 square forward move
//         if (temp == 1 && temp1 == 0) {
//             if (destinationPiece == EMPTY) {
//                 square[x][y].setupPiece(EMPTY, NONE);
//                 square[RowUpdated][ColUpdated].setupPiece(PAWN, BLACK);
//                 Serial.println("Move: 1 square forward");
//                 return true;
//             }
//         }

//         // Black Pawn diagonal capture
//         if (temp == 1 && temp1 == 1) {
//             if (destinationPiece != EMPTY) {
//                 if (destinationColor == WHITE) {
//                     square[x][y].setupPiece(EMPTY, NONE);
//                     square[RowUpdated][ColUpdated].setupPiece(PAWN, BLACK);
//                     Serial.println("Diagonal capture move");
//                     return true;
//                 } else {
//                     Serial.println("Capture failed: Destination color is not opponent's.");
//                 }
//             } else {
//                 Serial.println("Capture failed: Destination is empty.");
//             }
//         }
//     } else if (color == WHITE && piece == PAWN) {
//         // White Pawn first move, 2 squares forward
//         if (x == 6 && temp == 2 && temp1 == 0) {
//             if (destinationPiece == EMPTY) {
//                 square[x][y].setupPiece(EMPTY, NONE);
//                 square[RowUpdated][ColUpdated].setupPiece(PAWN, WHITE);
//                 Serial.println("First move: 2 squares forward");
//                 return true;
//             }
//         }

//         // White Pawn regular 1 square forward move
//         if (temp == 1 && temp1 == 0) {
//             if (destinationPiece == EMPTY) {
//                 square[x][y].setupPiece(EMPTY, NONE);
//                 square[RowUpdated][ColUpdated].setupPiece(PAWN, WHITE);
//                 Serial.println("Move: 1 square forward");
//                 return true;
//             }
//         }

//         // White Pawn diagonal capture
//         if (temp == 1 && temp1 == 1) {
//             if (destinationPiece != EMPTY) {
//                 if (destinationColor == BLACK) {
//                     square[x][y].setupPiece(EMPTY, NONE);
//                     square[RowUpdated][ColUpdated].setupPiece(PAWN, WHITE);
//                     Serial.println("Diagonal capture move");
//                     return true;
//                 } else {
//                     Serial.println("Capture failed: Destination color is not opponent's.");
//                 }
//             } else {
//                 Serial.println("Capture failed: Destination is empty.");
//             }
//         }
//     }

//     Serial.println("Move is invalid");
//     return false; // If no valid move was made
// }


bool Board::moveRook(int row, int col, int RowUpdated, int ColUpdated) {
  int x = row;
  int y = col;

  Piece piece = square[x][y].getPiece();
  Color color = square[x][y].getColor();

  Serial.print("Attempting to move Rook from (");
  Serial.print(row);
  Serial.print(", ");
  Serial.print(col);
  Serial.print(") to (");
  Serial.print(RowUpdated);
  Serial.print(", ");
  Serial.print(ColUpdated);
  Serial.println(")");
  int temp = abs(ColUpdated - col);
  int temp1 = abs(RowUpdated - row);

  if ((piece == ROOK || piece == QUEEN) && (temp == 0 || temp1 == 0)) {

    if (temp == 0) { // check column
      if (row > RowUpdated) { // ROOK is moving up
        for (int i = row - 1; i > RowUpdated; i--) {
          Piece check = square[i][col].getPiece();
          if (check != EMPTY) { // if there's a piece, there's an error
            Serial.print("Move failed: Path blocked at (");
            Serial.print(i);
            Serial.print(", ");
            Serial.print(col);
            Serial.println(").");
            return false;
          }
        }
      }
      if (row < RowUpdated) { // ROOK is moving down
        for (int i = row + 1; i < RowUpdated; i++) {
          Piece check = square[i][col].getPiece();
          if (check != EMPTY) { // if there's a piece, there's an error
            Serial.print("Move failed: Path blocked at (");
            Serial.print(i);
            Serial.print(", ");
            Serial.print(col);
            Serial.println(").");
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
            Serial.print("Move failed: Path blocked at (");
            Serial.print(row);
            Serial.print(", ");
            Serial.print(i);
            Serial.println(").");
            return false;
          }
        }
      }
      if (col < ColUpdated) { // ROOK is moving to the right
        for (int i = col + 1; i < ColUpdated; i++) {
          Piece check = square[row][i].getPiece();
          if (check != EMPTY) { // if there's a piece, there's an error
            Serial.print("Move failed: Path blocked at (");
            Serial.print(row);
            Serial.print(", ");
            Serial.print(i);
            Serial.println(").");
            return false;
          }
        }
      }
    }

    // Check if the destination square is occupied by a piece of the same color
    Piece targetPiece = square[RowUpdated][ColUpdated].getPiece();
    Color targetColor = square[RowUpdated][ColUpdated].getColor();

    if (targetPiece != EMPTY && targetColor == color) {
      Serial.println("Move failed: Destination occupied by own piece.");
      return false; // The destination square is occupied by a piece of the same color
    }

    // If no error, move the Rook to the destination square
    square[x][y].setupPiece(EMPTY, NONE);
    square[RowUpdated][ColUpdated].setupPiece(ROOK, color);
    Serial.println("Rook move successful.");
    LastMoveArray[0] = piece;
    LastMoveArray[1] = color;
    LastMoveArray[2] = row;
    LastMoveArray[3] = col;
    LastMoveArray[4] = RowUpdated;
    LastMoveArray[5] = ColUpdated;
    return true;
  }

  Serial.println("Move failed: Not a vertical or horizontal move.");
  return false; // if move is not vertical or horizontal, then return false
}

bool Board::moveKnight(int row, int col, int RowUpdated, int ColUpdated) {
  int startX = row;
  int startY = col;
  int endX = RowUpdated;
  int endY = ColUpdated;

  // Ensure the starting square contains a knight
  Piece piece = square[startX][startY].getPiece();
  if (piece != KNIGHT) {
    Serial.println("Move failed: No knight at start position.");
    return false;
  }

  // Calculate the move pattern
  int dx = abs(endX - startX);
  int dy = abs(endY - startY);

  // Check if the move pattern is valid for a knight
  if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
    Serial.println("Move failed: Invalid knight move pattern.");
    return false;
  }

  // Check the destination square
  Piece destinationPiece = square[endX][endY].getPiece();
  Color destinationColor = square[endX][endY].getColor();
  Color pieceColor = square[startX][startY].getColor();

  // Ensure the destination is either empty or contains an opponent's piece
  if (destinationPiece != EMPTY && destinationColor == pieceColor) {
    Serial.println("Move failed: Destination occupied by own piece.");
    return false;
  }

  // Move the knight
  square[startX][startY].setupPiece(EMPTY, NONE);
  square[endX][endY].setupPiece(KNIGHT, pieceColor);

  Serial.println("Knight move successful.");
  LastMoveArray[0] = piece;
  LastMoveArray[1] = pieceColor;
  LastMoveArray[2] = row;
  LastMoveArray[3] = col;
  LastMoveArray[4] = RowUpdated;
  LastMoveArray[5] = ColUpdated;
  return true;
}

bool Board::moveBishop(int row, int col, int RowUpdated, int ColUpdated) {
  //1. Get Coordinates: Fetch the coordinates of the bishop's current and target positions
  //2. Calculate Differences: Determine how far the bishop needs to move horizontally and vertically
  //3. Check Move Pattern: Ensure the move is diagonal by comparing the differences in coordinates
  //4. Determine Direction: Calculate the direction to move along the diagonal
  //5. Check Path: Verify that no pieces are blocking the diagonal path
  //6. Check Destination: Ensure the target square is either empty or occupied by an opponent's piece
  //7. Execute Move: Move the bishop to the target square and clear the original square
  //8. Return Result: Indicate whether the move was valid with bool

  //Reference logic: https://stackoverflow.com/questions/69523744/diagonal-bishop-moves-on-chess-board-with-python

  //Get the coordinates of the current square (thisBishop) and the target square (thatSpace)
  int startX = row;
  int startY = col;
  int endX = RowUpdated;
  int endY = ColUpdated;
  Piece piece = square[startX][startY].getPiece();
  if (piece != BISHOP && piece != QUEEN) {
    Serial.println("Move failed: No bishop at start position.");
    return false;
  }

  // Calculate the differences in the x and y coordinates
  int dx = abs(endX - startX);
  int dy = abs(endY - startY);

  // Check if the move is diagonal
  if (dx != dy) {
    Serial.println("Move failed: Not a diagonal move.");
    return false;
  }

  // Determine the direction of movement along the diagonal
  int xDirection = (endX - startX) / dx;
  int yDirection = (endY - startY) / dy;

  // Check if all squares between the start and end positions are empty
  for (int i = 1; i < dx; ++i) {
    int intermediateX = startX + i * xDirection;
    int intermediateY = startY + i * yDirection;
    Piece intermediatePiece = square[intermediateX][intermediateY].getPiece();

    if (intermediatePiece != EMPTY) {
      Serial.print("Move failed: Path blocked at (");
      Serial.print(intermediateX);
      Serial.print(", ");
      Serial.print(intermediateY);
      Serial.println(").");
      return false; // There's a piece blocking the path
    }
  }

  // Get the piece and color at the target square
  Piece targetPiece = square[endX][endY].getPiece();
  Color targetColor = square[endX][endY].getColor();
  Color bishopColor = square[startX][startY].getColor();

  // Check if the destination square is either empty or occupied by an opponent's piece
  if (targetPiece != EMPTY && targetColor == bishopColor) {
    Serial.println("Move failed: Destination occupied by own piece.");
    return false; // The destination square is occupied by same color piece
  }

  // Move the bishop to the destination square
  square[startX][startY].setupPiece(EMPTY, NONE); // Clear the original square
  square[endX][endY].setupPiece(BISHOP, bishopColor); // Set the target square with the bishop

  Serial.println("Bishop move successful.");
  LastMoveArray[0] = piece;
  LastMoveArray[1] = bishopColor;
  LastMoveArray[2] = row;
  LastMoveArray[3] = col;
  LastMoveArray[4] = RowUpdated;
  LastMoveArray[5] = ColUpdated;
  return true;
}

bool Board::moveQueen(int row, int col, int RowUpdated, int ColUpdated) {
  int startX = row;
  int startY = col;
  int endX = RowUpdated;
  int endY = ColUpdated;

  Piece piece = square[startX][startY].getPiece();
  Color color = square[startX][startY].getColor();

  Serial.print("Attempting to move Queen from (");
  Serial.print(row);
  Serial.print(", ");
  Serial.print(col);
  Serial.print(") to (");
  Serial.print(RowUpdated);
  Serial.print(", ");
  Serial.print(ColUpdated);
  Serial.println(")");

  // Check if piece being moved is a queen
  // if (piece != QUEEN) {
  //     Serial.println("Move failed: Piece is not a Queen.");
  //     return false;
  // }

  // Calculate the differences in the coordinates
  int dx = abs(endX - startX);
  int dy = abs(endY - startY);

  // See if the move is a rook-like or bishop-like move
  bool isRookMove = (dx == 0 || dy == 0); // Horizontal or vertical move
  bool isBishopMove = (dx == dy); // Diagonal move

  // Use the existing methods to handle the move
  if (isRookMove) {
    bool result = moveRook(startX, startY, endX, endY);
    if (result) {
      // Move the Queen to the destination square
      square[startX][startY].setupPiece(EMPTY, NONE);
      square[endX][endY].setupPiece(QUEEN, color);
      Serial.println("Queen move successful (Rook-like move).");
      return true;
    } else {
      Serial.println("Move failed: Invalid Rook-like move for Queen.");
      return false;
    }
  }
  if (isBishopMove) {
    bool result = moveBishop(startX, startY, endX, endY);
    if (result) {
      // Move the Queen to the destination square
      square[startX][startY].setupPiece(EMPTY, NONE);
      square[endX][endY].setupPiece(QUEEN, color);
      Serial.println("Queen move successful (Bishop-like move).");
      return true;
    } else {
      Serial.println("Move failed: Invalid Bishop-like move for Queen.");
      return false;
    }
  }

  Serial.println("Move failed: Invalid move for Queen (not Rook-like or Bishop-like).");
  return false; // If the move is neither rook-like nor bishop-like, it's invalid
}

bool Board::moveKing(int row, int col, int RowUpdated, int ColUpdated) {
  //https://stackoverflow.com/questions/58075207/python-code-for-validating-chess-king-movement
  int startX = row;
  int startY = col;
  int endX = RowUpdated;
  int endY = ColUpdated;

  Piece piece = square[startX][startY].getPiece();
  Color color = square[startX][startY].getColor();

  //Check if the piece is a King
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

  // Check if the move puts the King in check
  bool inCheck = CheckKing(endX, endY);

  // Undo the temporary move
  square[endX][endY].setupPiece(targetPiece, targetColor); // Restore the original piece at the destination
  square[startX][startY].setupPiece(KING, color);          // Place the King back in its original position

  // If moving the King puts it in check, the move is invalid
  if (inCheck) {
    return false;
  }

  // Finalize the move
  square[startX][startY].setupPiece(EMPTY, NONE);  // Remove the King from the starting position
  square[endX][endY].setupPiece(KING, color);      // Place the King in the final position

  LastMoveArray[0] = piece;
  LastMoveArray[1] = color;
  LastMoveArray[2] = row;
  LastMoveArray[3] = col;
  LastMoveArray[4] = RowUpdated;
  LastMoveArray[5] = ColUpdated;
  return true;  // The move is valid
}

bool Board::CheckKing(int row, int col) {
  // Get the king's color
  Color kingColor = square[row][col].getColor();

  // Check if the king is in check by any opponent piece
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      Piece piece = square[r][c].getPiece();
      Color color = square[r][c].getColor();

      if (color == kingColor || piece == 7) {
        continue;
      }

      int dx = abs(row - r);
      int dy = abs(col - c);

      // Check if the piece is a pawn
      if (piece == PAWN) {
        int direction;
        if (color == WHITE) {
          direction = -1; // White pawns move "up"
        } else {
          direction = 1;  // Black pawns move "down"
        }
        if (row == r + direction && (col == c - 1 || col == c + 1)) {
          printf("pawn check, row: %d, col: %d, color: %d\n", r, c, color);
          return true; // The pawn can attack the king diagonally
        }
      }
      // Check if the piece is a knight
      else if (piece == KNIGHT) {
        if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
          printf("knight check, row: %d, col: %d, color: %d\n", r, c, color);
          return true; // The knight can move to the king's square
        }
      }
      // Check if the piece is a queen
      else if (piece == QUEEN) {
        // Diagonal movement check
        if (dx == dy) {
          int xDirection, yDirection;
          if (r > row) {
            xDirection = 1;
          } else {
            xDirection = -1;
          }
          if (c > col) {
            yDirection = 1;
          } else {
            yDirection = -1;
          }
          bool pathClear = true;
          for (int i = 1; i < dx; i++) {
            int intermediateX = row + i * xDirection;
            int intermediateY = col + i * yDirection;
            if (square[intermediateX][intermediateY].getPiece() != EMPTY) {
              pathClear = false;
              break;
            }
          }
          if (pathClear) {
            printf("queen check, row: %d, col: %d, color: %d\n", r, c, color);
            return true; // The queen can move to the king's square
          }
        }

        // Straight-line movement check
        else if (dx == 0 || dy == 0) {
          int stepX = 0;
          int stepY = 0;
          if (dx != 0) {
            if (row > r) {
              stepX = 1;
            } else {
              stepX = -1;
            }
          }
          if (dy != 0) {
            if (col > c) {
              stepY = 1;
            } else {
              stepY = -1;
            }
          }
          bool pathClear = true; // Check if the path is clear
          int currentX = r + stepX;
          int currentY = c + stepY;
          while (currentX != row || currentY != col) {
            if (square[currentX][currentY].getPiece() != EMPTY) {
              pathClear = false;
              break;
            }
            currentX += stepX;
            currentY += stepY;
          }
          if (pathClear) {
            printf("queen check, row: %d, col: %d, color: %d\n", r, c, color);
            return true; // The queen can move to the king's square
          }
        }
      }
      // Check if the piece is a bishop
      else if (piece == BISHOP) {
        if (dx == dy) {
          int xDirection, yDirection;
          if (r > row) {
            xDirection = 1;
          } else {
            xDirection = -1;
          }
          if (c > col) {
            yDirection = 1;
          } else {
            yDirection = -1;
          }
          bool pathClear = true;
          for (int i = 1; i < dx; i++) {
            int intermediateX = row + i * xDirection;
            int intermediateY = col + i * yDirection;
            if (square[intermediateX][intermediateY].getPiece() != EMPTY) {
              pathClear = false;
              break;
            }
          }
          if (pathClear) {
            printf("bishop check, row: %d, col: %d, color: %d\n", r, c, color);
            return true; // The bishop can move to the king's square
          }
        }
      }
      // Check if the piece is a rook
      else if (piece == ROOK) {
        if (dx == 0 || dy == 0) {
          int stepX = 0;
          int stepY = 0;
          if (dx != 0) {
            if (row > r) {
              stepX = 1;
            } else {
              stepX = -1;
            }
          }
          if (dy != 0) {
            if (col > c) {
              stepY = 1;
            } else {
              stepY = -1;
            }
          }
          bool pathClear = true; // Check if the path is clear
          int currentX = r + stepX;
          int currentY = c + stepY;
          while (currentX != row || currentY != col) {
            if (square[currentX][currentY].getPiece() != EMPTY) {
              pathClear = false;
              break;
            }
            currentX += stepX;
            currentY += stepY;
          }
          if (pathClear) {
            printf("rook check, row: %d, col: %d, color: %d\n", r, c, color);
            return true; // The rook can attack the king
          }
        }
      }
    }
  }
  return false;//no attack on king

}

Square::Square()
{
  piece = EMPTY;
  color = NONE;
}

void Board:: testing() {

  Piece piece = square[2][2].getPiece();
  Color color = square[2][2].getColor();

  if (piece == KNIGHT || color == BLACK) {
    Serial.println("Your mom");
  }

}

void Board::createChessBoard() {
  //square[0][0].setupPiece(ROOK, BLACK);
  //square[0][1].setupPiece(KNIGHT, BLACK);
  //square[0][2].setupPiece(BISHOP, BLACK);
  //square[0][3].setupPiece(QUEEN, BLACK);
  //square[0][4].setupPiece(KING, BLACK);
  //square[0][5].setupPiece(BISHOP, BLACK);
  //square[0][6].setupPiece(KNIGHT, BLACK);
  //square[0][7].setupPiece(ROOK, BLACK);

  // square[1][0].setupPiece(PAWN, BLACK);
  // square[1][1].setupPiece(PAWN, BLACK);
  // square[1][2].setupPiece(PAWN, BLACK);
  // square[1][3].setupPiece(PAWN, BLACK);
  // square[1][4].setupPiece(PAWN, BLACK);
  // square[1][5].setupPiece(PAWN, BLACK);
  // square[1][6].setupPiece(PAWN, BLACK);
  // square[1][7].setupPiece(PAWN, BLACK);

  // square[6][0].setupPiece(PAWN, WHITE);
  // square[6][1].setupPiece(PAWN, WHITE);//Changed this for testing
  // square[6][2].setupPiece(PAWN, WHITE);
  // square[6][3].setupPiece(PAWN, WHITE);
  // square[6][4].setupPiece(PAWN, WHITE);
  // square[6][5].setupPiece(PAWN, WHITE);
  // square[6][6].setupPiece(PAWN, WHITE);
  // square[6][7].setupPiece(PAWN, WHITE);

  //square[7][0].setupPiece(ROOK, WHITE);
  //square[7][1].setupPiece(KNIGHT, WHITE);
  //square[7][2].setupPiece(BISHOP, WHITE); //
  //square[7][3].setupPiece(QUEEN, WHITE);
  //square[7][4].setupPiece(KING, WHITE);
  //square[7][5].setupPiece(BISHOP, WHITE);
  //square[7][6].setupPiece(KNIGHT, WHITE);
  //square[7][7].setupPiece(ROOK, WHITE);

  for (int y = 2; y < 6; y++) { //rest of pieces are empty
    for (int x = 0; x < 8; x++ ) {
      square[y][x].setupPiece(EMPTY, NONE);
    }
  }
}

int Board:: IndexConverter(int row, int col) {


  int temp = 0;
  int temp1 = 0;

  if (row % 2 == 0) { // even
    temp = row * 8;

    for (int x = 1; x < col + 1; x++) {
      temp += 1;
    }
    return temp;
  }
  else if (row % 2 != 0) { //odd
    temp1 = row * 8;
    for (int y = 6; y > col - 1; y--) {
      temp1 += 1;
    }
    return temp1;

  }

}
using namespace std;

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

int* Board::ShowAllKingMoves(int row, int col) {
  static int moves[8];  // The king can move a maximum of 8 squares
  vector<int> validMoves;

  // Possible King moves
  int possibleMoves[8][2] = {
    {row + 1, col},     // down
    {row - 1, col},     // up
    {row, col + 1},     // right
    {row, col - 1},     // left
    {row + 1, col + 1}, // down-right
    {row + 1, col - 1}, // down-left
    {row - 1, col + 1}, // up-right
    {row - 1, col - 1}  // up-left
  };

  Color ogColor = square[row][col].getColor();

  // Loop through all possible King moves
  for (int i = 0; i < 8; i++) {
    int newRow = possibleMoves[i][0];
    int newCol = possibleMoves[i][1];

    // Check if the new position is within bounds
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
      Piece piece = square[newRow][newCol].getPiece();
      Color targetColor = square[newRow][newCol].getColor();

      // Add valid move if the square is empty or contains an opponent's piece
      if (piece == EMPTY || targetColor != ogColor) {
        // check if moving the King to this square will result in a check

        //Temporarily move the king to the destination square to check for checks
        square[row][col].setupPiece(EMPTY, NONE);
        square[newRow][newCol].setupPiece(KING, ogColor);

        if (!CheckKing(newRow, newCol)) {
          // If the move doesn't put the King in check, add it to valid moves
          validMoves.push_back(IndexConverter(newRow, newCol));
        }
        else {
          printf("check, row: %d, col: %d\n", newRow, newCol );
        }

        // Undo the temporary move
        square[row][col].setupPiece(KING, ogColor);
        square[newRow][newCol].setupPiece(piece, targetColor);
      }
      else {
        printf("piece: %d, color: %d, row: %d, col: %d\n", piece, targetColor, newRow, newCol);
      }
    }
  }

  // Copy valid moves to the static array
  int moveIndex = 0;
  for (size_t i = 0; i < validMoves.size(); i++) {
    moves[moveIndex++] = validMoves[i];
  }

  // Fill remaining elements with -1 to mark the end
  for (int i = moveIndex; i < 8; i++) {
    moves[i] = -1;
  }

  return moves;
}

int* Board::CheckKingGetChecks(int row, int col) {
  // 0/1 if check, -1 or type of piece 1, -1 or row of piece 1, -1 or col of piece 1
  // -1 or type of piece 2, -1 or row of piece 2, -1 or col of piece 2
  static int CheckState[7] = {0, -1, -1, -1, -1, -1, -1};

  bool Piece1Found = false; // Set as true if checking piece 1 found, start appending in 2nd half of CheckState
  bool CheckFound = false; // Set as true when a check is found

  // Get the king's color
  Color kingColor = square[row][col].getColor();

  // Check if the king is in check by any opponent piece
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      Piece piece = square[r][c].getPiece();
      Color color = square[r][c].getColor();

      if (color == kingColor || piece == 6) {
        continue;
      }

      int dx = abs(row - r);
      int dy = abs(col - c);

      // Check if the piece is a pawn
      if (piece == PAWN) {
        int direction;
        if (color == WHITE) {
          direction = -1; // White pawns move "up"
        } else {
          direction = 1;  // Black pawns move "down"
        }
        if (row == r + direction && (col == c - 1 || col == c + 1)) {
          // The pawn can attack the king diagonally
          printf("pawn check, row: %d, col: %d, color: %d\n", r, c, color);
          CheckFound = true;
        }
      }
      // Check if the piece is a knight
      else if (piece == KNIGHT) {
        if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
          // The knight can move to the king's square
          printf("knight check, row: %d, col: %d, color: %d\n", r, c, color);
          CheckFound = true;
        }
      }
      // Check if the piece is a queen
      else if (piece == QUEEN) {
        // Check if the path is clear
        bool pathClear = true;

        // Diagonal movement check
        if (dx == dy) {
          int xDirection, yDirection;
          if (r > row) {
            xDirection = 1;
          } else {
            xDirection = -1;
          }
          if (c > col) {
            yDirection = 1;
          } else {
            yDirection = -1;
          }
          for (int i = 1; i < dx; i++) {
            int intermediateX = row + i * xDirection;
            int intermediateY = col + i * yDirection;
            if (square[intermediateX][intermediateY].getPiece() != EMPTY) {
              pathClear = false;
            }
          }
        }

        // Straight-line movement check
        else if (dx == 0 || dy == 0) {
          int stepX = 0;
          int stepY = 0;
          if (dx != 0) {
            if (row > r) {
              stepX = 1;
            } else {
              stepX = -1;
            }
          }
          if (dy != 0) {
            if (col > c) {
              stepY = 1;
            } else {
              stepY = -1;
            }
          }
          int currentX = r + stepX;
          int currentY = c + stepY;
          while (currentX != row || currentY != col) {
            if (square[currentX][currentY].getPiece() != EMPTY) {
              pathClear = false;
            }
            currentX += stepX;
            currentY += stepY;
          }
        }
        if (pathClear) {
          // The queen can move to the king's square
          printf("queen check, row: %d, col: %d, color: %d\n", r, c, color);
          CheckFound = true;
        }
      }
      // Check if the piece is a bishop
      else if (piece == BISHOP) {
        if (dx == dy) {
          int xDirection, yDirection;
          if (r > row) {
            xDirection = 1;
          } else {
            xDirection = -1;
          }
          if (c > col) {
            yDirection = 1;
          } else {
            yDirection = -1;
          }
          bool pathClear = true;
          for (int i = 1; i < dx; i++) {
            int intermediateX = row + i * xDirection;
            int intermediateY = col + i * yDirection;
            if (square[intermediateX][intermediateY].getPiece() != EMPTY) {
              pathClear = false;
            }
          }
          if (pathClear) {
            // The bishop can move to the king's square
            printf("bishop check, row: %d, col: %d, color: %d\n", r, c, color);
            CheckFound = true;
          }
        }
      }
      // Check if the piece is a rook
      else if (piece == ROOK) {
        if (dx == 0 || dy == 0) {
          int stepX = 0;
          int stepY = 0;
          if (dx != 0) {
            if (row > r) {
              stepX = 1;
            } else {
              stepX = -1;
            }
          }
          if (dy != 0) {
            if (col > c) {
              stepY = 1;
            } else {
              stepY = -1;
            }
          }
          bool pathClear = true; // Check if the path is clear
          int currentX = r + stepX;
          int currentY = c + stepY;
          while (currentX != row || currentY != col) {
            if (square[currentX][currentY].getPiece() != EMPTY) {
              pathClear = false;
            }
            currentX += stepX;
            currentY += stepY;
          }
          if (pathClear) {
            // The rook can move to the king's square
            printf("rook check, row: %d, col: %d, color: %d\n", r, c, color);
            CheckFound = true;
          }
        }
      }
      // If a check was found
      if (CheckFound) {
        if (!Piece1Found) {
          // No other piece found yet
          Piece1Found = true;
          CheckState[0] = 1;
          CheckState[1] = piece;
          CheckState[2] = r;
          CheckState[3] = c;
        }
        else {
          // Double check
          CheckState[4] = piece;
          CheckState[5] = r;
          CheckState[6] = c;
        }
        CheckFound = false;
      }
    }
  }
  return CheckState;
}

bool Board::Checkmate(int row, int col) {
  int* CurrentChecks = CheckKingGetChecks(row, col);
  Color kingColor = square[row][col].getColor();

  // If there's a check
  if (CurrentChecks[0]) {
    // King has no moves
    if ((ShowAllKingMoves(row, col))[0] == -1) {
      // 1 piece check, must capture or block
      if (CurrentChecks[4] == -1) {
        Piece CheckingPiece = square[CurrentChecks[2]][CurrentChecks[3]].getPiece();
        Color CheckingPieceColor = square[CurrentChecks[2]][CurrentChecks[3]].getColor();

        // Looping through all pieces
        for (int r = 0; r < 8; r++) {
          for (int c = 0; c < 8; c++) {
            Piece piece = square[r][c].getPiece();
            Color color = square[r][c].getColor();

            if (color != kingColor || piece == 6 || piece == 0) {
              continue;
            }

            // Verifying if the checking piece can be captured by current defending piece
            // Queen
            if (piece == QUEEN) {
              if (moveQueen(r, c, CurrentChecks[2], CurrentChecks[3])) {
                // Undo the temporary move
                square[r][c].setupPiece(QUEEN, kingColor);
                square[CurrentChecks[2]][CurrentChecks[3]].setupPiece(CheckingPiece, CheckingPieceColor);
                return false;
              }
            }
            // Bishop
            else if (piece == BISHOP) {
              if (moveBishop(r, c, CurrentChecks[2], CurrentChecks[3])) {
                // Undo the temporary move
                square[r][c].setupPiece(BISHOP, kingColor);
                square[CurrentChecks[2]][CurrentChecks[3]].setupPiece(CheckingPiece, CheckingPieceColor);
                return false;
              }
            }
            // Knight
            else if (piece == KNIGHT) {
              if (moveKnight(r, c, CurrentChecks[2], CurrentChecks[3])) {
                // Undo the temporary move
                square[r][c].setupPiece(KNIGHT, kingColor);
                square[CurrentChecks[2]][CurrentChecks[3]].setupPiece(CheckingPiece, CheckingPieceColor);
                return false;
              }
            }
            // Rook
            else if (piece == ROOK) {
              if (moveRook(r, c, CurrentChecks[2], CurrentChecks[3])) {
                // Undo the temporary move
                square[r][c].setupPiece(ROOK, kingColor);
                square[CurrentChecks[2]][CurrentChecks[3]].setupPiece(CheckingPiece, CheckingPieceColor);
                return false;
              }
            }
            // Pawn
            else if (piece == PAWN) {
              if (movePawn(r, c, CurrentChecks[2], CurrentChecks[3])) {
                // Undo the temporary move
                square[r][c].setupPiece(PAWN, kingColor);
                square[CurrentChecks[2]][CurrentChecks[3]].setupPiece(CheckingPiece, CheckingPieceColor);
                return false;
              }
            }

            // If checking piece is a knight or pawn, only option is to capture it
            // Verifying if the current defending piece can block the path to the king
            if (!(CheckingPiece == 3 || CheckingPiece == 5)) {
              int dx = abs(row - CurrentChecks[2]);
              int dy = abs(col - CurrentChecks[3]);
              int stepX = 0;
              int stepY = 0;
              if (dx != 0) {
                if (row < CurrentChecks[2]) {
                  stepX = 1;
                } else {
                  stepX = -1;
                }
              }
              if (dy != 0) {
                if (col < CurrentChecks[3]) {
                  stepY = 1;
                } else {
                  stepY = -1;
                }
              }
              int currentX = row + stepX;
              int currentY = col + stepY;
              while (!(currentX == CurrentChecks[2] && currentY == CurrentChecks[3])) {

                // Verifying if current defending piece can move to square[currentX][currentY]
                // Queen
                if (piece == QUEEN) {
                  if (moveQueen(r, c, currentX, currentY)) {
                    // Undo the temporary move
                    square[r][c].setupPiece(QUEEN, kingColor);
                    square[currentX][currentY].setupPiece(EMPTY, NONE);
                    return false;
                  }
                }
                // Bishop
                else if (piece == BISHOP) {
                  if (moveQueen(r, c, currentX, currentY)) {
                    // Undo the temporary move
                    square[r][c].setupPiece(BISHOP, kingColor);
                    square[currentX][currentY].setupPiece(EMPTY, NONE);
                    return false;
                  }
                }
                // Knight
                else if (piece == KNIGHT) {
                  if (moveQueen(r, c, currentX, currentY)) {
                    // Undo the temporary move
                    square[r][c].setupPiece(KNIGHT, kingColor);
                    square[currentX][currentY].setupPiece(EMPTY, NONE);
                    return false;
                  }
                }
                // Rook
                else if (piece == ROOK) {
                  if (moveQueen(r, c, currentX, currentY)) {
                    // Undo the temporary move
                    square[r][c].setupPiece(ROOK, kingColor);
                    square[currentX][currentY].setupPiece(EMPTY, NONE);
                    return false;
                  }
                }
                // Pawn
                else if (piece == PAWN) {
                  if (moveQueen(r, c, currentX, currentY)) {
                    // Undo the temporary move
                    square[r][c].setupPiece(PAWN, kingColor);
                    square[currentX][currentY].setupPiece(EMPTY, NONE);
                    return false;
                  }
                }
                currentX += stepX;
                currentY += stepY;
              }
            }

          }
        }
      }
      // Double-check and King has no moves OR no defending piece can block/capture the piece
      return true;
    }
  }
  // No check or King has moves
  return false;
}

int* Board::GetLastMove() {
  return LastMoveArray;
}

int** ShiftRegisterArray() {
  //shift register input converter

  int ioSelect = 2; // SR Pin 15.
  int clockPulse = 3; // SR Pin 7.
  int dataOut = 4; // SR Pin 13.
  int value = 0;


  int** ShiftRegisterOutput = new int*[8]; //empty 8x8 array
  for (int i = 0; i < 8; i++) {


    if (i % 2 == 0) { //if i is even
      for (int j = 0; j < 8; j++) {
        int value = digitalRead(dataOut); // Reads data from SR serial data out pin.
        ShiftRegisterOutput[i][j] = value;
        digitalWrite(clockPulse, LOW);
        digitalWrite(clockPulse, HIGH);


      }
    }
    if (i % 2 != 0) {
      for (int j = 7; j >= 0; j--) {
        int value = digitalRead(dataOut); // Reads data from SR serial data out pin.
        ShiftRegisterOutput[i][j] = value;
        digitalWrite(clockPulse, LOW);
        digitalWrite(clockPulse, HIGH);


      }


    }
  }
  return ShiftRegisterOutput;
}
