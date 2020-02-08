#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ParseDFA.hpp"

namespace Client {
  bool preProcess(std::istream &Stream);
  bool scan(std::istream &IStream);
  bool scan(std::istream &IStream, std::ostream &OStream);
  bool parse(Parse::DFA &Parser, std::istream &IStream);
  bool parse(Parse::DFA &Parser, std::istream &IStream, std::ostream &OStream);
};

#endif // CLIENT_HPP