int power2(int n){
 int pow = 1;
 int p = 2;
 while(1 < n){
   if (n&1){
     pow *= p;
   }
   n >>=1;
   p *= p;
 }
 return pow;
 }//O(log(n)) = O(r)，r 为输入指数n的比特数
 
