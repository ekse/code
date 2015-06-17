#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

string RunLength(string str) { 

  // code goes here   
  string rle_string;
  char prev;
  unsigned int count = 0;
  for (auto c : str) {
    if (count == 0) {
        prev = c;
        count = 1;
    }
    else if (c == prev) {
        count += 1;
    } else {
        rle_string.append(std::to_string(count));
        rle_string.push_back(prev);
        prev = c;
        count = 1;
    }
  }

  rle_string.append(std::to_string(count));
  rle_string.push_back(prev);
  
  return rle_string;
}

int main() { 
  
  cout << RunLength("aaabbcccccdd");
  return 0;
    
} 


