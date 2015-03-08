// Lab 1c : Defines the entry point for the console application.
//
//Class: CSE2320-001
//Professor:                Dr. Bob Weems
//TA:                       Zhouyuan (Jhonnie) Huo
//Student:                  Scott Nidell
//Date Due:                 September 25th 2014 10:45am
//Project Name:             Lab1 binary Search, maps/permutations, inderection, swapping
//File format promised as in the Data files provided in the Lab1 webpage

#include<stdio.h>
#include<string.h>
#include<stdlib.h> 

void printCounterIndex(int *map, int*index, int*count,int arraySize);//method for command 1
void prinCounterValue(int *map, int*index, int*count, int arraySize);
void addCounter(int *map, int*index, int*count, int arraySize,int indexToIncrement);
void subtractCounter(int *map, int*index, int*count, int arraySize,int indexToIncrement);
void countersInRange(int*count, int arraySize,int highVal, int lowVal);
int binSearchFirst(int *a,int n,int key);
int binSearchLast(int *a,int n,int key);
//start of main 
int main (int argc, char* argv[])
{	
	int arraySize,i;
	int *map,*index,*count;
	int command=100; //command being read by keyboard/file
	int indexInPlay; //index to be increased/decreased
	int smallestI=0;
	int largestJ= 0;//values to be comared when doing comman 5

	scanf("%d",&arraySize);	//scanf is used as suggested in lecure  Sep9 @12:30
    printf("Array Size%d \n", arraySize);
	//allocate memory for arrays use calloc to set all numbers to zero for counters
	count=(int*)calloc(arraySize,sizeof(int)*arraySize);
	map=(int*)malloc(sizeof(int)*arraySize);
	index=(int*)malloc(sizeof(int)*arraySize);

	//set values for map and index

	for(i=0;i<arraySize;i++){
	   index[i]=i;
	   map[i]=i;
	}


	do
	{
		scanf("%d",&command);//
		
		switch(command)
		{
		case 1:
			printCounterIndex(map,index,count,arraySize);
			break;
		case 2:
			prinCounterValue(map,index,count,arraySize);
			break;
		case 3:
			scanf("%d",&indexInPlay);
			addCounter(map,index,count,arraySize,indexInPlay);			
			break;
		case 4:
			scanf("%d",&indexInPlay);
			subtractCounter(map,index,count,arraySize,indexInPlay);
			break;
		case 5:
			scanf("%d %d",&smallestI,&largestJ);
			countersInRange(count,arraySize,largestJ,smallestI);
			break;
		}

	}while(command!=0);

	//Holds screen to see the result
    return 0;

}
//Credit: Bob Weems Lab1 assignment Sheet, Modified by Scott Nidell 9/20/2014
//Prints counters in ascending index value order
//Input: Map[] array index[] array count[] array, size of all arrays
//Output: void, prints results to screen
void printCounterIndex(int *map, int*index, int*count,int arraySize){
	int i=0;
	printf("Print By Count\n");
	for (i=0;i<arraySize;i++)
       printf("%d     %d\n",i,count[map[i]]);
	printf("\n");
}
//Credit: Bob Weems Lab1 assignment Sheet, Modified by Scott Nidell 9/20/2014
//Prints counters in ascending counter value order
//Input: Map[] array index[] array count[] array, size of all arrays
//Output: void, prints results to screen
void prinCounterValue(int *map, int*index, int*count, int arraySize){
	int i=0;
	printf("Print By Index\n");
	for (i=0;i<arraySize;i++)
       printf("%d %d\n",index[i],count[i]);
	printf("\n");
}
//Adds 1 from the indicated counter array index-indexToIncrement
//Input: Map[] array index[] array count[] array, size of all arrays and the index to find
//the counter
//Output: void no visible change to terminal or file.
void addCounter(int *map, int*index, int*count, int arraySize,int indexToIncrement){
	int temp=-10000;
	int binSearchResults=-10000;
	int i=0;
	int input=map[indexToIncrement];//save initial index
	int temp_map1,temp_map2,temp_map_swap;
	//get index that needs to be incremented and and increment it
	
	//conduct binary search and find the index needed to place new value in
    binSearchResults=binSearchLast(count,arraySize,count[map[indexToIncrement]]);

	count[map[indexToIncrement]]++;
	temp=count[map[indexToIncrement]];
	count[map[indexToIncrement]]=count[binSearchResults];
	count[binSearchResults]=temp;
	

	//update values stored in index array 
	temp=index[map[indexToIncrement]];
	index[map[indexToIncrement]]=index[binSearchResults];
	index[binSearchResults]=temp;
	
	//update map according to its index location and swap
	temp_map1=index[input];
	temp_map2=index[binSearchResults];

	temp_map_swap=map[temp_map1];
	map[temp_map1]=map[temp_map2];
	map[temp_map2]=temp_map_swap;

	
	
}
//Subtracts 1 from the indicated counter array index-indexToDecmrement
//Input: Map[] array index[] array count[] array, size of all arrays and the index to find
//the counter
//Output: void no visible change to terminal or file.
void subtractCounter(int *map, int*index, int*count, int arraySize,int indexToDecrement){
	int temp=-10000;
	int binSearchResults=-10000;
	int i=0;
	int input=map[indexToDecrement];//save initial index
	int temp_map1,temp_map2,temp_map_swap;
	
	//conduct binary search and find the index needed to place new value in
    binSearchResults=binSearchFirst(count,arraySize,count[map[indexToDecrement]]);

	//decrement count now
	count[map[indexToDecrement]]--;
	temp=count[map[indexToDecrement]];
	count[map[indexToDecrement]]=count[binSearchResults];
	count[binSearchResults]=temp;	

	//update values stored in index array 
	temp=index[map[indexToDecrement]];
	index[map[indexToDecrement]]=index[binSearchResults];
	index[binSearchResults]=temp;
		
	temp_map1=index[input];
	temp_map2=index[binSearchResults];

	temp_map_swap=map[temp_map1];
	map[temp_map1]=map[temp_map2];
	map[temp_map2]=temp_map_swap;
}

