#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

struct LexicalError : std::runtime_error {
	LexicalError(const char* msg) : std::runtime_error(msg) { }
	LexicalError(std::string msg) : std::runtime_error(msg.c_str()) { }
};

struct ParseError : std::runtime_error {
	ParseError(const char* msg) : std::runtime_error(msg) { }
	ParseError(std::string msg) : std::runtime_error(msg.c_str()) { }
};

struct ContextError : std::runtime_error {
	ContextError(const char* msg) : std::runtime_error(msg) { }
	ContextError(std::string msg) : std::runtime_error(msg.c_str()) { }
};

struct DivisionByZeroError : std::runtime_error {
	DivisionByZeroError(const char* msg) : std::runtime_error(msg) { }
	DivisionByZeroError(std::string msg) : std::runtime_error(msg.c_str()) { }
};

struct InputError : std::runtime_error {
	InputError(const char* msg) : std::runtime_error(msg) { }
	InputError(std::string msg) : std::runtime_error(msg.c_str()) { }
};
#endif
