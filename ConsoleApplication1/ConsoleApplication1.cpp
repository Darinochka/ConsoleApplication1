#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        newNumerator = 0;
        newDenominator = 1;
    }

    Rational(long numerator, long denominator) {
        newNumerator = numerator;
        newDenominator = denominator;
        if (newNumerator == 0) {
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
    long newNumerator, newDenominator, neg = 1;
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

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}