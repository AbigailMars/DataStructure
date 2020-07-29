
#include <iostream>

using namespace std;

class Fib{
    private:
       int f,g;
    public:
       Fib(int n){
           f = 0 ; g = 1;
           while( f < n) next();
       }; // min fib(k) >= n 
       int get() { return f;}
       int next(){ 
            f +=g; 
            g = f - g;
            return f;
       }
       int prev(){
            g = f - g;
            f -= g;
            return f;
       }
    
};

int main(){
    Fib fib(143);
    cout<<fib.get()<<endl;
    cout<<fib.next()<<endl;
    cout<<fib.prev()<<endl;
}
