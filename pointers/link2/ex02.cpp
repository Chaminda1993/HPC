#include <iostream>
using namespace std;

int main(){
	float arr[5];

	cout << "Displaying address using pointers notation: " << endl;
	for(int i = 0; i<5; ++i){
		cout << arr +i << endl;
	}

	return 0;
}
