/*
  Problem Name:Ex2
  Programmers'Name: Amit Vikram Singh
  Roll No.:111601001
  Data:22/08/2017
  NOTE: Precision upto 1e-9
*/

#include<stdio.h>

int size;  //size is the variable to store the legth of array.

//function minimum finds minimum element in array
double minimum(double *ptr, int index){  //ptr is pointer to first element of arr
	if(index==size-1){
		return ptr[index];  		   //returning to calling function
	}
	
	double temp=minimum(ptr, index+1);
	if(ptr[index]<temp){  
		return ptr[index];
	}
	
	else return temp;
}

//BEGINNING OF MAIN FUNCTION
int main(){
	printf("Enter size of array: ");
	scanf("%d",&size); //scanning size of array
	double arr[size];
	int i;
	printf("Enter Elements of Array: ");
	for(i=0;i<size;i++){
		scanf("%lf",&arr[i]);
	}
	
	int index=0;
	printf("Minumum Element: %.10lf\n",minimum(arr, index)); //calling function minimum, which return the minimum element in array. AND printing minimum 
	
	return 0;
}
//ENDING OF MAIN FUNCTION
