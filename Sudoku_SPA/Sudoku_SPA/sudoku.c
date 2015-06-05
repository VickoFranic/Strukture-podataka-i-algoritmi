#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

static int posCnt = 0;

// kreira novi sudoku od zadanih brojeva
Position* fromGrid(int grid[9][9]) {
	int i,j;
	Position* sudoku =(Position*)malloc(sizeof(Position));

	for(i=0; i < 9; i++) {
		for(j=0; j < 9; j++)
			sudoku->board[i][j] = grid[i][j];
	}
	sudoku->positionCnt = 0;

	return sudoku;
}

void printPosition(Position *p) {
	int i,j;

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
			printf("%d ", p->board[i][j]);
		if (j == 9)
			printf("\n");
	}
	printf("\nBroj pozicija: %d\n", posCnt);
	printf("\n");
}

int checkColumn(Position* p, int col, int num) {
	int row = 0;

	for (row; row < 9; row++) {
		if (p->board[row][col] == num)
			return 0;
	}
	return 1;
}

int checkRow(Position* p, int row, int num) {
	int col = 0;

	for (col; col < 9; col++) {
		if (p->board[row][col] == num)
			return 0;
	}
	return 1;
}

int checkGrid(Position* p, int row, int col, int num) {
	int i, j;

	int sectorR = (row / 3) * 3;
	int sectorC = (col / 3) * 3;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (p->board[sectorR + i][sectorC + j] == num)
				return 0;
		}
	}
	return 1;
}

// ispunjava moves sa legalnim potezima u poziciji p
// vra�a broj leganih poteza
int legalMoves(Position *p, Move moves[1000]) {
	int r, c, broj, test;
	int cnt = 0;

	for (r = 0; r < 9; r++) {
		for (c = 0; c < 9; c++) {
			if (p->board[r][c] != 0)
				continue;
			else {
				for (test = 1; test < 10; test++)
					if (checkColumn(p, c, test) && checkRow(p, r, test) && checkGrid(p, r, c, test)) {
						moves[cnt].broj = test;
						moves[cnt].r = r;
						moves[cnt].c = c;
						p->positionCnt++;
						cnt++;
					}
				}
			}
		}

	return cnt;
}

void makeMove(Position *p, Move m) {
		p->board[m.r][m.c] = m.broj;

		p->positionCnt++;
}

void undoMove(Position *p, Move m) {
	p->board[m.r][m.c] = 0;

	p->positionCnt--;
}
// provjeri da li je rjesen
int checkSudoku(Position* p) {
	int r, c;
	int cnt = 1;

	for (r = 0; r < 9; r++) {
		for (c = 0; c < 9; c++) {
			if (p->board[r][c] == 0)
				return 0;
		}
	}
	return 1;
}

// rekurzivna funkcija koja implementira DFS pretragu 
int solveSudoku(Position *p) {
	int i, n;
	Move moves[1000];

	posCnt++;

	if (checkSudoku(p))
		return 1;

	n = legalMoves(p, moves);	// vrati broj legalnih poteza

	for (i=0; i < n; i++) {
		makeMove(p, moves[i]);
		if (solveSudoku(p))
			return 1;
		undoMove(p, moves[i]);
	}
	return 0;
}

void sortMoves(Move moves[1000], int n) {

}