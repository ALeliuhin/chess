# chess-C++
<img src = "./Picture/Screenshot 2024-06-07 234132.png" width = "600px" height = "250px"/>

## Project Description
Our project is a command block application that let's you play chess, together with your friends.
It is using the rules of any game of chess, and it even allows for special moves such as Castling or En Passant.

## Contributors
- Ecaterina Manole
- Stefan-Silviu Mitrea
- Artiom Leliuhin
## How to play
In order to start the game, you need to provide any input to the command line.\
Now that the board is ready, you have to provide a position owned by the current team's turn and a position on which the piece should end up. (Keep in mind the type of the piece!)\
Now try to check mate your opponent!

## Documentation
The source code is spread across 3 source files: "main.cpp", "chess.cpp", "chess.h".\
The program comprises 3 classes: Square, enPassant, Board, declared in "chess.h".
- Class Square consist of certain methods that allow manipulating the board space.
- Class enPassant provides a special case-scenario for "enPassant".
- Class Board includes methods for pieces' movements, as well as performs possible moves checks and allows to set the board.


Each possible moves checking function ensures valid moves for each piece, according to the rules of the Chess game.\
Likewise, we have functions doMove() and makeMove() that allow us to perform moves based on user inputs.

The input of the user is source (x, y) coordinates and destination (x, y) coordinates. Overlappings, obstacles and friendly-fire are considered.

Initially, the board is set accordingly to the actual board, comprising Pieces and Empty spaces, using enums "Piece" and "Color", whilst "Color" is either black, white or none. The smart pointer of type "std::shared_ptr" is created to set the game.

The cases for checkmates are also taken into account.


## Requirements

- C++17 and higher
- Windows 10/11
- G++ compiler 13.2.0
