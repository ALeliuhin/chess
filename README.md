# chess-C++

## Documentation

1. The source code is spread across 3 source files: "main.cpp", "chess.cpp", "chess.h".
2. The program comprises 3 classes: Square, enPassant, Board, declared in "chess.h".
    - Class Square consist of certain methods that allow manipulating the board space.
    - Class enPassant provides a special case-scenario for "enPassant".
    - Class Board includes methods for pieces' movements, as well as performs possible moves checks and allows to set the board.
3. Each possible moves checking function ensures valid moves for each piece, according to the rules of the Chess game.
Likewise, we have functions doMove() and makeMove() that allow us to perform moves based on user inputs. The input of the user is source (x, y) coordinates and destination (x, y) coordinates. Overlappings, obstacles and friendly-fire are considered.
4. Initially, the board is set accordingly to the actual board, comprising Pieces and Empty spaces, using enums "Piece" and "Color", whilst "Color" is either black, white or none. The smart pointer of type "std::shared_ptr" is created to set the game.
5. The cases for checkmates are also taken into account.


## Requirements

- C++17 and higher
- Windows 10/11
- G++ compiler 13.2.0
