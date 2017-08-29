// -----------------------------------------------------------
// NAME : Leopold Eckert                     User ID: lweckert
// DUE DATE : 12/12/2014
// PROGRAM ASSIGNMENT # 6
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
//    This file implements the main thread that is started
//    when the process starts.
// -----------------------------------------------------------

//#include "ThreadClass.h"
//#include "thread.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int l, m, u, v, i, j, input;
	//Semaphore output = new Semaphore("output", 1);
	
	scanf("%d", &l);
	scanf("%d", &m);
	int matrixA[l][m+1];
	for (i = 0; i < l; i++) {
		for (j = 0; j < m; j++) {
			scanf("%d", &input);
			matrixA[j][i] = input;
		}
		matrixA[i][m] = -1;
	}
	scanf("%d", &u);
	scanf("%d", &v);
	int matrixB[v][u+1];
	for (i = 0; i < v; i++) {
		for (j = 0; j < u; j++) {
			scanf("%d", &input);
			matrixB[i][j] = input;
		}
		matrixB[i][u] = -1;
	}
	if (m != u) {
		printf("Invalid input, the matrices cannot be multiplied.\n");
	}
	int matrixC[l][v];
	/*Row *rows[l];
	SynOneToOneChannel *downChannels[l+2][v];
	SynOneToOneChannel *rightChannels[l][v+2];
	Column *columns[v];
	Multiplier *multipliers[l][v];
	for (i = 0; i <= l; i++) {
		for (j = 0; j < v; j++) {
			downChannels[i][j] = new SynOneToOneChannel("", i + (j * (v + 1)) + 1, i + ((j + 1) * (v + 1)) + 1);
			downChannels[l+1][j] = NULL;
		}
	}
	for (i = 0; i < l; i++) {
		for (j = 0; j <= v; j++) {
			rightChannels[i][j] = new SynOneToOneChannel("", v + i + j + 1, v + i + j + 2);
		}
		rightChannels[i][v+1] = NULL;
	}
	for (i = 0; i < v; i++) {
		columns[i] = new Column(i + 1, i + 1, matrixB[i], downChannels[0][i], output);
		columns[i]->Begin();
	}
	for (i = 0; i < l; i++) {
		rows[i] = new Row(i + 1, i * (v + 1), matrixA[i], rightChannels[i][0], output);
		rows[i]->Begin();
	}
	for (i = 0; i < l; i++) {
		for (j = 0; j < v; j++) {
			multipliers[i][j] = new Multiplier(i, j, (i * (v + 1)) + j + 1,
					rightChannels[i][j+1], downChannels[i+1][j], downChannels[i][j],
					rightChannels[i][j], output, matrixC);
			multipliers[i][j]->Begin();
		}
	}
	multipliers[l-1][v-1]->Join();*/
	cout << "*** From main ***\n";
	printf("Matrix A: %d rows and %d columns\n", l, m);
	for (i = 0; i < l; i++) {
		for (j = 0; j < m; j++) {
			printf("%d ", matrixA[j][i]);
		}
		printf("\n");
	}
	printf("Matrix B: %d rows and %d columns\n", u, v);
	for (i = 0; i < u; i++) {
		for (j = 0; j < v; j++) {
			printf("%d ", matrixA[i][j]);
		}
		printf("\n");
	}
	
}