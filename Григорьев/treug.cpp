#include <iostream>
#include <cmath>
using namespace std;

bool raznZnak(double x, double y) {
    return x * y < 0;
}

double koren(double a, double b, double (*f)(double), double eps) {
    double fa = f(a);
    double fb = f(b);

    if (!raznZnak(fa, fb)) {
        cout << "Oshibka odinak znaki" << endl;
        return 0;
    }

    double c;
    while ((b - a) / 2 > eps) {
        c = (a + b) / 2;
        double fc = f(c);

        if (fc == 0) return c;

        if (raznZnak(fa, fc)) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
    }
    return (a + b) / 2;
}

//x^2 - 2
double f1(double x) {
    return x * x - 2;
}

//x^3 - x - 2
double f2(double x) {
    return x * x * x - x - 2;
}

int main() {
    double eps = 0.0001;

    double kor1 = koren(1.0, 2.0, f1, eps);
    cout << "Koren uravneniya x^2 - 2 = 0: " << kor1 << endl;

    double kor2 = koren(1.0, 2.0, f2, eps);
    cout << "Koren uravneniya x^3 - x - 2 = 0: " << kor2 << endl;

    return 0;
}