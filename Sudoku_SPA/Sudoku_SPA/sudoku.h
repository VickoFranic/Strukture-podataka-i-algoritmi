#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct {
	// struktura opisuje poziciju (npr. 9x9 matrica)
	int board[9][9];
	// struktura može imati dodatne èlanove da bi se olakšale neke provjere (npr. broj ispunjenih polja)
	int positionCnt;
} Position;

typedef struct {
	// struktura opisuje upisivanje jednog broja u sudoku
	int r;
	int c;
	int broj;
} Move;

// kreira novi sudoku od zadanih brojeva
Position* fromGrid(int grid[9][9]);

// ispisuje sudoku poziciju
void printPosition(Position *p);

int checkSudoku(Position* p);

// ispunjava moves sa legalnim potezima u poziciji p
// vraæa broj leganih poteza
int legalMoves(Position *p, Move moves[1000]);

int checkColumn(Position* p, int col);
int checkRow(Position* p, int row);
int checkGrid(Position* p, int row, int col, int num);

// upisuje potez m u poziciju p 
void makeMove(Position *p, Move m);

// poništava potez m u poziciji p 
void undoMove(Position *p, Move m);

// rekurzivna funkcija koja implementira DFS pretragu 
int solveSudoku(Position *p);

// sortiranje poteza (za dodatni dio zadatka)
void sortMoves(Move moves[1000], int n);

#endif