#include <iostream>
#include <string>
using namespace std;

	class LengthConverter {
	private:
		double meters;
	public:
		LengthConverter() {
			meters = 0;
		}

		void setMeters(double m) {
			meters = m;
		}

		double getMeters() {
			return meters;
		}
		
		double convertTo(string unit){
			if (unit == "ft") {
				return meters * 3.28084;
			}
			else if (unit == "yd") {
				return meters * 1.09361;
			}
			else if (unit == "duim") {
				return meters * 39.3701;
			}
			else if (unit == "km") {
				return meters / 1000;
			}
			else if (unit == "cm") {
				return meters * 100;
			}
			else if (unit == "mi") {
				return meters * 0.000621371;
			}
			else {
				cout << "Neizvestnaya edinica izmereniya!" << endl;
				return -1;
			}
		}

		void print(){
			cout << " Dlina: " << meters << "metrov" << endl;
			cout << " Futy: " << convertTo("ft") << "ft" << endl;
			cout << " Yardy: " << convertTo("yd") << " yd" << endl;
			cout << " Duimy: " << convertTo("duim") << " duim" << endl;
			cout << " Kilometry: " << convertTo("km") << " km" << endl;
			cout << " Santimetry: " << convertTo("cm") << " cm" << endl;
		}
};

int main() {
	double userMeters;
	int choice;
	string unit;

	LengthConverter len;

	cout << "Vvedite dlinu v metrah: ";
	cin >> userMeters;

	len.setMeters(userMeters);

	do {
		cout << "1. Pokazat vse edinicy" << endl;
		cout << "2. Konvertirovat v konkretnuyu edinicu" << endl;
		cout << "3. Ustanovit novuyu dlinu" << endl;
		cout << "4. Vyiti" << endl;
		cout << "Vash vybor: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "\n";
			len.print();
			break;

		case 2:
			cout << "Vvedite edinicu (ft, yd, duim, km, cm, mi): ";
			cin >> unit;
			cout << "Rezultat: " << len.convertTo(unit) << " " << unit << endl;
			break;

		case 3:
			cout << "Vvedite novuyu dlinu v metrah: ";
			cin >> userMeters;
			len.setMeters(userMeters);
			cout << "Dlina obnovlena!" << endl;
			break;

		case 4:
			cout << "Programma zavershena" << endl;
			break;

		default:
			cout << "Nevernyy vybor!" << endl;
		}

	} while (choice != 4);

	return 0;
}