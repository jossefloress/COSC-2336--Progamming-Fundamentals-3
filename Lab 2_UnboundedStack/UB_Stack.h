#ifndef UB_STACK
#define UB_STACK

#include "WCS_UB_Array.h"

enum UB_Stack_Exception
					{
						STACK_OK,
						POP_FAILED,
						};

template <class DATA>
	class UB_Stack: private WCS_UB_Array <DATA, int> // instead of using <int, DATA>
		{
		public:
								UB_Stack	();
								~UB_Stack	();
			UB_Stack_Exception	Pop			(DATA &);
			UB_Stack_Exception	Push		(const DATA &);
		private:
								UB_Stack	(const UB_Stack <DATA> &);

			int		Top;
		};

template <class DATA>
	UB_Stack <DATA>::UB_Stack (): Top (0)
		{
		}

template <class DATA>
	UB_Stack <DATA>::~UB_Stack ()
		{
		//DeleteAll();
		}

template <class DATA>
	UB_Stack_Exception UB_Stack <DATA>::Pop (DATA & Data)
		{
		if (Top > 0)
				{
				Top--;
				Data = WCS_UB_Array<DATA,int>::At(Top); //same thing as     operator [] (Top); 
				return STACK_OK;
				}
			else
				return POP_FAILED;
		}

template <class DATA>
	UB_Stack_Exception UB_Stack <DATA>::Push (const DATA & Data)
		{
		(*this)[Top++] = Data;
		//WCS_UB_Array<DATA>::At(Top++) = Data; // same thing as:   (*this) [Top++] = Data;
		return STACK_OK;
		}


#endif
