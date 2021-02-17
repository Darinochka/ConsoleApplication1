/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <sstream>

using namespace std;

class Date {
public:
    Date() {}
    Date(int new_year, int new_month, int new_day) {
        year = new_year;
        month = new_month;
        day = new_day;
        if (month < 0 || month > 12) {
            throw runtime_error("Month value is invalid: " + to_string(month));
        }
        if (day < 0 || day > 31) {
            throw runtime_error("Day value is invalid: " + to_string(day));
        }
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
      return month;
    }
    int GetDay() const {
      return day;
    }
private:
    int year;
    int month;
    int day;
};

istream& operator>>(istream& stream, Date& date) {
    istream& new_stream = stream;
    string wrongDate;
    getline(new_stream, wrongDate);
    int year, month, day;
    char first, second, remaind = '0';
    try {
        stream >> year >> first >> month >> second >> day >> remaind;
        if (first == '-' && second == '-' && remaind == "0") {
            date = Date(year, month, day);
        }
        else {
            throw invalid_argument("");
        }
    }
    catch (invalid_argument&) {
        throw runtime_error("Wrong date format: " + wrongDate);
    }
    return stream;
};

int main()
{
    Date date;
    string command, act, event, dateExpr;
    cin >> command;
    stringstream input(command);
    try {
        input >> date;
    }
    catch (exception& ex) {
        cout << ex.what();
    }
    return 0;
}
