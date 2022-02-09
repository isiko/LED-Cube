// A 3D Version of Conway's game of life
#include <Arduino.h>
#include <Animation.h>

class GameOfLife : public Animation {
public:
    GameOfLife(int maxIterations, int maxFrames, int pStartingPoints);

    ledState getState(int kFrame) override;

    void reset() override;

private:
    bool state[xLen][yLen][zLen] = {{{false}}};
    bool tempState[xLen][yLen][zLen];

    int startingPoints;
    int maxSteps;
    int step = 0;
    const int minSurvival = 5;
    const int maxSurvival = 6;
    const int resurection = 4;

    int checkLifeCells(int x, int y, int z) const;
    bool getNextCellState(int x, int y, int z);

    void addRandomCell();

    void resetState();
};

GameOfLife::GameOfLife(int maxIterations, int pMaxSteps, int pStartingPoints) : Animation(maxIterations) {
    startingPoints = pStartingPoints;
    maxSteps = pMaxSteps;
}

ledState GameOfLife::getState(int kFrame) {
    step++;

    if (step > maxSteps && maxIterations>0){
        resetState();
    }

    if (step > 1) {
        for (int x = 0; x < xLen; x++)
            for (int y = 0; y < yLen; y++)
                for (int z = 0; z < zLen; z++)
                    tempState[x][y][z] = getNextCellState(x, y, z);

        bool stepIsDone = true;
        for (int x = 0; x < xLen; x++)
            for (int y = 0; y < yLen; y++)
                for (int z = 0; z < zLen; z++) {
                    state[x][y][z] = tempState[x][y][z];
                    if (state[x][y][z]) stepIsDone = false;
                }

        if(stepIsDone)
            resetState();

        return tempState;
    }

    for (int i = 0; i < startingPoints; ++i) {
        addRandomCell();
    }

    return state;
}

void GameOfLife::addRandomCell(){
    int cell[3];

    do {
        cell[0] = random(xLen);
        cell[1] = random(yLen);
        cell[2] = random(zLen);
    } while (state[cell[0]][cell[1]][cell[2]]);
    state[cell[0]][cell[1]][cell[2]] = true;
}

int GameOfLife::checkLifeCells(int xCell, int yCell, int zCell) const {
    int lifeCells = 0;
    for (int x = xCell - 1; x <= xCell + 1; ++x) {
        for (int y = yCell - 1; y <= yCell + 1; ++y) {
            for (int z = zCell - 1; z <= zCell + 1; ++z) {
                if ((x >= 0 && y >= 0 && z >= 0) && (x < xLen && y < yLen && z < zLen) && state[x][y][z])
                    lifeCells++;
            }
        }
    }

    lifeCells -= state[xCell][yCell][zCell];

    return lifeCells;
}

bool GameOfLife::getNextCellState(int x, int y, int z) {

    int life = checkLifeCells(x, y, z);
    if (state[x][y][z] && (minSurvival <= life && life <= maxSurvival)) return true;
    if (!state[x][y][z] && life == resurection) return true;

    return false;
}

void GameOfLife::resetState(){
    memset(state, 0, sizeof(state));
    iterations++;
    step = 0;
}

void GameOfLife::reset() {
    resetState();
    iterations = 0;
}