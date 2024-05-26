#include <iostream>
#include <string>
#include <windows.h>
#include "chess.h"

using namespace std;

int main()
{
	system("cls");
	Board b;
	string s;
	bool newgame = true;
	cout << "\033[1;32m" << "   _____ _    _ ______  _____ _____ \n  / ____| |  | |  ____|/ ____/ ____| \n | |    | |__| | |__  | (___| (___  \n | |    |  __  |  __|  \\___  \\___ \\ \n | |____| |  | | |____ ____) |___) | \n  \\_____|_|  |_|______|_____/_____/ \n" << "\033[0m" << endl;
	cout << "\033[1;32mEnter any key to continue\033[0m" << endl;
	cin >> s;

	while(newgame){
		b.setBoard_EnPassant();
		while (b.playGame());
		cout << "Do you want to play again? (y for yes, anything else for no) ";
		cin >> s;
		if (s != "y")
			newgame = false;
	}


	return 0;
}