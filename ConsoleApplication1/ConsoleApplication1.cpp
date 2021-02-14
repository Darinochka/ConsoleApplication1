#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

class Rational {
public:
    long newNumerator;
    long newDenominator;
    Rational() {
        newNumerator = 0;
        newDenominator = 1;
        Rational(newNumerator, newDenominator);
    }

    Rational(long numerator, long denominator) {
        newNumerator = numerator;
        newDenominator = denominator;
        if (newNumerator == 0 || newDenominator == 0) {
            newNumerator = 0;
            newDenominator = 1;
        } else {
            long maxDivider = Divider(abs(newNumerator), abs(newDenominator));
            if (newNumerator * newDenominator < 0) {
                neg = -1;
            }
            newNumerator /= maxDivider;
            newDenominator /= maxDivider;
        }
    }

    int Numerator() const {
        return abs(newNumerator) * neg;
    }

    int Denominator() const {
        return abs(newDenominator);
    }
private:
    int neg = 1;
    long Divider(int numerator, int denominator) {
        int remainder = 1;
        while (remainder != 0) {
            remainder = max(numerator, denominator) % min(numerator, denominator);
            if (numerator > denominator) {
                numerator = remainder;
            } else {
                denominator = remainder;
            }
        }  
        return max(numerator, denominator); 
    }
};

Rational operator+(const Rational& first, const Rational& second) {
  int numerator = first.Numerator() * second.Denominator() + second.Numerator() * first.Denominator();
  int denominator = first.Denominator() * second.Denominator();
  return Rational(numerator, denominator);
}

Rational operator-(const Rational& first, const Rational& second) {
  int numerator = first.Numerator() * second.Denominator() - second.Numerator() * first.Denominator();
  int denominator = first.Denominator() * second.Denominator();
  return Rational(numerator, denominator);
}

Rational operator*(const Rational& first, const Rational& second) {
  long numerator = first.Numerator() * second.Numerator();
  long denominator = first.Denominator() * second.Denominator();
  return Rational(numerator, denominator);
}

Rational operator/(const Rational& first, const Rational& second) {
  long numerator = first.Numerator() * second.Denominator();
  long denominator = first.Denominator() * second.Numerator();
  return Rational(numerator, denominator);
}

bool operator==(const Rational& first, const Rational& second) {
    return first.Numerator() == second.Numerator() && first.Denominator() == second.Denominator();
}

bool operator<(const Rational& first, const Rational& second) {
    if (first.Denominator() == second.Denominator()) {
        return first.Numerator() < second.Numerator();
    }
    return first.Numerator() * second.Denominator() < second.Numerator() * first.Denominator();
}

ostream& operator<<(ostream& stream, const Rational& number) {
    stream << number.Numerator() << '/' << number.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& number) {
    char divideSymbol = '/';
    long numerator = 0, denominator = 0;
    stream >> numerator;
    stream >> divideSymbol;
    stream >> denominator;
    if (divideSymbol == '/' && denominator != 0) {
        number = Rational(numerator, denominator);
    }
    return stream;
}

int main() {
    {
        const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            cout << x << endl;
            v.push_back(x);
        }
        if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}