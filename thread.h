// -----------------------------------------------------------
// NAME : Leopold Eckert                     User ID: lweckert
// DUE DATE : 12/12/2014
// PROGRAM ASSIGNMENT # 6
// FILE NAME : thread.h
// PROGRAM PURPOSE :
//    This file contains the definitions of all the threads
//    in program 6.
// -----------------------------------------------------------

#include "ThreadClass.h"

using namespace std;

class Row : public Thread {
	public:
		Row(int rid, int id, int *rd, SynOneToOneChannel *r, Semaphore *o);
	private:
		void ThreadFunc();
		int row;
		int *rowData;
		SynOneToOneChannel *right;
		Semaphore *output;
};

class Column : public Thread {
	public:
		Column(int cid, int id, int *cd, SynOneToOneChannel *d, Semaphore *o);
	private:
		void ThreadFunc();
		int columnId;
		int *columnData;
		SynOneToOneChannel *down;
		Semaphore *output;
};

class Multiplier : public Thread {
	public:
		Multiplier(int x, int y, int id, SynOneToOneChannel *r, SynOneToOneChannel *d,
				SynOneToOneChannel *u, SynOneToOneChannel *l, Semaphore *o, int **m);
	private:
		void ThreadFunc();
		int xPos;
		int yPos;
		int number;
		int **matrix;
		SynOneToOneChannel *up;
		SynOneToOneChannel *left;
		SynOneToOneChannel *right;
		SynOneToOneChannel *down;
		Semaphore *output;
};