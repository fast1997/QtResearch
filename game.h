#ifndef GAME_H
#define GAME_H
<<<<<<< HEAD

#include<QGraphicsView>
#include<QGraphicsRectItem>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsScene>
#include<vector>
#include<string>
#include<QPaintEvent>
=======
#include <iostream>
#include <vector>
#include <QPoint>
#include <QGraphicsRectItem>
#include <QPen>
#include <QPaintEvent>
#include<QGraphicsScene>
#include <QtDebug>
#include <QMainWindow>
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0

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

<<<<<<< HEAD
class Game{

public:
    Game(QGraphicsScene*,QGraphicsView*);
    void Init ();
    void MakeMove (int Who, int Row, int Col);
    bool Done();
    int Winner ();

    void setUpDisplay();
    void Click(QMouseEvent*);
    void updatedScreen();

private:
        struct Cell
        {
            Cell();
            Cell(int row, int col);
=======
class Game
{
    public:
        Game (QGraphicsScene * s, QMainWindow * mw);
        void Init ();//Needs to be modified
        void Display ();//Needs to be modified

        void MakeMove (int Who, int Row, int Col);
        void Click(QPoint position);

        bool ChooseMove (int Who, int & Row, int & Col);//Needs to be modified
        bool AiPlayer (int Who, int & Row, int & Col);
        bool Done ();
        int Winner (ostream & outs);

    private:
        struct Cell
        {
            Cell();
            Cell(int row, int col,QGraphicsScene * s);
            void Display(ostream & outs);
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0

            int owner;
            int r, c;
            int possibleFlips;
            QGraphicsRectItem * cellRect;
        };
<<<<<<< HEAD
=======

        void SetUpRects();
        void PrintTopBorder( ostream & outs, int maxCol );
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0

        void CalculateScores(int numFlipped);
        void CalculateValidMoves();
        int GetNumOfValidFlips(int startRow, int startCol);
        int GetNumOfValidFlipsDirection(int, int, GameDirection);


        void updateScoreDisplay(int, int);
        void drawMove(int x, int y);
        void drawCircle(int x, int y, int player);

        bool IsValidMove(int r, int c);
        void FlipAllValid(int startRow, int startCol);
        void  FlipOnDirection(int startRow, int startCol, GameDirection d);

        Cell gameBoard[ROWS][COLS];
        vector<Cell> validMoves;
        std::vector<int *> coordinatesToFlip;
        string title;
        int humanScore, aiScore;
        int currentPlayer;
        int movesLeft;
<<<<<<< HEAD
        int boardSize;
        int theWinner;

        bool noValidMoves[3];
        bool gameOver;

        QBrush colorOne;
        QBrush colorTwo;

        QGraphicsTextItem * p1ScoreText;
        QGraphicsTextItem * p2ScoreText;
        QGraphicsTextItem * inValidMoveDisplay;
=======

        int maxWidth;
        int maxHeight;

        QGraphicsScene * scene;
        QMainWindow * mWindow;
        QGraphicsRectItem *gameBoardRect;
        QGraphicsRectItem *dataRect;
};
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0

        QGraphicsRectItem *thisRect;
        QGraphicsRectItem *boardRect;


        QGraphicsScene * scene;
        QGraphicsView * view;


};
#endif
