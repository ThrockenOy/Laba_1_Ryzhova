#include "../engine/TypesAndConsts.h"
#include "../invalidbot/InvalidBot.h"
#include "../engine/Engine.h"

// #include "TypesAndConsts.h"
// #include "InvalidBot.h"
// #include "Engine.h"

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <array>
#define DEBUG TRUE

using std::array;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;

namespace pecus
{
    #include "Bot.h"
}

struct Result
{
    int round_ticks;
    int turns;
};

void Log(array< array<char, FIELD_SIZE>, FIELD_SIZE> & field)
{
    fstream file;
    file.open("Log.txt", std::ios::out | std::ios::app);
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            file << field[i][j];
        }
        file << endl;
    }
    file << "\n\n";
    file.close();
}

void PrintField(array< array<char, FIELD_SIZE>, FIELD_SIZE> & field)
{
    initscr();
        
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);    // field
    init_pair(2, COLOR_BLACK, COLOR_WHITE);   // text 
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // ship
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // hit
    init_pair(5, COLOR_CYAN, COLOR_BLACK);    // killed
    init_pair(6, COLOR_RED, COLOR_BLACK);     // miss
    attron(COLOR_PAIR(2));
        
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            switch(field[i][j])
            {
                case 's':
                {   
                    attron(COLOR_PAIR(3)); 
                    printw("s ");
                    break;
                }
                case 'h':
                {
                    attron(COLOR_PAIR(4));
                    printw("x ");
                    break;
                }
                case 'm':
                {
                    attron(COLOR_PAIR(6));
                    printw("x ");
                    break;
                }
                case 'o':
                {   
                    attron(COLOR_PAIR(1));
                    printw("o ");
                    break;
                }
                case 'k':
                {   
                    attron(COLOR_PAIR(5));
                    printw("k ");
                    break;
                }
            }
        }
        printw("\n");
    }

    attron(COLOR_PAIR(2));
    mvaddstr(1, 40, "Press 'Space' to continue");
    attron(COLOR_PAIR(3));
    mvaddstr(3, 40, "s - alive ship");
    attron(COLOR_PAIR(4));
    mvaddstr(5, 40, "h - hitten ship");
    attron(COLOR_PAIR(6));
    mvaddstr(7, 40, "x - missed shoot");
    attron(COLOR_PAIR(1));
    mvaddstr(9, 40, "o - field");
    attron(COLOR_PAIR(5));
    mvaddstr(11, 40, "k - killed ship");
    getch();
    refresh();
    endwin();
}

void PrintResult(Result res)
{
    
}

Result PShootsB()
{
    char field[FIELD_SIZE][FIELD_SIZE];

    Engine eng;
    eng.setFromDeploy(deploy);
    ShotResult prevShot = FIRST_TURN;

    move(0,0);
    PrintField(eng.getField());

    int turns = 0;

    Result result;
    
    auto clStart_round = clock();    

    while(prevShot != WIN and turns < FIELD_SIZE * FIELD_SIZE)
    {
        Point shot = pecus::shoot(prevShot);
        prevShot = eng.makeShot(shot);

        move(0,0);
        PrintField(eng.getField());

        turns ++;
        Log(eng.getField());
    }
    auto clEnd_round = clock();   

    result.round_ticks = clEnd_round - clStart_round;
    result.turns = turns;
    return result;
}

Result BShootsP()
{
    int turns = 0;

    char field[FIELD_SIZE][FIELD_SIZE];
    
    Engine eng;
    auto res = eng.setFromDeploy((pecus::deploy));

    Result result;

    if (!std::get<0>(res))
    {   
        cout << std::get<1>(res) << endl;
        result.turns = 0;
        result.round_ticks = 0;
    }
    else
    {
        ShotResult prevShot = FIRST_TURN;

        move(0,0);
        PrintField(eng.getField());

        auto clStart_round = clock();

        while(prevShot != WIN and turns <= FIELD_SIZE * FIELD_SIZE)
        {
            Point shot = shoot(prevShot);
            prevShot = eng.makeShot(shot);

            move(0,0);
            PrintField(eng.getField());

            turns ++;
            Log(eng.getField());
        }

        auto clEnd_round = clock();   

        result.round_ticks = clEnd_round - clStart_round;
        result.turns = turns;
    }

    return result;
}

Result PShootsP()
{
    int turns = 0;

    char field[FIELD_SIZE][FIELD_SIZE];
    
    Engine eng;
    auto res = eng.setFromDeploy(pecus::deploy);
    Result result;

    if (!std::get<0>(res))
    {   
        cout << std::get<1>(res) << endl;
        result.turns = 0;
        result.round_ticks = 0;
    }
    else
    {    
        ShotResult prevShot = FIRST_TURN;

        move(0,0);
        PrintField(eng.getField());

        auto clStart_round = clock();

        while(prevShot != WIN and turns <= FIELD_SIZE * FIELD_SIZE)
        {
            Point shot = pecus::shoot(prevShot);
            prevShot = eng.makeShot(shot);
            
            move(0,0);
            PrintField(eng.getField());

            turns ++;
            Log(eng.getField());
        }
        auto clEnd_round = clock();   

        result.round_ticks = clEnd_round - clStart_round;
        result.turns = turns;
    }

    return result;
}


Result BShootsB()
{
    char field[FIELD_SIZE][FIELD_SIZE];

    Engine eng;
    eng.setFromDeploy(deploy);
    ShotResult prevShot = FIRST_TURN;

    move(0,0);
    PrintField(eng.getField());

    int turns = 0;
    
    auto clStart_round = clock();    

    while(prevShot != WIN and turns <= FIELD_SIZE * FIELD_SIZE)
    {
        Point shot = shoot(prevShot);
        prevShot = eng.makeShot(shot);

        move(0,0);
        PrintField(eng.getField());

        turns ++;
        Log(eng.getField());
    }

    auto clEnd_round = clock();   

    Result result;
    result.round_ticks = clEnd_round - clStart_round;
    result.turns = turns;

    return result;
}

Result SwitchModes()
{
    int mode;
    cout << "\nEnter mode number: " << endl;
    cout << "// Enter 0 for list of modes //\n" << endl;
    cin >> mode;
    switch (mode)
    {
        case 0:
        {
            cout << "1 - Your bot shoots down invalidbot's field" << endl;
            cout << "2 - Invalidbot shoots down your field" << endl;
            cout << "3 - Your bot shoots down your field" << endl;
            if (DEBUG)
                cout << "4 - Fight of invalids" << endl;
            return SwitchModes();
        }
        case 1:
        {
            return PShootsB();
        }
        case 2:
        {
            return BShootsP();
        }
        case 3:
        {
            return PShootsP();
        }
        case 4:
        {
            if (DEBUG)
                return BShootsB();
            else
            {
                cout << "Wrong mode" << endl;
                Result result;
                result.round_ticks = 0;
                result.turns = 0;
                return result;
            }
        }
        default:
        {
            cout << "Wrong mode" << endl;
            Result result;
            result.round_ticks = 0;
            result.turns = 0;
            return result;
        }
    }
}

int main()
{
    bool file_exist = static_cast<bool>(std::ifstream("Log.txt"));
    if (file_exist)
        std::remove("Log.txt");

    Result res = SwitchModes();
    cout << "\nProcessor ticks per round: " << res.round_ticks << endl;
    cout << "Turns: " << res.turns << endl;
    return 0;
}
