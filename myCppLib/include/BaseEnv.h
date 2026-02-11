//
// Created by adam on 05/02/2026.
//

#ifndef MYCPPLIB_BASE_ENV_H
#define MYCPPLIB_BASE_ENV_H

class BaseEnv {
public:
    static void make();
    static void step();
    static void reset();
    static void get_action_space();
    static void get_observation_space();
    static void monitor();
    static void render();
    static void is_game_over();
};

#endif //MYCPPLIB_BASE_ENV_H