#ifndef UB_ARRAY_H
#define UB_ARRAY_H

#include "WCS_Pointer.h" // Instead of #include <WCS_Pointer.h>

enum WCS_Exceptions	{
					ValidOperation,
					IndexDoesNotExist,
					IteratorNotSetUp,
					ArrayEmpty,
					NoPrevElement,
					NoNextElement
					};


// NOTE: whatever is used for the INDEX below must have support for the comparison operators

template <class DATA, class INDEX = int>
	class WCS_UB_Array
		{
		private:
			struct Node: public RefCount
				{
				WCS_Pointer <Node>	pNext;
				WCS_Pointer <Node>	pPrev;
				DATA				Data;
				INDEX				Index;

				Node (const INDEX &, size_t &);
				};
		public:
											WCS_UB_Array	();
			virtual							~WCS_UB_Array	();
							DATA &			At				(const INDEX &);
					const	DATA &			At				(const INDEX &)			const;
							void			DeleteAll		();
							WCS_Exceptions	GetFirst		(DATA &);
							WCS_Exceptions	GetFirst		(DATA &)				const;
							WCS_Exceptions	GetLast			(DATA &);
							WCS_Exceptions	GetLast			(DATA &)				const;
							WCS_Exceptions	GetNext			(DATA &);
							WCS_Exceptions	GetNext			(DATA &)				const;
							WCS_Exceptions	GetPrev			(DATA &);
							WCS_Exceptions	GetPrev			(DATA &)				const;
							WCS_Exceptions	Remove			(const INDEX &, DATA &);
							size_t			Size			()						const;
							DATA &			operator []		(const INDEX &);
					const	DATA &			operator []		(const INDEX &)			const;
		private:
							WCS_Pointer <Node>		pHead;
							WCS_Pointer <Node>		pTail;
				mutable		WCS_Pointer <Node>		pCurrent;
							size_t					NumElements;

									WCS_UB_Array	(const WCS_UB_Array <DATA, INDEX> &);
							void	operator =		(const WCS_UB_Array <DATA, INDEX> &);
		};

template <class DATA, class INDEX>
	WCS_UB_Array <DATA, INDEX>::Node::Node (const INDEX & I, size_t & NumElements): Index (I)
		{
		NumElements++;
		}

template <class DATA, class INDEX>
	WCS_UB_Array <DATA, INDEX>::WCS_UB_Array (): NumElements (0)
		{
		}

template <class DATA, class INDEX>
	WCS_UB_Array <DATA, INDEX>::~WCS_UB_Array ()
		{
		DeleteAll ();
		}

template <class DATA, class INDEX>
	inline DATA & WCS_UB_Array <DATA, INDEX>::At (const INDEX & I)
		{
		return (*this) [I];
		}

template <class DATA, class INDEX>
	inline const DATA & WCS_UB_Array <DATA, INDEX>::At (const INDEX & I) const
		{
		return (*this) [I];
		}