//checks for how many counters are in range between lowVal and HighVal
// Input: count[] with arraySize=size of the array with highVal being
//biggestJ and lowVal being smallestI
//Output: void, prints counters found between range to terminal
void countersInRange(int*count, int arraySize,int highVal, int lowVal){
	int low;
	int high;
	high=binSearchFirst(count,arraySize,lowVal);
	low=binSearchLast(count,arraySize,highVal);

	printf("%d counters valued between %d and %d\n",low-high+1,lowVal,highVal);
}
//Binary Search Credit: Dr. Bob Weems UT Arlington
// Input: int array a[] with n elements in ascending order.
//        int key to find.
// Output: Returns subscript of the first a element >= key.
//         Returns n if key>a[n-1].
// Processing: Binary search.
int binSearchFirst(int *a,int n,int key){
  int low,high,mid;
  low=0;
  high=n-1;
// Subscripts between low and high are in search range.
// Size of range halves in each iteration.
// When low>high, low==high+1 and a[high]<key and a[low]>=key.
  while (low<=high)
  {
    mid=(low+high)/2;
    if (a[mid]<key)
      low=mid+1;
    else
      high=mid-1;
  }
  return low;
}
//Binary Search Credit: Dr. Bob Weems UT Arlington
// Input: int array a[] with n elements in ascending order.
//        int key to find.
// Output: Returns subscript of the last a element <= key.
//         Returns -1 if key<a[0].
// Processing: Binary search.
int binSearchLast(int *a,int n,int key)
{

  int low,high,mid;
  low=0;
  high=n-1;
// subscripts between low and high are in search range.
// size of range halves in each iteration.
// When low>high, low==high+1 and a[high]<=key and a[low]>key.
  while (low<=high)
  {
    mid=(low+high)/2;
    if (a[mid]<=key)
      low=mid+1;
    else
      high=mid-1;
  }
  return high;
}





	
