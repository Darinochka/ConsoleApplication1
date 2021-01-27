#include <iostream>
#include <set>
#include <map>

using namespace std;

int CheckStops(const map <int, set<string>>& stops, const set <string>& temp) {
    for (const auto& [key, value] : stops) {
            if (value == temp) {
                return key;
            }
    }
    return 0;
}

int main() {
    int n, q = 0;
    string stop;
    cin >> n;
    map <int, set<string>> stops;
    set <string> temp;
    for (int i = 0; i < n; i++) {
        int count;
        cin >> count;
        temp.clear();
        for (int j = 0; j < count; j++) {
            cin >> stop;
            temp.insert(stop);
        }
        if (CheckStops(stops, temp) == 0) {
            stops[++q] = temp;
            cout << "New bus " << q << endl; 
        } else {
            cout << "Already exists for " << CheckStops(stops, temp) << endl;
        }
    }
    return 0;
}