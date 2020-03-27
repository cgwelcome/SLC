#ifndef ENJOOSBODY_HPP
#define ENJOOSBODY_HPP

#include "ASTVisitor.hpp"
#include <set>
#include <vector>

namespace Env {

enum class Modifier {
  Public,
  Protected,
  Static,
  Abstract,
  Final,
  Native,
};

const std::unordered_map<std::string, Modifier> nameModifier{
    {"PUBLIC", Modifier::Public}, {"PROTECTED", Modifier::Protected},
    {"STATIC", Modifier::Static}, {"ABSTRACT", Modifier::Abstract},
    {"FINAL", Modifier::Final},   {"NATIVE", Modifier::Native},
};

const std::unordered_map<Modifier, std::string> modifierName{
    {Modifier::Public, "PUBLIC"}, {Modifier::Protected, "PROTECTED"},
    {Modifier::Static, "STATIC"}, {Modifier::Abstract, "ABSTRACT"},
    {Modifier::Final, "FINAL"},   {Modifier::Native, "NATIVE"},
};

enum class VariableType {
  SimpleType,
  ArrayType,
};

const std::unordered_map<VariableType, std::string> variableTypeName{
    {VariableType::SimpleType, "SimpleType"},
    {VariableType::ArrayType, "ArrayType"},
};

struct VariableDescriptor {
  VariableType variableType;
  std::vector<std::string> dataType;
  VariableDescriptor() = default;
  VariableDescriptor(VariableType variableType,
                     std::vector<std::string> dataType);
  bool operator==(const VariableDescriptor &variableDescriptor) const;
};
std::ostream &operator<<(std::ostream &stream,
                         const VariableDescriptor &variableDescriptor);

struct JoosField {
  std::set<Modifier> modifiers;
  VariableDescriptor variableDescriptor;
  std::string identifier;
  const AST::FieldDeclaration *astNode;
  JoosField() = default;
  JoosField(std::set<Modifier> modifiers, VariableDescriptor descriptor,
            std::string identifier, const AST::FieldDeclaration *astNode);
  bool operator==(const JoosField &joosField) const;
};
std::ostream &operator<<(std::ostream &stream, const JoosField &joosField);

struct JoosMethod {
  std::set<Modifier> modifiers;
  VariableDescriptor returnType;
  std::string identifier;
  std::vector<VariableDescriptor> args;
  const AST::MethodDeclaration *astNode;
  JoosMethod() = default;
  JoosMethod(std::set<Modifier> modifiers, VariableDescriptor returnType,
             std::string identifier, std::vector<VariableDescriptor> args,
             const AST::MethodDeclaration *astNode);
  bool operator==(const JoosMethod &joosMethod) const;
};
std::ostream &operator<<(std::ostream &stream, const JoosMethod &joosMethod);

struct JoosConstructor {
  std::set<Modifier> modifiers;
  std::string identifier;
  std::vector<VariableDescriptor> args;
  const AST::ConstructorDeclaration *astNode;
  JoosConstructor(std::set<Modifier> modifiers, std::string identifier,
                  std::vector<VariableDescriptor> args,
                  const AST::ConstructorDeclaration *astNode);
  bool operator==(const JoosConstructor &joosConstructor) const;
};
std::ostream &operator<<(std::ostream &stream,
                         const JoosConstructor &joosConstructor);

class JoosBody {
public:
  const std::vector<JoosField> &getFields() const;
  bool addField(JoosField joosField);

  const std::vector<JoosMethod> &getMethods() const;
  bool addMethod(JoosMethod joosMethod);

  const std::vector<JoosConstructor> &getConstructors() const;
  bool addConstructor(JoosConstructor joosConstructor);

  void setAbstract();

private:
  friend std::ostream &operator<<(std::ostream &stream,
                                  const JoosBody &joosBody);
  std::vector<JoosMethod> methods;
  std::vector<JoosField> fields;
  std::vector<JoosConstructor> constructors;
};
std::ostream &operator<<(std::ostream &stream, const JoosBody &joosBody);

class JoosBodyVisitor : public AST::Visitor {
public:
  void visit(const AST::Start &start) override;
  void visit(const AST::ClassDeclaration &decl) override;
  void visit(const AST::InterfaceDeclaration &decl) override;
  void visit(const AST::FieldDeclaration &field) override;
  void visit(const AST::MethodDeclaration &decl) override;
  void visit(const AST::ConstructorDeclaration &decl) override;
  std::vector<JoosField> getJoosFields();
  std::vector<JoosMethod> getJoosMethods();
  std::vector<JoosConstructor> getJoosConstructors();

private:
  std::vector<JoosField> fields;
  std::vector<JoosMethod> methods;
  std::vector<JoosConstructor> constructors;
};

} // namespace Env

#endif // ENJOOSBODY_HPP