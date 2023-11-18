/****************************************************************************** 
Program 3: Traffic Jam
This program is a computer replication of the game Rush Hour! 
Author: Sri Vishal Payaniappa
System: Visual Studio Code * On MacOS
Oct 6, 2023
*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

// Functions

/*
CarPresent:
* Checks whether the car is on board.
* Inputs: car(first character of user input), gameBoard(the game board)
* Outputs: true or false.
*/ 
bool carPresent(char car, char gameBoard[6][6]) {
    for(int i = 0; i <6; i++){
        for(int j = 0; j < 6; j++){
            if (car == gameBoard[i][j]){
                return true;
                break;
            }
        }
    
    }
    return false;
}

/*
minValue:
* gives the lowest value in a vector.
* Inputs: numbers(a vector which has the possible moves for any car)
* Outputs: minValue(lowest value in Vector)
*/ 
int minValue(const vector<int>& numbers) {
    
    if (numbers.empty()) {
        return 0; 
    }

    int minValue = numbers[0]; 

    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < minValue) {
            minValue = numbers[i];
        }
    }
    return minValue;
}

/*
displayBoard:
* Displays the Game Board.
* Inputs: gameboard
* Outputs: void function so no return, but the board is outputted in the terminal
*/ 
void displayBoard(char gameBoard[6][6]) {

    cout << "--------" << endl;
    for(int i = 0; i < 6; i++){
        cout << "|";
        for(int j = 0; j < 6; j++){
            cout << gameBoard[i][j];
        }
        if (i == 2)
        cout << "=";
        else
        cout << "|";
        cout << endl;
    }
    cout << "--------" << endl;
}

/*
spacesAllowedRD:
* Calculates and return the number of spaces allowed in the Right or Down direction.
* Inputs: spaces(number of spaces to move), car, dirc(direction), gameboard
* Outputs: newSpaces(the spaces which can be moved for the cars) or spaces, depending on spaces.
*/ 

int spacesAllowedRD(int spaces, char car, char dirc, char gameBoard[6][6]){ // change to int to return spaces.

    int newSpaces;
    int moves;
    vector <int> setOfMoves;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            
            // For Right
            if(dirc == 'R'){
                if(car == gameBoard[i][j] ){ 
                    moves = 0;
                    for(int x = j+1; x <= j+spaces; x++){
                        if(gameBoard[i][x] == '.' || gameBoard[i][x] == car){
                            moves++;
                        }
                        else{
                            break;
                        }
                    }
                    setOfMoves.push_back(moves);
                    newSpaces = minValue(setOfMoves);
                }
            } // Right ends here   
            
            // For down
            else if(dirc =='D'){

                if(car == gameBoard[i][j]){
                    moves = 0;
                    for(int x = i+1; x <= i + spaces ; x++){
                        if(gameBoard[x][j] == '.' || gameBoard[x][j] == car){
                            moves++;
                        }
                        else{
                            break;
                        }
                    }
                    setOfMoves.push_back(moves);
                    newSpaces = minValue(setOfMoves);
                } // Down ends here
            } 
        }
    }
   if(newSpaces <= spaces)
    return newSpaces;

    else
    return spaces;
}

/*
spacesAllowedLU:
* Calculates and return the number of spaces allowed in the Left or Up direction.
* Inputs: spaces(number of spaces to move), car, dirc(direction), gameboard
* Outputs: newSpaces(the spaces which can be moved for the cars) or spaces, depending on spaces.
*/

int spacesAllowedLU(int spaces, char car, char dirc, char gameBoard[6][6]){ // change to int to return spaces.

    int newSpaces;
    int moves;
    vector <int> setOfMoves;

    for(int i = 5; i >= 0; i--){
        for(int j = 5; j >= 0; j--){
            
            // For left
            if(dirc == 'L'){
                if(car ==gameBoard[i][j]){

                    moves = 0;
                    for(int x = j-1; x <= j + spaces; x--){
                        if(gameBoard[i][x] == '.' || gameBoard[i][x] == car){
                            moves++;
                        }
                        else{
                            break;
                        }
                    }
                    setOfMoves.push_back(moves);
                    newSpaces = minValue(setOfMoves);
                }
            } // Left ends here   

            // For Up
            else if(dirc =='U'){

                if(car ==gameBoard[i][j]){

                    moves = 0;
                    for(int x = i-1; x <= i + spaces; x--){
                        if(gameBoard[x][j] == '.'|| gameBoard[x][j] == car ){
                            moves++;
                        }
                        else{
                            break;
                        }
                    }
                    setOfMoves.push_back(moves);
                    newSpaces = minValue(setOfMoves);
                }
            } // Up ends here
        }
    }
    

    if(newSpaces <= spaces)
    return newSpaces;

    else
    return spaces;
}


