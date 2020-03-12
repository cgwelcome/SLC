#include "EnvPackageTree.hpp"
#include "TestConfig.hpp"
#include "TestUtil.hpp"
#include "catch.hpp"

TEST_CASE("Package Node", "[PackageNode]") {
  Env::PackageNode root{Env::PackageNode::Type::Global};
  Env::PackageNode *foo = root.update(Env::PackageNode::Type::Package, "foo");
  Env::PackageNode *bar = foo->update(Env::PackageNode::Type::Package, "bar");
  bar->update(Env::PackageNode::Type::JoosType, "canary");

  SECTION("Node will reject duplicates") {
    Env::PackageNode *node;
    node = foo->update(Env::PackageNode::Type::JoosType, "bar");
    REQUIRE(node == nullptr);
    node = foo->update(Env::PackageNode::Type::Package, "bar");
    REQUIRE(node != nullptr);
    node = bar->update(Env::PackageNode::Type::Package, "canary");
    REQUIRE(node == nullptr);
    node = bar->update(Env::PackageNode::Type::JoosType, "canary");
    REQUIRE(node == nullptr);
    node = bar->update(Env::PackageNode::Type::JoosType, "canary");
    REQUIRE(node == nullptr);
  }
}

TEST_CASE("Package Tree", "[PackageTreeLookup]]") {
  Env::PackageTree Tree;

  SECTION("Basic lookup") {
    Env::FileHeader CanaryHeader({}, {Env::Type::Class, "canary"});
    Env::FileHeader BarHeader({}, {Env::Type::Class, "bar"});
    REQUIRE(Tree.update({"foo", "bar"}, CanaryHeader));
    REQUIRE_FALSE(Tree.update({"foo"}, BarHeader));
    REQUIRE(Tree.findHeader({"foo", "bar", "canary"}) == &CanaryHeader);
    REQUIRE(Tree.findHeader({"foo"}) == nullptr);
  }

  SECTION("Single File") {
    Env::FileHeader AHeader({}, {Env::Type::Class, "A"});
    Env::FileHeader MainHeader({}, {Env::Type::Class, "Main"});
    REQUIRE(Tree.update({"Main", "B"}, AHeader));
    REQUIRE(Tree.update({}, MainHeader));
  }
}

TEST_CASE("Package Tree Visitor", "[PackageTreeVisitor]") {
  Client Client = createClient();
  std::unique_ptr<AST::Start> Root = Client.buildAST(
      TestDataDir + "/java/a2/J1_3_PackageClashWithType_Linked_Mutated/javax/"
                    "swing/tree/TreeNode.java");
  Env::PackageTreeVisitor Visitor;
  Root->accept(Visitor);
  REQUIRE(Visitor.getPackagePath() ==
          std::vector<std::string>{"javax", "swing", "tree"});
}
