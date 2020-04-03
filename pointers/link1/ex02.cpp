#include <iostream>
using namespace std;

int main(){
	int *pc, c;

	c = 5;
	cout << "Address of c (&c): " << &c << endl;
	cout << "Value of c (c): " << c << endl << endl;

	pc = &c;
	cout << "Address that pointer pc holds (pc): " << pc << endl;
	cout << "Content of the address pointer pc holds (*pc): " << *pc << endl << endl;

	c = 11;
	cout << "Address pointer pc holds (pc): " << pc << endl;
	cout << "Content of the address pointer pc holds (*pc): " << *pc << endl << endl;

	*pc = 2;
	cout << "Address of c(&c): " << &c << endl;
	cout << "Value of c (c): " << c << endl << endl;

	return 0;
}
