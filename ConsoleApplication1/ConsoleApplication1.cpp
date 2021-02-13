#include <iostream>
#include <sstream>
using namespace std;

class Rational {
public:
    long newNumerator;
    long newDenominator;
    int neg = 1;
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

bool operator==(Rational first, Rational second) {
  if (first.Numerator() == second.Numerator() && first.Denominator() == second.Denominator()) {
    return true;
  } else {
    return false;
  }
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
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("a/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational() && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational() && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}