#include<stdio.h>
int m = 15 , n = 20, loc[2], null_output[2] = {-1,-1};
int *SearchInMatrix(int a[m][n], int search_element)
{ 
    int row_number = 0, column_number = n-1, flg = 0;
    while(row_number<m && column_number>=0)
    {
        if (a[row_number][column_number] == search_element)
        {
            loc[0] = row_number;
            loc[1] = column_number;
            return loc;
        }
            //return (row_number*n + column_number + 1);
        else if (a[row_number][column_number] > search_element)
            column_number--;
        else
            row_number++;    
    }
    return null_output;
}

int main()
{
    int a[m][n], i, j, elem = 1, search_elem;
    int *pos;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j] = elem++;
        }
    }
    printf("Enter Search Element: ");
    scanf("%d",&search_elem);
    pos = SearchInMatrix(a,search_elem);
    if (pos[0] != -1)
        printf("%d %d", pos[0], pos[1]);
    else printf("%d", null_output[0]);
    return 0;
}
