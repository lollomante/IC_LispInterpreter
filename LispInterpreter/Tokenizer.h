

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>


#include "Token.h"
#include "Exceptions.h"

class Tokenizer {
public:
	Tokenizer() = default;
	Tokenizer(const Tokenizer& t) = default;
	~Tokenizer() = default;
	Tokenizer& operator=(const Tokenizer& other) = default;


	std::vector<Token> operator()(std::ifstream& inputFile) {
		std::vector<Token> inputTokens;
		tokenizeInputFile(inputFile, inputTokens);
		return inputTokens;
	}

private:
	void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens);

};

#endif

