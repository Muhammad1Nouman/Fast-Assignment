#include "..\\include\\chessPlayer.h"
#include "..\\include\\\ENUM.h"
#include <iostream>
#include <algorithm> 
using namespace std;

int totalPieces(chessBoard b, int player);
int getValue(int pieceNumber, int row, int col, bool endGame);
bool t = false;
struct eval_move {
	int actionIndex;
	int score;
};
int MAX_DEPTH = 2;
eval_move currBestMove;

int chessPlayer::alphaBetaSearch(gameState* state, int dept, action* Move)
{
	int ma = maxValue(state, -100000, 100000, dept, Move,0);

	return currBestMove.actionIndex;
}

int chessPlayer::maxValue(gameState* state, int alpha, int beta, int depth, action* Move,int index)
{
	if (depth == 0)
	{
		return evaluationFunction(state);
	}
	int v = -10000;
	for (int i = 0; i < sqrt(state->Actions.getActionCount()); i++)
	{
		gameState* nextState = new gameState();

		nextState->copyConstructor(state);
		nextState->Actions.getAction(i, Move);
		nextState->applyMove(*Move);
		v = std::max(v, minValue(nextState, alpha, beta, depth - 1, Move,i));
		
		if (v >= beta)
		{
			currBestMove.score = v;
			return v;
		}
		if (alpha <= v)
		{
			alpha = v;
			if (depth == MAX_DEPTH)
				currBestMove.actionIndex = i;
		
			
		}
	}
	currBestMove.score = v;
	return v;
}
int chessPlayer::minValue(gameState* state, int alpha, int beta, int depth, action* Move,int index)
{
	if (depth == 0)
	{

		return evaluationFunction(state);
	}

	int v = 10000;
	for (int i = 0; i < sqrt(state->Actions.getActionCount()); i++)
	{
		gameState* nextState = new gameState();
		nextState->copyConstructor(state);
		nextState->Actions.getAction(i, Move);
		nextState->applyMove(*Move);

		v = std::min(v, maxValue(nextState, alpha, beta, depth - 1, Move,i));
		if (v <= alpha)
		{
			return v;
		}
		beta = std::min(beta, v);
	}

	return v;
}

int chessPlayer::evaluationFunction(gameState* currState)
{
	// returns an integer
	chessBoard b = currState->Board;
	int relativePiecesScore = 0;
	int accumulativeScore = 0;
	int multiplier = 1; //increases in central part of board
	int kingR = -1;
	int kingC = -1;
	int player = 1; //1 for white, -1 for black.
	if (currState->getPlayer() == Black) {
		player = -1;
	}

	int numOfPieces = totalPieces(b, player);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			relativePiecesScore += player * getValue(b.board[i][j], i, j, numOfPieces < 8);
			if (player*b.board[i][j] == 6) {
				kingR = i; //saving row
				kingC = j; //saving col
			}
		}
	}



	accumulativeScore += relativePiecesScore;

	int piecesAroundKing = 0;
	if (kingC < 7 && player*b.board[kingR][kingC + 1] > 0) {
		piecesAroundKing++;
		if (kingR < 7 && player*b.board[kingR + 1][kingC + 1] > 0) {
			piecesAroundKing++;
		}
		if (kingR > 0 && player*b.board[kingR - 1][kingC + 1] > 0) {
			piecesAroundKing++;
		}
	}
	if (kingC > 0 && player*b.board[kingR][kingC - 1] > 0) {
		piecesAroundKing++;
		if (kingR < 7 && player*b.board[kingR + 1][kingC - 1] > 0) {
			piecesAroundKing++;
		}
		if (kingR > 0 && player*b.board[kingR - 1][kingC - 1] > 0) {
			piecesAroundKing++;
		}
	}
	if (kingR > 0 && player*b.board[kingR - 1][kingC] > 0) {
		piecesAroundKing++;
	}
	if (kingR < 7 && player*b.board[kingR + 1][kingC] > 0) {
		piecesAroundKing++;
	}

	accumulativeScore += piecesAroundKing * 10;

	return accumulativeScore;
}


int totalPieces(chessBoard b, int player) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (player*b.board[i][j] > 0) {
				count++;
			}
		}
	}
	return count;
}

//4: Rook
//2: Knight
//3: Bishop
//5: Queen
//6: King
//1: Pawn


//below values are taken from https://www.chessprogramming.org/Simplified_Evaluation_Function

