#ifndef ENGINE
#define ENGINE

#include "TypesAndConsts.h"
#include <array>
#include <string>
#include <tuple>

using std::array;
using std::string;
using std::to_string;


class Engine {
private:
    array< array<char, FIELD_SIZE>, FIELD_SIZE> field; // storing the field
    int turn;                    // storing turns number for timeout

    bool ShipIsDead(Point shot);
public:
    void setField(array< array<char, FIELD_SIZE>, FIELD_SIZE>& src);
    bool checkField(string &err_mes); //checking of fleet deployment; /err_mes/ - is string for error output
    ShotResult makeShot(Point shot);
    array< array<char, FIELD_SIZE>, FIELD_SIZE> & getField();

    template<typename deployFunction>
    std::tuple<bool, std::string> setFromDeploy(deployFunction & f) {
        f(reinterpret_cast<char(*) [FIELD_SIZE]>(field.data()));
        std::string err;
        auto res = checkField(err);
        return {res, err};
    }
};

#endif
