#include "Bot.h"
#include <iostream>

int Pecusmain() {
    PecusBot bot;

    std::cout << "Bot name: " << bot.getName() << std::endl;

    Point shot = bot.shoot(FIRST_TURN);
    std::cout << "First shot: (" << shot.x << ", " << shot.y << ")\n";

    char battlefield[FIELD_SIZE][FIELD_SIZE];
    bot.deploy(battlefield);

    std::cout << "Deployment complete!\n";
    return 0;
}
