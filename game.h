#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
using namespace std;

const int ROWS = 8;
const int COLS = 8;

enum GameDirection {
    GameLEFT = 0,
    GameRIGHT, //1
    GameUP, //2
    GameBOTTOM, //3
    GameLEFTUP, //4
    GameLEFTBOTTOM, //5
    GameRIGHTUP, //6
    GameRIGHTBOTTOM //7
};

class Game
{
    public:
        Game ();
        Game (int w, int h, string title);
        void Init ();//Needs to be modified
        void Display (ostream & outs);//Needs to be modified

        void MakeMove (int Who, int Row, int Col);
        void Click();

        bool ChooseMove (int Who, int & Row, int & Col);//Needs to be modified
        bool AiPlayer (int Who, int & Row, int & Col);
        bool Done ();
        int Winner (ostream & outs);
    private:
        struct Cell
        {
            Cell();
            Cell(int row, int col);
            void Display(ostream & outs);

            int importance;
            int owner;
            int r, c;
            int possibleFlips;
        };
        void PrintTopBorder( ostream & outs, int maxCol );

        void CalculateScores(int numFlipped);

        void CalculateValidMoves();
        int GetNumOfValidFlips(int startRow, int startCol);
        int GetNumOfValidFlipsDirection(int, int, GameDirection);

        bool IsValidMove(int r, int c);

        void FlipAllValid(int startRow, int startCol);
        void  FlipOnDirection(int startRow, int startCol, GameDirection d);

        Cell gameBoard[ROWS][COLS];
        vector<Cell> validMoves;
        string title;
        int humanScore, aiScore;
        bool noValidMoves[3];
        bool gameOver;
        int currentPlayer;
        int movesLeft;
};

#endif // GAME_H
