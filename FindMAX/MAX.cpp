#include<iostream>
#include<limits.h>
#include<math.h>
using namespace std;
//从n个整数中找出最大者

int max1(int A[],int n){
    int m= INT_MIN; //O(1)
    for( int i = 0;i < n; i++){
        m = max(m,A[i]);//O(n)
    }
    return m;//O(1)
}//O(1)+O(n)+O(1) = O(n)

int max2(int A[],int n){
    if(2>n){
        return A[n-1];
    }else{
        return max(max2(A,n-1),A[n-1]);
    }
}//O(1) * 递归深度 = O(1) * O(n+1) = O(n)

int max3(int A[],int lo,int hi){
    if(lo+1 == hi) {
     return A[lo];
    }else{
        int mi = (lo+hi)>>1;
        return max(max3(A,lo,mi),max3(A,mi,hi));
    }
} // O(hi -lo)

// 空间复杂度 ： max1 -> O(1) ; max2 -> O(n); max3 -> O(logn)
int main(){
    int array[] ={8,1,2,3,6};
    cout<<max1(array,5)<<endl;
    cout<<max2(array,5)<<endl;
    cout<<max3(array,0,4)<<endl;
}
