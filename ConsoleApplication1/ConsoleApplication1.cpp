#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void PrintMap(const map <string, vector<string>>& buses_stops) {
    for (const auto& item : buses_stops) {
        cout << "Bus " << item.first << ": ";
        for (const string stop : item.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
}

void Print
int main() {
    map <string, vector<string>> buses_stops;
    int n;
    string command;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> command;
        if (command == "NEW_BUS") {
            string bus, temp;
            int stop_count;
            cin >> bus >> stop_count;
            for (int j = 0; j < stop_count; j++) {
                cin >> temp;
                buses_stops[bus].push_back(temp);
            }
        }
        if (command == "BUSES_FOR_STOP") {
            string stop;
            bool key;
            cin >> stop;
            key = false;
            for (const auto& item: buses_stops) {
                if (find(item.second.begin(), item.second.end(), stop) != item.second.end()) {
                    cout << item.first << " ";
                    key = true;
                }
            }
            if (!key) {
                cout << "No bus" << endl;
            }
            cout << endl;
        }
    }
    PrintMap(buses_stops);
}