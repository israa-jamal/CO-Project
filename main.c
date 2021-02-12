#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void initialize_list (char list[][2],int size);
bool is_full (char array[][2], int size);
void associate_request (int size, char list_1[][2],char list_2[][2],char list_3[][2],char list_4[][2],char request,char priority);
void associate(char list[][2],int size,char request, char priority);
void delete_requests(char list_1[][2],char list_2[][2],char list_3[][2],char list_4[][2],int size, char priority);
void delete_requests_from_list(char list[] [2], int size, char priority);

void sortIt(char word[][2], int left, int right);
void quickSort(char word[][2], int length);
int binarySearch(int a[][2], int s, int e, int f);

int main()
{
    int size = 3;
    char list_1[size][2];
    char list_2[size][2];
    char list_3[size][2];
    char list_4[size][2];

    initialize_list (list_1, size);
    initialize_list (list_2, size);
    initialize_list (list_3, size);
    initialize_list (list_4, size);

    bool test;

    list_1[0][0]='a';
    list_1[0][1]='a';
    list_1[1][0]='a';
    list_1[1][1]='a';
    list_1[2][0]='a';
    list_1[2][1]='a';
    list_2[0][0]='n';
    list_2[0][1]='n';

    printf("%c\n",list_1[1][0]);
    test = is_full(list_1,size);
    printf("%s\n", test ? "true" : "false");


    associate_request (size, list_1, list_2, list_3, list_4, 'a', 'p');
    printf("%c\n",list_2[1][0]);
    printf("%c\n",list_2[1][1]);
    printf("%c\n",list_1[0][1]);



}

void initialize_list (char list[][2],int size)  //use it to empty the list
{
    for (int i=0;i<size;i++)
    {
        list[i][0]='0';
        list[i][1]='0';
        printf("%c\n",list[i][0]);
    }
}
bool is_full (char array[][2], int size)
{
    bool flag = false;
    for (int i=0;i <size;i++)
    {
        if(array[i][0]== '0')
        {
            flag = false;
            return flag;
        }
        else
        {
            flag = true;
        }
    }

    return flag;
}
void associate_request (int size, char list_1[][2],char list_2[][2],char list_3[][2],char list_4[][2],char request,char priority)
{
    if (!is_full(list_1,size))
    {
        associate(list_1,size,request,priority);
        printf("Associated Successfully in List 1!\n");
    }
    else
    {
        if (!is_full(list_2,size))
        {
            associate(list_2,size,request,priority);
            printf("Associated Successfully in List 2!\n");
        }
        else
        {
            if (!is_full(list_3,size))
            {
                associate(list_3,size,request,priority);
                printf("Associated Successfully in List 3!\n");
            }
            else
            {
                if (!is_full(list_4,size))
                {
                    associate(list_4,size,request,priority);
                    printf("Associated Successfully in List 4!\n");
                }
                else
                {
                    printf("All Lists Are Full!");
                }
            }
        }
    }
}

void associate(char list[][2],int size,char request,char priority)
{
    for (int i=0;i<size;i++)
    {
        if (list[i][0]=='0')
        {
            list[i][0]=request;
            list[i][1]=priority;
            break;
        }
    }
}

void delete_requests(char list_1[][2],char list_2[][2],char list_3[][2],char list_4[][2],int size, char priority)
{
    delete_requests_from_list(list_1,size,priority);
    delete_requests_from_list(list_2,size,priority);
    delete_requests_from_list(list_3,size,priority);
    delete_requests_from_list(list_4,size,priority);
}

void delete_requests_from_list(char list[] [2], int size, char priority)
{
    for(int i=0;i<size;i++)
    {
        if(list[i][1]==priority)
        {
            list[i][0]='0';
            list[i][1]='0';
        }
    }
}

int binarySearch(int a[][2], int s, int e, int f) {
    int m;

    if (s > e) // Not found
        return -1;

    m = (s + e)/2;

    if (a[m][0] == f)  // element found
        return m;
    else if (f > a[m][0])
        return binarySearch(a, m+1, e, f);
    else
        return binarySearch(a, s, m-1, f);
}

void quickSort(char word[][2], int length){
    sortIt(word, 0, length-1);
}


void sortIt(char word[][2], int left, int right){

    char *mid = &word[(left+right)/2][2]; //point to the middle
    char temp[right+1];
    int i= left;
    int j = right;

    while(i <= j){

        //word[i] is less than mid and i<right
        while((strcmp(&word[i][0], mid) < 0) && (i < right)){
            i++;
        }

        //word[i] is greater than mid and j>left
        while((strcmp(&word[j][0],mid) > 0) && (j > left)){
            j--;
        }

        //swap
        if(i <= j){
            strcpy(temp, word[i]);
            strcpy(&word[i][2], &word[j][2]);
            strcpy(&word[j][2], temp);
            i++;
            j--;
        }
    }

    if(left<j){
        sortIt(word,left,j);
    }
    if(i<right){
        sortIt(word, i,right);
    }
}
