
#include "Tokenizer.h"
#include "Parser.h"
#include "Interpreter.h"

int main()
{
	//string source = "a = true and false or 23 >= (5.2 * pi) \n if a then print \"pene\" else print a";
	string source = "a = 15 b = 16 print a print b a = b print a";

	Tokenizer tokenizer(source.c_str());


	tokenizer.tokenize();

	for (Token& token : tokenizer.tokens)
	{
		cout << token << endl;
	}

	Parser parser;

	Node* root = parser.parse_program(&tokenizer.tokens);

	cout << *root << endl;

	Interpreter interpreter;

	interpreter.interpret(root);

	return 0;
}