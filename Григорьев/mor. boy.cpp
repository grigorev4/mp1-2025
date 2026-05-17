#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int Empty = 0;
const int ship = 1;
const int hit = 2;
const int miss = 3;

struct Ship {
    int x, y;
    int napr;
    int dlina;
    int zhiv;
};

class Gamer {
public:
    int moyaBoard[6][6];
    int vragBoard[6][6];
    Ship korabli[3];
    int razmer;

    Gamer() {
        razmer = 6;
        for (int i = 0; i < razmer; i++) {
            for (int j = 0; j < razmer; j++) {
                moyaBoard[i][j] = Empty;
                vragBoard[i][j] = Empty;
            }
        }
        korabli[0].dlina = 1;
        korabli[1].dlina = 2;
        korabli[2].dlina = 3;
        for (int i = 0; i < 3; i++) {
            korabli[i].zhiv = korabli[i].dlina;
        }
    }

    virtual ~Gamer() {}

    virtual void sdelatHod(int& x, int& y) = 0;
    virtual void otvetitNaHod(int x, int y, bool popal) = 0;
    virtual void rasstavitKorabli() = 0;

    int getKorabliOstalos() {
        int zhivye = 0;
        for (int i = 0; i < 3; i++) {
            if (korabli[i].zhiv > 0) zhivye++;
        }
        return zhivye;
    }

    bool mozhnoPostavit(int x, int y, int dlina, int napr) {
        if (napr == 0) {
            if (y + dlina > razmer) return false;
        }
        else {
            if (x + dlina > razmer) return false;
        }

        for (int i = -1; i <= dlina; i++) {
            for (int j = -1; j <= 1; j++) {
                int cx = x, cy = y;
                if (napr == 0) {
                    cy = y + i;
                    cx = x + j;
                }
                else {
                    cx = x + i;
                    cy = y + j;
                }

                if (cx >= 0 && cx < razmer && cy >= 0 && cy < razmer) {
                    if (moyaBoard[cx][cy] != Empty) return false;
                }
            }
        }

        return true;
    }

    void postavitKorabl(int x, int y, int dlina, int napr, int index) {
        korabli[index].x = x;
        korabli[index].y = y;
        korabli[index].napr = napr;

        for (int i = 0; i < dlina; i++) {
            int cx = x, cy = y;
            if (napr == 0) cy = y + i;
            else cx = x + i;
            moyaBoard[cx][cy] = ship;
        }
    }

    bool vystrelit(int x, int y) {
        if (moyaBoard[x][y] == ship) {
            moyaBoard[x][y] = hit;
            for (int i = 0; i < 3; i++) {
                Ship& s = korabli[i];
                if (s.zhiv <= 0) continue;

                for (int j = 0; j < s.dlina; j++) {
                    int cx = s.x, cy = s.y;
                    if (s.napr == 0) cy = s.y + j;
                    else cx = s.x + j;

                    if (cx == x && cy == y) {
                        s.zhiv--;
                        break;
                    }
                }
            }
            return true;
        }
        return false;
    }

    void zapomnitVystrel(int x, int y, bool popal) {
        if (popal) {
            vragBoard[x][y] = hit;
        }
        else {
            vragBoard[x][y] = miss;
        }
    }

    void pokazatMoyuBoard() {
        cout << "  ";
        for (int i = 0; i < razmer; i++) cout << i << " ";
        cout << endl;

        for (int i = 0; i < razmer; i++) {
            cout << i << " ";
            for (int j = 0; j < razmer; j++) {
                if (moyaBoard[i][j] == ship) cout << "# ";
                else if (moyaBoard[i][j] == hit) cout << "X ";
                else if (moyaBoard[i][j] == miss) cout << "o ";
                else cout << ". ";
            }
            cout << endl;
        }
    }

    void pokazatVragBoard() {
        cout << "  ";
        for (int i = 0; i < razmer; i++) cout << i << " ";
        cout << endl;

        for (int i = 0; i < razmer; i++) {
            cout << i << " ";
            for (int j = 0; j < razmer; j++) {
                if (vragBoard[i][j] == hit) cout << "X ";
                else if (vragBoard[i][j] == miss) cout << "o ";
                else cout << ". ";
            }
            cout << endl;
        }
    }
};



class User : public Gamer {
public:
    void rasstavitKorabli() {
        cout << "\nRASSTANOVKA KORABLEY" << endl;
        cout << "y tebya 3 korablya: 1 kletka, 2 kl., 3 kl." << endl;
        cout << "Korabli ne dolzhny kasatsya po gorizontali i vertikali" << endl;

        int razmery[3] = { 1, 2, 3 };

        for (int i = 0; i < 3; i++) {
            int dlina = razmery[i];
            cout << "\npostav korabl dlinoy " << dlina << ":" << endl;

            bool postavlen = false;
            while (!postavlen) {
                pokazatMoyuBoard();
                int x, y, napr;
                cout << "Vvedi koordinaty nachala (x y) i napravlenie (0 - gorizont, 1 - vertikal): ";
                cin >> x >> y >> napr;

                if (x < 0 || x >= razmer || y < 0 || y >= razmer) {
                    cout << "oshibka!" << endl;
                    continue;
                }

                if (napr != 0 && napr != 1) {
                    cout << "oshibka!" << endl;
                    continue;
                }

                if (mozhnoPostavit(x, y, dlina, napr)) {
                    postavitKorabl(x, y, dlina, napr, i);
                    postavlen = true;
                    cout << "korabl postavlen" << endl;
                }
                else {
                    cout << "nelzya postavit. Korabl peresekaetsya s drugim ili slishkom blizko." << endl;
                }
            }
        }
        cout << "\nTvoya doska:" << endl;
        pokazatMoyuBoard();
    }

