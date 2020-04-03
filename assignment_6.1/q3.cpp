#include <iostream>
using namespace std;

int countEven(int*,int);

int main(){
	// Read values for array
	cout << "Enter array size: ";
	int size;
	cin >> size;
	cout << "Enter " << size << " numbers: ";
	int arr[size];
	for(int i = 0;i < size; ++i){
		cin >> *(arr+i);
	}

	// Call function and print value
	int count = countEven(&arr[0],size);
	cout << "Even number count is: " << count << endl;
}

int countEven(int *a, int n){
	int count = 0;
	for( int i= 0;i<n;i++){
		if(*(a+i)%2 == 0){
			count++;
		}
	}
	return count;
}
