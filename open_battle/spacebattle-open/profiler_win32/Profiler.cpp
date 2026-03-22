#include "../engine/TypesAndConsts.h"
#include "../invalidbot/InvalidBot.h"
#include "../engine/Engine.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <array>
#include <ctime>

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

enum Cell {
    ALIVE,
    HITTEN,
    MISSED,
    FIELD,
    KILLED
};
HANDLE hout;

void print(char c, bool newc)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hout, &csbiInfo);
    WORD wOldColorAttrs = csbiInfo.wAttributes;
    switch (c)
    {
        case 's':
            SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << 'o'; break;
        case 'h':
            SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << 'h'; break;
        case 'x':
            SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
            cout << 'x'; break;
        case 'o':
            SetConsoleTextAttribute(hout, FOREGROUND_INTENSITY);
            cout << '.'; break;
        case 'k':
            SetConsoleTextAttribute(hout, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
            cout << 'k'; break;
        default:
            cout << ' '; break;
    }
    SetConsoleTextAttribute(hout, wOldColorAttrs);
}

void PrintField(array< array<char, FIELD_SIZE>, FIELD_SIZE> & field)
{
    DWORD l;
    COORD point = {0, 0};
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    FillConsoleOutputAttribute(hout, 0, 2000, point, &l);

    for (int i = 0; i < FIELD_SIZE; i++)
    {
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            //point.X = i * 2;
            //point.Y = j;
            //SetConsoleCursorPosition(hout, point);
            print(field[i][j], false);
            cout << " ";
        }
        cout << endl;
    }

    //point.X = 0;
    //point.Y = FIELD_SIZE + 3;

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hout, &csbiInfo);
    WORD wOldColorAttrs = csbiInfo.wAttributes;
    WORD light = ( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY );

    SetConsoleTextAttribute(hout, light);
    //SetConsoleCursorPosition(hout, point);
    cout << endl << endl << "Press 'Power' to continue" << endl << endl;

    SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "    o - alive ship\n";
    SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "    h - hitten ship\n";
    SetConsoleTextAttribute(hout, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "    k - killed ship\n";
    SetConsoleTextAttribute(hout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    cout << "    x - missed shoot\n";
    SetConsoleTextAttribute(hout, FOREGROUND_INTENSITY);
    cout << "    . - field\n\n";

    getch();
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

    PrintField(eng.getField());

    int turns = 0;

    Result result;

    auto clStart_round = clock();

    while(prevShot != WIN)
    {
        Point shot = pecus::shoot(prevShot);
        prevShot = eng.makeShot(shot);

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

        PrintField(eng.getField());

        auto clStart_round = clock();

        while(prevShot != WIN)
        {
            Point shot = shoot(prevShot);
            prevShot = eng.makeShot(shot);

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

        PrintField(eng.getField());

        auto clStart_round = clock();

        while(prevShot != WIN)
        {
            Point shot = pecus::shoot(prevShot);
            prevShot = eng.makeShot(shot);

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

    PrintField(eng.getField());

    int turns = 0;

    auto clStart_round = clock();

    while(prevShot != WIN)
    {
        Point shot = shoot(prevShot);
        prevShot = eng.makeShot(shot);

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
