//******************************************************************************
//
//		Example Class to act as a string of characters
//
//		Copyright:	2002-2007  WCS Software Services
//		Author:		Bill Slater
//
//******************************************************************************

#ifndef WCS_STRING_H
#define WCS_STRING_H

#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

#pragma warning (disable:4996)

/*
#ifdef VISUAL_STUDIO
*/
#define STRCMP_NO_CASE _strcmpi
/*
#else
#define STRCMP_NO_CASE strcasecmp
#endif
*/

class WCS_String
	{
//************* Exceptions *****
	public:
		enum		Exceptions	{IndexOutOfBounds};
//************* Method Prototypes *****
	public:
		explicit				WCS_String				(const char * = "");
								WCS_String				(const WCS_String &);
		virtual					~WCS_String				();
				int				Compare					(const WCS_String &)	const;
				int				Compare					(const char *)			const;
				WCS_String &	Concat					(const WCS_String &);
				WCS_String &	Concat					(const char *);
				WCS_String &	Copy					(const WCS_String &);
				WCS_String &	Copy					(const char *);
				ostream &		Display					(ostream & = cout)		const;
				bool			GetAt					(char &, int)			const;
				bool			IsEmpty					()						const;
				size_t			Length					()						const;
				istream &		Read					(istream & = cin);
				bool			SetAt					(char, int);
				WCS_String &	ToLower					();
				WCS_String &	ToUpper					();
								operator bool			()						const;
								operator const char *	()						const;
				WCS_String &	operator =				(const WCS_String &);
				WCS_String &	operator =				(const char *);
				bool			operator <				(const WCS_String &)	const;
				bool			operator <				(const char *)			const;
				bool			operator <=				(const WCS_String &)	const;
				bool			operator <=				(const char *)			const;
				bool			operator ==				(const WCS_String &)	const;
				bool			operator ==				(const char *)			const;
				bool			operator >=				(const WCS_String &)	const;
				bool			operator >=				(const char *)			const;
				bool			operator >				(const WCS_String &)	const;
				bool			operator >				(const char *)			const;
				bool			operator !=				(const WCS_String &)	const;
				bool			operator !=				(const char *)			const;
				WCS_String		operator &				(const WCS_String &)	const;
				WCS_String		operator &				(const char *)			const;
				WCS_String &	operator &=				(const WCS_String &);
				WCS_String &	operator &=				(const char *);
				char &			operator []				(int);
				char			operator []				(int)					const;
	private:
				bool			IsValidSubscript		(int)					const;
				void			LocalCheckAndCopy		(const char *);
				WCS_String &	LocalConcat				(const char *);
				void			LocalCopy				(const char *);
				WCS_String		NewConcat				(const char *)			const;
		static	char			ReadChar				(istream & = cin);
								operator char *			()						const;
//************* Properties *****
	private:
				char *	pChar;
				size_t	CharCount;
				size_t	MaxSize;
	};

//************* Method Definitions *****

inline WCS_String::WCS_String (const char * p): CharCount (0), MaxSize (0), pChar (0)
	{
	LocalCopy (p);
	}

inline WCS_String::WCS_String (const WCS_String & M)
	{
	LocalCopy (M.pChar);
	}

inline int WCS_String::Compare (const WCS_String & M) const
	{
	return STRCMP_NO_CASE (pChar, M.pChar);
	}

inline int WCS_String::Compare (const char * p) const
	{
	return STRCMP_NO_CASE (pChar, p);
	}

inline WCS_String & WCS_String::Concat (const WCS_String & M)
	{
	return LocalConcat (M.pChar);
	}

inline WCS_String & WCS_String::Concat (const char * p)
	{
	return LocalConcat (p);
	}

inline WCS_String & WCS_String::Copy (const WCS_String & M)
	{
	return *this = M;
	}

inline WCS_String & WCS_String::Copy (const char * p)
	{
	return *this = p;
	}

inline ostream & WCS_String::Display (ostream & out) const
	{
	return out << pChar;
	}

