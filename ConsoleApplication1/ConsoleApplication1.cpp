#include <iostream>
#include <map>

using namespace std;

void ChangeCapital(map <string, string>& countries_capitals, const string& country, const string& capital) {
    countries_capitals[country] = capital;
}

map <string, string> ChangeCountry(const map <string, string>& countries_capitals, const string& country_old, const string& country_new) {
    map <string, string> countries_capitals_new;
    for (auto& [key, value]: countries_capitals) {
        if (key != country_old) {
            countries_capitals_new[key] = value;
        } else {
            countries_capitals_new[country_new] = value;
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
                cout << "Country " << country << " hasn't changed its " << capital << endl;
            }
            else {
                cout << "Country" << country << " has changed its capital from " << countries_capitals[country] << " to " << capital << endl;
                ChangeCapital(countries_capitals, country, capital);
            }
        }
        if (command == "RENAME") {
            string country_old, country_new;
            cin >> country_old >> country_new;
            if (country_old == country_new || countries_capitals.count(country_old) == 0 || countries_capitals.count(country_new) == 1) {
                cout << "Incorrect rename, skip" << endl;
            } 
            else {
                cout << "Country " << country_old << " with capital " << countries_capitals[country_old] << " has been renamed to " << country_new;
                countries_capitals = ChangeCountry(countries_capitals, country_old, country_new);
            }
        }
        //if (command == "ABOUT") {

       // }
        //if (command == "DUMP") {

        //}
    }
}