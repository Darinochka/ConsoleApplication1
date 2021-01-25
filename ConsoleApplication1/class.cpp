#include <iostream>
#include <map>

using namespace std;

void PrintMap(map <string, string>& countries_capitals) {
    for(auto item: countries_capitals) {
        cout << item.first << "/" << item.second << " ";
    }
    cout << endl;
}

void ChangeCapital(map <string, string>& countries_capitals, const string& country, const string& capital) {
    countries_capitals[country] = capital;
}

map <string, string> ChangeCountry(const map <string, string>& countries_capitals, const string& country_old, const string& country_new) {
    map <string, string> countries_capitals_new;
    for (auto item: countries_capitals) {       
        if (item.first != country_old) {
            countries_capitals_new[item.first] = item.second;
        } else {
            countries_capitals_new[country_new] = item.second;
        }
    }
    return countries_capitals_new;
}

int main() {
    int n, i;
    string command;
    map <string, string> countries_capitals;
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> command;
        if (command == "CHANGE_CAPITAL") {
            string country, capital;
            cin >> country >> capital;
            if (countries_capitals.count(country) == 0) {
                cout << "Introduce new country " << country << " with capital " << capital << endl;
            }
            else if (countries_capitals[country] == capital) {
                cout << "Country " << country << " hasn't changed its capital" << endl;
            }
            else {
                cout << "Country " << country << " has changed its capital from " 
                << countries_capitals[country] << " to " << capital << endl;
            }
            ChangeCapital(countries_capitals, country, capital);
        }
        if (command == "RENAME") {
            string country_old, country_new;
            cin >> country_old >> country_new;
            if (country_old == country_new || countries_capitals.count(country_old) == 0 || countries_capitals.count(country_new) == 1) {
                cout << "Incorrect rename, skip" << endl;
            } 
            else {
                cout << "Country " << country_old << " with capital " 
                << countries_capitals[country_old] << " has been renamed to " << country_new << endl;
                countries_capitals = ChangeCountry(countries_capitals, country_old, country_new);
            }
        }
        if (command == "ABOUT") {
            string country;
            cin >> country;
            if (countries_capitals.count(country) == 0) {
                cout << "Country " << country << " doesn't exist" << endl;
            } else {
                cout << "Country " << country << " has capital " << countries_capitals[country] << endl;
            }
        }
        if (command == "DUMP") {
            if (countries_capitals.empty()) {
                cout << "There are no countries in the world" << endl;
            }
            else {
                PrintMap(countries_capitals);
            }
        }
    }
}