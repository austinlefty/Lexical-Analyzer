/*
Name: Austin Krause
Homework: Compiler Part 1: Lexical Analysis
Class: CSCE 306
Description: This program reads in a source code file and
creates a corresponding lexeme file for the source code file.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <map>
using namespace std;

class LexAnalyzer
{
private:
	vector<string> lexemes; //Vector of lexemes in source code
	vector<string> tokens; //Vector of tokens in source code
	map<string, string> tokenmap; //Map of all pairs

public:

	LexAnalyzer(ifstream& infile) //Populates the map
	{
		string l, t;

		while (!infile.eof())
		{
			infile >> t;
			tokens.push_back(t);

			infile >> l;
			lexemes.push_back(l);
		}

		for (int i = 0; i < lexemes.size(); i++)
			tokenmap[lexemes.at(i)] = tokens.at(i);

		tokens.clear();
		lexemes.clear();
	}

	void scanFile(ifstream& infile, ostream& outfile) //Checks every token to find matches with source
	{
		string line;
		string letter;
		string temp;
		int count = 0;

		while (getline(infile, line))
		{
			for (unsigned i = 0; i < line.length(); i++)
			{
				letter = line.at(i); //Takes reference letter from line from source
				if (letter != " ")
				{
					temp.append(letter); //Adds letter to string
				}

				for (auto it = tokenmap.begin(); it != tokenmap.end(); ++it)
				{
					if (it->first.compare(temp) == 0)
					{
						if (temp.find('\"') != string::npos) //If it finds quotation marks, it'll loop until another one is found
						{
							temp = ""; //Resets string
							int count = 1;
							do
							{
								letter = line.at(i + count);
								temp.append(letter);
								count++;
							} while (letter != "\""); //End of string
							addStr(temp);
							temp = ""; //Resets string
							i = i + count;
						}

						if (temp == "main") //Checks if main will be keyword
						{
							if ((i < 4 || (line.at(i - 4 == ' ') && !isalpha(line.at(i - 4))))) //Checks if any other characters are connected
							{
								if (i < line.length() - 1) //Checks if there is a character after the last one
								{
									if (!isalpha(line.at(i + 1))) //Checks if character is not a letter 
									{
										addMain();
										temp = ""; //Resets string
									}
								}
								else //Skips check and makes main a keyword 
								{
									addMain();
									temp = ""; //Resets string
								}
							}
							else //Assigns main and other proeceeding characters as an identifier
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter); //Adds extra letters to the indentifier
								addIdentifier(temp);
								temp = ""; //Resets string
							}
						}

						//For other keywords, the above comments are identical
						if (temp == "begin")
						{
							if ((i < 5 || (line.at(i - 5 == ' ') && !isalpha(line.at(i - 5)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addBegin();
										temp = "";
									}
								}
								else
								{
									addBegin();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						if (temp == "end")
						{
							if ((i < 3 || (line.at(i - 3 == ' ') && !isalpha(line.at(i - 3)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addEnd();
										temp = "";
									}
								}
								else
								{
									addEnd();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						if (temp == "else")
						{
							if ((i < 4 || (line.at(i - 4 == ' ') && !isalpha(line.at(i - 4)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addElse();
										temp = "";
									}
								}
								else
								{
									addElse();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						if (temp == "if")
						{
							if ((i < 2 || (line.at(i - 2 == ' ') && !isalpha(line.at(i - 2)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addIf();
										temp = "";
									}
								}
								else
								{
									addIf();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						if (temp == "input")
						{
							if ((i < 5 || (line.at(i - 5 == ' ') && !isalpha(line.at(i - 5)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addInput();
										temp = "";
									}
								}
								else
								{
									addInput();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						if (temp == "integer")
						{
							if ((i < 7 || (line.at(i - 7 == ' ') && !isalpha(line.at(i - 7)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addInteger();
										temp = "";
									}
								}
								else
								{
									addInteger();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						if (temp == "string")
						{
							if ((i < 6 || (line.at(i - 6 == ' ') && !isalpha(line.at(i - 6)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addString();
										temp = "";
									}
								}
								else
								{
									addString();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}
						if (temp == "loop")
						{
							if ((i < 4 || (line.at(i - 4 == ' ') && !isalpha(line.at(i - 4)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addLoop();
										temp = "";
									}
								}
								else
								{
									addLoop();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}
						if (temp == "output")
						{
							if ((i < 6 || (line.at(i - 6 == ' ') && !isalpha(line.at(i - 6)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addOutput();
										temp = "";
									}
								}
								else
								{
									addOutput();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}
						if (temp == "then")
						{
							if ((i < 4 || (line.at(i - 4 == ' ') && !isalpha(line.at(i - 4)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addThen();
										temp = "";
									}
								}
								else
								{
									addThen();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}
						if (temp == "var")
						{
							if ((i < 3 || (line.at(i - 3 == ' ') && !isalpha(line.at(i - 3)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addVar();
										temp = "";
									}
								}
								else
								{
									addVar();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}
						if (temp == "while")
						{
							if ((i < 5 || (line.at(i - 5 == ' ') && !isalpha(line.at(i - 5)))))
							{
								if (i < line.length() - 1)
								{
									if (!isalpha(line.at(i + 1)))
									{
										addWhile();
										temp = "";
									}
								}
								else
								{
									addWhile();
									temp = "";
								}
							}

							else
							{
								if (i < line.length() - 1)
									letter = line.at(i + 1);
								temp.append(letter);
								addIdentifier(temp);
								temp = "";
							}
						}

						//Punctuation Marks
						if (temp.find('(') != string::npos) //Checks if string has a character in it
						{
							addLParen();
							temp = ""; //Resets string

						//For other puncuation, the above comments are similar
						}
						else if (temp.find(')') != string::npos)
						{
							addRParen();
							temp = "";
						}
						else if (temp.find('=') != string::npos)
						{
							if (i < line.length() - 1) //Checks to see if there is another equal sign
								if (line.at(i + 1) == '=')
									addEQ(); //Adds it as ==
								else
									addAssign(); //Adds it as =
							temp = ""; //Resets string
						}
						else if (temp.find(',') != string::npos)
						{
							addComma();
							temp = "";
						}
						else if (temp.find(';') != string::npos)
						{
							addSemi();
							temp = "";
						}
						else if (temp.find('<') != string::npos)
						{
							if (i < line.length() - 1)
								if (line.at(i + 1) == '=')
									addLE();
								else
									addLT();
							temp = "";
						}
						else if (temp.find('>') != string::npos)
						{
							if (i < line.length() - 1)
								if (line.at(i + 1) == '=')
									addGT();
								else
									addGE();
							temp = "";
						}
						else if (temp.find('!') != string::npos)
						{
							if (i < line.length() - 1)
								if (line.at(i + 1) == '=')
									addNE();
								else
									addNot();
							temp = "";
						}
						else if (temp.find('+') != string::npos)
						{
							addPlus();
							temp = "";
						}
						else if (temp.find('-') != string::npos)
						{
							addMinus();
							temp = "";
						}
						else if (temp.find('*') != string::npos)
						{
							addMult();
							temp = "";
						}
						else if (temp.find('/') != string::npos)
						{
							addDiv();
							temp = "";
						}
						else if (temp.find('%') != string::npos)
						{
							addMod();
							temp = "";
						}
						else if (temp.find('&') != string::npos)
						{
							if (i < line.length() - 1)
								if (line.at(i + 1) == '&')
									addAnd();
								else
								{
									cerr << "Error: Illegal Character" << endl;
									exit(1);
								}
							temp = "";
						}
						else if (temp.find('|') != string::npos)
						{
							if (i < line.length() - 1)
								if (line.at(i + 1) == '|')
									addOr();
								else
								{
									cerr << "Error: Illegal Character" << endl;
									exit(1);
								}
							temp = "";
						}
					}
				}
			}
		}
	}

	//Adds token and lexeme to vectors
	void addIdentifier(string id)
	{
		tokens.push_back("t_id");
		lexemes.push_back(id);
	}
	void addStr(string str)
	{
		tokens.push_back("t_str");
		lexemes.push_back(str);
	}
	void addMain()
	{
		tokens.push_back(tokenmap.find("main")->second);
		lexemes.push_back("main");
	}
	void addBegin()
	{
		tokens.push_back(tokenmap.find("begin")->second);
		lexemes.push_back("begin");
	}
	void addEnd()
	{
		tokens.push_back(tokenmap.find("end")->second);
		lexemes.push_back("end");
	}
	void addElse()
	{
		tokens.push_back(tokenmap.find("else")->second);
		lexemes.push_back("else");
	}
	void addIf()
	{
		tokens.push_back(tokenmap.find("if")->second);
		lexemes.push_back("if");
	}
	void addInput()
	{
		tokens.push_back(tokenmap.find("input")->second);
		lexemes.push_back("input");
	}
	void addInteger()
	{
		tokens.push_back(tokenmap.find("integer")->second);
		lexemes.push_back("integer");
	}
	void addString()
	{
		tokens.push_back(tokenmap.find("string")->second);
		lexemes.push_back("string");
	}
	void addLoop()
	{
		tokens.push_back(tokenmap.find("loop")->second);
		lexemes.push_back("loop");
	}
	void addOutput()
	{
		tokens.push_back(tokenmap.find("output")->second);
		lexemes.push_back("output");
	}
	void addThen()
	{
		tokens.push_back(tokenmap.find("then")->second);
		lexemes.push_back("then");
	}
	void addVar()
	{
		tokens.push_back(tokenmap.find("var")->second);
		lexemes.push_back("var");
	}
	void addWhile()
	{
		tokens.push_back(tokenmap.find("while")->second);
		lexemes.push_back("while");
	}
	void addLParen()
	{
		tokens.push_back(tokenmap.find("(")->second);
		lexemes.push_back("(");
	}
	void addRParen()
	{
		tokens.push_back(tokenmap.find(")")->second);
		lexemes.push_back(")");
	}
	void addAssign()
	{
		tokens.push_back(tokenmap.find("=")->second);
		lexemes.push_back("=");
	}
	void addComma()
	{
		tokens.push_back(tokenmap.find(",")->second);
		lexemes.push_back(",");
	}
	void addSemi()
	{
		tokens.push_back(tokenmap.find(";")->second);
		lexemes.push_back(";");
	}
	void addLT()
	{
		tokens.push_back(tokenmap.find("<")->second);
		lexemes.push_back("<");
	}
	void addLE()
	{
		tokens.push_back(tokenmap.find("<=")->second);
		lexemes.push_back("<=");
	}
	void addGT()
	{
		tokens.push_back(tokenmap.find(">")->second);
		lexemes.push_back(">");
	}
	void addGE()
	{
		tokens.push_back(tokenmap.find(">=")->second);
		lexemes.push_back(">=");
	}
	void addEQ()
	{
		tokens.push_back(tokenmap.find("==")->second);
		lexemes.push_back("==");
	}
	void addNE()
	{
		tokens.push_back(tokenmap.find("!=")->second);
		lexemes.push_back("!=");
	}
	void addPlus()
	{
		tokens.push_back(tokenmap.find("+")->second);
		lexemes.push_back("+");
	}
	void addMinus()
	{
		tokens.push_back(tokenmap.find("-")->second);
		lexemes.push_back("-");
	}
	void addMult()
	{
		tokens.push_back(tokenmap.find("*")->second);
		lexemes.push_back("*");
	}
	void addDiv()
	{
		tokens.push_back(tokenmap.find("/")->second);
		lexemes.push_back("/");
	}
	void addMod()
	{
		tokens.push_back(tokenmap.find("%")->second);
		lexemes.push_back("%");
	}
	void addAnd()
	{
		tokens.push_back(tokenmap.find("&&")->second);
		lexemes.push_back("&&");
	}
	void addOr()
	{
		tokens.push_back(tokenmap.find("||")->second);
		lexemes.push_back("||");
	}
	void addNot()
	{
		tokens.push_back(tokenmap.find("!")->second);
		lexemes.push_back("!");
	}

	//Prints token/lexeme pairs and writes them to output file
	void printPairs(ostream& outfile)
	{
		for (int i = 0; i < lexemes.size(); i++)
		{
			cout << tokens.at(i) << " : " << lexemes.at(i) << endl; //Printing
			outfile << tokens.at(i) << " : " << lexemes.at(i) << endl; //Writing to output
		}
	}
};

int main()
{
	string txt;
	ifstream pairs;
	ifstream input;
	ofstream output;

	cout << "Enter the name of the token/lexeme pairs file (_____.txt): "; //Asks user for name of file
	cin >> txt;

	pairs.open(txt); //Opens file

	if (pairs.fail())
	{
		cerr << "Error: File Not Found" << endl; //Prints error and exits program if file is not found
		exit(1);
	}

	LexAnalyzer la(pairs);

	cout << "Enter the name of the source code file (_____.txt): "; //Asks user for name of file
	cin >> txt;

	input.open(txt); //Opens file

	if (input.fail())
	{
		cerr << "Error: File Not Found" << endl; //Prints error and exits program if file is not found
		exit(1);
	}

	cout << "Enter the name of the empty output file (_____.txt): "; //Asks user for name of file
	cin >> txt;
	txt = "outputcode.txt";

	output.open(txt); //Opens file

	if (output.fail())
	{
		cerr << "Error: File Not Found" << endl; //Prints error and exits program if file is not found
		exit(1);
	}

	la.scanFile(input, output); //References input file to scan
	la.printPairs(output); //Writes the pairs on output file

	return (0);
}
