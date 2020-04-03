#include <iostream>
using namespace std;

int main(){
	char c='T', d='S';
	char *p1 = &c;
	char *p2 = &d;
	char *p3;

	p3 = &d;
	cout << "*p3 = " << *p3 << endl;

	p3 = p1;
	cout << "*p3 = " << *p3
		<< ", p3 = " << p3 << endl;

	*p1 = *p2;
	cout << "*p1 = " << *p1
		<< ", p1 = " << p1 << endl;
}
