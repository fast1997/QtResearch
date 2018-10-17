#ifndef GAME_H
#define GAME_H

#include<QGraphicsView>
#include<QGraphicsRectItem>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsScene>
#include<vector>
#include<string>
#include<QPaintEvent>

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

class Game{

public:
    Game(QGraphicsScene*,QGraphicsView*);
    void Init ();
    void MakeMove (int Who, int Row, int Col);
    bool Done();
    int Winner ();

    void setUpDisplay();
    void Click(QPoint,int Who);
    void updatedScreen();

private:
        struct Cell
        {
            Cell();
            Cell(int row, int col);
            void Display();

            int owner;
            int r, c;
            int possibleFlips;
            QGraphicsRectItem * cellRect;
            QGraphicsEllipseItem * ownerCir;
        };

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
        int boardSize;
        int theWinner;
        int cellSize;
        bool noValidMoves[3];
        bool gameOver;



        QGraphicsTextItem * p1ScoreText;
        QGraphicsTextItem * p2ScoreText;
        QGraphicsTextItem * inValidMoveDisplay;

        QGraphicsRectItem *thisRect;
        QGraphicsRectItem *boardRect;


        QGraphicsScene * scene;
        QGraphicsView * view;


};
#endif
