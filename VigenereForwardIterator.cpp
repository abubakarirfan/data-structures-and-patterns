#include "VigenereForwardIterator.h"

using namespace std;

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) : fIStream(aIStream), fEOF(false), fCurrentChar(1)
{
	if (!fEOF)
	{
		fIStream >> fCurrentChar;
	}
}

char VigenereForwardIterator::operator*() const
{
	return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{
	if (!fEOF)
	{
		fIStream >> fCurrentChar;
		fEOF = fIStream.eof();
	}
	return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
	VigenereForwardIterator temp = *this;
	++(*this);
	return temp;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
	return ((fEOF == aOther.fEOF) && (aOther.fIStream.position() == fIStream.position()));
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
	return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const
{
	VigenereForwardIterator Result = *this;
	Result.fIStream.reset();

	Result.fEOF = Result.fIStream.eof();

	if (Result.fEOF)
	{
		Result.fCurrentChar = 0;
	}
	else
	{
		Result.fIStream >> Result.fCurrentChar;
	}

	return Result;
}

VigenereForwardIterator VigenereForwardIterator::end() const
{
	VigenereForwardIterator Result = *this;
	Result.fCurrentChar = 0;
	Result.fEOF = true;
	return Result;
}