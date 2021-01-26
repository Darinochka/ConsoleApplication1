#include <iostream>
#include <vector>
#include <map>

using namespace std;

int CheckStop(const map <int, vector<string>>& stops, const vector <string>& c) {
    bool flag = false;
    for (const auto& [key, value] : stops) {
        if (value.size() == c.size()) {
            flag = true;
            for (int i = 0; i < value.size(); i++) {
                if (value[i] != c[i]) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            return key;
        }
    }
    return -1;
}

int main() {
    int n, coun;
    string temp;
    map <int, vector<string>> stops;
    vector <string> c;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> coun;
        c.clear();
        for (int j = 0; j < coun; j++) {
            cin >> temp;
            c.push_back(temp); 
        }
        if (CheckStop(stops, c) == -1) {
            for (auto item : c) {
                stops[i+1].push_back(item);
            }
            cout << "New bus " << i + 1 << endl;;
        }
        else {
            cout << "Already exists for " << CheckStop(stops, c) << endl;
        }
    }
    return 0;
}