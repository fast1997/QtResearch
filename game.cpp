#include "game.h"
#include "QtDebug"
#include<QTimer>
#include<iostream>
using namespace std;

Game::Cell::Cell()
{
    owner = 0;
    possibleFlips = 0;
    r = c = 0;
    cellRect = nullptr;
    ownerCir = nullptr;

}

Game::Cell::Cell(int row, int col)
{
    owner = 0;
    possibleFlips = 0;
    r = row;
    c = col;
    cellRect = nullptr;
    ownerCir = nullptr;
}

void Game::Cell::Display()
{
    //int row = int(x) * cellSize; int column = int(y) * cellSize;
    switch(owner){
    case 0:
        ownerCir->setOpacity(Qt::BrushStyle::NoBrush);
        break;
    case 1:
        ownerCir->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        break;
    case 2:
        ownerCir->setBrush(QBrush(Qt::green,Qt::SolidPattern));
        break;
    }
}

Game::Game(QGraphicsScene * _scene, QGraphicsView * _view)
{
    view = _view;
    scene = _scene;

}

void Game::Init()
{
    qDebug () << "The function Init function is being called";
    cellSize = 50;
    movesLeft = ROWS*ROWS - 4;
    currentPlayer = 1;
    humanScore = aiScore = 2;
    gameOver = false;
    noValidMoves[0] = false;
    noValidMoves[1] = false;
    noValidMoves[3] = false;

    int middle = ROWS/2;

    for(int r = 0; r < ROWS; r++)
    {
        for( int c = 0; c < COLS; c++)
        {
            gameBoard[r][c] = Cell(r,c);

            double currentDeltaY = middle - r;
            double currentDeltaX = middle - c;
        }
    }

    gameBoard[middle][middle].owner = 1;
    gameBoard[middle-1][middle].owner = 2;
    gameBoard[middle][middle-1].owner = 2;
    gameBoard[middle-1][middle-1].owner = 1;

    CalculateValidMoves();

}



void Game::MakeMove(int Who, int Row, int Col)
{
    //this->coordinatesToFlip.clear();
    currentPlayer = Who;

        //Rechecks whether opponent can make a move or not for the Proj2Comp.
        //Otherwise the noValidMoves array will not be set correctly.
        CalculateValidMoves();
        if( validMoves.size() == 0 )
            noValidMoves[Who] = true;

        if( !noValidMoves[Who]  )
        {
            movesLeft--;
            FlipAllValid(Row, Col);
            CalculateScores( gameBoard[Row][Col].possibleFlips );
            noValidMoves[2] = false;
            noValidMoves[1] = false;
        }
        else
            cout << endl << "NO VALID MOVE FOR PLAYER " << Who << endl << endl;
}

bool Game::Done()
{
    if( noValidMoves[1] && noValidMoves[2] )
            return true;
        int numOfMaxMoves = ROWS*COLS;
        if(aiScore + humanScore >= numOfMaxMoves)
            return true;
        return false;
}

int Game::Winner()
{
    if( aiScore > humanScore )
        {
            qDebug() << "Player 2 Won!\tWinner's Score: " << aiScore << endl;
            qDebug() << "Player 1 Lost!\tLosers's Score: " << humanScore << endl;

            return 2;
        }
        else if( aiScore < humanScore ){

            qDebug() << "Player 1 Won!\tWinner's Score: " << humanScore << endl;
            qDebug() << "Player 2 Lost!\tLosers's Score: " << aiScore << endl;

            return 1;
        }
        else
        {
            qDebug() << "There was a tie!\tScore: " << aiScore << endl;
            return 3;
    }
}
void Game::updateScoreDisplay(int Score1, int Score2)

{

}

void Game::CalculateScores(int numFlipped)
{
    if( currentPlayer == 1 )
        {
            humanScore++;
            humanScore += numFlipped;
            aiScore -= numFlipped;
        }
        else
        {
            aiScore++;
            aiScore += numFlipped;
            humanScore -= numFlipped;
        }
}

void Game::CalculateValidMoves()
{
    validMoves.clear();
        for(int r = 0; r < ROWS; r++)
        {
            for(int c = 0; c < COLS; c++)
            {
                gameBoard[r][c].possibleFlips = GetNumOfValidFlips(r,c);
                if( gameBoard[r][c].possibleFlips > 0 )
                {
                    validMoves.push_back( gameBoard[r][c]);
                }
            }
        }
}

int Game::GetNumOfValidFlips(int startRow, int startCol)
{
    int totalFlips = 0;

        for(int i = 0; i < 8; i++)
        {
            totalFlips += GetNumOfValidFlipsDirection(startRow, startCol, static_cast<GameDirection>(i) );
        }

        return totalFlips;
}

