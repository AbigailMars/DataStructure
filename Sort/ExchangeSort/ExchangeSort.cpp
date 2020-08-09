
#include <iostream>
using namespace std;


int Partition(int A[],int lo,int hi){
    int pivot = A[lo];
    while(lo<hi){
        while(lo<hi&&A[hi]>=pivot){
            --hi;
            cout<<"hi: "<<hi<<endl;
        }
        A[lo] = A[hi];
        cout<<"HI: ";
        for(int i=0;i<10;i++){
                   cout<<A[i]<<",";
               }
        cout<<endl;
        while(lo<hi&&A[lo]<=pivot){
            ++lo;
            cout<<"lo: "<<lo<<endl;
        }
        A[hi] = A[lo];
           cout<<"LO: ";
        for(int i=0;i<10;i++){
              cout<<A[i]<<",";
          }
        cout<<endl;
    }
        A[lo] = pivot;
    cout<<"FINAL: ";
    for(int i=0;i<10;i++){
                 cout<<A[i]<<",";
             }
           cout<<endl;
        return lo;
}

void QuickSort(int array[],int lo,int hi){
    if(lo<hi){
        int pivotpos = Partition(array,lo,hi);
        QuickSort(array, lo, pivotpos-1);
        QuickSort(array, pivotpos+1, hi);
    }
}

    
    int main(int argc, const char * argv[]){
    int array[10] = {49,38,65,97,76,13,27,49,55,04};
    //straightInsertionSort2(array,8);
    // binaryInsertionSort(array,8);
    //shellInsertionSort1(array,10);
    QuickSort(array,0 ,9);
    for(int i=0;i<9;i++){
        cout<<array[i]<<',';
    }
    
    return 0;
    }
