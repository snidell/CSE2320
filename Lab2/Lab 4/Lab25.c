// Optimal matrix multiplication order using dynamic programming

#include <stdio.h>
#include <conio.h>

int p[20];
int n;
int c[20][20];
int trace[20][20];

void tree(int left,int right,int indent)
{
int i;

if (left==right)
{
  for (i=0;i<indent;i++)
    printf("   ");
  printf("%d\n",left);
  return;
}
tree(trace[left][right]+1,right,indent+1);
for (i=0;i<indent;i++)
  printf("   ");
printf("%d %d\n",left,right);
tree(left,trace[left][right],indent+1);
}

main()
{
int i,j,k;
int work;

scanf("%d",&n);

for (i=0;i<=n;i++)
  scanf("%d",&p[i]);

for (i=1;i<=n;i++)
  c[i][i]=trace[i][i]=0;

for (i=1;i<n;i++)
  for (j=1;j<=n-i;j++)
  {
    printf("Compute c[%d][%d]\n",j,j+i);
    c[j][j+i]=999999;
    for (k=j;k<j+i;k++)
    {
      work=c[j][k]+c[k+1][j+i]+p[j-1]*p[k]*p[j+i];
      printf("  k=%d gives cost %3d=c[%d][%d]+c[%d][%d]+p[%d]*p[%d]*p[%d]\n",
        k,work,j,k,k+1,j+i,j-1,k,j+i);
      if (c[j][j+i]>work)
      {
        c[j][j+i]=work;
        trace[j][j+i]=k;
      }
    }
    printf("  c[%d][%d]==%d,trace[%d][%d]==%d\n",j,j+i,
      c[j][j+i],j,j+i,trace[j][j+i]);
  }

printf("   ");
for (i=1;i<=n;i++)
  printf("   %3d   ",i);
printf("\n");
for (i=1;i<=n;i++)
{
  printf("%2d ",i);
  for (j=1;j<=n;j++)
    if (i>j)
      printf(" ------- ");
    else
      printf(" %3d %3d ",c[i][j],trace[i][j]);
  printf("\n");

  printf("\n");
}

tree(1,n,0);
getch();
}