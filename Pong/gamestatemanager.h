#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

class GameState;

class GameStateManager
{
public:
    virtual ~GameStateManager() {}
    virtual void changeState(GameState* state)=0;
    virtual GameState* getCurrentState()=0;
    virtual void update()=0;
};

#endif // GAMESTATEMANAGER_H
