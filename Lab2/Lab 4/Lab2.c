// Lab 2c : Defines the entry point for the console application.
//
//Class: CSE2320-001
//Professor:                Dr. Bob Weems
//TA:                       Zhouyuan (Jhonnie) Huo
//Student:                  Scott Nidell
//Date Due:                 October 23rd 2014 10:45am
//Project Name:             Lab2 heaps and interfacing with a dictionary, dynamic programming
//File format promised as in the Data files provided in the Lab2 webpage


// Huffman code using a minHeap with handles (index-heap-based priority queue).
// Heap routines are adapted from "Algorithms in C, Third Edition", and
// "Algorithms in Java, Third Edition", Robert Sedgewick

// This is a prototype for demonstration purposes only.
// Minimally, the heap/priority queue implementation should
// be in a different source file.

#include <stdio.h>
#include <stdlib.h>
  
int N,          // Number of items in queue
*pq,        // Priority queue
*qp,        // Table of handles (for tracking)
maxQueued;  // Capacity of priority queue
int last_Node;  //last node of frequencies
int right_Node; //right node of approximate
int *a;      // Pointer to user's table

void exch(int i, int j)
{
    // Swaps parent with child
    int t;
    
    t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void PQinit(int *items,int n,int m)
{
    int i;
    
    a = items;    // Save reference to index table
    maxQueued=m;
    N = 0;
    pq=(int*) malloc((maxQueued+1)*sizeof(int)); // Contains subscripts to a[]
    qp=(int*) malloc(n*sizeof(int));   // Inverse of pq, allows changing priorities
    if (!pq || !qp)
    {
        printf("malloc failed %d\n",__LINE__);
        exit(0);
    }
    // Set all handles to unused
    for (i=0;i<n;i++)
        qp[i]=(-1);
}

int PQempty()
{
    return !N;
}

int PQfull()
{
    return N == maxQueued;
}

int less(int i, int j)
{
    // Notice how heap entries reference a[]
    return a[pq[i]] < a[pq[j]];
}
int getApproximate(int *frequency, int n, int *tracker, int i,int *freqOriginal,int parentIndex)
{
    int first=0;int index=0;
    int second;
    int leastSum=99999;
    
    int left_Node;
    //go down frequencys to get the smallest summation of two nodes
    while((first+1)<last_Node)    
    {
        //add up new frequency if it the smallest
        if(frequency[first]+frequency[first+1]<leastSum)
        {
            leastSum=frequency[first]+frequency[first+1];
            index=first;			
        }
        first++;	
    }
	//Determine if multiple matches exist  
	
	freqOriginal[parentIndex]=freqOriginal[index]+frequency[index+1];
	//store the smallest addition to original
	frequency[index]=frequency[index]+frequency[index+1];
	//Update loc of parent
    left_Node=tracker[index];               
    right_Node =tracker[index+1];
	//update parent value to tracking
    tracker[index]=i;  

	//move all indexes down to the end
    for (second=index+1; second<last_Node; second++){                                   
        if(second+1==last_Node){
            frequency[second]=-1;
            tracker[second]=-1;
        }
        frequency[second]=frequency[second+1];
        tracker[second]=tracker[second+1];

    }
    last_Node--; //update last node so it doesn't print anymore

    return left_Node;
}

void fixUp(int *pq,int k) // AKA swim
{
    while (k>1 && less(k,k/2))
    {
        exch(k, k/2);
        k = k/2;
    }
}

void fixDown(int *pq,int k, int N) // AKA sink
{
    int j;
    
    while (2*k <= N)
    {
        j = 2*k;
        if (j < N && less(j+1, j))
            j++;
        if (!less(j, k))
            break;
        exch(k, j);
        k = j;
    }
}

void PQinsert(int k)
{
    qp[k] = ++N;
    pq[N] = k;
    fixUp(pq, N);
}

int PQdelmin()
{
    int i=0;
	exch(1, N);
    fixDown(pq, 1, --N);	
    qp[pq[N+1]]=(-1);  // Set to unused
    return pq[N+1];
}

void PQchange(int k)
{
    fixUp(pq, qp[k]);
    fixDown(pq, qp[k], N);
}

int isParent(int index, int n){
	if(index>=n){
		return 1;
	}else{
		return 0;
	}
}

int isChild(int index){
}

int main()
{
    int left_Node; 
	int n,m,op,i,j,val;
    int *freq,freqSum,expectedTotal=0;
    int *left,*right;  // Links for Huffman code tree, root is subscript m-1
	int *freq_Copy;   
    int *trackers; 
    int *parent;  // For printing the codes
    int *length;
    char *outString;
    
          
    
         
	int temp=0;
    
    printf("Enter alphabet size\n");
    scanf("%d",&n);    
    m=2*n-1;  // Number of nodes in tree
    freq_Copy=(int*) malloc(m*sizeof(int));
    trackers=(int*) malloc(m*sizeof(int));
    freq=(int*) malloc(m*sizeof(int));
    left=(int*) malloc(m*sizeof(int));
    right=(int*) malloc(m*sizeof(int));
    parent=(int*) malloc(m*sizeof(int)); //allocate mem for new arrays
    outString=(char*) malloc((n+1)*sizeof(char));  
	last_Node=n;
    
    length=(int*) malloc(m*sizeof(int));
    if (!freq || !left || !right || !parent || !outString || !length)
    {
        printf("malloc problem %d\n",__LINE__);
        exit(0);
    }
    
    PQinit(freq,m,n);
    
    // Read and load alphabet symbols' frequencies into priority queue.
    freqSum=0;
    for (i=0;i<n;i++)
    {
        scanf("%d",freq+i);
        freq_Copy[i]=freq[i];
        trackers[i]=i;
        freqSum+=freq[i];
        PQinsert(i);
        left[i]=right[i]=(-1);
		
    }
    // Huffman code tree construction
	temp=n;
	
    for (i=n;i<m;i++)
    {        
		left_Node=getApproximate(freq_Copy,n,trackers,i,freq,temp);
		temp++;
        
        right[i]=right_Node;

		left[i]=left_Node;
        parent[left[i]]=parent[right[i]]=i;
		parent[m-1]=-1;
    }
    
    // Goes breadth-first from root to compute length of prefix bit codes.
    length[m-1]=0;
    
    for (i=m-1;i>=n;i--){
        length[left[i]]=length[right[i]]=length[i]+1;
    }
    printf("Printinging Approximate Solution\n");
    // Print the leaves, i.e. for the alphabet symbols
    printf("   i  freq  parent  bits product  code\n");
    
     for (i=0;i<n;i++)
     {
     // Crawl up the tree to get prefix code
     //outString[length[i]]='\0';
     
     //for (j=i;j!=m-1;j=parent[j]){
     printf("%5d %5d %5d %5d   %5d \n",i,freq[i],parent[i],length[i],freq[i]*length[i]);
     expectedTotal+=freq[i]*length[i];
     //}
     
     }
     printf("Weighted sum: %d\n",expectedTotal);
     
     // Print the internal nodes
     printf("   i  freq    left right parent\n");
     for (i=n;i<m;i++){
     printf("%5d %5d %5d %5d %5d \n",i,freq[i],left[i],right[i],parent[i]);
     }     
     printf("No Solution for Exact/Dynamic\n");
     getchar();

    free(freq);
	free(trackers);
    free(left);
    free(right);
    free(parent);
	free(freq_Copy);
    free(outString);
    free(length);
    free(pq);
    free(qp);    
    
}
