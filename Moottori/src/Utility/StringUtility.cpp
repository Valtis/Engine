#include "Utility/StringUtility.h"
namespace Utility
{
	std::vector<std::string> Tokenize(std::string text, std::string delimiters)
	{
		std::vector<std::string> tokens;
		if (text.size() == 0)
		{
			return tokens;
		}

		char *retVal;
		const unsigned int textbufferSize = text.length() + 1;
		char *textBuffer = new char[textbufferSize];
		for (unsigned int i = 0; i < textbufferSize; ++i)
		{
			textBuffer[i] = '\0';
		}
#ifdef _MSC_VER
		strncpy_s(textBuffer, textbufferSize, text.c_str(), text.length());
		char *nextToken = nullptr;
		retVal = strtok_s(textBuffer, delimiters.c_str(), &nextToken);
#else
		strncpy(textBuffer, text.c_str(), text.length());
		retVal = strtok(textBuffer, delimiters.c_str());
#endif



		while (retVal != nullptr)
		{
			tokens.push_back(retVal);
#ifdef _MSC_VER
			retVal = strtok_s(nullptr, delimiters.c_str(), &nextToken);
#else
			retVal = strtok(nullptr, delimiters.c_str());
#endif
		}

		delete [] textBuffer;
		return tokens;
	}
}