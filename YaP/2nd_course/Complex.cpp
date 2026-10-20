#include <iostream>
#include <sstream>
using namespace std;


constexpr double EPS = 1e-8;
bool is_equal(double a, double b) {
    return abs(a - b) < EPS;
}

class RealyBadError : public logic_error {
public:
    using logic_error::logic_error;
};

void ask(char* str = "") {
    cout << "Set " << str << ": ";
}

class Complex {
    static int _global_count;

    double Re=0;
    double Im=0;
   public:
    void set_from_console() {
        ask("real part");
        cin >> Re;
        ask("complex part");
        cin >> Im;
        cout << ">>> " << str() << "\n";
    }

    string str() const {
        ostringstream oss;
        oss << Re << " + " << Im << "i";
        return oss.str();
    }

    void print(const string& pref = ">>>", const string& post = "") const {
        cout << pref << " " << str() << " " << post << "\n";
    }
    void setRe(double re) {
        Re = re;
    }
    double getRe() const {
        return Re;
    }

    void setIm(double im) {
        Im = im;
    }
    double getIm() const {
        return Im;
    }

    void set(const Complex& other) {
        Re = other.Re;
        Im = other.Im;
    }

    void set(double a, double b) {
        Re = a;
        Im = b;
    }

    void verbose_set(const Complex& other) {
        cout << str() << " --> " << other.str() << "\n";
        set(other);
    }

    Complex() {
        ++_global_count;
    };
    Complex(double re, double im)
        : Re{re}, Im{im} {
        ++_global_count;
    }
    Complex(const Complex& other)
        : Re{other.Re}, Im{other.Im} {
        ++_global_count;
    }
    ~Complex() {
        --_global_count;
        cout << "xxx Complex destruction xxx\n";
    }

    bool operator==(const Complex& other) const {
        return is_equal(Re, other.Re)
                && is_equal(Im, other.Im);
    }
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    Complex operator-() const {
        return {-Re, -Im};
    }
    Complex operator!() const {
        return {Re, -Im};
    }
    Complex operator++() {
        Complex t = *this;
        ++Im;
        return t;
    }
    Complex operator++(Complex) {
        ++Im;
        return *this;
    }

    Complex operator--() {
        Complex t = *this;
        --Im;
        return t;
    }
    Complex operator--(Complex) {
        --Im;
        return *this;
    }


    Complex operator+(const Complex& other) const {
        return Complex(Re + other.Re, Im + other.Im);
    }
    Complex operator-(const Complex& other) {
        return -*this + other;
    }

    Complex operator*(const Complex& other) const {
        return Complex(Re * other.Re - Im * other.Im, Re * other.Im + Im * other.Re);
    }

    Complex operator/(const Complex& other) const {
        const double& c = other.Re;
        const double& d = other.Im;
        double divider = c*c + d*d;
        if (is_equal(divider, 0))
            throw RealyBadError("Don't divide by zero! Our universe is not ready for this!");
        return Complex((Re * c + Im * d) / divider,
                       (Im * c - Re * d) / divider);
    }
};

Complex Scale(const Complex& a, double sc) {
    return {
        a.getRe() * sc,
        a.getIm() * sc
    };
}

Complex Neg(const Complex& a) {
    return Scale(a, -1);
}

Complex Sum(const Complex& a, const Complex& b) {
    Complex c;
    c.setRe(a.getRe() + b.getRe());
    c.setIm(a.getIm() + b.getIm());
    return c;
}

Complex Sub(const Complex& a, const Complex& b) {
    return Sum(a, Neg(b));
}

Complex Prod(const Complex& a, const Complex& b) {
    Complex c;
    c.setRe(a.getRe() * b.getRe() - a.getIm() * b.getIm());
    c.setIm(a.getRe() * b.getIm() + a.getIm() * b.getRe());
    return c;
}


const Complex ErrorNumber(0, 0);

Complex Div(const Complex& a, const Complex& b) {
    Complex c;
    double br = b.getRe();
    double bi = b.getIm();
    double div = br*br + bi*bi;

    if (div < EPS) {
        // throw RealyBadError{"DivByZero"};
        cout << "Complex Div(const Complex& a, const Complex& b) -> ZeroDivisionError\n=> So you get Zero Instead!";
        return ErrorNumber;
    }
    double ar = a.getRe();
    double ai = a.getIm();

    c.setRe((ar * br + ai * bi) / div);
    c.setIm((ai * br - ar * bi) / div);

    return c;
}

Complex operator++() {

}

int main() {
    Complex z0 = {};
    z0.print();

    Complex z1(1, 1);
    z1.print();

    Complex z2 = Sum(Complex(-10, 10), z1);
    z2.print();

    Complex z3(Sub(z2, z1));
    z3.print();

    Complex zErr = Div(z1, z0);
    zErr.print();

    Complex z4 = Div(z1, Scale(z1, 0.0001));
    z4.print();

    Complex z5;
    z5.set_from_console();

    (Prod(z5, z0)).print("");

    (-z1).print();
    (z0).print();
    (z0).print();
    (z0).print();
    (z0).print();
}