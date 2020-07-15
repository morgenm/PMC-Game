/*
PMC
PMC is the game engine itself. It controls all other subengines and
controls the main game loop. It controls the Messaging System.
*/

#pragma once

class PMC {
public:
    PMC(); //Constructs all other engines and the messaging system
    void run(); //Runs the engine.
private:
    bool m_IsGameRunning;
};
