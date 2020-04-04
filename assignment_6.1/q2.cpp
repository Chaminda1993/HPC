#include <iostream>
using namespace std;

int main(){
	char blocks[3] = {'A', 'B', 'C'};
	char *ptr = &blocks[0];					// 4434
	cout << "*ptr = &blocks[0]:\t" << &ptr << endl;
	char temp;

	temp = blocks[0];					// A
	cout << "temp = blocks[0]:\t" << temp << endl;
	temp = *(blocks + 2);					// C
	cout << "temp = *(blocks+2):\t" << temp << endl;
	temp = *(ptr + 1);					// B
	cout << "temp = *(ptr+1):\t" << temp << endl;
	temp = *ptr;						// A
	cout << "temp = *ptr:\t\t" << temp << endl <<endl;
	
	ptr = &blocks[0] + 1;					// 4435
	cout << "ptr = blocks+1:\t\t" << &ptr << endl;
	temp = *ptr;						// B
	cout << "temp = *ptr:\t\t" << temp << endl;
	temp = *(ptr + 1);					// C
	cout << "temp = *(ptr+1):\t" << temp << endl << endl;

	ptr = &blocks[0];					// 4434
	cout << "ptr = blocks:\t\t" << &ptr << endl;
	temp = *++ptr;						// B
	cout << "temp = *++ptr:\t\t" << temp << endl;
	temp = ++*ptr;						// C
	cout << "temp = ++*ptr:\t\t" << temp << endl;
	temp = *ptr++;						// C
	cout << "temp = *+tr++:\t\t" << temp << endl;
	temp = *ptr;						// C
	cout << "temp = *ptr: \t\t" << temp << endl;

	return 0;
}
