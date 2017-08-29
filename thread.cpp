// -----------------------------------------------------------
// NAME : Leopold Eckert                     User ID: lweckert
// DUE DATE : 12/12/2014
// PROGRAM ASSIGNMENT # 6
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
//    This file implements all the threads in program 6.
// -----------------------------------------------------------

#include "ThreadClass.h"
#include "thread.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

// ----------------------------------------------------------- 
// FUNCTION  Row::Row :                          
//     Creates a new Row thread.
// PARAMETER USAGE :
//    rid: the number of the row that is being passed in
//    id: the id of the thread
//    rd: the data that the thread will pass
//    r: the channel to communicate with the thread to the right
//    o: Semaphore to protect output
// FUNCTION CALLED :
//    
// -----------------------------------------------------------

Row::Row(int rid, int id, int *rd, SynOneToOneChannel *r, Semaphore *o) {
	row = rid;
	rowData = rd;
	UserDefinedThreadID = id;
	right = r;
	output = o;
}

// ----------------------------------------------------------- 
// FUNCTION  Row::ThreadFunc :                          
//     Runs a Row thread
// PARAMETER USAGE :
//    
// FUNCTION CALLED :
//    sprintf
//    Semaphore::Wait
//    Semaphore::Signal
//    SynOneToOneChannel::Send
// -----------------------------------------------------------

void Row::ThreadFunc() {
	Thread::ThreadFunc();
	int index = 0;
	int data;
	sprintf(buffer, "Row thread r[%d] started\n", row);
	output->Wait();
	cout << buffer;
	output->Signal();
	while(true) {
		data = rowData[index];
		if (data == -1) {
			break;
		}
		else {
			down->Send(&data, sizeof(int));
			sprintf(buffer, "Row thread r[%d] sent %d to P[%d,1]\n", row, data, row);
			output->Wait();
			cout << buffer;
			output->Signal();
			index += 1;
		}
	}
	down->Send(&data, sizeof(int));
	sprintf(buffer, "Row thread r[%d] sent EOD to P[%d,1] and terminated\n", row, row);
	output->Wait();
	cout << buffer;
	output->Signal();
	Exit();
}

// ----------------------------------------------------------- 
// FUNCTION  Column::Column :                          
//     Creates a new Column thread.
// PARAMETER USAGE :
//    cid: the number of the column that is being passed in
//    id: the id of the thread
//    cd: the data that the thread will pass
//    d: the channel to communicate with the down thread
//    o: semaphore to protect output
// FUNCTION CALLED :
//    
// -----------------------------------------------------------

Column::Column(int cid, int id, int *cd, SynOneToOneChannel *d, Semaphore *o) {
	column = cid;
	columnData = cd;
	UserDefinedThreadID = id;
	down = d;
	output = o;
}

// ----------------------------------------------------------- 
// FUNCTION  Column::ThreadFunc :                          
//     Runs a Column thread
// PARAMETER USAGE :
//    
// FUNCTION CALLED :
//    sprintf
//    Semaphore::Wait
//    Semaphore::Signal
//    SynOneToOneChannel::Send
// -----------------------------------------------------------

void Column::ThreadFunc() {
	Thread::ThreadFunc();
	int index = 0;
	int data;
	sprintf(buffer, "   Column thread c[%d] started\n", column);
	output->Wait();
	cout << buffer;
	output->Signal();
	while(true) {
		data = columnData[index];
		if (data == -1) {
			break;
		}
		else {
			down->Send(&data, sizeof(int));
			sprintf(buffer, "   Column thread c[%d] sent %d to P[1,%d]\n", column, data, column);
			output->Wait();
			cout << buffer;
			output->Signal();
			index += 1;
		}
	}
	down->Send(&data, sizeof(int));
	sprintf(buffer, "   Column thread c[%d] sent EOD to P[1,%d] and terminated\n", column, column);
	output->Wait();
	cout << buffer;
	output->Signal();
	Exit();
}

// ----------------------------------------------------------- 
// FUNCTION  Multiplier::Multiplier :                          
//     Creates a new Multiplier thread.
// PARAMETER USAGE :
//    x: the horizontal position of the thread
//    y: the vertical position of the thread
//    id: the thread's ID
//    r: the channel to communicate with the thread to the right
//    d: the channel to communicate with the thread below
//    u: the channel to communicate with the thread above
//    l: the channel to communicate with the thread to the left
//    o: semaphore to protect output
//    m: matrix to write to
// FUNCTION CALLED :
//    
// -----------------------------------------------------------

Multiplier::Multiplier(int x, int y, int id, SynOneToOneChannel *r, SynOneToOneChannel *d,
		SynOneToOneChannel *u, SynOneToOneChannel *l, Semaphore *o, int** m) {
	xPos = x;
	yPos = y;
	UserDefinedThreadID = id;
	right = r;
	down = d;
	up = u;
	left = l;
	output = o;
	number = 0;
	matrix = m;
}

// ----------------------------------------------------------- 
// FUNCTION  Multiplier::ThreadFunc :                          
//     Runs a Multiplier thread
// PARAMETER USAGE :
//    
// FUNCTION CALLED :
//    sprintf
//    Semaphore::Wait
//    Semaphore::Signal
//    SynOneToOneChannel::Recieve
//    SynOneToOneChannel::Send
// -----------------------------------------------------------

void Multiplier::ThreadFunc() {
	Thread::ThreadFunc();
	buffer char[256];
	int tmpNum, rowNumber, columnNumber;
	Thread_t self = GetID();
	sprintf(buffer, "      Thread P[%d,%d] started\n", yPos, xPos);
	output->Wait();
	cout << buffer;
	output->Signal();
	while(true) {
		up->Recieve(&columnNumber, sizeof(int));
		left->Recieve(&rowNumber, sizeof(int));
		if (columnNumber == -1 && rowNumber == -1) {
			break;
		}
		sprintf(buffer, "      Thread P[%d,%d] received %d from above and %d from left\n",
				yPos, xPos, columnNumber, rowNumber);
		output->Wait();
		cout << buffer;
		output->Signal();
		tmpNum = columnNumber * rowNumber;
		number += tmpNum;
		if (down != NULL) {
			down->Send(&columnNumber, sizeof(int));
		}
		if (right != NULL) {
			right->Send(&rowNumber, sizeof(int));
		}
		sprintf(buffer, "      Thread P[%d,%d] sent %d to below and %d to right\n",
				yPos, xPos, columnNumber, rowNumber);
		output->Wait();
		cout << buffer;
		output->Signal();
	}
	if (down != NULL) {
		down->Send(&columnNumber, sizeOf(int));
	}
	if (right != NULL) {
		right->Send(&rowNumber, sizeOf(int));
	}
	matrix[xPos][yPos] = number;
	sprintf(buffer, "      Thread P[%d,%d] received EOD, saved result %d and terminated\n",
			yPos, xPos, number);
	output->Wait();
	cout << buffer;
	output->Signal();
	Exit();
}