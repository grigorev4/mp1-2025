#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Vector {
private:
    int size;
    double* data;

public:
    Vector(int s = 0) {
        size = s;
        if (size > 0) {
            data = new double[size];
            for (int i = 0; i < size; i++) {
                data[i] = 0;
            }
        }
        else {
            data = nullptr;
        }
    }

    Vector(const Vector& other) {
        size = other.size;
        if (size > 0) {
            data = new double[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }

    ~Vector() {
        if (data != nullptr) {
            delete[] data;
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if (data != nullptr) {
                delete[] data;
            }
            size = other.size;
            if (size > 0) {
                data = new double[size];
                for (int i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
            else {
                data = nullptr;
            }
        }
        return *this;
    }

    int getSize() const {
        return size;
    }

    void setComponent(int index, double value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
        else {
            cout << "Oshibka" << endl;
        }
    }

    double getComponent(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        else {
            cout << "Oshibka" << endl;
            return 0;
        }
    }

    void print() const {
        cout << "(";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) {
                cout << " ";
            }
        }
        cout << ")" << endl;
    }
};

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
            cout << "Oshibka" << endl;
        }
    }

    double getElement(int i, int j) const {
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            return data[i][j];
        }
        else {
            cout << "Oshibka" << endl;
            return 0.0;
        }
    }

    void print() const {
        if (rows == 0 || cols == 0) {
            cout << "Matrica pusta" << endl;
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
        cout << "Vvedite elementy matricy " << rows << " x " << cols << ":" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[" << i << "][" << j << "] = ";
                cin >> data[i][j];
            }
        }
    }
};

class Solver {
private:
    Matrica A;
    Vector b;
    Vector x;
    int n;

public:
    void readSystem(const char* filename) {
        ifstream fin;
        fin.open(filename);

        fin >> n;

        A = Matrica(n, n);
        b = Vector(n);
        x = Vector(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double t;
                fin >> t;
                A.setElement(i, j, t);
            }
        }

        for (int i = 0; i < n; i++) {
            double t;
            fin >> t;
            b.setComponent(i, t);
        }

        fin.close();
    }

    void forwardStep() {
        double** aug = new double* [n];
        for (int i = 0; i < n; i++) {
            aug[i] = new double[n + 1];
            for (int j = 0; j < n; j++) {
                aug[i][j] = A.getElement(i, j);
            }
            aug[i][n] = b.getComponent(i);
        }

        for (int k = 0; k < n; k++) {
            double pivot = aug[k][k];
            for (int j = k; j <= n; j++) {
                aug[k][j] = aug[k][j] / pivot;
            }

            for (int i = 0; i < n; i++) {
                if (i != k) {
                    double factor = aug[i][k];
                    for (int j = k; j <= n; j++) {
                        aug[i][j] = aug[i][j] - factor * aug[k][j];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            x.setComponent(i, aug[i][n]);
        }

        for (int i = 0; i < n; i++) {
            delete[] aug[i];
        }
        delete[] aug;
    }

    Vector vectorSolve() {
        return x;
    }

    double check() {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            double Ax = 0;
            for (int j = 0; j < n; j++) {
                Ax = Ax + A.getElement(i, j) * x.getComponent(j);
            }
            double diff = Ax - b.getComponent(i);
            sum = sum + diff * diff;
        }
        return sqrt(sum);
    }

    void write(const char* filename) {
        ofstream fout;
        fout.open(filename);
        fout << "Reshenie sistemy:" << endl;
        for (int i = 0; i < n; i++) {
            fout << "x" << i + 1 << " = " << x.getComponent(i) << endl;
        }
        fout << "Raznicha = " << check() << endl;
        fout.close();
    }
};

int main() {
    Solver s;

    s.readSystem("sistema.txt");
    s.forwardStep();

    cout << "Reshenie: ";
    s.vectorSolve().print();
    cout << "Raznicha: " << s.check() << endl;

    s.write("reshenie.txt");

    return 0;
}