#include<stdio.h>
    int r,c;
    void display(int a[][10],int n){
        int i,j;
        for(i=0; i<n;i++){
        printf("\n");
         for(j=0;j<n;j++)
             printf("\t%d",a[i][j]);
             }
             printf("\nNumber of Empty rows : %d\n Number of Empty Columns : %d\n",n-r,n-c);
    }
 void main(){

    int a[10][10],n,i,j,k;
    printf("Enter the size of array :");
    scanf("%d",&n);

    for(i=0; i<n;i++)
        for(j=0;j<n;j++)
            a[i][j]=0;
    printf("\nArray of size %d created",n);
    display(a,n);
    r=c=0;
    while(1){
        printf("Enter \n\t1. Row\n\t2. Column\n\t3. Display \n\t4. exit\n ");
        scanf("%d",&k);
        if(k == 4)
            break;
        if(r==n && c==n){
            printf("\n--INSUFFICIENT SPACE--");
            break;
            }
            
        switch (k)
        {
        case 1:
            printf("\n Enter %d Values\n",n-c);
            for(i=c; i<n;i++)
                scanf("%d",&a[r][i]);

                r++;
            printf("\n--Row Appended--\n");
            break;
        case 2:
            printf("\n Enter %d Values\n",n-r);
            for(i=r; i<n;i++)
                scanf("%d",&a[i][c]);

                c++;
            printf("\n--Column Appended--\n");
            break;
        case 3:
            display(a,n);

        default:
            break;
        }
        if(n-r==0 || n-c ==0)
            r=c=n;

    }
display(a,n);

 }
           