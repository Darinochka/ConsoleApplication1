#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>

using namespace std;

class Date {
public:
    Date() {}
    Date(int new_year, int new_month, int new_day) {
        year = new_year;
        month = new_month;
        day = new_day;
        if (month <= 0 || month > 12) {
            throw runtime_error("Month value is invalid: " + to_string(month));
        }
        if (day <= 0 || day > 31) {
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

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()){
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setfill('0');
  stream << setw(4) << date.GetYear() << '-' << 
          setw(2) << date.GetMonth() << '-' << 
          setw(2) << date.GetDay();
  return stream;
}

istream& operator>>(istream& new_stream, Date& date) {
    string wrongDate, remaind = "";
    new_stream >> wrongDate;
    stringstream stream(wrongDate);

    int year, month, day;
    char first, second;
    if (stream >> year >> first >> month >> second >> day) {
        if (first == '-' && second == '-' && stream.eof()) {
            date = Date(year, month, day);
            return new_stream;
        }
    }
    throw runtime_error("Wrong date format: " + wrongDate);
};

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    shedulEvents[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) {
    if (event == "") {
      throw DeleteDate(date);
    }
    if (shedulEvents[date].count(event) > 0) {
      shedulEvents[date].erase(event);
      return true;
    }
    return false;
  }

  int  DeleteDate(const Date& date) {
    int quantity = 0;
    if (shedulEvents.count(date) > 0) {
      quantity = shedulEvents[date].size();
      shedulEvents.erase(date);
    }
    return quantity;
  }

  void Find(const Date& date) const {
    set<string> events;
    if (shedulEvents.count(date) > 0) {
      events = shedulEvents.at(date);
    }
    for (auto event : events) {
      cout << event << endl;
    }
  }
  
  void Print() const {
    for (auto [key, events] : shedulEvents) {
      for (auto event : events) {
        cout << key << " " << event << endl;
      }
    }
  }
private:
  map<Date, set<string>> shedulEvents;
};

int main() {
  Database db;
  Date date;
  string command, act, event, dateExpr;

  while (getline(cin, command)) {
    stringstream input(command);
    input >> act;
    if (!input) {}
    else if (act == "Add") {
      try {
        input >> date;
        input >> event;
        db.AddEvent(date, event);
      } catch (runtime_error& ex) {
        cout << ex.what() << endl;
        return 0;
      }
    } 
    else if (act == "Del") {
      try {      
        event = "";
        input >> date;
        input >> event;
        if (db.DeleteEvent(date, event)) {
          cout << "Deleted successfully" << endl;
        } else {
          cout << "Event not found" << endl;
        }
      } catch (int quatityEvents) {
          cout << "Deleted " << quatityEvents << " events" << endl;
      } catch (runtime_error& ex) {
        cout << ex.what() << endl;
        return 0;
      }
    } 
    else if (act == "Find") {
      try {
        input >> date;
        db.Find(date);
      } catch (runtime_error& ex) {
        cout << ex.what() << endl;
        return 0;
      }
    } 
    else if (act == "Print") {
      db.Print();
    } 
    else {
      cout << "Unknown command: " << act << endl;
      return 0;
    }
  }
  return 0;
}