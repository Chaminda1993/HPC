#include <iostream>
using namespace std;

double* maximum(double*,int);

int main(){
	// Read values for array
	cout << "Enter array size: ";
	int size;
	cin >> size;
	cout << "Enter " << size << " numbers: ";
	double arr[size];
	for(int i = 0;i < size; ++i){
		cin >> *(arr+i);
	}

	// Call function and print value
	double* maxAddr = maximum(&arr[0],size);
	cout << "Address of maximum number: " << maxAddr << endl;
	cout << "Value of maximum number: " << *maxAddr << endl;
}

double* maximum(double *a, int n){
	double *max = a;	
	for( int i= 1;i<n;i++){
		if(*(a+i) > *max){
			*max = *(a+i);
		}
	}
	return max;
}
