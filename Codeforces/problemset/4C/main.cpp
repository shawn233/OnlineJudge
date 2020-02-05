#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

int main () {
    int n;
    unordered_set <string> s;
    unordered_map <string, int> t;

    cin >> n;
    string str;
    for (int i = 0; i < n; ++ i) {
        cin >> str;
        if (s.count (str) == 1) {
            cout << str << t[str] << endl;
            t[str] += 1;
        } else {
            s.insert (str);
            t[str] = 1;
            cout << "OK" << endl;
        }
    }

    return 0;
}