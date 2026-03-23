#include <iostream>
using namespace std;

class Matrica {
private:
    int rows;
    int cols;
    double** data;

public:
    Matrica(int r = 0, int c = 0) {
        rows = r;
        cols = c;

        if (rows > 0 && cols > 0) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = 0.0;
                }
            }
        }
        else {
            data = nullptr;
        }
    }

    Matrica(const Matrica& other) {
        rows = other.rows;
        cols = other.cols;

        if (rows > 0 && cols > 0) {
            data = new double* [rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new double[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        else {
            data = nullptr;
        }
    }

    ~Matrica() {
        if (data != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    Matrica& operator=(const Matrica& other) {
        if (this != &other) {
            if (data != nullptr) {
                for (int i = 0; i < rows; i++) {
                    delete[] data[i];
                }
                delete[] data;
            }
            rows = other.rows;
            cols = other.cols;

            if (rows > 0 && cols > 0) {
                data = new double* [rows];
                for (int i = 0; i < rows; i++) {
                    data[i] = new double[cols];
                    for (int j = 0; j < cols; j++) {
                        data[i][j] = other.data[i][j];
                    }
                }
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    void setElement(int i, int j, double value) {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            data[i][j] = value;
        }
        else {
            cout <<"Oshibka" << endl;
        }
    }

    double getElement(int i, int j) const {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            return data[i][j];
        }
        else {
            cout <<"Oshibka" << endl;
            return 0.0;
        }
    }

    void print() const {
        if (rows == 0 || cols == 0) {
            cout <<"Matrica pusta" << endl;
            return;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    void input() {
        cout <<"Vvedite elementy matricy " << rows << " x " << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[" << i << "][" << j << "] = ";
                cin >> data[i][j];
            }
        }
    }
};


int main() {
    Matrica m;
    int choice;

    do {
        cout << "1. Zadat razmer matricy" << endl;
        cout << "2. Uznat razmer matricy" << endl;
        cout << "3. Zadat element matricy" << endl;
        cout << "4. Uznat element matricy" << endl;
        cout << "5. Vvesti vsyu matricu" << endl;
        cout << "6. Vyvesti matricu" << endl;
        cout << "0. Vyhod" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            int r, c;
            cout << "Vvedite kolichestvo strok: ";
            cin >> r;
            cout << "Vvedite kolichestvo stolbcov: ";
            cin >> c;
            m = Matrica(r, c);
            cout << "Sozdana matrica " << r << " x " << c << endl;
            break;
        }
        case 2: {
            cout << "Razmer matricy: " << m.getRows() << " x " << m.getCols() << endl;
            break;
        }
        case 3: {
            int i, j;
            double val;
            cout << "Vvedite nomer stroki: ";
            cin >> i;
            cout << "Vvedite nomer stolbca: ";
            cin >> j;
            cout << "Vvedite znachenie: ";
            cin >> val;
            m.setElement(i, j, val);
            cout << "Element ustanovlen" << endl;
            break;
        }
        case 4: {
            int i, j;
            cout << "Vvedite nomer stroki: ";
            cin >> i;
            cout << "Vvedite nomer stolbca: ";
            cin >> j;
            cout << "Element [" << i << "][" << j << "] = " << m.getElement(i, j) << endl;
            break;
        }
        case 5: {
            if (m.getRows() == 0 || m.getCols() == 0) {
                cout << "Snachala zadayte razmer matricy" << endl;
            }
            else {
                m.input();
            }
            break;
        }
        case 6: {
            if (m.getRows() == 0 || m.getCols() == 0) {
                cout << "Snachala zadayte razmer" << endl;
            }
            else {
                cout << "\nMatrica:" << endl;
                m.print();
            }
            break;
        }
        case 0:
            cout <<"Programma zavershena" << endl;
            break;
        default:
            cout << "Nevernyy vybor" << endl;
        }
    } while (choice != 0);

    return 0;
}