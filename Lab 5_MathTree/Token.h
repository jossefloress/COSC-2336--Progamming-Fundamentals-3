#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <fstream>

using namespace std;

#include "WCS_Pointer.h"
#include "WCS_String.h"
#include "Operator.h"
#include "Variable.h"

class Token: public RefCount
	{
	public:
			typedef unsigned char			UChar;
			enum	Variables				{
											NumVariables = 100
											};
			enum	Exception				{
											TokenFileNotOpen
											};
			enum	TokenType				{
											EndOfInputToken,
											UnknownToken,
											VariableToken,
											ConstantToken,
											KeywordEvalToken,
											KeywordExpToken,
											KeywordValueToken,
											OperatorPlusToken,
											OperatorMinusToken,
											OperatorAsteriskToken,
											OperatorSlashToken,
											SymbolOpenParenToken,
											SymbolCloseParenToken,
											SymbolSemiColonToken,

											NumTokens
											};

											Token			();
											Token			(const Token &);
											Token			(const WCS_Pointer<Token> &);
											Token			(TokenType, int);
											~Token			();
					Token &					Build			();
			static	void					CloseFile		();
					Operator::Precedence	GetPrecedence	() const;
					TokenType				GetType			() const;
					Variable::ValueType		GetValue		() const;
					int						GetWhich		() const;
			static	void					OpenFile		(const WCS_String &);
			static	void					OpenKeyboard	();
					void					SetValue		(Variable::ValueType);
					Token &					operator=		(const Token &);

					//The next 3 functions were moved from Private to Public
					void					SetPrecedence(Operator::Precedence);
					void					SetType(TokenType);
					void					SetWhich(int);
	private:
			enum	InputType				{
											InputUnknown,
											InputA,
											InputE,
											InputL,
											InputP,
											InputU,
											InputV,
											InputX,
											Input0,
											Input1,
											Input2,
											Input3,
											Input4,
											Input5,
											Input6,
											Input7,
											Input8,
											Input9,
											InputPlus,
											InputMinus,
											InputAsterisk,
											InputSlash,
											InputOpenParen,
											InputCloseParen,
											InputSemiColon,
											InputSpace,
											EndOfFile,

											NumInputs
											};
			enum	TokenState				{
											TokenComplete = -1,
											StartGettingToken,
											AfterE,
											AfterV,
											AfterEV,
											AfterEVA,
											AfterEX,
											AfterVA,
											AfterVAL,
											AfterVALU,
											AfterVDigit,
											AfterDigit,

											NumStates
											};
			typedef int						State;
			typedef TokenState				(*TokenFunc)	(Token &);

					InputType				GetInputChar	();
					void					Init			(TokenType, int);
			static	void					PutBackLastChar	();
					//The next 3 functions were moved from Private to Public
					//void					SetPrecedence	(Operator::Precedence);
					//void					SetType			(TokenType);
					//void					SetWhich		(int);
			static	int						ConvertLastChar	();

				//	***** State Functions *****

			static	TokenState				InvalidCharacter			(Token &);
			static	TokenState				NotYetImplemented			(Token &);
			static	TokenState				GotE						(Token &);
			static	TokenState				GotV						(Token &);
			static	TokenState				GotVAfterE					(Token &);
			static	TokenState				GotAAfterEV					(Token &);
			static	TokenState				GotLAfterEVA				(Token &);
			static	TokenState				GotXAfterE					(Token &);
			static	TokenState				GotPAfterEX					(Token &);
			static	TokenState				GotAAfterV					(Token &);
			static	TokenState				GotLAfterVA					(Token &);
			static	TokenState				GotUAfterVAL				(Token &);
			static	TokenState				GotEAfterVALU				(Token &);
			static	TokenState				GotPlus						(Token &);
			static	TokenState				GotMinus					(Token &);
			static	TokenState				GotAsterisk					(Token &);
			static	TokenState				GotSlash					(Token &);
			static	TokenState				GotOpenParen				(Token &);
			static	TokenState				GotCloseParen				(Token &);
			static	TokenState				GotSemiColon				(Token &);
			static	TokenState				GotSpace					(Token &);
			static	TokenState				GotEOF						(Token &);
			static	TokenState				GotDigitAfterV				(Token &);
			static	TokenState				GotDigitAfterVDigit			(Token &);
			static	TokenState				GotFirstDigit				(Token &);
			static	TokenState				GotFollowingDigit			(Token &);
			static	TokenState				GotNonDigitFollowingDigit	(Token &);
			static	TokenState				GotUnExpectedEOF			(Token &);

			static	InputType				InputTable		[];
			static	UChar					LastChar;
			static	ifstream				SourceFile;
			static	TokenFunc				StateFunction	[];
			static	int						StateTable		[NumInputs] [NumStates];
			static	Variable				VariableArray	[NumVariables];

// ***** Data members *****

					TokenType				Type;
					union
						{
						int						Which;
						Operator::Precedence	Precedence;
						Variable::ValueType		Value;
						};
	};

inline Token::Token ()
	{
	Init (EndOfInputToken, 0);
	}

inline Token::Token (const Token & T)
	{
	Init (T.Type, T.Which);
	}

inline Token::Token (const WCS_Pointer<Token> & T)
	{
	Init ((*T).Type, (*T).Which);
	}

inline Token::Token (TokenType NewType, int NewValue)
	{
	Init (NewType, NewValue);
	}

inline Token::~Token ()
	{
	}

inline void Token::CloseFile ()
	{
	SourceFile.close ();
	}

inline int Token::ConvertLastChar ()
	{
	return LastChar - '0';
	}

inline Operator::Precedence Token::GetPrecedence () const
	{
	return Precedence;
	}

inline Token::TokenType Token::GetType () const
	{
	return Type;
	}

inline Variable::ValueType Token::GetValue () const
	{
	return (Type == VariableToken) ? VariableArray [Which].GetValue () : Value;
	}

inline int Token::GetWhich () const
	{
	return Which;
	}

inline void Token::OpenFile (const WCS_String & FileName)
	{
	SourceFile.open ((const char *) FileName);
	}

inline void Token::OpenKeyboard ()
	{
//	SourceFile.attach (0);  // no longer available under new release of iostream
	}

inline void Token::SetValue (Variable::ValueType V)
	{
	if (Type == VariableToken)
			VariableArray [Which].SetValue (V);
		else
			Value = V;
	}

inline Token & Token::operator= (const Token & T)
	{
	Init (T.Type, T.Which);
	return *this;
	}

inline Token::InputType Token::GetInputChar ()
	{
	return InputTable [LastChar = (UChar) SourceFile.get ()];
	}

inline void Token::Init (TokenType T, int V)
	{
	Type = T;
	Value = V;
	}

inline void Token::PutBackLastChar ()
	{
	SourceFile.putback (LastChar);
	}

inline void Token::SetPrecedence (Operator::Precedence P)
	{
	Precedence = P;
	}

inline void Token::SetType (TokenType T)
	{
	Type = T;
	}

inline void Token::SetWhich (int W)
	{
	Which = W;
	}

#endif
