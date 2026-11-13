#include <iostream>
#include <vector>
using namespace std;

template <typename T1 , unsigned int N>
void simplify(T1 (&arr)[N] ,  int &size)
{
    for (int i = 0 ; i <size ; i++)
    {
        for (int j = i+1 ; j < size ; j++)
        {
            if(arr[i] == arr[j])
            {
                for (int l = j ; l < size -1 ; l++)
                {
                    arr[l]=arr[l+1];
                }
                size--;
                j--;
             }
            
        }
    }
}



int main()
{
    int array[10]= {0 , 2 , 1 , 1 , 1 , 2 , 3 , 1 , 9 , 9 };
    int size = 10;
    simplify(array , size);
    for (int i = 0 ; i < size ; i++)
    {
        cout<<array[i];
    }
    

    return 0;
}