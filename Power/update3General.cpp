int power( int a ,int n){
  int pow = 1;
  int p = a;
  while( 0 < n){
   if(1&n){
   pow *= p;}
   n >>= 1;
   p *= p;
}
   return pow;
}