template <class DATA, class INDEX>
	void WCS_UB_Array <DATA, INDEX>::DeleteAll ()
		{
		if (pHead.Exists ())
				{
				while ((*pHead).pNext.Exists ())
					{
					pHead = (*pHead).pNext;
					(*pHead).pPrev.SetToNull ();
					}
				pHead.SetToNull ();
				pCurrent.SetToNull ();
				pTail.SetToNull ();
				}
			else;
		NumElements = 0;
		//return ValidOperation;
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetFirst (DATA & D)
		{
		if (pHead.DoesNotExist ())
				return ArrayEmpty;
			else
				{
				pCurrent	= pHead;
				D			= (*pCurrent).Data;
				return ValidOperation;
				}
		}


template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetFirst (DATA & D) const
		{
		if (pHead.DoesNotExist ())
				return ArrayEmpty;
			else
				{
				pCurrent	= pHead;
				D			= (*pCurrent).Data;
				return ValidOperation;
				}
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetLast (DATA & D)
		{
		if (pHead.DoesNotExist ())
				return ArrayEmpty;
			else
				{
				pCurrent	= pTail;
				D			= (*pCurrent).Data;
				return ValidOperation;
				}
		}


template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetLast (DATA & D) const
		{
		if (pHead.DoesNotExist ())
				return ArrayEmpty;
			else
				{
				pCurrent	= pTail;
				D			= (*pCurrent).Data;
				return ValidOperation;
				}
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetNext (DATA & D)
		{
		if (pCurrent.DoesNotExist ())
				return IteratorNotSetUp;
			else
				if (pCurrent == pTail)
						return NoNextElement;
					else
						{
						pCurrent	= (*pCurrent).pNext;
						D			= (*pCurrent).Data;
						return ValidOperation;
						}
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetNext (DATA & D) const
		{
		if (pCurrent.DoesNotExist ())
				return IteratorNotSetUp;
			else
				if (pCurrent == pTail)
						return NoNextElement;
					else
						{
						pCurrent	= (*pCurrent).pNext;
						D			= (*pCurrent).Data;
						return ValidOperation;
						}
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetPrev (DATA & D)
		{
		if (pCurrent.DoesNotExist ())
				return IteratorNotSetUp;
			else
				if (pCurrent == pHead)
						return NoPrevElement;
					else
						{
						pCurrent	= (*pCurrent).pPrev;
						D			= (*pCurrent).Data;
						return ValidOperation;
						}
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::GetPrev (DATA & D) const
		{
		if (pCurrent.DoesNotExist ())
				return IteratorNotSetUp;
			else
				if (pCurrent == pHead)
						return NoPrevElement;
					else
						{
						pCurrent	= (*pCurrent).pPrev;
						D			= (*pCurrent).Data;
						return ValidOperation;
						}
		}

template <class DATA, class INDEX>
	WCS_Exceptions WCS_UB_Array <DATA, INDEX>::Remove (const INDEX & I, DATA & D)
		{
		WCS_Pointer <Node>	pNode;

		pNode = pHead;
		while (pNode.Exists () && ((*pNode).Index < I))
				pNode = (*pNode).pNext;
		if (!pNode.Exists () || ((*pNode).Index > I))
				return IndexDoesNotExist;
			else
				{
				if (pNode == pCurrent)	// update iterator if necessary
						pCurrent.SetToNull ();
					else;
				if (pNode == pHead)
						{
						pHead = (*pHead).pNext;
						if (pHead.Exists ())
								(*pHead).pPrev.SetToNull ();
							else
								pTail.SetToNull ();
						}
					else
						if (pNode == pTail)
								{
								pTail = (*pTail).pPrev;
								(*pTail).pNext.SetToNull ();
								}
							else
								{
								WCS_Pointer <Node> pTemp;

								pTemp = (*pNode).pNext;
								if (pTemp.Exists ())
										(*pTemp).pPrev = (*pNode).pPrev;
									else;
								pTemp = (*pNode).pPrev;
								if (pTemp.Exists ())
										(*pTemp).pNext = (*pNode).pNext;
									else;
								}
				D = (*pNode).Data;
				pNode.SetToNull ();
				NumElements--;
				return ValidOperation;
				}
		}

template <class DATA, class INDEX>
	inline size_t WCS_UB_Array <DATA, INDEX>::Size () const
		{
		return NumElements;
		}

template <class DATA, class INDEX>
	DATA & WCS_UB_Array <DATA, INDEX>::operator [] (const INDEX & I)
		{
		WCS_Pointer <Node>	pNode;

		if (pHead.DoesNotExist ())	// is the list empty
				{
				pHead	= WCS_Pointer <Node> (new Node (I, NumElements));
				pTail	= pHead;
				return (*pHead).Data;
				}
			else
				if (I < (*pHead).Index)	// is the index in front of the existing list
						{
						pNode		= WCS_Pointer <Node> (new Node (I, NumElements));
						(*pNode).pNext	= pHead;
						(*pHead).pPrev	= pNode;
						pHead		= pNode;
						return (*pNode).Data;
						}
					else
						if (I > (*pTail).Index) // is the index after the existing list
								{
								pNode		= WCS_Pointer <Node> (new Node (I, NumElements));
								(*pNode).pPrev	= pTail;
								(*pTail).pNext	= pNode;
								pTail		= pNode;
								return (*pNode).Data;
								}
							else
								if (I == (*pHead).Index)	// is the Index the first thing in the list
										return (*pHead).Data;
									else
										if (I == (*pTail).Index)	// is the Index the last element
												return (*pTail).Data;
											else
												{
												for (pNode = pHead; I > (*pNode).Index; pNode = (*pNode).pNext);
												if (I == (*pNode).Index) // Is this the node I want
														return (*pNode).Data;
													else	// This is the node after where the new node needs to go
														{
														WCS_Pointer <Node> pNode2 (WCS_Pointer <Node> (new Node (I, NumElements)));
														(*pNode2).pNext			= pNode;
														(*pNode2).pPrev			= (*pNode).pPrev;
														(*(*pNode2).pPrev).pNext	= pNode2;
														(*pNode).pPrev			= pNode2;
														return (*pNode2).Data;
														}
												}
		}

template <class DATA, class INDEX>
	const DATA & WCS_UB_Array <DATA, INDEX>::operator [] (const INDEX & I) const
		{
		WCS_Pointer <Node>	pNode;

		if (pHead.DoesNotExist ())	// is the list empty
				throw ArrayEmpty;
			else
				if (I < (*pHead).Index)	// is the index in front of the existing list
						throw IndexDoesNotExist;
					else
						if (I > (*pTail).Index) // is the index after the existing list
								throw IndexDoesNotExist;
							else
								if (I == (*pHead).Index)	// is the Index the first thing in the list
										return (*pHead).Data;
									else
										if (I == (*pTail).Index)	// is the Index the last element
												return (*pTail).Data;
											else
												{
												for (pNode = pHead; I > (*pNode).Index; pNode = (*pNode).pNext);
												if (I == (*pNode).Index) // Is this the node I want
														return (*pNode).Data;
													else	// This is the node after where the new node needs to go
														throw IndexDoesNotExist;
												}
		}

#endif
