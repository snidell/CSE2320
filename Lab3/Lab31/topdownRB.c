// topdownRB.c          fleshed out methods
//
//Class: CSE2320-001
//Professor:                Dr. Bob Weems
//TA:                       Zhouyuan (Jhonnie) Huo
//Student:                  Scott Nidell
//Date Due:                 November 18th 2014 10:45am
//Project Name:             Lab3 Red Black Trees, Subtree Root Ranks, Recursive tree processing, rank queiries
//File format promised as in the Data files provided in the Lab1 webpage
//File provided by CSE 2320 webpge
// Top-down red-black tree header file
// Top-down red-black tree implementation without deletions,
// so free() does not appear.


#include <stdlib.h>
#include <stdio.h>
#include "topdownRB.h"

link z,head;               // Pointers to sentinel and root
Item NULLitem=(-9999999);  // Data for sentinel
int sizeOfTree=0;//Subtree size of root is the size of the whole tree.
int trace=0;  // Controls trace output for insert

link NEW(Item item, link l, link r, int N)
// Allocates and fills in a node
{
link x = (STnode*)malloc(sizeof *x); 
x->item = item;
x->l = l;
x->r = r;
x->red = 1;
x->rank=0;//added SN
return x;
}

void STinit()
{
// Root/sentinel (head/z) starts out red, but first insert makes root black
// and second insert makes sentinel black.
head = (z = NEW(NULLitem, 0, 0, 0));
}

Item searchR(link h, Key v)
// Recursive search for a key
{ 
Key t = key(h->item);
if (h == z) 
  return NULLitem;
if (eq(v, t))
  return h->item;
if (less(v, t))
  return searchR(h->l, v);
return searchR(h->r, v);
}

Item STsearch(Key v) 
{
return searchR(head, v);
}
//h=node being investigated, k= key needing to be found
Item selectR(link h, int k)
// See Sedgewick - implements "zero-based indexing".
// Returns the kth smallest key where k=0 returns the smallest
// key.  Thus, this is like flattening the tree inorder into an array
// and applying k as a subscript.
{ 
int t = h->rank; 

if (h == z)
{
  printf("Impossible situation in selectR\n");
  STprintTree();
  exit(0);
}
if (t > k){
  return selectR(h->l, k);
}
if (t < k){
  return selectR(h->r, k-t-1);
}
return h->item;
}
// Treat tree as flattened into an ordered array
//k = rank needed to be found
Item STselect(int k)
{
if (k<0 || k>=sizeOfTree)//if key is negitave or if the key is bigger than the Heads Subtree size report error
{
  return NULLitem; //return null since there is no item that has that rank
}
return selectR(head, k);
}

int invSelectR(link h, Key v)
// Inverse of selectR
{
Key t = key(h->item);
int work;

if (h==z)
  return -1;  // v doesn't appear as a key
if (eq(v, t))
  return h->rank;
if (less(v, t))
  return invSelectR(h->l,v);
work=invSelectR(h->r,v);
if (work==(-1))
  return -1;  // v doesn't appear as a key
return 1+h->rank + work;//please note::  used computed rank instead of subtree size---SN
}

int STinvSelect(Key v)
{
return invSelectR(head,v);
}

int bullshitRootRankCall(){
	return computeRootRank(head->l);//give it the root and we will start from there...
}
int computeRootRank(link h){
 int count=0;
 if(h==z){
	 return 0;
 }
 else{
	 count=1+(computeRootRank(h->l)+computeRootRank(h->r));
 }
 return count;

}

void fixRank(link h){
h->rank=computeRootRank(h->l);
}

link rotR(link h)
// Rotate right at h, i.e. flip edge between h & h->l
{
link x = h->l;//x is the temp link to swap
h->l = x->r;
x->r = h;
fixRank(x->r);
return x;
}

link rotL(link h)
// Rotate left at h, i.e. flip edge between h & h->r
{
link x = h->r;
h->r = x->l;
x->l = h;
fixRank(x->l);//now fixes root rank instead
return x;
}

link rsRBinsert(link h, Item item, int sw)
// Sedgewick's code, with details included - NOT TESTED
{
Key v = key(item);

if (h == z)
  return NEW(item, z, z, 1);

if ((h->l->red) && (h->r->red)) 
{
  h->red = 1;
  h->l->red = 0;
  h->r->red = 0;
}

if (less(v, key(h->item))) 
{ 
  h->l = rsRBinsert(h->l, item, 0); 
  if (h->red && h->l->red && sw)
    h = rotR(h); 
  if (h->l->red && h->l->l->red) 
  {
    h = rotR(h);
    h->red = 0;
    h->r->red = 1;
   }
}
else
{ 
  h->r = rsRBinsert(h->r, item, 1); 
  if (h->red && h->r->red && !sw)
    h = rotL(h); 
  if (h->r->red && h->r->r->red) 
  {
    h = rotL(h);
    h->red = 0;
    h->l->red = 1;
  }
}
fixRank(h);
return h;
}

void extendedTraceOn()
{
trace=2;
}

void basicTraceOn()
{
trace=1;
}

void traceOff()
{
trace=0;
}

void tracePrint(char *s,link h)
{
if (trace)
  if (h==z)
    printf("%s at sentinel\n",s);
  else
    printf("%s at %d\n",s,key(h->item));
}

