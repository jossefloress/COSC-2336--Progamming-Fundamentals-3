/******************
	
*******************/

#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>

//#include "UB_Stack.h"
#include "UB_Queue.h"
#include <iostream>
#include <string>
using namespace std;

void funcQ(UB_Queue <string>&);
void funcD(UB_Queue <string>&);

int main ()
	{
	bool done = false;
	string userInput;
	char enteredComnd;
	string first;

	UB_Queue <string>	UBQ;
	
	cout << "Commands:\n"
		<< "Q - Add a string to the queue\n"
		<< "D - Removes & prints first item on queue\n"
		<< "X - Terminate program\n\n";

	while (!done)
	{
		cout << "Enter a command: ";
		getline(std::cin,userInput);
		enteredComnd = userInput[0];

		
		if (enteredComnd == 'Q' || enteredComnd == 'q')
		{
			funcQ(UBQ);
		}

		else if (enteredComnd == 'D' || enteredComnd == 'd')
		{
			funcD(UBQ);
		}

		else if (enteredComnd == 'X' || enteredComnd == 'x')
		{
			done = true;
			if (UBQ.Size() > 0)
			{
				cout << "\nAll the remaining items on the queue:\n"
					<< UBQ.printAll() << endl
					<< endl;
			}
		}

		else
		{
			cout << "\nInvalid Entry.\n"
				<< "Enter one of the 3 commands.\n\n";
		}

	}
	

	system ("pause");
	return 0;
	}

void funcQ(UB_Queue <string>& UBQ)
{
	string enteredStr;
	cout << "Enter the string you would like to add to the queue: \n";
	getline(cin,enteredStr);
	UBQ.Queue(enteredStr);
	cout << endl;
}


void funcD(UB_Queue <string>& UBQ)
{
	string popped;

	if (UBQ.Size() == 0)
	{
		cout << "Nothing was removed because Queue is empty.\n\n";
	}

	else
	{
		UBQ.DeQueue(popped);
		cout << "\nThis was removed from the queue: " << popped << endl << endl;
	}

}