int pawnValue[8][8] = { { 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 50, 50, 50, 50, 50, 50, 50, 50 },
						{ 10, 10, 20, 30, 30, 20, 10, 10},
						{ 5, 5, 10, 25, 25, 10, 5, 5},
						{ 0, 0, 0, 20, 20, 0, 0, 0},
						{ 5, -5, -10, 0, 0, -10, -5, 5},
						{ 5, 10, 10, -20, -20, 10, 10, 5},
						{ 0, 0, 0, 0, 0, 0, 0, 0} };

int knightValue[8][8] = { { -50,-40,-30,-30,-30,-30,-40,-50 },
						{ -40,-20,  0,  0,  0,  0,-20,-40 },
						{ -30,  0, 10, 15, 15, 10,  0,-30 },
						{ -30,  5, 15, 20, 20, 15,  5,-30 },
						{ -30,  0, 15, 20, 20, 15,  0,-30 },
						{ -30,  5, 10, 15, 15, 10,  5,-30 },
						{ -40,-20,  0,  5,  5,  0,-20,-40 },
						{ -50,-40,-30,-30,-30,-30,-40,-50 } };

int bishopValue[8][8] = { { -20,-10,-10,-10,-10,-10,-10,-20 },
							{ -10,  0,  0,  0,  0,  0,  0,-10 },
							{ -10,  0,  5, 10, 10,  5,  0,-10 },
							{ -10,  5,  5, 10, 10,  5,  5,-10 },
							{ -10,  0, 10, 10, 10, 10,  0,-10 },
							{ -10, 10, 10, 10, 10, 10, 10,-10 },
							{ -10,  5,  0,  0,  0,  0,  5,-10 },
							{ -20,-10,-10,-10,-10,-10,-10,-20} };

int rookValue[8][8] = { { 0,  0,  0,  0,  0,  0,  0,  0 },
						{ 5, 10, 10, 10, 10, 10, 10,  5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ 0,  0,  0,  5,  5,  0,  0,  0 } };

int queenValue[8][8] = { { -20,-10,-10, -5, -5,-10,-10,-20 },
						{ -10,  0,  0,  0,  0,  0,  0,-10 },
						{ -10,  0,  5,  5,  5,  5,  0,-10 },
						{ -5,  0,  5,  5,  5,  5,  0, -5 },
						{ 0,  0,  5,  5,  5,  5,  0, -5 },
						{ -10,  5,  5,  5,  5,  5,  0,-10 },
						{ -10,  0,  5,  0,  0,  0,  0,-10 },
						{ -20, -10, -10, -5, -5, -10, -10, -20 } };

int kingMidValue[8][8] = { { -30,-40,-40,-50,-50,-40,-40,-30 },
							{ -30,-40,-40,-50,-50,-40,-40,-30 },
							{ -30,-40,-40,-50,-50,-40,-40,-30 },
							{ -30,-40,-40,-50,-50,-40,-40,-30 },
							{ -20,-30,-30,-40,-40,-30,-30,-20 },
							{ -10,-20,-20,-20,-20,-20,-20,-10 },
							{ 20, 20,  0,  0,  0,  0, 20, 20 },
							{ 20, 30, 10,  0,  0, 10, 30, 20 } };

int kingEndValue[8][8] = { { -50,-40,-30,-20,-20,-30,-40,-50 },
							{ -30,-20,-10,  0,  0,-10,-20,-30 },
							{ -30,-10, 20, 30, 30, 20,-10,-30 },
							{ -30,-10, 30, 40, 40, 30,-10,-30 },
							{ -30,-10, 30, 40, 40, 30,-10,-30 },
							{ -30,-10, 20, 30, 30, 20,-10,-30 },
							{ -30,-30,  0,  0,  0,  0,-30,-30 },
							{ -50,-30,-30,-30,-30,-30,-30,-50 } };


int getValue(int pieceNumber, int row, int col, bool endGame) {
	if (pieceNumber == 1) {
		return pawnValue[row][col];
	}
	if (pieceNumber == 4) {
		return rookValue[row][col];
	}
	if (pieceNumber == 2) {
		return knightValue[row][col];
	}
	if (pieceNumber == 3) {
		return bishopValue[row][col];
	}
	if (pieceNumber == 5) {
		return queenValue[row][col];
	}
	if (pieceNumber == 6 && endGame) {
		return kingEndValue[row][col];
	}
	else {
		return kingMidValue[row][col];
	}
}