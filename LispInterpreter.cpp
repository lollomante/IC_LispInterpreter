#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "Token.h"
#include "Tokenizer.h"
#include "Exceptions.h"
#include "Parser.h"
#include "MemoryManager.h"
//#include "Context.h"

#include "Program.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "File non specificato!" << std::endl;
        std::cerr << "Utilizzo: " << argv[0] << " <nome_file>" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream inputFile;
    try {
        inputFile.open(argv[1]);
    }
    catch (std::exception& exc) {
        std::cerr << "Il file: " << argv[1] << " non esiste. "<<std::endl;
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    //Tokenize phase
    Tokenizer tokenize;
    std::vector<Token> inputTokens;

    try {
        inputTokens = std::move(tokenize(inputFile));
        inputFile.close();
    }
    catch (LexicalError& le) {
        std::cerr << "Errore in fase di analisi lessicale" << std::endl;
        std::cerr << le.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::exception& exc) {
        std::cerr << "Non posso leggere da " << argv[1] << std::endl;
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    //create simbletable
    SimbleTable s;

    // create memory manager
    MemoryManager m (s); 

    //parse and evaluation phase
    try {
        ProgramParse parse(inputTokens, m, s);
        if (parse(inputTokens)) {
            StatementBlock* st = parse.getStmBlock();           
            st->interpret();
        }
    }
    catch(ParseError& pe) {
        std::cerr << "Error during parsing" << std::endl;
        std::cerr << pe.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (ContextError& ce) {
        std::cerr << "Error: variable does not exist " << std::endl;
        std::cerr << ce.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (DivisionByZeroError& dz) {
        std::cerr << "Error: Cannot divide by zero " << std::endl;
        std::cerr << dz.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (InputError& ie) {
        std::cerr << ie.what() << std::endl;
    }
    return EXIT_SUCCESS;
}

