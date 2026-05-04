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

    void pokazatInfo(double ob) {
        cout << "Figura: " << nazvanie << endl;
        cout << "Obyom: " << ob << endl;
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
    cout << endl;

    Shar shar(3.0);
    shar.pokazatInfo(shar.obyom());
    cout << endl;

    Kub kub(4.0);
    kub.pokazatInfo(kub.obyom());
    cout << endl;

    Parallelepiped box(3.0, 4.0, 5.0);
    box.pokazatInfo(box.obyom());
    cout << endl;

    Cilindr cilindr(2.0, 7.0);
    cilindr.pokazatInfo(cilindr.obyom());
    cout << endl;

    Konus konus(3.0, 5.0);
    konus.pokazatInfo(konus.obyom());

    return 0;
}