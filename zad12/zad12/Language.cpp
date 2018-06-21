#include"Language.h"
#include<iostream>
#include<fstream>
#include <string>

void Language::read(string ifilename)
{
	ifstream ifile;
	ifile.open(ifilename.c_str(), ios::in);
	if (!ifile.is_open())
		throw "Cannot open input file";

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
				letters[c]++;
			}
		}
	}
	ifile.close();
}

void Language::compare(map<string,string> name)
{
	for (map<string, string>::iterator it=name.begin();it!=name.end();it++)
	{
		ifstream ifile;
		ifile.open(it->second.c_str(), ios::in);
		if (!ifile.is_open())
			throw "Cannot open model file " + it->second;
		map<char,long int> tmp;
		char a;
		int x;
		for (char l = 'a'; l < 'z'; l++)
		{
			ifile >> a;
			ifile >> x;
			if (a == l)
				tmp.insert(pair<char, int>(l, x));
			else
				throw "Wrong model file " + it->second;
		}
		ifile.close();
		double dif[26], sdif = 0;
		long unsigned int sum = 0, sum_m = 0;
		for (char l = 'a'; l < 'z'; l++)
		{
			sum += letters[l];
			sum_m += tmp[l];
		}
		int b = 0;
		for (char l = 'a'; l < 'z'; l++)
		{
			dif[b] =sqrt(pow( (static_cast<double>(letters[l]) / sum) - (static_cast<double>(tmp[l]) / sum_m),2));
			b++;
		}
		for (int i = 0; i < 25; i++)
		{
			sdif += dif[i];
		}
		_dif[it->first] = sdif / 26;
	}
}

void Language::result()
{
	double x = _dif.begin()->second;
	for (map<string, double>::iterator it = _dif.begin(); it != _dif.end(); it++)
	{
		if (it->second < x)
			x = it->second;
	}
	map<string, double>::iterator res;
	for (map<string, double>::iterator it = _dif.begin(); it != _dif.end(); it++)
	{
		if (it->second == x)
		{
			res = it;
			break;
		}
	}
	cout << "Wykryty jezyk: " << res->first << "\t" << res->second * 100 << " % roznicy" << endl;
	cout << "Pozostle: \n";
	for (map<string, double>::iterator it = _dif.begin(); it != _dif.end(); it++)
	{
		cout << it->first << "\t" << it->second * 100 << " %\n";
	}

}