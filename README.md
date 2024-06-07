# chess-C++

## Documentation

1. The source code is spread across 3 source files: "main.cpp", "chess.cpp", "chess.h".
2. The program comprises 3 classes: Square, enPassant, Board, declared in "chess.h".
    1.1. Class Square consist of certain methods that allow manipulating the board space.
    1.2. Class enPassant provides a special case-scenario for "enPassant".
    1.3. Class Board includes methods for pieces' movements, as well as performs possible moves checks and allows to set the board.
3. Each possible moves checking function ensures valid moves for each piece, according to the rules of the Chess game.
Likewise, we have functions doMove() and makeMove() that allow us to perform moves based on user inputs. The input of the user is source (x, y) coordinates and destination (x, y) coordinates. Overlappings, obstacles and friendly-fire are considered.
4. 
