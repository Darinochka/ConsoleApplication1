#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;

class ReversibleString {
  public:
    ReversibleString(const string& s) {
      new_s = s;
    }
    void Reverse() {
      for (int i = 0; i < new_s.size()/2; i++) {
        char temp = new_s[i];
        new_s[i] = new_s[new_s.size()-1-i];
        new_s[new_s.size()-1-i] = temp;
      }
    }
    string ToString() const {
      return new_s;
    }
  private:
    string new_s;
};

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
  
  return 0;
}