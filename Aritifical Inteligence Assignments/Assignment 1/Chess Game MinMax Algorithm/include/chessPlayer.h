#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include<string>
#include "ENUM.h"
#include "gameState.h"
#include "actionList.h"

class chessPlayer{
    public:
        std::string playerName;
        Color playerColor;
        chessPlayer(std::string playerName = "", Color playerColor=White){
            this->playerName = playerName;
            this->playerColor = playerColor;
        }
		int evaluationFunction(gameState*);
		int alphaBetaSearch(gameState* state,int depth,action* Move);
        virtual void decideMove(gameState* state, action* Move, int maxDepth=-1)=0;
		int maxValue(gameState* state, int alpha, int beta, int depth, action* Move,int i);
		int minValue(gameState* state, int alpha, int beta, int depth, action* Move,int j);
};

#endif // CHESSPLAYER_H
