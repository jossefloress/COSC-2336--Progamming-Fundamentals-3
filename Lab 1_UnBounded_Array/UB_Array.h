#ifndef UB_ARRAY_H
#define UB_ARRAY_H

// Jose Flores
// COSC2336.S01 – Program 1

#include "WCS_Pointer.h"	//Instead of using #include <WCS_Pointer.h>

//	the class used for INDEX below must support the comparison operators <  <=  ==  !=  >=  >

enum UB_Array_Exceptions	{
							OK,
							ArrayEmpty,
							IteratorNotInitialized,
							NodeNotFound,
							NoNextElement,
							NoPrevElement
							};

template <class INDEX, class DATA>
	class UB_Array
		{
		private:
			struct Node: public RefCount
				{
				INDEX				Index;
				DATA				Data;
				WCS_Pointer <Node>	pNext;
				WCS_Pointer <Node>	pPrev;


				Node	();
				Node	(const INDEX &);
				};
		public:
										UB_Array	();
										~UB_Array	();

					UB_Array_Exceptions	GetFirst	(DATA &) const;
					UB_Array_Exceptions	GetLast		(DATA &) const;

					UB_Array_Exceptions	GetNext		(DATA &) const;
					UB_Array_Exceptions	GetPrev		(DATA &) const;

			const	DATA &				At			(const INDEX &) const;
					UB_Array_Exceptions	Remove		(const INDEX &, DATA &);
					size_t Size		();
										
					DATA &				operator []	(const INDEX &);
			const	DATA &				operator []	(const INDEX &) const;
		private:
										UB_Array	(const UB_Array <INDEX, DATA> &);
					size_t					numNodes;
					WCS_Pointer <Node>		pHead;
					WCS_Pointer <Node>		pTail;
			mutable	WCS_Pointer <Node>		pCurrent;
		};

template <class INDEX, class DATA>
	UB_Array <INDEX, DATA>::Node::Node ()
		{
		}

template <class INDEX, class DATA>
	UB_Array <INDEX, DATA>::Node::Node (const INDEX & I)
		{
		Index	= I;
		}

template <class INDEX, class DATA>
	UB_Array <INDEX, DATA>::UB_Array () : numNodes(0)
		{
		}

template <class INDEX, class DATA>
	UB_Array <INDEX, DATA>::~UB_Array ()
		{
			WCS_Pointer <Node> tempNode;
			for (int i = 0; i >= numNodes; tempNode = (*tempNode).pNext)
				tempNode.SetToNull();
		}
	


template <class INDEX, class DATA>
	UB_Array_Exceptions UB_Array <INDEX, DATA>::GetFirst (DATA & D) const
		{
		if (!pHead)
				return ArrayEmpty;
			else
				{
				D			= (*pHead).Data;
				pCurrent	= pHead;
				return OK;
				}
		}

template <class INDEX, class DATA>
		UB_Array_Exceptions UB_Array <INDEX, DATA>::GetLast (DATA & D) const
		{
			if (!pHead)
				return ArrayEmpty;
			else
			{
				D = (*pTail).Data;
				pCurrent = pTail;
				return OK;
			}
		}

template <class INDEX, class DATA>
	UB_Array_Exceptions UB_Array <INDEX, DATA>::GetNext (DATA & D) const
		{
		if (!pHead)
				return ArrayEmpty;
			else
				if (!pCurrent)
						return IteratorNotInitialized;
					else
						if (!(*pCurrent).pNext)
								return NoNextElement;
							else
								{
								pCurrent	= (*pCurrent).pNext;
								D			= (*pCurrent).Data;
								return OK;
								}
		}

template <class INDEX, class DATA>
	UB_Array_Exceptions UB_Array <INDEX, DATA>::GetPrev	(DATA & D) const
	{
		if (!pHead)
			return ArrayEmpty;
		else
			if (!pCurrent)
				return IteratorNotInitialized;
			else
				if (!(*pCurrent).pPrev)
					return NoPrevElement;
				else
				{
					pCurrent = (*pCurrent).pPrev;
					D = (*pCurrent).Data;
					return OK;
				}
	}

template <class INDEX, class DATA>
	const DATA& UB_Array <INDEX, DATA>::At (const INDEX& I) const
	{
		return operator[](I);
	}
	



