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
#include <map>
using namespace std;

class LexAnalyzer
{
private:
	vector<string> lexemes;
	vector<string> tokens;
	map<string, string> tokenmap;

	string l, t;

	void enterPairFile()
	{

	}

public:

	LexAnalyzer(ifstream& infile)
	{
		while (!infile.eof())
		{
			infile >> t;
			tokens.push_back(t);

			infile >> l;
			lexemes.push_back(l);
		}

		for (int i = 0; i < 5; i++)
		{
			tokenmap[lexemes.at(i)] = tokens.at(i);
		}
	}

	void scanFile(istream& infile, ostream& outfile)
	{

	}
};


int main()
{
	string txt;
	ifstream pairs;
	ifstream input;
	ofstream output;
	//cout << "Enter the name of the token/lexeme pairs file (_____.txt): "; //UNCOMMENT LATER
	//cin >> txt; //UNCOMMENT LATER
	txt = "tokenlexemedata.txt"; //JUST FOR NOW //DELETE LATER

	pairs.open(txt);

	if (pairs.fail())
	{
		cerr << "Error: File Not Found" << endl;
		exit(1);
	}

	LexAnalyzer la(pairs);

	//cout << "Enter the name of the source code file (_____.txt): "; //UNCOMMENT LATER
	//cin >> txt; //UNCOMMENT LATER
	txt = "sourcecode.txt"; //JUST FOR NOW //DELETE LATER

	input.open(txt);

	if (input.fail())
	{
		cerr << "Error: File Not Found" << endl;
		exit(1);
	}

	//cout << "Enter the name of the empty output file (_____.txt): "; //UNCOMMENT LATER
	//cin >> txt; //UNCOMMENT LATER
	txt = "outputcode.txt"; //JUST FOR NOW //DELETE LATER

	output.open(txt);

	if (output.fail())
	{
		cerr << "Error: File Not Found" << endl;
		exit(1);
	}

	la.scanFile(input, output);

	return (0);
}
