#include "Tokenizer.h"

void Tokenizer::tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens) {
	//read file and copy it's content into a std::string variable
	char ch;
	std::string input;
	while (!inputFile.eof()) {
		ch = inputFile.get();
		input.push_back(ch);
	}
	//analize the string value
	for (int i = 0; i < (input.size()-1); ) {
		//skip "white" spaces
		if (isspace(input[i])) {
			i++;
			continue;
		}
		if (input[i] == '(') {
			inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP] });
			i++;
			continue;
		}
		if (input[i] == ')') {
			inputTokens.push_back(Token{ Token::RP, Token::id2word[Token::RP] });
			i++;
			continue;
		}
		else {
			//save "potenzial" token into another std::srting variable
			std::string token;
			while ((i < input.size() && !isspace(input[i]))  && !(input[i] == ')')) {
				token.push_back(input[i]);
				i++;
			}
			if (!token.compare(Token::id2word[Token::SET])) {
				inputTokens.push_back(Token{ Token::SET, Token::id2word[Token::SET] });
			}
			else if (!token.compare(Token::id2word[Token::PRINT])) {
				inputTokens.push_back(Token{ Token::PRINT, Token::id2word[Token::PRINT] });
			}
			else if (!token.compare(Token::id2word[Token::INPUT])) {
				inputTokens.push_back(Token{ Token::INPUT, Token::id2word[Token::INPUT] });
			}
			else if (!token.compare(Token::id2word[Token::IF])) {
				inputTokens.push_back(Token{ Token::IF, Token::id2word[Token::IF] });
			}
			else if (!token.compare(Token::id2word[Token::WHILE])) {
				inputTokens.push_back(Token{ Token::WHILE, Token::id2word[Token::WHILE] });
			}
			else if (!token.compare(Token::id2word[Token::ADD])) {
				inputTokens.push_back(Token{ Token::ADD, Token::id2word[Token::ADD] });
			}
			else if (!token.compare(Token::id2word[Token::SUB])) {
				inputTokens.push_back(Token{ Token::SUB, Token::id2word[Token::SUB] });
			}
			else if (!token.compare(Token::id2word[Token::MUL])) {
				inputTokens.push_back(Token{ Token::MUL, Token::id2word[Token::MUL] });
			}
			else if (!token.compare(Token::id2word[Token::DIV])) {
				inputTokens.push_back(Token{ Token::DIV, Token::id2word[Token::DIV] });
			}
			else if (!token.compare(Token::id2word[Token::GT])) {
				inputTokens.push_back(Token{ Token::GT, Token::id2word[Token::GT] });
			}
			else if (!token.compare(Token::id2word[Token::LT])) {
				inputTokens.push_back(Token{ Token::LT, Token::id2word[Token::LT] });
			}
			else if (!token.compare(Token::id2word[Token::EQ])) {
				inputTokens.push_back(Token{ Token::EQ, Token::id2word[Token::EQ] });
			}
			else if (!token.compare(Token::id2word[Token::AND])) {
				inputTokens.push_back(Token{ Token::AND, Token::id2word[Token::AND] });
			}
			else if (!token.compare(Token::id2word[Token::OR])) {
				inputTokens.push_back(Token{ Token::OR, Token::id2word[Token::OR] });
			}
			else if (!token.compare(Token::id2word[Token::NOT])) {
				inputTokens.push_back(Token{ Token::NOT, Token::id2word[Token::NOT] });
			}
			else if (!token.compare(Token::id2word[Token::TRUE])) {
				inputTokens.push_back(Token{ Token::TRUE, Token::id2word[Token::TRUE] });
			}
			else if (!token.compare(Token::id2word[Token::FALSE])) {
				inputTokens.push_back(Token{ Token::FALSE, Token::id2word[Token::FALSE] });
			}
			else if (!token.compare(Token::id2word[Token::BLOCK])) {
				inputTokens.push_back(Token{ Token::BLOCK, Token::id2word[Token::BLOCK] });
			}
			// if is not a key word token could be a number or a variable token
			else {
				int ceckdigit = 0;
				int ceckalpha = 0;
				std::stringstream tmp{};
				//managing possible '-' in numbers
				if (token[0] == '-') {
					ceckdigit++;
				}
				for (int i = 0; i < token.size(); i++) {
					tmp << token[i];
					if (std::isalpha(token[i])) {
						ceckalpha++;
					}
					if (std::isdigit(token[i])) {
						ceckdigit++;
					}
				}
				if (ceckdigit == token.size()) {
					inputTokens.push_back(Token{ Token::NUMBER, tmp.str() });
				}
				else if (ceckalpha == token.size()) {
					inputTokens.push_back(Token{ Token::VARIABLE, tmp.str() });
				}
				else {
					//if it is neither of those, than it is not a token
					//use exception mecanism to retur an error message
					std::stringstream temp{};
					temp << "Error: " << token <<" is not a word of this language";
					throw LexicalError(temp.str());
				}
			}
		}
	}
}
