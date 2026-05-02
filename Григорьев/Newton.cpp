#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

class Newton {
private:
    double tochnost;
    int max_iter;

public:
    Newton(double t = 0.0001, int max_it = 1000) {
        tochnost = t;
        max_iter = max_it;
    }

    double koren(double x0, std::function<double(double)> f, std::function<double(double)> df) {
        double x = x0;
        int iter = 0;

        while (abs(f(x)) > tochnost && iter < max_iter) {
            double fx = f(x);
            double dfx = df(x);

            if (abs(dfx) < 1e-12) {
                cout << "Оshibka. proizvod == 0" << endl;
                return x;
            }

            x = x - fx / dfx;
            iter++;
        }

        if (iter == max_iter) {
            cout << "max iter" << endl;
        }

        return x;
    }
};

double f1(double x) {
    return x * x - 2;
}
double df1(double x) {
    return 2 * x;
}

double f2(double x) {
    return x * x * x - x - 2;
}
double df2(double x) {
    return 3 * x * x - 1;
}


double f3(double x) {
    return cos(x);
}
double df3(double x) {
    return -sin(x);
}

int main() {
    Newton newton(0.0001);

    double k1 = newton.koren(1.5, f1, df1);
    cout << "x^2 - 2 = 0. koren: " << k1 << " (check: " << f1(k1) << ")" << endl;

    double k2 = newton.koren(1.5, f2, df2);
    cout << "x^3 - x - 2 = 0. koren: " << k2 << " (check: " << f2(k2) << ")" << endl;

    double k3 = newton.koren(1.5, f3, df3);
    cout << "cos(x) = 0. koren: " << k3 << " (check: " << f3(k3) << ")" << endl;

    return 0;
}