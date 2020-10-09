/******************
	RAFile
*******************/

#pragma warning (disable:4996)

#include <iostream>

using namespace std;

#include <stdlib.h>

#include "RAFile.h"


int main ()
{
	RAFile		DB1;
	WCS_String inputCommand, inputStr, gotRqstedStr;
	size_t inputIndex;
	bool done = false;
	char command;
	


	WCS_String myTxt("MyFile.txt");

	DB1.Open(myTxt);
	myTxt = "Hello";
	DB1.Insert(0, myTxt);
	myTxt = "World";
	DB1.Insert(1, myTxt);


	cout << "		Valid Commands:\n"
		<< "________________________________________________________________\n"
		<< " G 	--	Gets and prints a string at a specified index.\n"
		<< " R 	--	Replaces a string on the requested index.\n"
		<< " I	--	Inserts a string into a specified index.\n"
		<< " P	--	Prints all data from the database.\n"
		<< " X	--	Ends the program.\n";

	while (!done)
	{
		cout << "\nPlease enter a command:\t";
		cin >> inputCommand;
		command = inputCommand[0];

		if (command == 'G' || command == 'g')
		{
			cout << "Please enter an integer for the index:  ";
			cin >> inputIndex;
			cin.ignore();
			DB1.Get(inputIndex, gotRqstedStr);
			cout << "This data was found: " << gotRqstedStr << endl << endl;

		}

		else if (command == 'R' || command == 'r')
		{

			cout << "Please enter an integer for the index:  ";
			cin >> inputIndex;
			cin.ignore();
			cout << "Please enter a string:  ";
			cin >> inputStr;
			DB1.Replace(inputIndex, inputStr);
		}

		else if (command == 'I' || command == 'i')
		{
			cout << "Please enter an integer for the index:  ";
			cin >> inputIndex;
			cin.ignore();
			cout << "Please enter a string:  ";
			cin >> inputStr;
			DB1.Insert(inputIndex, inputStr);
		}

		else if (command == 'X' || command == 'x')
		{
			done = true;
			cout << "\nAll the records from the database:\n";
			cout << DB1.GetAllData() << endl;
			DB1.Close();
		}

		else if (command == 'P' || command == 'p')
			cout << DB1.GetAllData() << endl;
		
		else
			cout << "Invalid command, please enter a valid command.\n\n";


	}



	system ("pause");
	return 0;
	}

