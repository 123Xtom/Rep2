#include"Language.h"
#include<iostream>
#include<string>
#include<fstream>
#include<map>
using namespace std;

void makeModel(string ifilename, string ofilename)
{
	ifstream ifile;
	ofstream ofile;
	map<char, int> tmp;
	for (char l ='a'; l < 'z'; l++)
		tmp.insert(pair<char, int>(l, 0));

	ifile.open(ifilename.c_str(), ios::in);
	if (!ifile.is_open())
		throw "Cannot open input file to model";

	string word;
	char c;
	while (!ifile.eof())
	{
		ifile >> word;
		for (int i = 0; i < word.size(); i++)
		{
			c = word[i];
			if (c >= 65 && c <= 90)
				c += 32;
			if (c >= 97 && c <= 122)
			{
				tmp[c]++;
			}
		}
	}
	ifile.close();

	ofile.open(ofilename, ios::trunc);
	if (!ofile.is_open())
		throw "Cannot open output file for model";
	for (map<char, int>::iterator it = tmp.begin(); it != tmp.end(); it++)
	{
		ofile << it->first << "\t" << it->second << endl;
	}
	ofile.close();
}

int main()
{
	try
	{
		makeModel("input_eng.txt", "model_eng.txt");
		makeModel("input_pol.txt", "model_pol.txt");
		makeModel("input_es.txt", "model_es.txt");
		makeModel("input_fr.txt", "model_fr.txt");
		makeModel("input_de.txt", "model_de.txt");
		vector<string> langs = { "Polski","Angielski", "Hiszpanski", "Francuski", "Niemiecki" };
		Language A(langs);
		A.read("text_pol.txt");
		vector<string> input = { "model_pol.txt" , "model_eng.txt", "model_es.txt", "model_fr.txt" , "model_de.txt" };
		map<string, string> mapa;
		for (unsigned int i=0;i<langs.size();i++)
		{
			mapa.insert(pair<string, string>(langs[i], input[i]));
		}
		A.compare(mapa);
		A.result();
	}
	catch(string f)
	{
		cerr << f << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}