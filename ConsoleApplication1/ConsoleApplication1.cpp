#include <iostream>
#include <map>

using namespace std;

void ChangeCapital(map <string, string>& countries_capitals, const string& country, const string& capital) {
    countries_capitals[country] = capital;
}
int main() {
    int n, i;
    string command, country, capital;
    map <string, string> countries_capitals;
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> command;
        if (command == "CHANGE_CAPITAL") {
            cin >> country >> capital;
            if (countries_capitals.count(country) == 0) {
                 cout << "Introduce new country " << country << " with capital " << capital;
            }
            else if (countries_capitals[country] == capital) {
                cout << "Country " << country << " hasn't changed its " << capital;
            }
            else {
                cout << "Country" << country << " has changed its capital from " << countries_capitals[country] << " to " << capital;
            }
            ChangeCapital(countries_capitals, country, capital);
        }
        if (command == "RENAME") {
            
        }
        if (command == "ABOUT") {

        }
        if (command == "DUMP") {

        }
    }
}