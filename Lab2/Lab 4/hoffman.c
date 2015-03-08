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

// main implements Huffman code.
// Index is just a table of priorities whose
// subscripts are used in the PQ.

int main()
{
int n,m,op,i,j,val;
int *freq,freqSum,expectedTotal=0;
int *left,*right;  // Links for Huffman code tree, root is subscript m-1
int *parent;  // For printing the codes
int *length;
char *outString;
int W;

printf("Enter alphabet size\n");
scanf("%d",&n);
m=2*n-1;  // Number of nodes in tree
freq=(int*) malloc(m*sizeof(int));
left=(int*) malloc(m*sizeof(int));
right=(int*) malloc(m*sizeof(int));
parent=(int*) malloc(m*sizeof(int));
outString=(char*) malloc((n+1)*sizeof(char));
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
  freqSum+=freq[i];
  PQinsert(i);
  left[i]=right[i]=(-1);
}
printf("Frequencies sum to %d\n",freqSum);

// Huffman code tree construction
for (i=n;i<m;i++)
{     
  left[i]=PQdelmin();
  right[i]=PQdelmin();
  parent[left[i]]=parent[right[i]]=i;
  freq[i]=freq[left[i]]+freq[right[i]];
  PQinsert(i);
}
i=PQdelmin();
if (i!=m-1)
{
  printf("The root isn't the root\n");
  exit(0);
}
parent[m-1]=(-1);

// Goes breadth-first from root to compute length of prefix bit codes.
length[m-1]=0;
for (i=m-1;i>=n;i--)
  length[left[i]]=length[right[i]]=length[i]+1;

// Print the leaves, i.e. for the alphabet symbols
printf("   i  freq  parent  bits product  code\n");
for (i=0;i<n;i++)
{
  // Crawl up the tree to get prefix code
  outString[length[i]]='\0';
  for (j=i;j!=m-1;j=parent[j])
    outString[length[j]-1]=(left[parent[j]]==j) ? '0' : '1';
  printf("%5d %5d %5d %5d   %5d  %s\n",
    i,freq[i],parent[i],length[i],freq[i]*length[i],outString);
  expectedTotal+=freq[i]*length[i];
}
printf("Weighted sum: %d\n",expectedTotal);

// Print the internal nodes
printf("   i  freq    left right parent\n");
for (i=n;i<m;i++)
  printf("%5d %5d %5d %5d  %5d\n",i,freq[i],left[i],right[i],parent[i]);
getchar();
free(freq);
free(left);
free(right);
free(parent);
free(outString);
free(length);
free(pq);
free(qp);
}