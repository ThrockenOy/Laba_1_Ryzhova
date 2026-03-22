#ifndef PECUS_BOT_H
#define PECUS_BOT_H

#include "../engine/TypesAndConsts.h"
#include <string>
#include <cstdlib>
#include <ctime>

class IBot {
public:
    virtual Point shoot(ShotResult previousShot) = 0;
    virtual void deploy(char (&field)[FIELD_SIZE][FIELD_SIZE]) = 0;
    virtual std::string getName() const = 0;
    virtual ~IBot() = default;
};

class PecusBot final : public IBot {
public:
    PecusBot() : m_initialized(false), m_counter(0) {}


    Point shoot(ShotResult /*previousShot*/) override {
        if (!m_initialized) {
            std::srand(static_cast<unsigned>(std::time(nullptr)));
            m_initialized = true;
        }

        Point shot;
        shot.x = std::rand() % FIELD_SIZE;
        shot.y = std::rand() % FIELD_SIZE;
        return shot;
    }


    void deploy(char (&field)[FIELD_SIZE][FIELD_SIZE]) override {
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
                field[i][j] = 'o';
            }
        }


        for (int i = 0; i < 4; ++i) field[1][1 + i] = 's';
        //3
        for (int i = 0; i < 3; ++i) field[3][1 + i] = 's';
        for (int i = 0; i < 3; ++i) field[5][1 + i] = 's';
        //2
        for (int i = 0; i < 2; ++i) field[1][4 + i] = 's';
        for (int i = 0; i < 2; ++i) field[3][4 + i] = 's';
        for (int i = 0; i < 2; ++i) field[5][4 + i] = 's';
        //1
        field[1][7] = 's';
        field[3][7] = 's';
        field[5][7] = 's';
        field[7][7] = 's';
    }


    std::string getName() const override {
        return "PecusBot";
    }

private:
    bool m_initialized;
    int m_counter;
};

#endif
