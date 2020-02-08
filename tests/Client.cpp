#include "Client.hpp"
#include "Config.hpp"
#include "TestConfig.hpp"
#include "catch.hpp"
#include <fstream>
#include <sstream>

TEST_CASE("client detects JoosW", "[client]") {
  Parse::DFA Parser;
  std::ifstream ParserStream;
  ParserStream.open(JoosLRFile);

  ParserStream >> Parser;

  //SECTION("scanner accept") {
    //std::ostringstream OStream;
    //std::ifstream JoosStream;
    //JoosStream.open(TestDataDir + "/marmoset/J1_publicclasses.java");
    //REQUIRE(Client::scan(JoosStream, OStream));

    //std::ifstream TokenStream;
    //TokenStream.open(TestDataDir + "/grammar/J1_publicclasses.token");
    //std::string TokenString(std::istreambuf_iterator<char>(TokenStream), {});
    //REQUIRE(TokenString == OStream.str());
  //}

  SECTION("parser accept") {
    std::ifstream TokenStream;
    TokenStream.open(TestDataDir + "/grammar/J1_publicclasses.token");
    std::cout << Parser.buildTree();
    REQUIRE(Client::parse(Parser, TokenStream));
  }

  //SECTION("scanner rejects") {
    //std::ifstream JoosStream;
    //JoosStream.open(TestDataDir +
                    //"/marmoset/Je_1_NonJoosConstructs_Unicode.java");
    //REQUIRE(!Client::scan(JoosStream));
  //}

  SECTION("parser rejects") {
    std::ifstream TokenStream;
    TokenStream.open(TestDataDir + "/grammar/SimpleReject.token");
    REQUIRE(!Client::parse(Parser, TokenStream));
    TokenStream.clear();
    Parser.clear();
    TokenStream.open(TestDataDir + "/grammar/MissingClassBody.token");
    REQUIRE(!Client::parse(Parser, TokenStream));
  }

  //SECTION("preprocessor parser reject") {
    //std::ifstream JoosStream;
    //JoosStream.open(TestDataDir +
                    //"/marmoset/Je_1_NonJoosConstructs_Volatile.java");
    //REQUIRE(!Client::scan(JoosStream));
  //}
}