int Game::GetNumOfValidFlipsDirection(int r , int c, GameDirection d)
{
    int total = 0;
        if( gameBoard[r][c].owner != 0 )
        {
            return 0;
        }

        int deltaR, deltaC;
        int checkRow = r, checkCol = c;
        Cell currentCell;

        //Based on the direction, check if the chosen move is on the border
        //of the matrix. If so, there are no valid cells to flip for the given direction.
        //If not, then set the starting cell and the detlaRow and deltaColumn based
        //on the direction of iteration.
        switch(d){
            case GameLEFT:
                if( c > 0 )//left
                {
                    checkCol = c-1;
                    deltaR = 0; deltaC = -1;
                }
                else
                    return 0;
                break;
            case GameRIGHT:
                if( c < ROWS-1 )//right
                {
                    checkCol = c+1;
                    deltaR = 0; deltaC = 1;
                }
                else
                    return 0;
                break;
            case GameUP://
                if( r > 0 )//up
                {
                    checkRow = r-1;
                    deltaR = -1; deltaC = 0;
                }
                else
                    return 0;

                break;
            case GameBOTTOM:
                if( r < ROWS-1 )//bottom
                {
                    checkRow = r+1;
                    deltaR = 1; deltaC = 0;
                }
                else
                    return 0;

                break;
            case GameLEFTUP:
                if( c > 0 && r > 0 )//left up
                {
                    checkCol = c-1; checkRow = r-1;
                    deltaR = -1; deltaC = -1;
                }
                else
                    return 0;

                break;
            case GameLEFTBOTTOM:
                if( c > 0 && r < ROWS-1 )//left bottom
                {
                    checkCol = c-1; checkRow = r+1;
                    deltaR = 1; deltaC = -1;
                }
                else
                    return 0;

                break;
            case GameRIGHTUP:
                if( c < ROWS-1 && r > 0 )//right up
                {
                    checkCol = c+1; checkRow = r-1;
                    deltaR = -1; deltaC = 1;
                }
                else
                    return 0;

                break;
            case GameRIGHTBOTTOM:
                if( c < ROWS-1 && r < ROWS-1 )//right bottom
                {
                    checkCol = c+1; checkRow = r+1;
                    deltaR = 1; deltaC = 1;
                }
                else
                    return 0;
                break;
        }

        //Initialize the starting cell and check whether that
        //cell have no owner or whether the current owner already owns it.
        //If so, then there are no valid cells to be flipped.
        currentCell = gameBoard[checkRow][checkCol];
        if( currentCell.owner == currentPlayer || currentCell.owner == 0 )
        {
            return 0;
        }

        //This while loop will iterate through the matrix until it reaches
        //a cell that is owned by the currentPlayer. As it iterate through
        //the matrix, it will increment the number of flippable cells.
        while( currentCell.owner != currentPlayer )
        {
            //If the current cell become an ownerless cell, then the
            //while iteration was invalid and the valid cells will not
            //be counted.
            if(currentCell.owner == 0)
                return 0;

            //Same idea when the currentCell row and column reach the border.
            //This means that the starting cell is not a valid move for this
            //current direction. Thus the current accumulated number of
            //possible flips will be forgotten.
            switch( d ){
                case GameLEFT:
                    if( checkCol <= 0)
                        return 0;

                    break;
                case GameRIGHT:
                    if( checkCol >= ROWS-1)
                        return 0;
                    break;
                case GameUP:
                    if( checkRow <= 0)
                        return 0;
                    break;
                case GameBOTTOM:
                    if( checkRow >= ROWS-1)
                        return 0;
                    break;
                case GameLEFTUP:
                    if( checkCol <= 0 || checkRow <= 0)
                        return 0;
                    break;
                case GameLEFTBOTTOM:
                    if(checkCol <= 0 || checkRow >= ROWS-1)
                        return 0;
                    break;
                case GameRIGHTUP:
                    if( checkCol >= ROWS-1 || checkRow <= 0)
                        return 0;
                    break;
                case GameRIGHTBOTTOM:
                    if( checkCol >= ROWS-1 || checkRow >= ROWS-1)
                        return 0;
                    break;
            }

            checkRow += deltaR; checkCol += deltaC;
            currentCell = gameBoard[checkRow][checkCol];
            total++;
        }
        return total;
}

bool Game::IsValidMove(int r, int c)
{
    if( r >= ROWS || r <= -1 || c >= COLS || c <= -1 )
            return false;
        if(gameBoard[r][c].possibleFlips > 0)
            return true;
        return false;
}

void Game::FlipAllValid(int startRow, int startCol)
{
    coordinatesToFlip.push_back(new int[2]{startRow, startCol});
    for(int i = 7; i >= 0 ; i--)
        {
            int dirNums = GetNumOfValidFlipsDirection( startRow, startCol, static_cast<GameDirection>(i) );
            if( dirNums > 0 )
            {
                FlipOnDirection( startRow, startCol, static_cast<GameDirection>(i) );
            }
        }
    gameBoard[startRow][startCol].owner = currentPlayer;
}

