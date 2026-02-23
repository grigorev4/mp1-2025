#include <iostream>
using namespace std;

int main() {
    double x; int n;
    cout << "Vvedite x: ";
    cin >> x;
    cout << "Vvedite kolichestvo chlenov ryada n: ";
    cin >> n;

    double sum = 1.0;
    double elem = 1.0;

    for (int i = 1; i <= n; i++) {
        elem = elem * (x / i);
        sum = sum + elem;
    }
    cout << "Znachenie e^x po ryadu Tejlora: " << sum << endl;
    return 0;
}