#include "Engine.h"


void Engine::setField(array< array<char, FIELD_SIZE>, FIELD_SIZE>& src) 
{
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            this->field[i][j] = src[i][j];
        }
    }
}

array< array<char, FIELD_SIZE>, FIELD_SIZE> & Engine::getField()
{
    return (this->field);
}

bool Engine::checkField(string &err_mes)
{
    int ships[GROUPS_NUM];
    for (int i=0; i<GROUPS_NUM; i++)
        ships[i] = FLEET_PATTERN[i][2];

    for (int i=0;i< FIELD_SIZE;i++)
        for (int j=0;j< FIELD_SIZE;j++)
            if (field[i][j]!='o' && field[i][j]!='s')
            {
                err_mes="incorrect symbol "+to_string(field[i][j])+'\n';
                return false;
            }

    //searching for ships
    for (int i=0; i<FIELD_SIZE; i++)
        for (int j=0; j<FIELD_SIZE; j++)
        {
            if (field[i][j]!='s') continue; //not a ship
            if (i>0 && field[i-1][j]=='s') continue; //part of another ship
            if (j>0 && field[i][j-1]=='s') continue; //part of another ship

            int si=0; //size-1 or shift from start to end
            int sj=0; //size-1 or shift from start to end

            while(i+si+1<FIELD_SIZE && field[i+si+1][j]=='s') si++;
            while(j+sj+1<FIELD_SIZE && field[i][j+sj+1]=='s') sj++;

            //checking shape
            for(int xi=i-1; xi<i+si+2; xi++)
                for(int xj=j-1; xj<j+sj+2; xj++)
                {
                    if (xi<0 || xj<0 || xi>FIELD_SIZE-1 || xj>FIELD_SIZE-1) continue; //out of borders
                    if (xi<i || xj<j || xi>i+si || xj>j+sj)
                    {
                        if (field[xi][xj]!='o')
                        {
                            err_mes = "weird shape near " + to_string(xi) + "x" + to_string(xj) + "\n";
                            return false;
                        }
                    }
                    else if (field[xi][xj]!='s')
                        {
                            err_mes = "weird shape near " + to_string(xi) + "x" + to_string(xj) + "\n";
                            return false;
                        }
                }

            //checking ship in pattern
            bool correct=false;
            for (int p=0; p<GROUPS_NUM; p++)
                if ((FLEET_PATTERN[p][0]==si+1 && FLEET_PATTERN[p][1]==sj+1) ||
                    (FLEET_PATTERN[p][1]==si+1 && FLEET_PATTERN[p][0]==sj+1))
                    {
                        correct = true;
                        ships[p]--;
                        break;
                    }

            if (!correct)
            {
                err_mes="incorrect size of ship near " + to_string(i) + "x" + to_string(j) + "\n";
                return false;
            }
        }

    //checking pattern
    bool correct = true;
    err_mes="";
    for (int p=0; p<GROUPS_NUM; p++)
    {
        if (ships[p]>0)
        {
            err_mes += "not enough " + to_string(FLEET_PATTERN[p][0]) + "x" + to_string(FLEET_PATTERN[p][1]) + " ships\n";
            correct = false;
        }
        if (ships[p]<0)
        {
            err_mes += "too much " + to_string(FLEET_PATTERN[p][0]) + "x" + to_string(FLEET_PATTERN[p][1]) + " ships\n";
            correct = false;
        }
    }
    if (!correct) return false;
    err_mes="it's fine\n";
    return true;
}

bool Engine::ShipIsDead(Point shot)
{
    int x = shot.x;
    int y = shot.y;

    switch (this->field[x][y])
    {
        case 's':
            return false;
        case 'o':
        case 'm':
            return true;
        case 'k':
            return false;
        case '0':
            return true;
        case 'h':
        {
            field[x][y] = '0';
            if (x > 0 && y > 0)
            {
                Point tmp;
                tmp.x = x-1;
                tmp.y = y-1;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (y > 0)
            {
                Point tmp;
                tmp.x = x;
                tmp.y = y-1;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (y > 0 && x < FIELD_SIZE - 1)
            {
                Point tmp;
                tmp.x = x+1;
                tmp.y = y-1;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (x < FIELD_SIZE - 1)
            {
                Point tmp;
                tmp.x = x+1;
                tmp.y = y;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (x < FIELD_SIZE - 1 && y < FIELD_SIZE - 1)
            {
                Point tmp;
                tmp.x = x+1;
                tmp.y = y+1;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (y < FIELD_SIZE - 1)
            {
                Point tmp;
                tmp.y = y+1;
                tmp.x = x;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (y < FIELD_SIZE - 1 && x > 0)
            {
                Point tmp;
                tmp.x = x-1;
                tmp.y = y+1;
                if (!ShipIsDead(tmp))
                    return false;
            }
            if (x > 0)
            {
                Point tmp;
                tmp.x = x-1;
                tmp.y = y;
                if (!ShipIsDead(tmp))
                    return false;
            }
        }
    }
    return true;
}

ShotResult Engine::makeShot(Point shot)
{
    int x = shot.x;
    int y = shot.y;

    switch (this->field[x][y])
    {
        case 'h':
            return HIT;
        case 'o':
        case 'm':
        {   
            this->field[x][y] = 'm';
            return MISS;
        }
        case 'k':
            return HIT;
        case 's':
        {
            int ships = 0;
            field[x][y] = 'h';
            if (ShipIsDead(shot))
            {
                for (int i = 0; i < FIELD_SIZE; i++)
                {
                    for (int j = 0; j < FIELD_SIZE; j++)
                    {
                        if (field[i][j] == '0')
                            field[i][j] = 'k';
                        if (field[i][j] == 's')
                            ships += 1;
                    }
                }
                if (ships)
                    return KILL;
                else
                    return WIN;
            }
    	    else
            {
                for (int i = 0; i < FIELD_SIZE; i++)
                {
                    for (int j = 0; j < FIELD_SIZE; j++)
                    {
                        if (field[i][j] == '0')
                            field[i][j] = 'h';
                    }
                }
                return HIT;
            }
        }
    }
    return MISS;
}
