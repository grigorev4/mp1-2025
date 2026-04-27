#include "iostream"
#include "cmath"
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

    double& operator()(int i) {
        return data[i];
    }

    double length() const {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i] * data[i];
        }
        return sqrt(sum);
    }

    double skalProizv(const Vector& other) const {

       // double t = other(5);
        if (size != other.size) {
            cout << "Oshibka" << endl;
            return 0;
        }
        double result = 0;
        for (int i = 0; i < size; i++) {
            result += data[i] * other.data[i];
        }
        return result;
    }

    Vector sum(const Vector& other) const {
        if (size != other.size) {
            cout << "Oshibka" << endl;
            return Vector(0);
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    void print() const {
        if (size == 0 || data == nullptr) {
            cout << "Vector pust" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Vector v1(3);
    v1(0) = 3;
    v1(1) = 4;
    v1(2) = 5;

    cout << "Vektor v1: ";
    v1.print();
    cout << "Razmer v1: " << v1.getSize() << endl;
    cout << "Komponenta v1[1]: " << v1(1) << endl;
    cout << "Dlina v1: " << v1.length() << endl;

    Vector v2(3);
    v2(0) = 1;
    v2(1) = 2;
    v2(2) = 3;

    cout << "Vektor v2: ";
    v2.print();

    cout << "Skaln proizved v1 * v2: " << v1.skalProizv(v2) << endl;

    Vector v3 = v1.sum(v2);
    cout << "Summa v1 + v2: ";
    v3.print();

    return 0;
}