#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<sstream>

const string DICTIONARY_PATH = ""; // The file location of the dictionary.
const string PERSONAL_DICTIONARY_PATH = ""; // The file location of the personal dictionary.

using namespace std;

class dictionary{
	private:
		// TODO: Replace with unordered_set because value is never used.
		unordered_map<string, string> word_list; // The key is the word in the dictionary.
	public:
		dictionary(){
			string word;
			
			// Add words too the hash table
			ifstream words(DICTIONARY_PATH);
			while (words >> word){
				word_list.emplace(word, word);
			}
			words.close();
			
			// Add personal words to the hash table
			ifstream personal_words(PERSONAL_DICTIONARY_PATH);
			while (personal_words >> word){
				if (word_list.find(word) == word_list.end()) word_list.emplace(word, word); // Only emplaces if it's not present
			}
			personal_words.close();
		}
		bool check_word(string word){
			if (word_list.find(word) != word_list.end()) return true;
			else return false;
		}
};

void spellcheck_add_char(string word, dictionary d){
	for(int i = 97; i < 26 + 97; i++){
		for (int j = 0; j < word.size() + 1; j++){
			string temp = word.substr(0, j) + (char) i + word.substr(j);
		
			if (d.check_word(temp)) {
				cout << temp << " ";
			}
		}
	}
}

void spellcheck_remove_char(string word, dictionary d){
	for(int i = 0; i < word.size(); i++){
		string temp = word.substr(0,i) + word.substr(i+1);
		
		if (d.check_word(temp)) {
				cout << temp << " ";
		}
	}	
}

void spellcheck_swap_char(string word, dictionary d){
	for (int i = 0; i < word.length() - 1; i++){
		string temp = word;
		swap(temp[i], temp[i+1]);
		
		if (d.check_word(temp)) {
			cout << temp + " ";
		}
	}
}

void spellcheck(string file_name){
	dictionary d;
	
	ifstream file(file_name);
	string word, line; int line_count;
	
	cout << "Found spelling errors in the following words: " << endl;
	while (getline(file,line)){ // Gets the next line in the file
		line_count++;
		istringstream current_line(line);
		
		while (current_line >> word){ // Gets the next word in the line
			if (!d.check_word(word)) {
				cout << "\t" << word << "\t (on line " << line_count << ")";
				cout << "\t Did you mean... ";
				spellcheck_add_char(word, d); spellcheck_remove_char(word, d); spellcheck_swap_char(word, d);
				cout << "?" << endl;
			}
		}
	}	
	
	file.close();
}

