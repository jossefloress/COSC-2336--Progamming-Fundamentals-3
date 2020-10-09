/*
* COSC 2336.S01 – Program 5
* Jose Flores
*/
#include <fstream>
#include <iostream>

using namespace std;

#include "WCS_Pointer.h"
#include "WCS_String.h"
#include "Token.h"

#include "MathTree.h"

int main (int argc, char * argv [])
	{
	char		Cmd;
	char		Op;
	int			Num;
	Token		Toke;
	fstream		File;
	MathTree	MT;
	bool		Done;

	File.open (argv [1], ios_base::in);
	Done = false;
	do	{
		do {
			File >> Cmd;
		} while (isspace(Cmd));

		switch (Cmd)
			{
			case 'C':
						File >> Num;
						Toke.SetType (Token::ConstantToken);
						Toke.SetValue (Num);
						MT.InsertOperand (Toke);
						break;
			case 'V':
						File >> Num;
						Toke.SetType (Token::VariableToken);
						Toke.SetWhich (Num);
						MT.InsertOperand (Toke);
						break;
			case 'O':
						File >> Op;
						switch (Op)
							{
							case '+':
										Toke.SetType (Token::OperatorPlusToken);
										break;
							case '-':
										Toke.SetType (Token::OperatorMinusToken);
										break;
							case '*':
										Toke.SetType (Token::OperatorAsteriskToken);
										break;
							case '/':
										Toke.SetType (Token::OperatorSlashToken);
							}
						File >> Num;
						Toke.SetPrecedence ((Operator::Precedence) Num);
						MT.InsertBinaryOperator (Toke);
						break;
			case 'v':
						File >> Num;		// read number of variable
						Toke.SetType (Token::VariableToken);
						Toke.SetWhich (Num);
						File >> Num;		// value to be placed into variable
						Toke.SetValue (Num);
						break;
			case 'E':
						cout << "Answer is " << MT.Evaluate () << endl;
						break;
			case 'D':
						MT.DeleteTree ();
						break;
			case 'X':
						Done = true;
			}
		} while (!Done);

		system("pause");
		return 0;
	}
