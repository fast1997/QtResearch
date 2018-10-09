#include "Game.h"
#include <iomanip>
#include <cmath>

Game::Cell::Cell()
{
    owner = 0;
    importance = 0;
    possibleFlips = 0;
    r = c = 0;
}

Game::Cell::Cell(int row, int col)
{
    owner = 0;
    importance = 0;
    possibleFlips = 0;
    r = row;
    c = col;
}
//Displays each cell based on who the owner of that cell is. Player 1 will be displayed as a red 1.
//Player 2 will be displayed as a blue 2.
//No owner is just a blank
void Game::Cell::Display( ostream & Out )
{
    switch(owner){
        case 1:
            break;
        case 2:
            break;
        default:

            break;
    }
}

Game::Game ()
{
   maxWidth = 400;
   maxHeight = 700;
    title = "Othello/Reversi";
    Init();
}
Game::Game(int w, int h, string t)
{
    maxWidth = w;
    maxHeight = h;
    title = t;
    Init();
}
void Game:: Click(QPoint position)
{

}
//Reset all attributes of the game back to the original.
//noValidMoves will be used to determine if there are no
//valid moves for both players.
void Game::Init ()
{
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
            gameBoard[r][c].importance = 10 - (int)(sqrt( (currentDeltaX * currentDeltaX) + ( currentDeltaY * currentDeltaY ) ));

            if( r == 0 )
                gameBoard[r][c].importance = 9;
            if( r == ROWS-1 )
                gameBoard[r][c].importance = 9;
            if( c == 0 )
                gameBoard[r][c].importance = 9;
            if( c == COLS-1 )
                gameBoard[r][c].importance = 9;
            if( (r == 0 && c == 0) || (r == 0 && c == COLS-1) || (r == ROWS-1 && c == COLS-1) || ( r == ROWS-1 && c == 0) )
                gameBoard[r][c].importance = 10;

        }
    }

    gameBoard[middle][middle].owner = 1;
    gameBoard[middle-1][middle].owner = 2;
    gameBoard[middle][middle-1].owner = 2;
    gameBoard[middle-1][middle-1].owner = 1;

    CalculateValidMoves();
}
//Helper function to print the top border of the game display.
void Game::PrintTopBorder( ostream & Out, int maxCol )
{
    Out << "  ";
    for(int i = 0; i < maxCol; i++)
    {
        if( i == maxCol-1 )
            Out << "+---+";
        else
            Out << "+---";
    }
}

//Display the detail of the game, such as the gameboard of the current state of the game.
//and the score of each players.
void Game::Display (ostream & Out)
{

}

//Determines whether the game is over.
//If both player's index in the noValidMoves array are true,
//both players were not able to make a move. Thus, the game is over
//because there are no valid move for both players to make.
//Otherwise, if both players' score reach the total number of cells
//on the gameboard, then the game is over.
bool Game::Done ()
{
    if( noValidMoves[1] && noValidMoves[2] )
        return true;
    int numOfMaxMoves = ROWS*COLS;
    if(aiScore + humanScore >= numOfMaxMoves)
        return true;
    return false;
}

//Determines the winner based on the scores of each players. Then return
//the winning player's number. If there is a tied, then number 3 will be returned.
int Game::Winner (ostream & Out)
{
    if( aiScore > humanScore )
    {
        Out << "Player AI Won!\tScore: " << aiScore << endl;
        return 2;
    }
    else if( aiScore < humanScore )
    {
        Out << "Player HUMAN Won!\tScore: " << humanScore << endl;
        return 1;
    }
    else
    {
        Out << "There was a tie!\tScore: " << aiScore << endl;
        return 3;
    }

}

