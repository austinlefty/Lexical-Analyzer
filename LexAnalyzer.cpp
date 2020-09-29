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

public:

	LexAnalyzer(istream& infile)
	{
		while (!infile.eof())
		{
			infile >> l;
			lexemes.push_back(l);
			cout << l << " ";

			infile >> t;
			lexemes.push_back(t);
			cout << t << endl;
		}
	}

	void scanFile(istream& infile, ostream& outfile)
	{

	}
};


int main()
{
	string txt;
	ifstream input;
	//cout << "Enter the name of the token/lexeme pairs file (_____.txt): "; //UNCOMMENT LATER
	//cin >> txt; //UNCOMMENT LATER
	txt = "tokenlexemedata.txt"; //JUST FOR NOW //DELETE LATER

	input.open(txt);

	if (input.fail())
	{
		cerr << "Error: File Not Found" << endl;
		exit(1);
	}

	new LexAnalyzer(input);

	return (0);
}