inline bool WCS_String::GetAt (char & c, int i) const
	{
	if (IsValidSubscript (i))
			{
			c = pChar [i];
			return true;
			}
		else
			return false;
	}

inline bool WCS_String::IsEmpty () const
	{
	return Length () == 0;
	}

inline bool WCS_String::IsValidSubscript (int i) const
	{
	return (i >= 0) && (i < static_cast <int> (CharCount));
	}

inline size_t WCS_String::Length () const
	{
	return CharCount;
	}

inline WCS_String WCS_String::NewConcat (const char * p) const
	{
	WCS_String S (*this);
	S.Concat (p);
	return S;
	}

inline WCS_String::operator bool () const
	{
	return Length () > 0;
	}

inline WCS_String::operator const char * () const
	{
	return pChar;
	}

inline WCS_String & WCS_String::operator = (const WCS_String & M)
	{
	if (this != &M)
			LocalCheckAndCopy (M.pChar);
		else;
	return *this;
	}

inline WCS_String & WCS_String::operator = (const char * p)
	{
	LocalCheckAndCopy (p);
	return *this;
	}

inline bool WCS_String::operator <	(const WCS_String & M) const
	{
	return Compare (M) < 0;
	}

inline bool WCS_String::operator <	(const char * p) const
	{
	return Compare (p) < 0;
	}

inline bool operator <	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) > 0;
	}

inline bool WCS_String::operator <=	(const WCS_String & M) const
	{
	return Compare (M) <= 0;
	}

inline bool WCS_String::operator <=	(const char * p) const
	{
	return Compare (p) <= 0;
	}

inline bool operator <=	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) >= 0;
	}

inline bool WCS_String::operator ==	(const WCS_String & M) const
	{
	return Compare (M) == 0;
	}

inline bool WCS_String::operator ==	(const char * p) const
	{
	return Compare (p) == 0;
	}

inline bool operator ==	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) == 0;
	}

inline bool WCS_String::operator >=	(const WCS_String & M) const
	{
	return Compare (M) >= 0;
	}

inline bool WCS_String::operator >=	(const char * p) const
	{
	return Compare (p) >= 0;
	}

inline bool operator >=	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) <= 0;
	}

inline bool WCS_String::operator >	(const WCS_String & M) const
	{
	return Compare (M) > 0;
	}

inline bool WCS_String::operator >	(const char * p) const
	{
	return Compare (p) > 0;
	}

inline bool operator >	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) < 0;
	}

inline bool WCS_String::operator !=	(const WCS_String & M) const
	{
	return Compare (M) != 0;
	}

inline bool WCS_String::operator !=	(const char * p) const
	{
	return Compare (p) != 0;
	}

inline bool operator !=	(const char * p, const WCS_String & S)
	{
	return S.Compare (p) != 0;
	}

inline WCS_String WCS_String::operator & (const WCS_String & M) const
	{
	return NewConcat (M.pChar);
	}

inline WCS_String WCS_String::operator & (const char * p) const
	{
	return NewConcat (p);
	}

inline WCS_String operator & (const char * p, const WCS_String & S)
	{
	WCS_String Temp (p);
	return Temp.Concat (S);
	}

inline WCS_String &	WCS_String::operator &=	(const WCS_String & M)
	{
	return Concat (M);
	}

inline WCS_String &	WCS_String::operator &=	(const char * p)
	{
	return Concat (p);
	}

inline char & WCS_String::operator [] (int i)
	{
	if (IsValidSubscript (i))
			return pChar [i];
		else
			throw IndexOutOfBounds;
	}

inline char WCS_String::operator [] (int i) const
	{
	return (*const_cast <WCS_String *> (this)).operator [] (i);
	}

inline bool WCS_String::SetAt (char c, int i)
	{
	if ((i >= 0) && (i < static_cast <int> (CharCount)))
			{
			pChar [i] = c;
			return true;
			}
		else
			return false;
	}

inline ostream & operator << (ostream & out, const WCS_String & M)
	{
	return M.Display (out);
	}

inline istream & operator >> (istream & in, WCS_String & M)
	{
	return M.Read (in);
	}

#pragma warning (default:4996)

#endif
