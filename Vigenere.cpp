#include "Vigenere.h"
#include <iostream>
using namespace std;

void Vigenere::initializeTable()
{
    for (char row = 0; row < CHARACTERS; row++)
    {
        char lChar = 'B' + row;
        for (char column = 0; column < CHARACTERS; column++)
        {
            if (lChar > 'Z')
                lChar = 'A';
            fMappingTable[row][column] = lChar++;
        }
    }
}

Vigenere::Vigenere(const std::string& aKeyword) : fKeywordProvider(aKeyword), fKeyword(aKeyword)
{
    initializeTable();
}

std::string Vigenere::getCurrentKeyword()
{
    string result = "";
    for (size_t i = 0; i < fKeyword.size(); i++)
    {
        result += *fKeywordProvider;
        fKeywordProvider << *fKeywordProvider;
    }
    return result;
}

void Vigenere::reset()
{
    fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter)
{
    if (isalpha(aCharacter))
    {
        bool isUpper = isupper(aCharacter);
        char encodedChar = fMappingTable[*fKeywordProvider - 65][toupper(aCharacter) - 65];
        fKeywordProvider << aCharacter;
        if (isUpper)
        {
            return encodedChar;
        }
        else
        {
            return tolower(encodedChar);
        }
    }
    else
    {
        return aCharacter;
    }
}

char Vigenere::decode(char aCharacter)
{
    if (isalpha(aCharacter))
    {
        for (size_t i = 65; i < 91; i++)
        {
            if (fMappingTable[*fKeywordProvider - 65][toupper(i) - 65] == toupper(aCharacter))
            {
                fKeywordProvider << i;
                if (isupper(aCharacter))
                {

                    return i;
                }
                else
                {
                    return tolower(i);
                }
            }
        }

    }
    else
    {
        return aCharacter;
    }
}