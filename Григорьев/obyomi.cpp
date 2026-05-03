#include <iostream>
#include <cmath>
using namespace std;

double PI = 3.141592;

class Figura {
protected:
    string nazvanie;

public:
    Figura(string n) {
        nazvanie = n;
    }

    void pokazatInfo() {
        cout << "Figura: " << nazvanie << endl;
        cout << "Obyom: " << obyom() << endl;
    }

    virtual double obyom() {
        return 0;
    }
};


class Shar : public Figura {
private:
    double radius;

public:
    Shar(double r) : Figura("Shar") {
        radius = r;
    }

    double obyom() {
        return (4.0 / 3.0) * PI * radius * radius * radius;
    }
};


class Kub : public Figura {
private:
    double storona;

public:
    Kub(double s) : Figura("Kub") {
        storona = s;
    }

    double obyom() {
        return storona * storona * storona;
    }
};


class Parallelepiped : public Figura {
private:
    double dlina, shirina, vysota;

public:
    Parallelepiped(double d, double sh, double v) : Figura("Parallelepiped") {
        dlina = d;
        shirina = sh;
        vysota = v;
    }

    double obyom() {
        return dlina * shirina * vysota;
    }
};


class Cilindr : public Figura {
private:
    double radius, vysota;

public:
    Cilindr(double r, double v) : Figura("Cilindr") {
        radius = r;
        vysota = v;
    }

    double obyom() {
        return PI * radius * radius * vysota;
    }
};


class Konus : public Figura {
private:
    double radius, vysota;

public:
    Konus(double r, double v) : Figura("Konus") {
        radius = r;
        vysota = v;
    }

    double obyom() {
        return (1.0 / 3.0) * PI * radius * radius * vysota;
    }
};


int main() {
    cout << "obyomi figur:" << endl;

    Shar shar(3.0);
    shar.pokazatInfo();
    cout << endl;

    Kub kub(4.0);
    kub.pokazatInfo();
    cout << endl;

    Parallelepiped box(3.0, 4.0, 5.0);
    box.pokazatInfo();
    cout << endl;

    Cilindr cilindr(2.0, 7.0);
    cilindr.pokazatInfo();
    cout << endl;

    Konus konus(3.0, 5.0);
    konus.pokazatInfo();

    return 0;
}