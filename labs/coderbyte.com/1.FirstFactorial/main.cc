#include <iostream>
using namespace std;

int FirstFactorial(int num) { 

    int fact = 1;
    for(int i = 1; i <= num; i++) {
        fact *= i;   
    }
    return fact; 
            
}

int main() { 
  
  // keep this function call here
  cout << FirstFactorial(8);
  return 0;
    
} 
