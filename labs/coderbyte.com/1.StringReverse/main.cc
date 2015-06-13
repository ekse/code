#include <iostream>
#include <algorithm>
using namespace std;

string FirstReverse(string str) { 

  std::reverse(str.begin(), str.end());  
  return str; 
            
}

int main() { 
  
  // keep this function call here
  cout << FirstReverse("hello world!");
  return 0;
    
} 

