#include <iostream>
using namespace std;

int main() {
	double x; int n;

	cout << "Vvedite x(v radianah dla sin/cos): ";
	cin >> x;
	cout << "Vvedite kol-vo chlenov ryda n: ";
	cin >> n;

	//e^x
	double sum_e = 1.0;
	double elem = 1.0;
	for (int i = 1; i <= n; i++){
		elem = elem * (x / i);
		sum_e = sum_e + elem;
	}
	cout << "e^x: " << sum_e << endl;

	//sin(x)
	double sum_sin = x; elem = x;
	for (int i = 1; i < n; i++){
		elem = -elem * x * x / ((2 * i) * (2 * i + 1));
		sum_sin = sum_sin + elem;
	}
	cout << "sin(x): " << sum_sin << endl;

	//cox(x)
	double sum_cos = 1.0; elem = 1.0;
	for (int i = 1; i < n; i++){
		elem = -elem * x * x / ((2 * i - 1) * (2 * i));
		sum_cos = sum_cos + elem;
	}
	cout << "cos(x): " << sum_cos << endl;

	//ln(1+x)
	double sum_ln = 0.0; elem = x;
	for (int i = 1; i <= n; i++){
		sum_ln = sum_ln + elem / i;
		elem = -elem * x;
	}
	cout << "ln(1+x): " << sum_ln << " (pri (x) < 1(modul)" << endl;

	//arctg(x)
	double sum_tg = x; elem = x;
	for (int i = 1; i < n; i++){
		elem = -elem * x * x;
		sum_tg = sum_tg + elem / (2 * i + 1);
	}
	cout << "arctg(x): " << sum_tg << "(pri (x) <=1 (modul)" << endl;

	return 0;
}