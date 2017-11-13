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
		unordered_map<int, int> terms;
	public:
		void add_term(int exp, int coeff){
			if ( terms.find(exp) == terms.end() ){ // Key doesn't exist
				terms.emplace(exp, coeff);
			} else { // Key already exists
				int new_coeff = coeff + terms.at(exp);
				terms.erase(exp);
				terms.emplace(exp, new_coeff);
			}
		}
		int size(){ return terms.size(); }
		int get_coeff(int key){ return terms.at(key); }
		void print(){
			for (int i = this->size() - 1; i >= 0; i--){
				cout << this->get_coeff(i) << "x^" << i;
				if (i != 0) cout << " + ";
			} cout << endl;
		}
		list<term> sort_poly(){
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
			int new_coeff = p1.get_coeff(i) * p2.get_coeff(j);
			int new_exp = i + j;
			p3.add_term(new_exp, new_coeff);
		}
	}
	
	return p3;
};

int main(void){
	polynomial p1; p1.add_term(0, 2); p1.add_term(1, 4); p1.add_term(2, 3);
	polynomial p2; p2.add_term(0, 2); p2.add_term(1, 3);
	polynomial p3 = multiply(p1, p2);	
	
	cout << "p1:\t"; p1.print(); 
	cout << "p2:\t"; p2.print();
	cout << "p3:\t"; p3.print();
	
	list<term> l = p3.sort_poly();
	
	return 0;
}
