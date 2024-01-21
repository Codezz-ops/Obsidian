#include "common.hpp"
#include "helper/flags.hpp"
#include "lexer/lexer.hpp"

#include "compiler/chunk.hpp"
#include "compiler/debug/debug.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  // flags(argc, argv);

  // const char* filePath = argv[1];
  // std::unique_ptr<char[]> src = readfile(filePath);
  // Lexer tokens(src.get(), filePath);
  // std::unique_ptr<Lexer::Token> token = tokens.scanToken();

  // while (token->kind != TokenKind::END_OF_FILE) {
  //     std::cout << token->kind << std::endl;
  //     token = tokens.scanToken();
  // }

  Chunk chunk;
  ChunkClass::initChunk(&chunk);

  int constant = ChunkClass::addConstant(&chunk, 1.2);
  ChunkClass::writeChunk(&chunk, OpCodes::OPConstant, 123);
  ChunkClass::writeChunk(&chunk, constant, 123);

  ChunkClass::writeChunk(&chunk, OpCodes::OPReturn, 123);

  Debug::dissassembleChunk(&chunk, "test chunk");

  ChunkClass::freeChunk(&chunk);

  return 0;
}
