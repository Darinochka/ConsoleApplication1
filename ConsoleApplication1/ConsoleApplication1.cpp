#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void AllBuses(const map <string, vector<string>>& buses_stops) {
    for (const auto& item : buses_stops) {
        cout << "Bus " << item.first << ": ";
        for (const string stop : item.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
}

int main() {
    map <string, vector<string>> buses_stops;
    vector <string> buses;
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
            buses.push_back(bus);
        }
        if (command == "BUSES_FOR_STOP") {
            string stop;
            bool key;
            cin >> stop;
            key = false;
            for (auto bus: buses) {
                for (const auto& item: buses_stops) {
                    if (find(item.second.begin(), item.second.end(), stop) != item.second.end() & bus == item.first) {
                        cout << item.first << " ";
                        key = true;
                    }
                }
            }
            if (!key) {
                cout << "No bus" << endl;
            }
            cout << endl;
        }
        if (command == "STOPS_FOR_BUS") {
            string bus;
            bool key;
            cin >> bus;
            if (find(buses.begin(), buses.end(), bus) != buses.end()) {
                for (auto stop: buses_stops[bus]) {
                    key = false;
                    cout << "Stop: " << stop << " ";
                    for (auto bus_name: buses) {
                        for (auto item: buses_stops) {
                            if (bus_name == item.first && bus_name != bus) {
                                if (find(item.second.begin(), item.second.end(), stop) != item.second.end()) {
                                    cout << item.first << " ";
                                    key = true;
                                }
                            }
                        }
                    }
                    if (!key) {
                        cout << "no interchange";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "No bus";
            }
        }
        if (command == "ALL_BUSES") {
            if (!buses_stops.empty()) {
                AllBuses(buses_stops);
            }
            else {
                cout << "No buses" << endl;
            }
        }
    }
}