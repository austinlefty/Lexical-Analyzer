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
	vector<string> lexemes;
	vector<string> tokens;
	map<string, string> tokenmap;

public:

	LexAnalyzer(ifstream& infile)
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
		{
			tokenmap[lexemes.at(i)] = tokens.at(i);
		}

		tokens.clear();
		lexemes.clear();
	}

	void scanFile(istream& infile, ostream& outfile)
	{

	}

	void readLine(ifstream& infile)
	{
		string line;
		string letter;
		string temp;

		while (getline(infile, line))
		{
			for (unsigned i = 0; i < line.length(); i++)
			{
				letter = line.at(i);
				temp.append(letter);

				for (auto it = tokenmap.begin(); it != tokenmap.end(); ++it)
				{
					cout << it->first << " => " << it->second << endl;
					if (it->first.compare(temp) == 0)
					{
						cerr << "MATCH FOUND!"; //Test to see if loop finds match to source
					}
				}
			}
		}
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

	la.readLine(input);
	la.scanFile(input, output);

	return (0);
}
