#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

struct term {
	private:
		int exp, coeff;
	public:
		void set_exp(int exponent){ exp = exponent; }
		void set_coeff(int coefficient){ coeff = coefficient; }
};

class polynomial {
	private:
		unordered_map<int, int> terms; // The hashtable stores each term of the polynomial.
						// The key is the exponent, and the value is the coefficient.
	public:
		void add_term(int exp, int coeff){
			if ( terms.find(exp) == terms.end() ){ // If the term with that exponent doesn't exist,
				terms.emplace(exp, coeff); // Create the term in the hashtable.
			} else { // If the term with that exponent does exist,
				int new_coeff = coeff + terms.at(exp); // add the two coefficients,
				terms.erase(exp); // get rid of the current term,
				terms.emplace(exp, new_coeff); // and replace it with the new coefficient.
			}
		}
		int size(){ return terms.size(); }
		int get_coeff(int key){ return terms.at(key); }
		void print(){ // Prints out the polynomial in descending order.
			for (int i = this->size() - 1; i >= 0; i--){
				cout << this->get_coeff(i) << "x^" << i;
				if (i != 0) cout << " + ";
			} cout << endl;
		}
		list<term> sort_poly(){ // Uses the hashtable to create a sorted dynamic array that stores the same information.
			list<term> sorted_terms(this->size());
			
			for (int i = this->size() - 1; i >= 0; i--){
				term t; t.set_exp(i); t.set_exp(this->get_coeff(i));
				sorted_terms.push_back(t);
			}
			
			return sorted_terms;
		}
};

polynomial multiply(polynomial p1, polynomial p2){
	polynomial p3;
	
	for (int i = 0; i < p1.size(); i++){
		for (int j = 0; j < p2.size(); j++){
			int new_coeff = p1.get_coeff(i) * p2.get_coeff(j); // The coefficients of two terms are multiplied together,
			int new_exp = i + j; // but the exponents of two terms are simply added together.
			p3.add_term(new_exp, new_coeff);
		}
	}
	
	return p3;
};
