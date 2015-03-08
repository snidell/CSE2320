// Lab 3c : Defines the entry point for the console application.
//
//Class: CSE2320-001
//Professor:                Dr. Bob Weems
//TA:                       Zhouyuan (Jhonnie) Huo
//Student:                  Scott Nidell
//Date Due:                 November 18th 2014 10:45am
//Project Name:             Lab3 Red Black Trees, Subtree Root Ranks, Recursive tree processing, rank queiries
//File format promised as in the Data files provided in the Lab1 webpage
//File provided by CSE 2320 webpge as a driver

#include <stdlib.h>
#include <stdio.h>
#include "topdownRB.h"

int main()
{
int cmd,key,rank;
Item pt;

STinit();

while (1)
{
  scanf("%d",&cmd);//get command
  switch (cmd) {
    case (0):
      printf("0: exit\n");
      exit(0);
    case (1):
      scanf("%d",&key);
      pt=STsearch(key);
      if (pt==NULLitem)
      {
        STinsert(key);
        printf("1: %d successfully inserted\n",key);
      }
      else
        printf("1: %d duplicate key\n",key);
      break;
    case (2):
      scanf("%d",&key);
      printf("2: %d ",key);
      rank=STinvSelect(key);
      if (rank==(-1))
        printf("bad key\n");
      else
        printf("rank %d\n",rank);
      break;
    case (3):
      scanf("%d",&rank);//get the rank
      printf("3: %d ",rank);
      pt=STselect(rank);//given the rank, find the key with that rank
      if (pt==NULLitem)
        printf("bad rank\n");
      else
        printf("key %d\n",pt);
      break;
    case (4):
      verifyRBproperties();
      printf("4: clean\n");
      break;

	case (7):
		STprintTree();
		printf("Root rank of Head is: %d\n",bullshitRootRankCall());
		
		break;

  }
}
}