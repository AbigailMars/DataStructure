int Power2(int n ){
  int pow = 1;
	while( 0 < n--){
		pow <<= 1;
	}
	return pow;      
} // O(n) = O(2^r) r为n的比特位数

int Power2(int n){ //n >= 0
	return (1 > n)? 1 : Power2( n-1)<<1;
}// O(n) = O(2^r) r为n的比特位数
