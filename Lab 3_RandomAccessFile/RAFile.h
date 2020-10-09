#ifndef RA_FILE_H
#define RA_FILE_H

#include <fstream>

using namespace std;

#include "WCS_Pointer.h"	// instead of #include <WCS_Pointer.h>
#include "WCS_String.h"		// instead of #include <WCS_String.h>
#include "WCS_UB_Array.h"	// instead of #include <WCS_UB_Array.h>

class RAFile
	{
	private:
		struct RecInfo
			{
			streamoff		Offset;
			size_t			Length;
			};
	public:
		enum	Exceptions	{
							File_OK,
							FileNotOpened,
							RecordDoesNotExist
							};
					RAFile		();
					RAFile		(const WCS_String &);
					~RAFile		();
		Exceptions	Close		();
		Exceptions	Get			(size_t, WCS_String &);
		Exceptions	Open		(const WCS_String &);
		Exceptions	Replace		(size_t, const WCS_String &);
		Exceptions	Insert		(size_t, const WCS_String &);
		string		GetAllData();
	private:
					RAFile		(const RAFile &);
		RAFile &	operator =	(const RAFile &);

		fstream							File;
		size_t							NumRecords;
		streamoff						EndOfRecords;
		WCS_UB_Array <RecInfo, size_t>	RecInfoArray;
	};

#endif
