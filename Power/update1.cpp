inline int sqr(int a) {return a*a;}
int power2(int n){
    if(0 == n) return 1;
    return (n & 1) ? sqr(power2(n >>1)) <<1 : sqr(power2(n>>1));
}//O(log(n)) = O(r) r为输入指数n的比特位数
