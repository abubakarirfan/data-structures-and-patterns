#include "iVigenereStream.h"
#include <fstream>
#include <string>

using namespace std;


iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
	aCharacter = fIStream.get();
	if (!bool())
	{
		aCharacter = fCipher(fCipherProvider, aCharacter);
	}
	return *this;
}


iVigenereStream::~iVigenereStream()
{
	close();
}

iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName) : fCipherProvider(aKeyword), fCipher(aCipher)
{
	open(aFileName);
}

void iVigenereStream::open(const char* aFileName)
{
	if (aFileName)
	{
		fIStream.open(aFileName, ios::binary);
	}

}

void iVigenereStream::reset()
{
	seekstart();
	fCipherProvider.reset();
}

void iVigenereStream::close()
{
	fIStream.close();

}

bool iVigenereStream::good() const
{
	return fIStream.good();
}

bool iVigenereStream::is_open() const
{
	return fIStream.is_open();
}

bool iVigenereStream::eof() const
{
	return fIStream.eof();
}
