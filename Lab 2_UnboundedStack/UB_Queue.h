#ifndef UB_QUEUE
#define UB_QUEUE

#include "WCS_UB_Array.h"

enum UB_Queue_Exception
			{
				QUEUE_OK,
				DEQUEUE_FAILED
			};
template <class DATA>
class UB_Queue : private WCS_UB_Array<DATA,int>
	{
	private:
		int Top;
	public:
		UB_Queue();
		~UB_Queue();
		UB_Queue_Exception	Queue(const DATA&);
		UB_Queue_Exception	DeQueue(DATA&);
		DATA				printAll();
		size_t				Size() const;
	};

template<class DATA>
	inline UB_Queue<DATA>::UB_Queue() : Top(0)
	{
	}

template<class DATA>
	inline UB_Queue<DATA>::~UB_Queue()
	{
		WCS_UB_Array<DATA, int>::DeleteAll();
		Top = 0;
	}
	
template<class DATA>
	UB_Queue_Exception UB_Queue<DATA>::Queue(const DATA& Data)
	{
		(*this)[Top++] = Data;
		return QUEUE_OK;
	}

template<class DATA>
	UB_Queue_Exception UB_Queue<DATA>::DeQueue(DATA& Data)
	{
		DATA deletedNode;
		if (Top > 0)
		{
			WCS_UB_Array<DATA, int>::Remove(Top-((int)Size()), deletedNode);
			Data = deletedNode;
			return QUEUE_OK;
		}
		else
			return DEQUEUE_FAILED;
	}


template <class DATA>
DATA UB_Queue<DATA>::printAll()
{
	DATA allElems;
	DATA oneElem;

	for (int i = 0; i < Size(); i++)
	{
		if (i == 0)
		{
			WCS_UB_Array<DATA, int>::GetFirst(oneElem);
			allElems = oneElem;
		}

		else
		{
			WCS_UB_Array<DATA, int>::GetNext(oneElem);
			allElems += ", " + oneElem;
		}
	}
	return allElems;
}


template<class DATA>
inline size_t UB_Queue<DATA>::Size() const
{
	return WCS_UB_Array<DATA, int>::Size();
}

#endif