/*
Car Move:
* Moves the car according to user input and while also applying the conditions on the cars. 
* The cars are moved by replacing their current position to '.' and shifting the car to the new space.
* Inputs: userMove(User's input for the game), gameBoard
* Outputs: newSpaces(the spaces which can be moved for the cars) or spaces, depending on spaces.
*/ 

void carMove(string userMove, char gameBoard[6][6]){
    
    char car , direc;
    int spaces, updSpaces;
    
    // Variables from user input
    car = toupper(userMove.at(0));
    spaces = userMove.at(1) - '0';
    direc = toupper(userMove.at(2));
    
    if(direc == 'L' || direc == 'U'){
        updSpaces = spacesAllowedLU(spaces,car, direc ,gameBoard);
    }   
    
    else if (direc == 'R' || direc == 'D'){
        updSpaces = spacesAllowedRD(spaces,car, direc, gameBoard);
    }

    if(direc == 'R'|| direc == 'U'){

        for(int i = 0; i < 6; i++){
            for(int j = 5; j >= 0; j--){
                if(car == gameBoard[i][j] && direc == 'R'){ // Car moving when direction is R
                    char temp = gameBoard[i][j];
                    gameBoard[i][j] = '.';
                    gameBoard[i][j + updSpaces] = temp;
                }

                else if (car == gameBoard[i][j] && direc == 'U'){ // Car moving when direction is U
                    char temp = gameBoard[i][j];
                    gameBoard[i][j] = '.';
                    gameBoard[i - updSpaces][j] = temp;
                }
            }
        
        }
    }
    
    else if ( direc == 'L'|| direc == 'D' ){

        for(int i = 5; i >= 0 ; i--){
            for(int j = 0; j < 6; j++){
                if(car == gameBoard[i][j] && direc == 'L'){ // Car moving when direction is L
                    char temp = gameBoard[i][j];
                    gameBoard[i][j] = '.';
                    gameBoard[i][j - updSpaces] = temp;
                }

                else if(car == gameBoard[i][j] && direc == 'D'){ // Car moving when direction is D
                    char temp = gameBoard[i][j];
                    gameBoard[i][j] = '.';
                    gameBoard[i + updSpaces][j] = temp;
                }
            }
        }
    }
    displayBoard(gameBoard);
}

// Main Code

int main(){
    
    // Variables
    string userFile = "board.txt"; 
    char gameBoard[6][6];
    bool gameOn = true;
    string tempLine;
    ifstream inFS;

    cin >> userFile;
    inFS.open(userFile);
    
    // Making the Game Board
   for(int i = 0; i < 6; i++){
        inFS >> tempLine;
        for(int j = 0; j < 6; j++){
            if (tempLine[j] == '-')
                tempLine.at(j) = '.';
            gameBoard[i][j] = tempLine[j];
        }
   }
    inFS.close();
    displayBoard(gameBoard);
    
    // Game Loop
    while (gameOn) {
        
        string userInput;
        bool carOnBoard;
        
        cout << "Enter next move (or Q to quit): ";
        cin >> userInput;

        if (toupper(userInput[0]) == 'Q'){ 
            gameOn = false;
            break;
        }

        carOnBoard = carPresent(toupper(userInput[0]), gameBoard); 

        if (carOnBoard){
            carMove(userInput, gameBoard);
        }
        else{
            cout << "That car is not on the board." << endl;
        }

        // Win Condition
        if(gameBoard[2][5] == 'R'){
            cout << "You win! Congratulations!" << endl;
            gameOn = false;
            break;
        }
    }
    return 0;
}