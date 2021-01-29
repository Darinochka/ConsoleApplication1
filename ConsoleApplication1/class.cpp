#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    int first, last;
    string result;
    first = CheckYear(first_names, year);
    last = CheckYear(last_names, year);
    if (first == -1 && last == -1) {
      result = "Incognito";
    } else if (first == -1 && last > 0) {
      result = last_names[last] + " with unknown first name";
    } else if (first > 0 && last == -1) {
      result = first_names[first] + " with unknown last name";
    } else {
      result = first_names[first] + " " + last_names[last];
    }
    return result;
  }
  string GetFullNameWithHistory(int year) {
    int first, last;
    string result;
    first = CheckYear(first_names, year);
    last = CheckYear(last_names, year);
    if (first == -1 && last == -1) {
      result = "Incognito";
    } else if (first == -1 && last > 0) {
      result = last_names[last] + Past(last_names, last) + " with unknown first name";
    } else if (first > 0 && last == -1) {
      result = first_names[first] + Past(first_names, first) + " with unknown last name";
    } else {
      result = first_names[first] + Past(first_names, first) + " " + last_names[last] + Past(last_names, last);
    }
    return result;
  }
  private:
    map <int, string> first_names;
    map <int, string> last_names;

    int CheckYear(map<int, string>& names, const int& year) {
      int by_year = -1;
      for (const auto& [key, value] : names) {
        if (key <= year){
          by_year = key;
        }
      }
      return by_year;
    }
    string Past(map <int, string>& names, const int& year) {
      string result;
      list <string> past_names;
      for (const auto& [key, value] : names) {
        if (key < year) {
          past_names.push_front(value);
        }
      }
      while (past_names.front() == names[year]) {
        past_names.pop_front();
      }
      for (const auto& item : past_names) {
        if (item != past_names.back()) {
          result += item + ", ";
        }
        else {
          result += item;
        }
      }
      if (result != "") {
        return " (" + result + ")";
      } else {
        return "";
      }
    }
};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  return 0;
}