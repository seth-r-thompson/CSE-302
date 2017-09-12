#include <iostream>

using namespace std;

void permute(const string & str);
void permute(const string & str, int low, int high);

int main(void){
	int rc = -1;
	
	string s = "abc"; // Test string.
	
	permute(s);
	rc = 0; // If the permute() method works, we'll return 0.
	
	return rc;
}

/**
* @param str The string literal that is passed to the method. The rvalue str can't be modified by the method.
*/
void permute(const string & str){
	int low = 0; // The starting index of the string.
	int high = str.length() / sizeof(char); // The number of characters in str.
                                          // Different computers may have different byte sizes for a char,
                                          // So divide the number of bytes by the computer's char size
                                          // to find the number of characters.
	
	permute(str, low, high); // Calls the function to find the permutations of the string.
}

/**
* @param str The string literal that is passed to the method.
* @param low The starting index the method begins to create permutations at.
* @param high The number of chars in str, used to avoid array index out of bounds exceptions.
*/
void permute(const string & str, int low, int high){
	string temp = str; // Creates a temporary string out of the string literal that can be modified.
	
	if (low == high) cout << str << endl; // If the starting index is the same as the length of the string,
                                        // then the method has finished finding permutations of the string,
                                        // so we print the str to the console.
                                        // This is the end case of our recursive method.
	else {
		for (int i = low; i < high; i++){ 
			swap(temp[low], temp[i]); // Swaps the character at the starting index with the char at the current index.
                                // This means it'd be swapping 0&0, then 0&1, then 0&2, etc.
                                // Thus it's swapping this beginning character with every other character in the string.
                                // We don't want to print to the console here, however, because it will end up finding
                                // some permutations multiple times (swapping 0&0 will just print the string, for example).
                                
			permute(temp, low+1, high); // Now recursion is used to find the permutations at all of the strings that just got swapped.
                                  // Start at low + 1 index so that the permutations just done with low aren't repeated again. 
                                  // Eventually this will find all the possible permutations of the string.
		}	
	}
}
