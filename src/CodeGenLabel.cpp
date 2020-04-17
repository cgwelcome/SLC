#include "CodeGenLabel.hpp"
#include "EnvTypeDeclaration.hpp"
#include <sstream>

namespace CodeGen {

LabelGenerator::LabelGenerator(std::vector<std::string> path)
    : path(std::move(path)) {}


//a general comment on the structure of the labels
/*
In order to encompass all potential names, we need an escape key
Just like how the combination of quotation marks and escape sequence allows us to express the sum of all strings
Having a dedicated delimiter/escape sequence allows us to avoid collisions
*/

//Underscore that does not denote member reference always comes in pairs;
// a pair of underscore implies it is directly from the string of the class name, where as a single underscore reliably indicates memeber relationship
std::string sanitizedLabelName(const std::string& reference, char esc = '_'){
	std::string lname = "";
	for(unsigned i=0; i<reference.length(); i++){
		if(reference[i] == esc){
			lname += esc;
		}
		lname += reference[i];
	}
	return lname;
}


void LabelGenerator::generateMethod(Env::Method &method) {
  //method.label = path.at(0) + '.' + method.identifier;

	std::ostringstream str;
	str<<method.offset;

	std::string className = sanitizedLabelName(path.at(0));
	std::string offset = str.str();

	method.label = className + '_' + offset;
}


void LabelGenerator::generateConstructor(Env::Constructor& constructor){	
	std::string className = sanitizedLabelName(path.at(0));
	std::string argChain = "";
	const auto &args = constructor.args;
	for(const auto &arg: args){
		std::string sargs = sanitizedLabelName(arg.declare->identifier);
		argChain += '_' + sargs;
	}
	
	constructor.label = className + argChain;
}



} // namespace CodeGen
