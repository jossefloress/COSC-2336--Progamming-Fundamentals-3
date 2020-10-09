// Jose Flores
// COSC2336.S01 – Program 1

#include <iostream>

using namespace std;

#include <stdlib.h>

#include "WCS_Pointer.h"		// Instead of #include <WCS_Pointer.h>
#include "WCS_String.h"			// Instead of #include <WCS_String.h>

#include "UB_Array.h"

class D
	{
	public:
		int		A;
	};

void Func (const UB_Array <int, char> &);
void Func2(const UB_Array <WCS_String, D>&, WCS_String);


int main ()
	{
	UB_Array <int, char>		U1;
	UB_Array <WCS_String, D>	U2;

	char myDataHolder;
	D myDataHolder2;
	
	WCS_String myStr("My first string.");
	WCS_String myStr2("My second string.");
	D something, something2;
	something.A = 2;
	something2.A = 4;

	U1 [4] = 'A';
	U1 [8] = 'B';
	U1 [2] = 'C';
	U1[23] = 'S';
	U1[24] = 'D';


	U2[myStr] = something;
	U2[myStr2] = something2;
	
	cout << "****************** UB_Array U1 ******************\n" 
		<< U1[2] << U1[4] << U1[8] << U1[23] << U1[24] << endl << endl;

	Func(U1);

	cout << endl << "The size of UB_Array U1 before using Remove() is " << U1.Size() << "." << endl;
	
	U1.Remove(23, myDataHolder);

	cout << "Remove() has been applied to UB_Array U1.\n"
		<< "This value was copied during Remove(): " << myDataHolder << "." << endl 
		<< "The size of UB_Array U1 after using Remove() is " << U1.Size() << "." << endl << endl;
	


	cout << "\n\n****************** UB_Array U2 ******************\n";
		
	Func2(U2,myStr); 

	cout << endl << "The size of UB_Array U2 before using Remove() is " << U2.Size() << "." << endl;

	U2.Remove(myStr2, myDataHolder2);

	cout << "Remove() has been applied to UB_Array U2.\n"
		<< "This value was copied during Remove(): " << myDataHolder2.A << "." << endl
		<< "The size of UB_Array U2 after using Remove() is " << U2.Size() << "." << endl << endl;

	
	system ("pause");
	return 0;
	

	}

void Func(const UB_Array <int, char>& U)
{
	char	C1;
	char lastElem;
	char nextElem;
	char prevElem;

	cout << "Using operator[], index 8 is " << U[8] << "." <<  endl;

	cout << "Using At(), Index 23 is " << U.At(24) << "." << endl << endl;

	U.GetFirst(C1);
	cout << "First item is " << C1 << "." << endl;

	U.GetNext(nextElem);
	cout << "The next item is " << nextElem << "." << endl;

	U.GetLast(lastElem);
	cout << "Last item is " << lastElem << "." << endl;

	U.GetPrev(prevElem);
	cout << "The previous item is " << prevElem << "." << endl;

}


void Func2(const UB_Array <WCS_String, D>& U, WCS_String str)
{
	D	C1;
	D lastElem;
	D nextElem;
	D prevElem;

	cout << "Using operator[], index myStr is " << U[str].A << "." << endl;

	cout << "Using At(), Index myStr is " << U.At(str).A << "." << endl << endl;

	U.GetFirst(C1);
	cout << "First item is " << C1.A << "." << endl;

	U.GetNext(nextElem);
	cout << "The next item is " << nextElem.A << "." << endl;

	U.GetLast(lastElem);
	cout << "Last item is " << lastElem.A << "." << endl;

	U.GetPrev(prevElem);
	cout << "The previous item is " << prevElem.A << "." << endl;

}