void Game::FlipOnDirection(int startRow, int startCol, GameDirection d)
{
    Cell currentCell;
        int deltaR, deltaC;
        switch( d ){
            case GameLEFT:
                currentCell = gameBoard[startRow][--startCol];
                deltaR = 0; deltaC = -1;
                break;
            case GameRIGHT:
                currentCell = gameBoard[startRow][++startCol];
                deltaR = 0; deltaC = 1;
                break;
            case GameUP:
                currentCell = gameBoard[--startRow][startCol];
                deltaR = -1; deltaC = 0;
                break;
            case GameBOTTOM:
                currentCell = gameBoard[++startRow][startCol];
                deltaR = 1; deltaC = 0;
                break;
            case GameLEFTUP:
                currentCell = gameBoard[--startRow][--startCol];
                deltaR = -1; deltaC = -1;
                break;
            case GameLEFTBOTTOM:
                currentCell = gameBoard[++startRow][--startCol];
                deltaR = 1; deltaC = -1;
                break;
            case GameRIGHTUP:
                currentCell = gameBoard[--startRow][++startCol];
                deltaR = -1; deltaC = 1;
                break;
            case GameRIGHTBOTTOM:
                currentCell = gameBoard[++startRow][++startCol];
                deltaR = 1; deltaC = 1;
                break;
        }

        //This while loop will iterate through the matrix based on the
        //deltaRow and deltaColumn and for each cell it vists, it will
        //change the owner to be of the currentPlayer until it reaches
        //a cell of the same owner as the currentPlayer
        while(currentCell.owner != currentPlayer)
        {
            if(currentCell.owner != currentPlayer)
                gameBoard[startRow][startCol].owner = currentPlayer;
            int * pointer = new int[2];
            pointer[0] = startRow;
            pointer[1] = startCol;
            this->coordinatesToFlip.push_back(pointer);

            startRow += deltaR;
            startCol += deltaC;
            currentCell = gameBoard[startRow][startCol];
        }
}

void Game::Click(QPoint p, int who)
{
    //qDebug() << "size of thisrect " << thisRect->rect().width() << thisRect->rect().height();
    if(thisRect->contains(p)){
            int row = int(p.x()/cellSize);
            int column = int(p.y()/cellSize);
            currentPlayer = who;
            CalculateValidMoves();
            if( validMoves.size() == 0 ){
                noValidMoves[who] = true;
                return;
            }

            if (IsValidMove(row,column))
            {
                MakeMove(who, row, column);
                updatedScreen();
            }

    }
}

void Game::drawCircle(int x, int y, int player)
{

}

void Game::updatedScreen()
{
    QSize viewSize = view->size();
    thisRect->setRect(0,0,viewSize.width(),viewSize.height());

    for (int j = 0; j < ROWS; j++){
        for (int i = 0; i < COLS; i++){
            gameBoard[j][i].Display();
        }
    }
}

void Game::setUpDisplay()
{
    thisRect = new QGraphicsRectItem(0,0,384,238);
    scene->addItem(thisRect);

    p1ScoreText = new QGraphicsTextItem();
    p1ScoreText->setPos(400,0);
    p1ScoreText->setPlainText("Player 1 Score: 0");


    p2ScoreText = new QGraphicsTextItem();
    p2ScoreText->setPos(400,50);
    p2ScoreText->setPlainText("Player 2 Score: 0");


    scene->addItem(p1ScoreText);
    scene->addItem(p2ScoreText);



    QBrush bl(Qt::SolidPattern); bl.setColor(Qt::black);
    QBrush wh(Qt::SolidPattern); wh.setColor(Qt::white);

    for (int j = 0; j < ROWS; j++){
        for (int i = 0; i < COLS; i++){
                gameBoard[j][i].cellRect = new QGraphicsRectItem();
                gameBoard[j][i].cellRect->setRect(i * cellSize,j * cellSize,cellSize,cellSize);
                //if(gameBoard[j][i].owner)
                gameBoard[j][i].ownerCir = new QGraphicsEllipseItem(i*cellSize ,j*cellSize,cellSize,cellSize);

                //gameBoard[j][i].colorOne.setStyle(Qt::SolidPattern); gameBoard[j][i].colorOne.setColor(Qt::red);
                //gameBoard[j][i].colorTwo.setStyle(Qt::SolidPattern); gameBoard[j][i].colorTwo.setColor(Qt::green);

                (i % 2 == 0) ? gameBoard[j][i].cellRect->setBrush(bl) : gameBoard[j][i].cellRect->setBrush(wh);
                scene->addItem(gameBoard[j][i].cellRect);
                gameBoard[j][i].Display();
                scene->addItem(gameBoard[j][i].ownerCir);

        }
        QBrush temp = bl;
        bl = wh;
        wh = temp;
    }

}
