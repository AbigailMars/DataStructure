int Power2(int n ){
  int pow = 1;
	while( 0 < n--){
		pow <<= 1;
	}
	return pow      
} // O(n) = O(2^r) r为n的比特位数
