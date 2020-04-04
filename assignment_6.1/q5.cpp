#include <iostream>
using namespace std;

void swap(int*);

int main(){
	// Read values for array
	int size = 3;
	cout << "Enter three numbers:";
	int arr[size];
	for(int i = 0;i < size; ++i){
		cin >> *(arr+i);
	}

	// Call function and print value
	swap(&arr[0]);
	swap(&arr[1]);
	swap(&arr[0]);
	cout << "Smallest number: " << arr[0] << endl;
	cout << "Largest number: " << arr[2] << endl;
}

void swap(int *a){
	if(*a > *(a+1)){
		int temp = *a;
		*a = *(a+1);
		*(a+1) = temp;
	}
}
