// Lab 4c : Defines the entry point for the console application.
//
//Class: CSE2320-001
//Professor:                Dr. Bob Weems
//TA:                       Zhouyuan (Jhonnie) Huo
//Student:                  Scott Nidell
//Date Due:                 Decemebr 4th 2014 10:45am
//Project Name:             Lab4 Warshalls algorithm and storngly connected components
//File format promised as in the Data files provided in the Lab4 webpage
//Used a modified version of Dr. Weems code posted in lab notes and on web page Warshal.c

#include <stdio.h>
#include <stdlib.h>


int main()
{
int tempStoreLead;
int leaderFlag=0; //If a leader is found flag it and store
int n,i,j,k; //N number of vectors, IJK are counters to go through arrays
scanf("%d",&n);
int succ[n][n];//Holds successors of each vertex
int VertexArray[n][n];  //Holds Graph


//Initialize the arrays
for (i=0;i<n;i++)
{
    for (j=0;j<n;j++)
	{
        succ[i][j]=(-1);//set to negitive one to show if we are there or not
        VertexArray[i][j]=(10000);  //set to something big so if we do find a large minimum we can replace
    }
    VertexArray[i][i]=i;      //Set diagnals to itself
	tempStoreLead=i+1;
}


while (1)//get data input
{
  scanf("%d %d",&i,&j);
    if (i==(-1))
	{
        break;
    }
  succ[i][j]=j;
}
    
for (i=0;i<n;i++) 
{
    for (k=0;k<n;k++) 
	{
        if (succ[i][k] == (-1))
            printf("%2d    ", succ[i][k]);
        else 
		{
            if (i >= succ[i][k])
                printf("%2d %2d ",k, succ[i][k]);
            else
                printf("%2d %2d ",i, succ[i][k]);
        }
    }
    printf("\n");
}

    
printf("-------------------------------\n");
/* Warshall */
/*Print out first array section*/
for (j=0;j<n;j++)
{
    for (i=0;i<n;i++)
	{
        if (succ[i][j]!=(-1))//if a path was found
            for (k=0;k<n;k++)
			{
                if (succ[i][k]==(-1) && succ[j][k]!=(-1))
				{
                    succ[i][k]=succ[i][j];
					tempStoreLead=j;
					//printf("succ: %d temp: %d",succ[i][k],tempSotreLead[i]);
				}
            }
        if(succ[i][j]!=(-1) && succ[j][i]!=(-1))
		{
            if (VertexArray[j][j]<VertexArray[i][i]) //if the column index is less than row
			{
                VertexArray[i][i]=VertexArray[j][j];//set to diagonal
            }
            if (VertexArray[j][j]>VertexArray[i][i]) //if the row is less than column
			{
                VertexArray[j][j]=VertexArray[i][i];//set to inverted diagonal
            }
        }
    }
	/*Print Second Array Section*/
    for (i=0;i<n;i++) 
	{
        for (k=0;k<n;k++) 
		{
            if (succ[i][k] == (-1))
                printf("%2d    ", succ[i][k]);
            else 
			{
                printf("%2d %2d ",VertexArray[i][i]>VertexArray[k][k]?VertexArray[k][k]:VertexArray[i][i], succ[i][k]);
            }
        }
        printf("\n");
    }
  printf("--------------------------------------------------\n");
}
/*Print out leaders*/
for (i=0;i<n;i++)
{
    if (i==VertexArray[i][i]){
		//if it is a leader
        printf("Vertex %d is a Leader\n ",i); //added to match his output
	}
    else
    {
        printf("Vertex path to Leader is:  ");//added to match his output
        for(j= i;j!=VertexArray[i][i];j=succ[j][VertexArray[i][i]])
		{
            printf("%d ",j);
		}
        
		printf("%d\n ", VertexArray[i][i]);
        printf("Vertex path from Leader is:    ");
        
		for(j = VertexArray[i][i];j!=i;j=succ[j][i])
		{
            printf("%d ",j);
		}
        printf("%d\n", i);
    }
 }
return(0);
}



