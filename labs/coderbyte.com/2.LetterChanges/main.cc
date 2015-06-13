/*Using the C++ language, have the function LetterChanges(str) take the str parameter being passed and modify it using the following algorithm. Replace every letter in the string with the letter following it in the alphabet (ie. c becomes d, z becomes a). Then capitalize every vowel in this new string (a, e, i, o, u) and finally return this modified string. */

#include <iostream>
using namespace std;

string LetterChanges(string str) { 

  for (int i = 0; i < str.length(); i++) {
    char c = str.at(i);
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        if (c == 'z') {
            str.replace(i, 1, "a");
        } else if (c == 'Z') {
            str.replace(i, 1, "A");
        } else {
            c += 1;

            if (c == 'a') {
                c = 'A';
            } else if (c == 'e') {
                c = 'E';
            } else if (c == 'i') {
                c = 'I';
            } else if (c == 'o') {
                c = 'O';
            } else if (c == 'o') {
                c = 'U';
            }
            
            str.replace(i, 1, string(1, c));
        }
    }

  }
  return str;          
}

int main() { 
  
  // keep this function call here
  cout << LetterChanges("abcdefzZ");
  return 0;
    
} 















  
