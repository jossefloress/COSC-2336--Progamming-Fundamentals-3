#pragma warning (disable:4996)

//	Lab 4
//	By: Jose Flores

#include <stdlib.h>

#include "Token.h"
#include "WCS_String.h"

int main (int argc, char * argv [])
	{
	WCS_String Temp;
	Token Toke;

//	cout << "argv [0] is " << argv [0] << endl;
//	cout << "argv [1] is " << argv [1] << endl;
//	return 0;
	if (argc < 2)
			{
			cout << "Error, not enough command line arguments" << endl;
			return 0;
			}
		else
			Temp = argv [1];
	Token::OpenFile (Temp);
	do	{
		Toke.Build ();
		switch (Toke.GetType ())
			{
			case Token::KeywordEvalToken:
				cout << "Found Keyword EVAL" << endl;
				break;
			case Token::KeywordValueToken:
				cout << "Found Keyword Value" << endl;
				break;
			case Token::KeywordExpToken:
				cout << "Found Keyword EXP" << endl;
				break;
			case Token::VariableToken:
				cout << "Found Variable" << " " << Toke.GetWhich() << endl;
				break;
			case Token::ConstantToken:
				cout << "Found a Constant Token" << endl;
				break;
			case Token::EndOfInputToken:
				cout << "End Of Input" << endl;
				break;
				
				//Operators
			case Token::OperatorPlusToken:
				cout << "Found a + Token" << endl;
				break;
			case Token::OperatorMinusToken:
				cout << "Found a - Token" << endl;
				break;
			case Token::OperatorAsteriskToken:
				cout << "Found a * Token" << endl;
				break;
			case Token::OperatorSlashToken:
				cout << "Found a / Token" << endl;
				break;

				// Symbols
			case Token::SymbolOpenParenToken:
				cout << "Found a ( Token" << endl;
				break;
			case Token::SymbolCloseParenToken:
				cout << "Found a ) Token" << endl;
				break;
			case Token::SymbolSemiColonToken:
				cout << "Found a ; Token" << endl;
				break;

			default:
				cout << "Should not get here" << endl;
			}
		} while (Toke.GetType () != Token::EndOfInputToken);
	Token::CloseFile ();

	system ("pause");
	return 0;
	}
