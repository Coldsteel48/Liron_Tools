#pragma once

#include <string>

struct StrDict 
{
	std::string origin;
	std::string target;

	StrDict(const std::string& in_origin, const std::string& in_target)
	{
		origin = std::move(in_origin);
		target = std::move(in_target);
	}

	static void CreateDictionary(std::vector<StrDict>& in_out_dictionary)
	{
		in_out_dictionary.reserve(20);

		in_out_dictionary.push_back(StrDict("_"," "));

		in_out_dictionary.push_back(StrDict("Its ", "It\'s "));
		in_out_dictionary.push_back(StrDict("its ", "it\'s "));

		in_out_dictionary.push_back(StrDict("Im ", "I\'m "));
		in_out_dictionary.push_back(StrDict("Id ", "I\'d "));
		in_out_dictionary.push_back(StrDict("Ive ", "I\'ve "));
		in_out_dictionary.push_back(StrDict("Ill ", "I\'ll "));

		in_out_dictionary.push_back(StrDict("Therell ", "There\'ll "));
		in_out_dictionary.push_back(StrDict("therell ", "there\'ll "));

		in_out_dictionary.push_back(StrDict("Dont ", "Don\'t "));
		in_out_dictionary.push_back(StrDict("dont ", "don\'t "));

		in_out_dictionary.push_back(StrDict("Lets ", "Let\'s "));
		in_out_dictionary.push_back(StrDict("lets ", "let\'s "));

		in_out_dictionary.push_back(StrDict("Weve ", "We\'ve "));
		in_out_dictionary.push_back(StrDict("weve ", "we\'ve "));

		//in_out_dictionary.push_back(StrDict("Were ", "We\'re "));
		//in_out_dictionary.push_back(StrDict("were ", "we\'re "));

		in_out_dictionary.push_back(StrDict("Cant ", "Can\'t "));
		in_out_dictionary.push_back(StrDict("cant ", "can\'t "));
		
		in_out_dictionary.push_back(StrDict("Wont ", "Won\'t "));
		in_out_dictionary.push_back(StrDict("wont ", "won\'t "));

		in_out_dictionary.push_back(StrDict("Shouldnt ", "Shouldn\'t "));
		in_out_dictionary.push_back(StrDict("shouldnt ", "shouldn\'t "));

		in_out_dictionary.push_back(StrDict("Wouldnt ", "Wouldn\'t "));
		in_out_dictionary.push_back(StrDict("wouldnt ", "wouldn\'t "));

		in_out_dictionary.push_back(StrDict("Couldnt ", "Couldn\'t "));
		in_out_dictionary.push_back(StrDict("couldnt ", "couldn\'t "));

		in_out_dictionary.push_back(StrDict("Wasnt ", "Wasn\'t ")); 
		in_out_dictionary.push_back(StrDict("wasnt ", "wasn\'t "));

		in_out_dictionary.push_back(StrDict("Shell ", "She\'ll "));
		in_out_dictionary.push_back(StrDict("shell ", "she\'ll "));

		in_out_dictionary.push_back(StrDict("Shes ", "She\'s "));
		in_out_dictionary.push_back(StrDict("shes ", "she\'s "));

		in_out_dictionary.push_back(StrDict("Hes ", "He\'s "));
		in_out_dictionary.push_back(StrDict("hes ", "he\'s "));

		in_out_dictionary.push_back(StrDict("Heres ", "Here\'s "));
		in_out_dictionary.push_back(StrDict("heres ", "here\'s "));

		in_out_dictionary.push_back(StrDict("thats ", "that\'s "));
		in_out_dictionary.push_back(StrDict("Thats ", "That\'s "));

		in_out_dictionary.push_back(StrDict("Whats ", "What\'s "));
		in_out_dictionary.push_back(StrDict("whats ", "what\'s "));

		in_out_dictionary.push_back(StrDict("Youll ", "You\'ll "));
		in_out_dictionary.push_back(StrDict("youll ", "you\'ll "));

		in_out_dictionary.push_back(StrDict("Youre ", "You\'re "));
		in_out_dictionary.push_back(StrDict("youre ", "you\'re "));

		in_out_dictionary.push_back(StrDict("theres ", "there\'s "));
		in_out_dictionary.push_back(StrDict("Theres ", "There\'s "));

		in_out_dictionary.push_back(StrDict("Youve", "You\'ve"));
		in_out_dictionary.push_back(StrDict("youve", "you\'ve"));

		in_out_dictionary.push_back(StrDict("Whered", "Where\'d"));
		in_out_dictionary.push_back(StrDict("whered", "where\'d"));

		in_out_dictionary.push_back(StrDict("Havent", "Haven\'t"));
		in_out_dictionary.push_back(StrDict("havent", "haven\'t"));

		in_out_dictionary.push_back(StrDict("Hasnt", "Hasn\'t"));
		in_out_dictionary.push_back(StrDict("hasnt", "hasn\'t"));

		in_out_dictionary.push_back(StrDict("Theyre", "They\'re"));
		in_out_dictionary.push_back(StrDict("theyre", "they\'re"));

		in_out_dictionary.push_back(StrDict("Theyve", "They\'ve"));
		in_out_dictionary.push_back(StrDict("theyve", "they\'ve"));

		in_out_dictionary.push_back(StrDict(" (Q)", "?"));
		in_out_dictionary.push_back(StrDict(" (q)", "?"));
	}
};
