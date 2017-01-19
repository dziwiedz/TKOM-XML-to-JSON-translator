cmake_minimum_required(VERSION 3.6)
project(TKOM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp include/jsoncpp.cpp Source.cpp Source.h Lexer.cpp Lexer.h Atoms.h Token.cpp Token.h Parser.cpp Parser.h XMLAttribute.cpp XMLAttribute.h XMLElement.cpp XMLElement.h JSValue.cpp JSValue.h JSObject.cpp JSObject.h JSArray.cpp JSArray.h JSPair.cpp JSPair.h JSNode.cpp JSNode.h Translator.cpp Translator.h ErrorHandler.cpp ErrorHandler.h)
add_executable(TKOM ${SOURCE_FILES})