link RBinsert(link h, Item item, int sw)
// Program 13.6 coded to be a bit clearer and make mutually exclusive
// cases obvious.  Also includes tracing.  See 2320 notes.  BPW
// h is present node in search down tree.
// Returns root of modified subtree.
// item is the Item to be inserted.
// sw == 1 <=> h is to the right of its parent.
{
Key v = key(item);
link before;  // Used to trigger printing of an intermediate tree

tracePrint("Down",h);
if (h == z)
  return NEW(item, z, z, 1);  // Attach red leaf

if ((h->l->red) && (h->r->red))      // Flip colors before searching down
{
  tracePrint("Color flip",h);
  h->red = 1;
  h->l->red = 0;
  h->r->red = 0;
  if (trace==2)
    STprintTree();
}

if (less(v, key(h->item))) 
{ 
  tracePrint("Insert left",h);
  before=h->l;
  h->l = RBinsert(h->l, item, 0);    // Insert in left subtree
  if (trace==2 && before!=h->l)      // Has a rotation occurred?
    STprintTree();
  if (h->l->red)
    if (h->red)
      if (sw)
      {
        tracePrint("Case ~1",h);
        h = rotR(h);                 // Set up case ~2 after return
      }
      else
        ;
    else if (h->l->l->red)
    {
      tracePrint("Case 2",h);
      h = rotR(h);
      h->red = 0;
      h->r->red = 1;
    }
}
else
{
  tracePrint("Insert right",h);
  before=h->r;
  h->r = RBinsert(h->r, item, 1);    // Insert in right subtree
  if (trace==2 && before!=h->r)      // Has a rotation occurred?
    STprintTree();
  if (h->r->red)
    if (h->red)
      if (!sw)
      {
        tracePrint("Case 1",h);
        h = rotL(h);                 // Set up case 2 after return
      }
      else
        ;
    else if (h->r->r->red)
    {
      tracePrint("Case ~2",h);
      h = rotL(h);
      h->red = 0;
      h->l->red = 1;
    }
}

fixRank(h); //fix the rank after rotating
tracePrint("Up",h);
return h;
}

void STinsert(Item item)
{
head = RBinsert(head, item, 0);
if (head->red)
  printf("red to black reset has occurred at root!!!\n");
head->red = 0;
sizeOfTree++;
}

void checkRed(link h,int redParent)
// Verifies property 3 in notes
{
if (redParent && h->red)
{
  printf("Red property problem at %d\n",key(h->item));
  STprintTree();
  exit(0);
}
if (h==z)
  return;
checkRed(h->l,h->red);
checkRed(h->r,h->red);
}

int leftPathBlackHeight(link h)
// Counts black nodes on path to the minimum
{
if (h==z)
  return !(h->red);
return leftPathBlackHeight(h->l) + !(h->red);
}

void checkBlack(link h,int blackCount)
// Checks that all paths downward from a node have the same
// number of black nodes
{
if (h==z)
  if (blackCount==!(h->red))
    return;
  else
  {
    printf("Black height problem!\n");
    STprintTree();
    exit(0);
  }
if (h->red)
{
  checkBlack(h->l,blackCount);
  checkBlack(h->r,blackCount);
}
else
{
  checkBlack(h->l,blackCount-1);
  checkBlack(h->r,blackCount-1);
}
}

Key lastInorder;    // Saves key from last node processed

void checkInorder(link h)
// Checks that inorder yields keys in ascending order
{
if (h==z)//go until you hit sentinel
  return;

checkInorder(h->l);//go left
if (less(h->item,lastInorder))//if current item is greater than parent error
{
  printf("Inorder error\n");
  STprintTree();
  exit(0);
}
lastInorder=key(h->item);//set last to current item and check right sides
checkInorder(h->r);//go right
}



void verifyRBproperties()
// Checks all required properties.
// If a fatal problem is found, the tree is printed before exit(0)
{
int lpbHeight;//left probe black height

if (head->red)//check to make sure root is black
  printf("Root is not black!\n");
if (z->red)//check to make sure sentinel is black
  printf("Sentinel is not black!\n");
lastInorder=(-99999999); //set the last node processed to not processed somewhat global variable
checkInorder(head);// Checks that inorder yields keys in ascending order 
checkRed(head,0);//checks for red parent and red child exisitence
lpbHeight=leftPathBlackHeight(head);//from the head checks the black height traversing to the minimum key value
checkBlack(head,lpbHeight);//checks the black height of a given node with an Int this being the height of the min key val
}

void printTree(link h,int depth,int bhAbove)
{
int i,bhBelow;

if (h==z)
{
  if (bhAbove!=1)
  {
    for (i=0;i<depth;i++)
      printf("     ");
    printf("Black-height issue detected at sentinel\n");
  }

  return;
}

if ((h->red))
  bhBelow=bhAbove;
else
  bhBelow=bhAbove-1;
printTree(h->r,depth+1,bhBelow);
for (i=0;i<depth;i++)
  printf("     ");
if (h->red)
  printf("[%d %d %d ]\n",key(h->item),bhBelow, h->rank);
else
  printf("(%d %d %d )\n",key(h->item),bhBelow, h->rank);
printTree(h->l,depth+1,bhBelow);
}

void STprintTree()
{
printTree(head,0,leftPathBlackHeight(head));
}
