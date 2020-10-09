#ifndef MATH_TREE_H
#define MATH_TREE_H

#include "WCS_Pointer.h"

#include "Token.h"

class MathTree
	{
	private:
		struct Node: public Token
			{
			WCS_Pointer <Node>		pParent;
			WCS_Pointer <Node>		pLeft;
			WCS_Pointer <Node>		pRight;
			bool					LeftSideDone;

			Node (const Token &);
			};

	public:
								MathTree				();
								~MathTree				();
		void					DeleteTree				();
		Variable::ValueType		Evaluate				();
		bool					InsertOperand			(const Token &);
		bool					InsertBinaryOperator	(const Token &);
		bool					InsertUnaryOperator		(const Token &);

		enum Exceptions			{DivideByZero};

	private:
								MathTree				(const MathTree &);
		MathTree &				operator =				(const MathTree &);
		WCS_Pointer <Node>		GetLeftMostOperator		(const WCS_Pointer <Node> &);
		WCS_Pointer <Node>		pRoot;
		WCS_Pointer <Node>		pLastOperator;
	};

#endif
