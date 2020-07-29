int countOnes(unsigned int n ){
	int ones = 0;
	while(0 < n ){
	count += (n&1);
	n >>= 1;
	}
	return ones;
}