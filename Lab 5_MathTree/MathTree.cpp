#include "MathTree.h"

MathTree::Node::Node (const Token & Toke): Token (Toke)
	{
	}

MathTree::MathTree ()
	{
	}

MathTree::~MathTree ()
	{
	DeleteTree ();
	}

void MathTree::DeleteTree ()
	{
	// need to go through and delete all nodes in the tree
	// Left as an excercise for the student
	bool Deleted = false;
	WCS_Pointer<Node> StartHere = pRoot;
	WCS_Pointer<Node> DeletePtr   = pRoot;

	while (pRoot.Exists())
	{		
		while (Deleted == false)
		{
			cout << "Deletion has begun: " << endl;
			DeletePtr = GetLeftMostOperator(StartHere);
				
			while (DeletePtr != pRoot)
			{
				string deleted = "			Successfully deleted the: ";

				if ((*DeletePtr).pLeft.Exists())
					(*DeletePtr).pLeft.SetToNull();
				deleted += "left most node";


				if ((*(*DeletePtr).pRight).pLeft.Exists() && (*DeletePtr).pRight.Exists())
					DeletePtr = (*(*DeletePtr).pRight).pLeft;


				if ((*DeletePtr).pLeft.Exists())
					(*DeletePtr).pLeft.SetToNull();
				deleted += ", left most node of next right node";


				if ((*DeletePtr).pRight.Exists())
					(*DeletePtr).pRight.SetToNull();
				deleted += ", right most node of next right node";

				cout << deleted << endl
					<< endl;

				if ((*DeletePtr).pParent.Exists())
					DeletePtr = (*DeletePtr).pParent;

			}

			Deleted = true;
			cout << "			Succesfully deleted nodes" << endl
				<< endl;
		}

		pRoot.SetToNull();
		cout << "			pRoot has been successfully deleted" << endl
			<< endl;
	}

	cout << "DeleteTree function has ended." << endl;		
	}

Variable::ValueType MathTree::Evaluate ()
	{
	if (pRoot.Exists ())
			{
			WCS_Pointer <Node> Ptr (GetLeftMostOperator (pRoot));

			while (Ptr.Exists ())
				if (!(*Ptr).LeftSideDone)
						{
						(*Ptr).SetValue ((*(*Ptr).pLeft).GetValue ());
						(*Ptr).LeftSideDone	= true;
						Ptr					= GetLeftMostOperator ((*Ptr).pRight);
						}
					else
						{
						switch ((*Ptr).GetType ())
							{
							case Token::OperatorPlusToken:
										(*Ptr).SetValue ((*Ptr).GetValue () + (*(*Ptr).pRight).GetValue ());
										break;
							case Token::OperatorMinusToken:
										// left as an exercise for the student
										// By student:
										(*Ptr).SetValue ((*Ptr).GetValue () - (*(*Ptr).pRight).GetValue ());
										break;
							case Token::OperatorAsteriskToken:
										// left as an exercise for the student
										// By student:
										(*Ptr).SetValue (((*Ptr).GetValue ()) * ((*(*Ptr).pRight).GetValue ()));
										
							case Token::OperatorSlashToken: 
										// left as an exercise for the student
										// By student:
										if ((*(*Ptr).pRight).GetValue() == 0)
											throw DivideByZero;
										(*Ptr).SetValue(((*Ptr).GetValue()) / ((*(*Ptr).pRight).GetValue()));
										break;
							}
						Ptr	= (*Ptr).pParent;
						}
			return (*pRoot).GetValue ();
			}
		else
			return 0;
	}

WCS_Pointer <MathTree::Node> MathTree::GetLeftMostOperator (const WCS_Pointer <Node> & pStart)
	{
	WCS_Pointer <Node>	Ptr (pStart);

	while ((*Ptr).pLeft.Exists ())
		{
		(*Ptr).LeftSideDone	= false;
		Ptr					= (*Ptr).pLeft;
		}
	return (*Ptr).pParent;
	}

bool MathTree::InsertOperand (const Token & Toke)
	{
	WCS_Pointer <Node> pTemp (new Node (Toke));

	if (!pRoot.Exists ())
			pRoot = pTemp;
		else
			{
			(*pLastOperator).pRight	= pTemp;
			(*pTemp).pParent		= pLastOperator;
			}
	return true;
	}

bool MathTree::InsertBinaryOperator (const Token & Toke)
	{
	WCS_Pointer <Node>	pNewOperator (new Node (Toke));

	while (pLastOperator.Exists () && ((*pLastOperator).GetPrecedence () >= (*pNewOperator).GetPrecedence ()))
		pLastOperator = (*pLastOperator).pParent;
	if (pLastOperator.DoesNotExist ())
			{
			(*pRoot).pParent		= pNewOperator;
			(*pNewOperator).pLeft	= pRoot;
			pRoot					= pNewOperator;
			}
		else
			{
			(*pNewOperator).pLeft				= (*pLastOperator).pRight;
			(*pNewOperator).pParent				= pLastOperator;
			(*pLastOperator).pRight				= pNewOperator;
			(*(*pNewOperator).pLeft).pParent	= pNewOperator;
			}
	pLastOperator	= pNewOperator;
	return true;
	}

/*	if (!pLastOperator.Exists ())
			{
			(*pRoot).pParent		= pNewOperator;
			(*pNewOperator).pLeft	= pRoot;
			pRoot					= pNewOperator;
			}
		else
			if ((*pLastOperator).GetPrecedence () >= (*pNewOperator).GetPrecedence ())
					{
					(*pNewOperator).pLeft		= pLastOperator;
					(*pLastOperator).pParent	= pNewOperator;
					pRoot						= pNewOperator;
					}
				else
					{
					(*pNewOperator).pParent				= pLastOperator;
					(*pNewOperator).pLeft				= (*pLastOperator).pRight;
					(*(*pNewOperator).pLeft).pParent	= pNewOperator;
					(*pLastOperator).pRight				= pNewOperator;
					}

	pLastOperator	= pNewOperator;
	return true;
	}
*/

bool MathTree::InsertUnaryOperator (const Token & Toke)
	{
	Token	Temp (Token::ConstantToken, 0);

	InsertOperand (Temp);
	InsertBinaryOperator (Toke);
	return true;
	}

