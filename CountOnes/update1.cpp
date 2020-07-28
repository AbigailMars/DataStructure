int countOne1(unsigned int n ){
	int ones = 0;
	while(0 < n){
	ones++;
    n &= n-1;
	}
    return ones;
}//O(countOne1(n))