template <class INDEX, class DATA>
	UB_Array_Exceptions UB_Array <INDEX, DATA>::Remove (const INDEX & I, DATA & moveToHere)
		{
		WCS_Pointer <Node> tempNode;
		tempNode.SetToNull();
		
		if (pHead.DoesNotExist())	//DoesNotExist() function is from WCS_Pointer.h
			return ArrayEmpty;
		else
			if (I < (*pHead).Index)
				return NodeNotFound;
			else
				if (I > (*pTail).Index)
					return NodeNotFound;
				else
					if (I == (*pTail).Index)
					{
						tempNode = pTail;
						moveToHere = (*pTail).Data;
						pTail = (*pTail).pPrev;
						numNodes--;
						((*tempNode).pPrev).SetToNull();
						((*tempNode).pNext).SetToNull();
						return OK;
					}
					else
						if (I == (*pHead).Index)
						{
							moveToHere = (*pHead).Data;
							pHead.SetToNull();
							pHead = (*pHead).pNext;
							numNodes--;							
							return OK;
						}
						else
						{
							for (tempNode = (*pHead).pNext; I > (*tempNode).Index; tempNode = (*tempNode).pNext);
							if (I == (*tempNode).Index)
							{
								moveToHere = (*tempNode).Data;
								((*(*tempNode).pNext).pPrev) = (*tempNode).pPrev;
								((*(*tempNode).pPrev).pNext) = (*tempNode).pNext;
								numNodes--;
								return OK;
							}
						}						
		}


template <class INDEX, class DATA>
	size_t UB_Array <INDEX, DATA>::Size()
	{
		return numNodes;
	}

template <class INDEX, class DATA>
	DATA & UB_Array <INDEX, DATA>::operator [] (const INDEX & I)
		{
		WCS_Pointer <Node>	pTemp;

		if (!pHead)
				{
				pHead	= WCS_Pointer <Node> (new Node (I));
				pTail	= pHead;
				numNodes++;
				return (*pHead).Data;
				}
			else
				if (I == (*pHead).Index)
						return (*pHead).Data;
					else
						if (I == (*pTail).Index)
								return (*pTail).Data;
							else
								if (I < (*pHead).Index)
										{
										pTemp			= WCS_Pointer <Node> (new Node (I));
										(*pHead).pPrev	= pTemp;
										(*pTemp).pNext	= pHead;
										pHead			= pTemp;
										numNodes++;
										return (*pHead).Data;
										}
									else
										if (I > (*pTail).Index)
												{
												pTemp			= WCS_Pointer <Node> (new Node (I));
												(*pTail).pNext	= pTemp;
												(*pTemp).pPrev	= pTail;
												pTail			= pTemp;
												numNodes++;
												return (*pTail).Data;
												}
											else
												{
												for (pTemp = (*pHead).pNext; I > (*pTemp).Index; pTemp = (*pTemp).pNext);
												if (I == (*pTemp).Index)
														return (*pTemp).Data;
													else
														{
														WCS_Pointer <Node>	pTemp2;

														pTemp2					= WCS_Pointer <Node> (new Node (I));
														(*pTemp2).pPrev			= (*pTemp).pPrev;
														(*(*pTemp).pPrev).pNext	= pTemp2;
														(*pTemp2).pNext			= pTemp;
														(*pTemp).pPrev			= pTemp2;
														numNodes++;
														return (*pTemp2).Data;
														}
												}
		}

template <class INDEX, class DATA>
	const DATA & UB_Array <INDEX, DATA>::operator [] (const INDEX & I) const
		{
		WCS_Pointer <Node>	pTemp;

		if (!pHead)
				{
				// throw an exception
				throw ArrayEmpty;
				}
			else
				if (I == (*pHead).Index)
						return (*pHead).Data;
					else
						if (I == (*pTail).Index)
								return (*pTail).Data;
							else
								if (I < (*pHead).Index)
										{
										// throw an exception
										throw NodeNotFound;
										}
									else
										if (I > (*pTail).Index)
												{
												// throw an exception
												throw NodeNotFound;
												}
											else
												{
												for (pTemp = (*pHead).pNext; I > (*pTemp).Index; pTemp = (*pTemp).pNext);
												if (I == (*pTemp).Index)
														return (*pTemp).Data;
													else
														{
														// throw an exception
														throw NodeNotFound;
														}
												}
		}

#endif
