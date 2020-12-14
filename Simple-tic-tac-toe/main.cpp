#include<iostream>
#include <stdlib.h> 
#include <time.h>  
const int MAX_SIZE = 9;
unsigned readSize() {
	unsigned n;
	do {
		std::cout << "Enter grid size:";
		std::cin >> n;
	} while (n < 3 || n>9);
	return n;
}
void setMatrix(char arr[][MAX_SIZE], unsigned size) {
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned col = 0; col < size; col++)
		{
			arr[row][col] = ' ';
		}
	}
}
void showStatus(char arr[][MAX_SIZE], unsigned size) {
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned col = 0; col < size; col++)
		{
			std::cout << "[" << arr[row][col] << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
bool checkColumn(char arr[][MAX_SIZE], unsigned size, unsigned col, char symbol) {
	for (unsigned i = 0; i < size; i++)
	{
		if (arr[i][col] != symbol)return false;
	}
	return true;
}
bool checkRow(char arr[][MAX_SIZE], unsigned size, unsigned row, char symbol) {
	for (unsigned i = 0; i < size; i++)
	{
		if (arr[row][i] != symbol)return false;
	}
	return true;
}
bool isWonByColumnOrRow(char arr[][MAX_SIZE], unsigned size) {
	for (unsigned i = 0; i < size; i++)
	{
		if (checkColumn(arr, size, i, 'X') == true || checkColumn(arr, size, i, 'O') == true) {
			return true;
		}
		if (checkRow(arr, size, i, 'X') == true || checkRow(arr, size, i, 'O') == true) {
			return true;
		}
	}
	return false;
}
bool checkMainDiagonal(char arr[][MAX_SIZE], unsigned size, char symbol) {
	for (unsigned row = 0; row < size; row++)
	{
		if (arr[row][row] != symbol)return false;
	}
	return true;
}
bool checkSecondaryDiagonal(char arr[][MAX_SIZE], unsigned size, char symbol) {
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned col = 0; col < size; col++)
		{
			if ((row + col == size - 1) && (arr[row][col] != symbol))return false;
		}
	}
	return true;
}
bool isWonByDiagonals(char arr[][MAX_SIZE], unsigned size) {
	for (unsigned i = 0; i < size; i++)
	{
		if (checkMainDiagonal(arr, size, 'X') == true || checkMainDiagonal(arr, size, 'O') == true || checkSecondaryDiagonal(arr, size, 'X') == true || checkSecondaryDiagonal(arr, size, 'O') == true) {
			return true;
		}
	}
	return false;
}
bool isEqual(char arr[][MAX_SIZE], unsigned size) {
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned col = 0; col < size; col++)
		{
			if (arr[row][col] == ' ')return false;
		}
	}
	return true;
}
bool didPlayerWin(char arr[][MAX_SIZE], unsigned size) {
	if (isWonByColumnOrRow(arr, size)) {
		return true;
	}
	else if (isWonByDiagonals(arr, size)) {
		return true;
	}
	return false;
}
bool isEmptyPlace(char arr[][MAX_SIZE], int x, int y) {
	if (arr[x][y] != ' ')
	{
		return true;
	}
	return false;
}
bool areValidCoordinates(int x, int y) {
	return (x >= 0 && x <= 9) && (y >= 0 && y <= 9);
}
bool isValidTurn(char arr[][MAX_SIZE], int x, int y) {
	if (areValidCoordinates(x, y) && isEmptyPlace(arr, x, y))return true;
	return false;
}
void computerTurn(char arr[][MAX_SIZE], unsigned size, char symbol) {
	int x;
	int y;
	do {
		srand(time(NULL));
		x = rand() % size + 0;
		y = rand() % size + 0;
	} while (isValidTurn(arr, x, y));
	arr[x][y] = symbol;
}
void PvP(char arr[][MAX_SIZE], unsigned size) {
	bool firstPlayerTurn = true;
	int x;
	int y;
	while (true) {
		if (firstPlayerTurn == true) {
			do {
				std::cout << "It's Player 1 turn:";
				std::cin >> x >> y;
				--x;
				--y;
			} while (isValidTurn(arr, x, y));
			arr[x][y] = 'X';
			showStatus(arr, size);
			if (isEqual(arr, size) && !didPlayerWin(arr, size)) {
				std::cout << "Nobody wins!" << std::endl;
				break;
			}
			else if (didPlayerWin(arr, size)) {
				std::cout << "Player 1 won!" << std::endl;
				break;
			}
		}
		else {
			do {
				std::cout << "It's Player 2 turn:";
				std::cin >> x >> y;
				--x;
				--y;
			} while (isValidTurn(arr, x, y));
			arr[x][y] = 'O';
			showStatus(arr, size);
			if (isEqual(arr, size) && !didPlayerWin(arr, size)) {
				std::cout << "Nobody wins!" << std::endl;
				break;
			}
			else if (didPlayerWin(arr, size)) {
				std::cout << "Player 2 won!" << std::endl;
				break;
			}
		}
		firstPlayerTurn = !firstPlayerTurn;
	}
}
void PvC(char arr[][MAX_SIZE], unsigned size) {
	bool isPlayerTurn = true;
	int x;
	int y;
	while (true) {
		if (isPlayerTurn == true) {
			do {
				std::cout << "It's Player 1 turn:";
				std::cin >> x >> y;
				--x;
				--y;
			} while (isValidTurn(arr, x, y));
			arr[x][y] = 'X';
			showStatus(arr, size);
			if (isEqual(arr, size) && !didPlayerWin(arr, size)) {
				std::cout << "Nobody wins!" << std::endl;
				break;
			}
			else if (didPlayerWin(arr, size)) {
				std::cout << "Player won!" << std::endl;
				break;
			}
		}
		else {
			std::cout << "It's computer turn:" << std::endl;
			computerTurn(arr, size, 'O');
			showStatus(arr, size);
			if (isEqual(arr, size) && !didPlayerWin(arr, size)) {
				std::cout << "Nobody wins!" << std::endl;
				break;
			}
			else if (didPlayerWin(arr, size)) {
				std::cout << "Computer won!" << std::endl;
				break;
			}
		}
		isPlayerTurn = !isPlayerTurn;
	}
}
void CvC(char arr[][MAX_SIZE], unsigned size) {
	bool firstComputerTurn = true;
	int x;
	int y;
	while (true) {
		if (firstComputerTurn) {
			std::cout << "It's Computer 1 turn:" << std::endl;
			computerTurn(arr, size, 'X');
			showStatus(arr, size);
			if (isEqual(arr, size) && !didPlayerWin(arr, size)) {
				std::cout << "Nobody wins!" << std::endl;
				break;
			}
			else if (didPlayerWin(arr, size)) {
				std::cout << "Computer 1 won!" << std::endl;
				break;
			}
		}
		else {
			std::cout << "It's Computer 2 turn:" << std::endl;
			computerTurn(arr, size, 'O');
			showStatus(arr, size);
			if (isEqual(arr, size) && !didPlayerWin(arr, size)) {
				std::cout << "Nobody wins!" << std::endl;
				break;
			}
			else if (didPlayerWin(arr, size)) {
				std::cout << "Computer 2 won!" << std::endl;
				break;
			}
		}
		firstComputerTurn = !firstComputerTurn;
	}
}
void startGame(char arr[][MAX_SIZE], unsigned size, int mode) {
	showStatus(arr, size);
	if (mode == 1) {
		PvP(arr, size);
	}
	else if (mode == 2) {
		PvC(arr, size);
	}
	else if (mode == 3) {
		CvC(arr, size);
	}
}
int main() {
	char matrix[MAX_SIZE][MAX_SIZE];
	unsigned size;
	int mode;
	size = readSize();
	setMatrix(matrix, size);
	std::cout << "Choose game mode (1 - PvP, 2 - PvC, 3 - CvC):";
	std::cin >> mode;
	startGame(matrix, size, mode);
	return 0;
}