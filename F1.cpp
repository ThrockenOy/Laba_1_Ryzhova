#include <iostream>
#include <string>

using namespace std;


class F1Team {
protected:
    string name;
    string engine;
    string principal;
    int points;
    string driverNames[2];
    int driverNumbers[2];
    int driverCount;

public:
    // Конструктор
    F1Team(string teamName, string engineType, string teamPrincipal) {
        name = teamName;
        engine = engineType;
        principal = teamPrincipal;
        points = 0;
        driverCount = 0;
    }

    // Деструктор
    ~F1Team() {
    }

    void addDriver(string driverName, int number) {
        if (driverCount < 2) {
            driverNames[driverCount] = driverName;
            driverNumbers[driverCount] = number;
            driverCount++;
        }
    }

    void addPoints(int newPoints) {
        points += newPoints;
    }

    void show() {
        cout << "\n" << name << endl;
        cout << " Engine: " << engine << endl;
        cout << " Principal: " << principal << endl;
        cout << " Points: " << points << endl;
        cout << " Drivers:" << endl;
        for (int i = 0; i < driverCount; i++) {
            cout << "  - " << driverNames[i] << ", " << driverNumbers[i] << endl;
        }
    }

    virtual void showUniqueFeature() {
        cout << "Team has " << points << " points" << endl;
    }
};


class Alpine: public F1Team {
public:
    Alpine(): F1Team("Alpine", "Mercedes", "Bruno Famin") {}
    void showUniqueFeature() override {
        cout << "Alpine has " << points << " points" << endl;
    }
};

class AstonMartin: public F1Team {
public:
    AstonMartin() : F1Team("Aston Martin", "Honda", "Mike Krack") {}
    void showUniqueFeature() override {
        cout << "Aston Martin has " << points << " points" << endl;
    }
};

class Williams: public F1Team {
public:
    Williams(): F1Team("Williams", "Mercedes", "James Vowles") {}
    void showUniqueFeature() override {
        cout << "Williams has " << points << " points" << endl;
    }
};

class Audi: public F1Team {
public:
    Audi(): F1Team("Audi", "Audi", "Andreas Seidl") {}
    void showUniqueFeature() override {
        cout << "Audi has " << points << " points" << endl;
    }
};

class Cadillac: public F1Team {
public:
    Cadillac(): F1Team("Cadillac", "Ferrari", "Graeme Lowdon") {}
    void showUniqueFeature() override {
        cout << "Cadillac has " << points << " points" << endl;
    }
};

class Ferrari: public F1Team {
public:
    Ferrari(): F1Team("Ferrari", "Ferrari", "Frederic Vasseur") {}
    void showUniqueFeature() override {
        cout << "Ferrari has " << points << " points" << endl;
    }
};

class Haas: public F1Team {
public:
    Haas(): F1Team("Haas", "Ferrari", "Ayao Komatsu") {}
    void showUniqueFeature() override {
        cout << "Haas has " << points << " points" << endl;
    }
};

class McLaren: public F1Team {
public:
    McLaren(): F1Team("McLaren", "Mercedes", "Andrea Stella") {}
    void showUniqueFeature() override {
        cout << "McLaren has " << points << " points" << endl;
    }
};

class Mercedes: public F1Team {
public:
    Mercedes(): F1Team("Mercedes", "Mercedes", "Toto Wolff") {}
    void showUniqueFeature() override {
        cout << "Mercedes has " << points << " points" << endl;
    }
};

class RedBull: public F1Team {
public:
    RedBull(): F1Team("Red Bull", "Red Bull", "Christian Horner") {}
    void showUniqueFeature() override {
        cout << "Red Bull has " << points << " points" << endl;
    }
};

class RacingBulls: public F1Team {
public:
    RacingBulls(): F1Team("Racing Bulls", "Red Bull", "Laurent Mekies") {}
    void showUniqueFeature() override {
        cout << "Racing Bulls has " << points << " points" << endl;
    }
};


int main() {
    Alpine alpine;
    AstonMartin aston;
    Williams williams;
    Audi audi;
    Cadillac cadillac;
    Ferrari ferrari;
    Haas haas;
    McLaren mclaren;
    Mercedes mercedes;
    RedBull redbull;
    RacingBulls bulls;


    alpine.addDriver("Pierre Gasly", 10);
    alpine.addDriver("Franco Colapinto", 43);

    aston.addDriver("Fernando Alonso", 14);
    aston.addDriver("Lance Stroll", 18);

    williams.addDriver("Alexander Albon", 23);
    williams.addDriver(" Carlos Sainz Jr.", 55);

    audi.addDriver("Nico Hulkenberg", 27);
    audi.addDriver("Gabriel Bortoleto", 5);

    cadillac.addDriver("Sergio Perez", 11);
    cadillac.addDriver("Valtteri Bottas", 77);

    ferrari.addDriver("Charles Leclerc", 16);
    ferrari.addDriver("Lewis Hamilton", 44);

    haas.addDriver("Esteban Ocon", 31);
    haas.addDriver("Oliver Bearman", 87);

    mclaren.addDriver("Lando Norris", 1);
    mclaren.addDriver("Oscar Piastri", 81);

    mercedes.addDriver("George Russell", 63);
    mercedes.addDriver("Kimi Antonelli", 12);

    redbull.addDriver("Max Verstappen", 3);
    redbull.addDriver("Isack Hadjar", 6);

    bulls.addDriver("Liam Lawson", 30);
    bulls.addDriver("Arvid Lindblad", 41);


    redbull.addPoints(44);
    mercedes.addPoints(30);
    ferrari.addPoints(27);
    mclaren.addPoints(18);
    aston.addPoints(15);
    alpine.addPoints(12);
    williams.addPoints(10);
    bulls.addPoints(8);
    haas.addPoints(6);
    cadillac.addPoints(4);
    audi.addPoints(2);


    alpine.show();
    aston.show();
    williams.show();
    audi.show();
    cadillac.show();
    ferrari.show();
    haas.show();
    mclaren.show();
    mercedes.show();
    redbull.show();
    bulls.show();

    cout << "Alpine: "; alpine.showUniqueFeature();
    cout << "Aston Martin: "; aston.showUniqueFeature();
    cout << "Williams: "; williams.showUniqueFeature();
    cout << "Audi: "; audi.showUniqueFeature();
    cout << "Cadillac: "; cadillac.showUniqueFeature();
    cout << "Ferrari: "; ferrari.showUniqueFeature();
    cout << "Haas: "; haas.showUniqueFeature();
    cout << "McLaren: "; mclaren.showUniqueFeature();
    cout << "Mercedes: "; mercedes.showUniqueFeature();
    cout << "Red Bull: "; redbull.showUniqueFeature();
    cout << "Racing Bulls: "; bulls.showUniqueFeature();

    return 0;
}
