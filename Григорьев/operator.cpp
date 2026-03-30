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

    Matrica operator+(const Matrica& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Oshibka" << endl;
            return Matrica();
        }

        Matrica result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrica& operator+=(const Matrica& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Oshibka" << endl;
            return *this;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    Matrica operator-(const Matrica& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Oshibka" << endl;
            return Matrica();
        }

        Matrica result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrica& operator-=(const Matrica& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Oshibka" << endl;
            return *this;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    bool operator==(const Matrica& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
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

int main() {
    cout << "Primer\n" << endl;

    Matrica A(2, 2);
    A.setElement(0, 0, 1);
    A.setElement(0, 1, 2);
    A.setElement(1, 0, 3);
    A.setElement(1, 1, 4);

    Matrica B(2, 2);
    B.setElement(0, 0, 5);
    B.setElement(0, 1, 6);
    B.setElement(1, 0, 7);
    B.setElement(1, 1, 8);

    cout << "Matrica A:" << endl;
    A.print();
    cout << "\nMatrica B:" << endl;
    B.print();

    cout << "\n(+):" << endl;
    Matrica C = A + B;
    cout << "A + B =" << endl;
    C.print();

    cout << "\n(-):" << endl;
    Matrica D = A - B;
    cout << "A - B =" << endl;
    D.print();

    cout << "\n(+=):" << endl;
    Matrica A_copy = A;
    A_copy += B;
    cout << "A+= B" << endl;
    A_copy.print();

    cout << "\n(-=):" << endl;
    Matrica A_copy2 = A;
    A_copy2 -= B;
    cout << "A-= B:" << endl;
    A_copy2.print();

    cout << "\n(==):" << endl;
    if (A == B) {
        cout << "A == B: DA" << endl;
    }
    else {
        cout << "A == B: NET" << endl;
    }

    Matrica E = A;
    cout << "Sozdaem E = A" << endl;
    if (E == A) {
        cout << "E == A: DA" << endl;
    }

    cout << "\nprisvaivaniya(=):" << endl;
    Matrica F;
    F = A;
    cout << "F = A, matrica F:" << endl;
    F.print();

    return 0;
}