    void sdelatHod(int& x, int& y) {
        cout << "Tvoy hod. Vvedi koordinaty (x y): ";
        cin >> x >> y;
    }

    void otvetitNaHod(int x, int y, bool popal) {
        if (popal) {
            cout << "kompYuter popal v (" << x << "," << y << ")!" << endl;
        }
        else {
            cout << "kompYuter promahnulsya" << endl;
        }
    }
};

// ==================== Klass Computer ====================
class Computer : public Gamer {
public:
    void rasstavitKorabli() {
        srand(time(NULL));

        int razmery[3] = { 1, 2, 3 };

        for (int i = 0; i < 3; i++) {
            int dlina = razmery[i];
            bool postavlen = false;

            while (!postavlen) {
                int x = rand() % razmer;
                int y = rand() % razmer;
                int napr = rand() % 2;

                if (mozhnoPostavit(x, y, dlina, napr)) {
                    postavitKorabl(x, y, dlina, napr, i);
                    postavlen = true;
                }
            }
        }
        cout << "kompYuter rasstavil korabli." << endl;
    }

    void sdelatHod(int& x, int& y) {
        do {
            x = rand() % razmer;
            y = rand() % razmer;
        } while (vragBoard[x][y] == hit || vragBoard[x][y] == miss);
    }

    void otvetitNaHod(int x, int y, bool popal) {
        if (popal) {
            cout << "ty popal v korabl kompYutera" << endl;
        }
        else {
            cout << "ty promahnulsya" << endl;
        }
    }
};


class Game {
private:
    User* user;
    Computer* computer;
    int tekushiyIgrok;

public:
    Game() {
        user = new User();
        computer = new Computer();
        tekushiyIgrok = 0;
    }

    ~Game() {
        delete user;
        delete computer;
    }

    void pokazatVseDoski() {
        cout << endl;
        cout << "tvoya doska: (# - tvoi korabli, X - popal kompYuter, o - mimo):" << endl;
        user->pokazatMoyuBoard();

        cout << "\ndoska komputera: (X - ty popal, o - ty mimo):" << endl;
        user->pokazatVragBoard();
    }

    void start() {
        cout << "        MORSKOY BOY:" << endl;

        user->rasstavitKorabli();
        computer->rasstavitKorabli();

        while (user->getKorabliOstalos() > 0 && computer->getKorabliOstalos() > 0) {

            pokazatVseDoski();

            if (tekushiyIgrok == 0) {
                cout << "\n tvoy hod" << endl;

                int x, y;
                user->sdelatHod(x, y);

                if (x < 0 || x >= 6 || y < 0 || y >= 6) {
                    cout << "Nevernye koordinaty. Hod perehodit pc." << endl;
                    tekushiyIgrok = 1;
                    continue;
                }

                if (user->vragBoard[x][y] != Empty) {
                    cout << "uzhe strelal suda" << endl;
                    tekushiyIgrok = 1;
                    continue;
                }

                bool popal = computer->vystrelit(x, y);
                user->zapomnitVystrel(x, y, popal);

                if (popal) {
                    cout << "popal. Eshe odin hod!" << endl;
                    computer->otvetitNaHod(x, y, popal);
                }
                else {
                    cout << "mimo" << endl;
                    computer->otvetitNaHod(x, y, popal);
                    tekushiyIgrok = 1;
                }

            }
            else {
                cout << "\n hod computera" << endl;

                int x, y;
                computer->sdelatHod(x, y);

                cout << "KompYuter vystrelil v (" << x << "," << y << ")" << endl;

                bool popal = user->vystrelit(x, y);
                computer->zapomnitVystrel(x, y, popal);

                if (!popal) {
                    user->moyaBoard[x][y] = miss;
                }

                if (popal) {
                    cout << "KompYuter popal v tvoy korabl" << endl;
                    user->otvetitNaHod(x, y, popal);
                }
                else {
                    cout << "KompYuter promahnulsya" << endl;
                    user->otvetitNaHod(x, y, popal);
                    tekushiyIgrok = 0;
                }
            }

            int userShips = user->getKorabliOstalos();
            int compShips = computer->getKorabliOstalos();

            cout << "\nchet: tvoih korabley - " << userShips;
            cout << ", korabley kompYutera - " << compShips << endl;
        }

        pokazatVseDoski();

        cout << endl;
        if (user->getKorabliOstalos() == 0) {
            cout << "KOMPYUTER POBEDIL!" << endl;
        }
        else {
            cout << "TY POBEDIL!" << endl;
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}