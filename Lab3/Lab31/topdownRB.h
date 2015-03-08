// topdownRB.h      defines methods for topdownRB.c and struct
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

// These will have to change if data in node is more than just an int.
typedef int Key;
typedef Key Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))

typedef struct STnode* link;

struct STnode 
{
Item item;  // Data for this node
link l, r;  // left & right links
char red;   // RB color
//int N;      // subtree size
int rank;  //keeps track of the rank given the subtree size go left
};

extern Item NULLitem;

void STinit();          // Initialize tree with just a sentinel

Item STsearch(Key v);   // Find node for a key

Item STselect(int k);   // Treat tree as flattened into an ordered array

int STinvSelect(Key v); // Inverse of STselect

void extendedTraceOn(); // Full tracing of intermediate trees

void basicTraceOn();    // Just trace down and up passes for insert

void traceOff();        // Run silent

void STinsert(Item item);     // Insert an item.  No uniqueness check

void verifyRBproperties();    // Ensure that tree isn't damaged

void STprintTree();           // Dumps out tree

void cleanUpUnbalanced(link h);  // Includes subtree sizes and verifies a tree
                                 // built without balancing
int computeRootRank(link h); //Calculates root rank of node the hard way

int bullshitRootRankCall();//bullshit to get into c file

void fixRank(link h);//replaces FixN, uses ranks to fix up instead of subtree size