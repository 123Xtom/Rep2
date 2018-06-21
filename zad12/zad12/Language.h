#pragma once
#include <map>
#include<vector>
using namespace std;
class Language
{
	map<char, int> letters;
	map<string, double> _dif;
public:
	Language(vector<string>& other_lang)
	{
		for (char l = 'a'; l < 'z'; l++)
			letters.insert(pair<char, int>(l, 0));
		for (int i = 0; i < other_lang.size(); i++)
			_dif.insert(pair<string, double>(other_lang[i], 0.0));

	}
	void result();
	void read(string ifile);
	void compare(map<string, string> name);
};