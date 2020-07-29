#include<iostream>
#include<cstring>
using namespace std;

//fibonacci数 
int fib1(int n){
    return (2 > n)?  n: fib1(n-1) + fib1(n-2);
}// O(2^n)

int fib2(int n,int& prev){
    if(0 == n){    // fib(-1) = 1; fib(0) = 1
        prev = 1;
        return 0;
    }else{
        int prevprev;prev = fib2(n-1,prevprev); //(n-1)-level prev address = 
                                               // n-level prevprev address
        return prevprev + prev;
    }
}//O(n),空间复杂度O(n)

int fib3(int n){//dynamic programming 
    int f = 0,g = 1;// f(0) =  0; f(-1) = 0
    while(0 < n--){
    f += g;
    g = f-g;
    }
    return f; 
}//O(n)，空间复杂度O(1)

//matrix 
struct Matrix { //定义矩阵结构体 
	int a[2][2];
}; 

Matrix muliMatrix(Matrix x, Matrix y) { //求两个矩阵相乘
	Matrix result; //结果矩阵result 
	memset(result.a, 0, sizeof(result.a)); //将结果矩阵的元素全部初始化为0
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 2; k++){
				result.a[i][j] += x.a[i][k] * y.a[k][j]; //矩阵的乘法 
			}
		}
	} 
	return result; 
} 

int MatrixPow(int n) { //快速幂求斐波那契数列
	Matrix res, c;
	memset(res.a, 0, sizeof(res.a));  
	for(int i = 0; i < 2; i++) {
		res.a[i][i] = 1; //将res初始化为单位矩阵，因为任何矩阵和单位矩阵相乘都是它本身 
	} 
	c.a[0][0] = 1; //构造斐波那契矩阵 
	c.a[0][1] = 1;
	c.a[1][0] = 1;
	c.a[1][1] = 0;
	
 	while(n) {
		if(n&1 != 0){ //这里和求x^n的快速幂类似 
			res = muliMatrix(res, c);
		}
		c = muliMatrix(c, c);
		n >>= 1; // 等价于把n右移一位并把结果赋给n即n=>>1 
	} 
	return res.a[0][1]; //由于斐波那契第n项Fn对应结果举证中res.a[0][1]的值 
}
 // O(logn)

int main(){
   int prev;
   cout<<fib1(45)<<endl;
   cout<<fib2(45, prev)<<endl;
   cout<<fib3(45)<<endl;
   cout<<MatrixPow(45);
}
