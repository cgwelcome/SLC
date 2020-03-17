#include "TestConfig.hpp"
#include "TestUtil.hpp"
#include "catch.hpp"
#include <fstream>

TEST_CASE("client process", "[client]") {
  Client client = createClient();

  SECTION("preprocess step") {
    client.setBreakPoint(Client::VerifyName);
    SECTION("accept") { REQUIRE(client.compile({"good.java"})); }
    SECTION("accept with folder") {
      REQUIRE(client.compile({"folder/good.java"}));
    }
    SECTION("reject") { REQUIRE_FALSE(client.compile({"foo.txt"})); }
    SECTION("reject first dot") {
      REQUIRE_FALSE(client.compile({"bar.foo.java"}));
    }
  }

  SECTION("a1") {
    SECTION("error VerifyName") {
      client.setBreakPoint(Client::VerifyName);
      for (const auto &fileName : a1ErrorPreprocess) {
        SECTION(fileName) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(1, {fileName})));
        }
      }
    }

    SECTION("error scan") {
      client.setBreakPoint(Client::Scan);
      for (const auto &fileName : a1ErrorScan) {
        SECTION(fileName) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(1, {fileName})));
        }
      }
    }

    SECTION("error parse") {
      client.setBreakPoint(Client::Parse);
      for (const auto &fileName : A1ErrorParse) {
        SECTION(fileName) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(1, {fileName})));
        }
      }
    }

    SECTION("accept") {
      for (const auto &fileName : a1Valid) {
        SECTION(fileName) {
          REQUIRE(client.compile(createMarmosetTest(1, {fileName})));
        }
      }
    }
  }

  SECTION("a2") {
    SECTION("parse-error") {
      client.setBreakPoint(Client::Parse);
      for (const auto &group : a2ErrorParse) {
        SECTION(group[0]) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(2, group)));
        }
      }
    }

    SECTION("fileheader-error") {
      client.setBreakPoint(Client::FileHeader);
      for (const auto &group : a2ErrorFileHeader) {
        SECTION(group[0]) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(2, group)));
        }
      }
    }

    SECTION("package-error") {
      client.setBreakPoint(Client::PackageTree);
      for (const auto &group : a2ErrorPackage) {
        SECTION(group[0]) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(2, group)));
        }
      }
    }
    SECTION("reject") {
      for (const auto &group : a2Error) {
        SECTION(group[0]) {
          REQUIRE(client.compile(createMarmosetTest(2, group)));
        }
      }
    }

    SECTION("accept") {
      for (const auto &group : a2Valid) {
        SECTION(group[0]) {
          REQUIRE(client.compile(createMarmosetTest(2, group)));
        }
      }
    }
  }

  SECTION("a3") {
    SECTION("accept") {
      for (const auto &group : a3Valid) {
        SECTION(group[0]) {
          REQUIRE(client.compile(createMarmosetTest(3, group)));
        }
      }
    }

    SECTION("parse-error") {
      client.setBreakPoint(Client::Parse);
      for (const auto &group : a3ErrorParse) {
        SECTION(group[0]) {
          REQUIRE_FALSE(client.compile(createMarmosetTest(3, group)));
        }
      }
    }
  }

  SECTION("a4") {
    SECTION("accept") {
      for (const auto &group : a4Valid) {
        SECTION(group[0]) {
          REQUIRE(client.compile(createMarmosetTest(4, group)));
        }
      }
    }
  }

  SECTION("multiple files") {
    std::vector<std::string> files{
        testDataDir +
            "/java/a2/J1_3_PackageDecl_SamePackageAndClassName/A/A.java",
        testDataDir +
            "/java/a2/J1_3_PackageDecl_SamePackageAndClassName/Main.java",
    };
    REQUIRE(client.compile(files));
  }

  SECTION("stdlib") {
    std::vector<std::string> files{
        testDataDir +
        "/java/a2/J1_3_PackageExists_AsPrefix_External/Main.java"};
    REQUIRE(client.compile(files));
  }
}
