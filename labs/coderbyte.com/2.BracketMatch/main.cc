#include <iostream>
using namespace std;

/* return 1 if the brackets are correctly matched and each one is accounted for.
 * Otherwise return 0. For example: if str is "(hello (world))", then the output
 * should be 1, but if str is "((hello (world))" the the output should be 0
 * because the brackets do not correctly match up. Only "(" and ")" will be used
 * as brackets. If str contains no brackets return 1.
*/

int BracketMatcher(string str) {
    int height = 0;

    for (auto c : str) {
        if (c == '(') {
            height += 1;
        } else if (c == ')') {
            height -= 1;
            if (height < 0) {
                return 0;
            }
        }
    }

    if (height != 0) {
        return 0;
    }

    return 1;
}

int main() {
    cout << BracketMatcher("(true)") << endl;
    cout << BracketMatcher("(false))") << endl;
    cout << BracketMatcher("(true())") << endl;
    cout << BracketMatcher("(false(())") << endl;
    return 0;
}

