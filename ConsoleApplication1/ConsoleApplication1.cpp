#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        newNumerator = 0;
        newDenominator = 1;
    }

    Rational(int numerator, int denominator) {
        newNumerator = numerator;
        newDenominator = denominator;
        if (newNumerator == 0) {
            newDenominator = 1;
        } else {
            int maxDivider = Divider(abs(newNumerator), abs(newDenominator));
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
    int newNumerator, newDenominator, neg = 1;
    int Divider(int numerator, int denominator) {
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

int main() {
    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
