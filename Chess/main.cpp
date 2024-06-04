#include <iostream>
#include <string>
#include <windows.h>
#include "chess.h"

const std::string RESET = "\033[0m";
const std::string BOLD_WHITE = "\033[1;37m";
const std::string BOLD_RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";

using namespace std;

int main()
{
    system("cls");
    unique_ptr<Board> b = make_unique<Board>(); 
    string s;
    bool newgame = true;
    cout << GREEN << "   _____ _    _ ______  _____ _____ \n  / ____| |  | |  ____|/ ____/ ____| \n | |    | |__| | |__  | (___| (___  \n | |    |  __  |  __|  \\___  \\___ \\ \n | |____| |  | | |____ ____) |___) | \n  \\_____|_|  |_|______|_____/_____/ \n" << RESET << endl;
	cout << GREEN << "Enter any key to continue" << RESET << endl;
	cin >> s;

    while(newgame){
        b->setBoard(); 
        while (b->playGame()); 
        cout << GREEN << "Do you want to play again? (y for yes, anything else for no) " << RESET;
        cin >> s;
        if (s != "y")
            newgame = false;
    }

    return 0;
}