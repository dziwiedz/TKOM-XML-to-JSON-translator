cmake_minimum_required(VERSION 3.6)
project(TKOM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Source.cpp Source.h Lexer.cpp Lexer.h Atoms.h Token.cpp Token.h Parser.cpp Parser.h XMLTree.cpp XMLTree.h XMLNode.cpp XMLNode.h Attribute.cpp Attribute.h JsonWriter.cpp JsonWriter.h LexerExceptions.cpp LexerExceptions.h ParserExceptions.cpp ParserExceptions.h)
add_executable(TKOM ${SOURCE_FILES})