//This function will check whether the current player is able to make any valid
//moves. If so, then it will calculate and add to their scores and flip all
//the valid cells based on their move.
void Game::MakeMove (int Who, int Row, int Col)
{
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

//This function is purely for the human player.
//Uses stringstream to check for invalid inputs such as datatypes
//that are not intergers.
bool Game::ChooseMove (int Who, int & Row, int & Col)
{ // Prompt user for location of move
    currentPlayer = Who;
    CalculateValidMoves();
    if( validMoves.size() == 0 )
    {
        noValidMoves[Who] = true;
        return false;
    }


    return true;
}

//This function will be used for hte AI.
//AI will go through the validMoves vector and determine if there
//are any valid corner cells. If so, then it will choose the corner
//with the largest possible flips. Otherwise, it will choose the cell
//that is closest to the center.
bool Game::AiPlayer (int Who, int & Row, int & Col)
{ // AI determines desired location of move
    currentPlayer = Who;
    CalculateValidMoves();
    if( validMoves.size() == 0 )
    {
        noValidMoves[Who] = true;
        return false;
    }


    //int middle = ROWS/2;
    //Cell shortestDistanceCell;
    //double shortestDistance = ROWS * COLS;

    vector<Cell> highestPriotity;

    int mostImportant = 0;
    for(int i = 0; i < validMoves.size(); i++)
    {
        if( mostImportant < validMoves[i].importance )
            mostImportant = validMoves[i].importance;
    }

    for(int i = 0; i < validMoves.size(); i++)
    {
        if( mostImportant == validMoves[i].importance )
            highestPriotity.push_back(  validMoves[i] );
    }

    Cell largest;
    for( int i = 0; i < highestPriotity.size(); i++)
    {
        if( largest.possibleFlips < highestPriotity[i].possibleFlips )
            largest = highestPriotity[i];
    }

    Row = largest.r;
    Col = largest.c;
    cout << "Row: " << Row << endl;
    cout << "Column: " << Col << endl;

    return true;

}

//This function will determine if hte chosen row and column
//are within the boundary of the gameboard matrix
bool Game::IsValidMove(int r, int c)
{
    if( r >= ROWS || r <= -1 || c >= COLS || c <= -1 )
        return false;
    if(gameBoard[r][c].possibleFlips > 0)
        return true;
    return false;
}

//This function will calculate the valid moves on the board
//for the currentPlayer and push it into the validMoves vector.
//It will determine the number of flips possible of each cell,
//and if the number of flips are greater than zero, it is a valid cell.
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

//This function will add the number of flipped cells to the
//score of the current player and decrement that number from the
//other player's score. It will always increment the current player
//score by 1 for the new cell they have claimed.
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

//This function will flip all the valid cells of the chosen move.
//It will check whether a certain direction needs to be flipped
//bassed on the number of possible flips of that direction.
//If the number of possible flips are more than zero, then it will
//flip all the flippable cells of that direction.
//Finally, it will set the owner of the chosen cell to be of
//the current player.
void Game::FlipAllValid(int startRow, int startCol)
{
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

//This function will flip based on the enumerated direction passed
//in the parameter. Based on the direction, the deltaRow and deltaColumn,
//which will be used to move from the starting cell to the final cell, will
//be set accordingly to the direction.
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
        startRow += deltaR;
        startCol += deltaC;
        currentCell = gameBoard[startRow][startCol];
    }

}

//This function will calculate the total possible flips of a certain cell
//in the matrix at row = startRow and column = startCol.
//It wiil accumulate the total amount of possible flips of each direction.
int Game::GetNumOfValidFlips(int startRow, int startCol)
{
    int totalFlips = 0;

    for(int i = 0; i < 8; i++)
    {
        totalFlips += GetNumOfValidFlipsDirection(startRow, startCol, static_cast<GameDirection>(i) );
    }

    return totalFlips;
}

//This function will accumulate the total possible flips of a given direction.
//It will determine the starting cell, deltaRow and deltaColumn to iterate through
//the matrix.
int Game::GetNumOfValidFlipsDirection(int r, int c, GameDirection d)
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
