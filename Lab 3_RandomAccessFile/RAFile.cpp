#include "RAFile.h"
#include <string>

RAFile::RAFile() : NumRecords(0), EndOfRecords(0)
{
}

RAFile::RAFile(const WCS_String& Str)
{
	Open(Str);
}

RAFile::~RAFile()
{
	Close();
}

RAFile::Exceptions RAFile::Close()
{
	size_t	i;

	if (File.is_open())
	{
		File.seekp(0);
		File.write((const char*)&NumRecords, sizeof(NumRecords));
		File.seekp(EndOfRecords);
		for (i = 0; i < NumRecords; i++)
			File.write((const char*)&RecInfoArray[i], sizeof(RecInfo));
		File.close();
		return File_OK;
	}
	else
		return FileNotOpened;
}

RAFile::Exceptions RAFile::Get(size_t Index, WCS_String& Data)
{
	char* pTemp;

	if (File.is_open())
	{
		if (Index < NumRecords)	// does the record already exist
		{
			if (RecInfoArray[Index].Length == 0) {	// is the record empty
				Data = "";
			}
			else	// no, need to actually read
			{
				File.seekg(RecInfoArray[Index].Offset);
				pTemp = new char[RecInfoArray[Index].Length + 1];
				File.read(pTemp, RecInfoArray[Index].Length);
				pTemp[RecInfoArray[Index].Length] = '\0';
				Data = pTemp;
				delete[] pTemp;
			}
			return File_OK;
		}
		else
			return RecordDoesNotExist;
	}
	else
		return FileNotOpened;
}

RAFile::Exceptions RAFile::Open(const WCS_String& Str)
{
	size_t	i;

	File.open((const char*)Str, ios_base::in | ios_base::out | ios_base::binary);
	if (!File.is_open())
	{	// if file does not exist we will try and create one
		File.clear();
		File.open((const char*)Str, ios_base::out | ios_base::binary);
		if (!File.is_open())
		{
			File.clear();
			return FileNotOpened;
		}
		else
		{
			NumRecords = 0;
			File.write((const char*)&NumRecords, sizeof(NumRecords));
			File.close();
			File.open((const char*)Str, ios_base::in | ios_base::out | ios_base::binary);
			if (!File.is_open())
				return FileNotOpened;
			else;
		}
	}
	else;
	// file is now opened for input and output
	File.seekg(0);
	File.read((char*)&NumRecords, sizeof(NumRecords));
	if (NumRecords > 0)
	{
		File.seekg(-((long)(NumRecords * sizeof(RecInfo))), ios_base::end);
		EndOfRecords = File.tellg();	// save the position of where we are right now
		for (i = 0; i < NumRecords; i++)
			File.read((char*)&RecInfoArray[i], sizeof(RecInfo));
	}
	else
		EndOfRecords = File.tellg();
	return File_OK;
}

RAFile::Exceptions RAFile::Replace(size_t Index, const WCS_String& Data)
{
	size_t	i;

	if (File.is_open())
	{
		if (Index < NumRecords)	// does the record already exist
			if (RecInfoArray[Index].Length >= Data.Length())	// is there room to right the new data
			{
				File.seekp(RecInfoArray[Index].Offset);	// go to where the record is
				File.write((const char*)Data, Data.Length());	// write the data
				RecInfoArray[Index].Length = Data.Length();
			}
			else
			{
				RecInfoArray[Index].Length = Data.Length();
				RecInfoArray[Index].Offset = EndOfRecords;
				File.seekp(EndOfRecords);
				File.write((const char*)Data, Data.Length());
				EndOfRecords = File.tellp();
			}
		else
		{	// fill in empty records for those being skipped
			for (i = NumRecords; i < Index; i++)
			{
				RecInfoArray[i].Length = 0;
				RecInfoArray[i].Offset = 0;
			}
			RecInfoArray[Index].Length = Data.Length();
			RecInfoArray[Index].Offset = EndOfRecords;
			File.seekp(EndOfRecords);
			File.write((const char*)Data, Data.Length());
			EndOfRecords = File.tellp();
			NumRecords = Index + 1;
		}
		return File_OK;
	}
	else
		return FileNotOpened;
}



RAFile::Exceptions RAFile::Insert(size_t Index, const WCS_String& Data)
{
	size_t records;

	if (File.is_open())
	{
		if (Index >= NumRecords)
		{
			Replace(Index, Data);
		}


		else
		{
			for (records = NumRecords; records > Index; records--)
			{
				RecInfoArray[records + 1] = RecInfoArray[records];
			}

			//	Copied from Replace() method
			RecInfoArray[Index].Length = Data.Length();
			RecInfoArray[Index].Offset = EndOfRecords;
			File.seekp(EndOfRecords);
			File.write((const char*)Data, Data.Length());
			EndOfRecords = File.tellp();
			NumRecords++;
			return File_OK;
		}
		return File_OK;
	}
	else
	{
		return FileNotOpened;
	}
}

string RAFile::GetAllData()
{
	WCS_String tempStr;
	string gotDataStr;
	for (size_t i = 0; i < NumRecords; i++)
	{
		Get(i, tempStr);
		gotDataStr = gotDataStr + "Index: " + to_string(i) + "\t\t" +  "Data: " + (string)(tempStr) + '\n';
	}
	return gotDataStr;
}