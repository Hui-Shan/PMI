// tt4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../std_lib_facilities.h"

int main()
{	
	vector<string> words_to_bleep;
	words_to_bleep.push_back("slow");
	words_to_bleep.push_back("results");

	vector<string> words;
	for (string temp; cin >> temp;)
		words.push_back(temp);

	cout << "Bleeped out version: \n";
	for (int i = 0; i < words.size(); i++)
	{
		string word_out = words[i];
		for (size_t j = 0; j < words_to_bleep.size(); j++)
		{
			if (words[i] == words_to_bleep[j])
				word_out = "BLEEP";				
		}
		cout << word_out << " ";
	}

	return 0;
}

