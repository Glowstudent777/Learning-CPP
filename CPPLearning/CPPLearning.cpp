#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <shellapi.h>

using namespace std;

#define KEY_UP 72       //Up arrow character
#define KEY_DOWN 80     //Down arrow character
#define KEY_ENTER '\r'  //Enter key character

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Used for goto
COORD CursorPosition; // Used for goto

bool running = true;
bool gameover = false;
bool firstGame = true;
int guesses;

const int DEFAULT_COLOR = 7; // White text on black background
const int SELECTED_COLOR = 240; // Black text on white background (you can adjust this color code)

void gotoXY(int, int); // Function defined below if this is new to you
void playGame(); // Function to play the guessing game
int menu(); // Function to display the menu

int main()
{
	srand(time(0));
	int choice;

	while (running)
	{
		choice = menu();

		switch (choice)
		{
		case 0:
			playGame();
			break;
		case 1:
			running = false;
			break;
		case 2:
			ShellExecute(0, 0, L"https://github.com/Glowstudent777/Learning-CPP", 0, 0, SW_SHOW);
			break;
		}
	}

	return 0;
}

int menu()
{
	system("cls");

	int selected = 0;    // Keeps track of which option is selected.
	int menuIndent = 0;  // The indentation of the menu from the left side of the screen.
	int x = 7;           // The x coordinate of the cursor.
	int numChoices = 3;  // The number of choices we have.
	bool selecting = true; // True if we are still waiting for the user to press enter.
	bool updated = true; // True if the selected value has just been updated.

	cout << "*******************************\n";
	cout << "*          Main Menu          *\n";
	cout << "*******************************\n\n";

	cout << "Use the up and down arrow keys to navigate the menu.\n";

	if (selected == 0) SetConsoleTextAttribute(console, SELECTED_COLOR);

	if (firstGame) {
		gotoXY((menuIndent + 2), 7); cout << "Play Game";
	}
	else {
		gotoXY((menuIndent + 2), 7); cout << "Play Again";
	}
	SetConsoleTextAttribute(console, DEFAULT_COLOR);

	gotoXY((menuIndent + 2), 8); cout << "Quit Program";
	gotoXY((menuIndent + 2), 9); cout << "Github Repo";

	gotoXY(menuIndent, x); cout << "->";
	gotoXY(menuIndent, 12);

	char c; // Store c outside of the loop for efficiency.
	while (selecting)
	{
		switch ((c = _getch()))
		{
		case KEY_UP:
			if (selected > 0 && x != 7)
			{
				gotoXY(menuIndent, x); cout << "  ";
				x--;
				gotoXY(menuIndent, x); cout << "->";
				--selected;
				updated = true;
			}
			break;
		case KEY_DOWN:
			if (selected < numChoices - 1 && x != 9)
			{
				gotoXY(menuIndent, x); cout << "  ";
				x++;
				gotoXY(menuIndent, x); cout << "->";
				++selected;
				updated = true;
			}
			break;
		case KEY_ENTER:
			// We are done selecting the option.
			selecting = false;
			break;
		default:
			break;
		}
		if (updated)
		{
			if (selected == 0) SetConsoleTextAttribute(console, SELECTED_COLOR);
			if (firstGame) {
				gotoXY((menuIndent + 2), 7); cout << "Play Game";
			}
			else {
				gotoXY((menuIndent + 2), 7); cout << "Play Again";
			}
			SetConsoleTextAttribute(console, DEFAULT_COLOR);

			if (selected == 1) SetConsoleTextAttribute(console, SELECTED_COLOR);
			gotoXY((menuIndent + 2), 8); cout << "Quit Program";
			SetConsoleTextAttribute(console, DEFAULT_COLOR);

			if (selected == 2) SetConsoleTextAttribute(console, SELECTED_COLOR);
			gotoXY((menuIndent + 2), 9); cout << "Github Repo";
			SetConsoleTextAttribute(console, DEFAULT_COLOR);

			updated = false;
		}
	}
	return selected;
}

void playGame()
{
	system("cls");

	srand(time(0));
	firstGame = false;
	gameover = false;
	guesses = 0;
	int number = rand() % 10 + 1;
	int imanint;

	cout << "I have chosen a number between 1 and 10. Try to guess it in 3 tries.\n\n";

	while (!gameover)
	{
		cout << "Your Guess: ";
		cin >> imanint;
		guesses++;

		while (imanint != number && guesses < 3)
		{
			if (imanint > number)
			{
				cout << "Too high!\n\n";
			}
			else if (imanint < number)
			{
				cout << "Too low!\n\n";
			}

			guesses++;
			cout << "Your Guess: ";
			cin >> imanint;
		}

		if (imanint == number)
		{
			cout << "That's it! You got it in " << guesses << " guesses!\n";
			gameover = true;
		}

		if (guesses >= 3)
		{
			cout << "Sorry, but I was really thinking of " << number << ".\n";
			gameover = true;
		}
	}

	_getch(); // Wait for a key press before returning to the menu
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
