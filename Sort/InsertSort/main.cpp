
#include <iostream>
using namespace std;

void straightInsertionSort1(int array[],int length){
    int tmp;
    int j;
    for(int i=1;i<length;++i){
        tmp = array[i];
        for(j= i;(j>0)&&(array[j-1]>tmp);--j){
            array[j] = array[j-1];
        }
        array[j] = tmp;
    }
}

void straightInsertionSort2(int array[],int length){
    for(int i=1;i<length;++i){
        for(int j=i;(j>0)&&(array[j]<array[j-1]);--j){
            int tmp = array[j];
            array[j] = array[j-1];
            array[j-1] = tmp;
        }
    }
}

void binaryInsertionSort(int array[],int length){
    int lo,hi,mi,tmp;
    for(int i=1;i<length;++i){
        lo = 0;
        hi = i-1;
            while(lo<=hi){
                mi = (lo+hi)/2;
                if(array[i]<array[mi]){
                    hi = mi-1;
                }else{
                    lo = mi+1;
                }
            }
           tmp = array[i];
           for (int j=i;j>lo;--j){
               array[j] = array[j-1];
        }
           array[lo] = tmp;
    }
}

void shellInsertionSort1(int array[],int length){
    for (int dk= length/2;dk>=1;dk=dk/2){
        cout<<"dk: "<<dk<<"; ";
        for(int i=dk;i<length;++i){
            cout<<"i: "<<i<<endl;
                for(int j=i;(j>0)&&(array[j]<array[j-1]);j-=dk){
                    int tmp = array[j];
                    array[j] = array[j-1];
                    array[j-1] = tmp;
                }
        }
    }
}



int main(int argc, const char * argv[]) {
    int array[10] = {49,38,65,97,76,13,27,49,55,04};
    //straightInsertionSort2(array,8);
    // binaryInsertionSort(array,8);
    shellInsertionSort1(array,10);
    for(int i=0;i<8;i++){
        cout<<array[i]<<',';
    }
    
    return 0;
}
