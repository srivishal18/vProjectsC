/****************************************************************************** 
Program 2: Twenty Four
This program can display all 3185 solutions to the game 24, and allows the user to play the game!
Author: Sri Vishal Payaniappa
System: Visual Studio Code * On MacOS
Sep 7, 2023
*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
ResultCalculation:

* Calculates an expression where the operator is interpreted as a number. 

* Inputs: numOne(first number of the expression), numTwo(second number of the expression), oper(Operator of the expression, interpreted as a number.)

* Outputs: result( the final value of the expression using two numbers and the operator).

*/ 

double resultCalculation( double numOne,  double numTwo, int Oper){
    
    double result = 0;

    switch (Oper){
        case 1:
        result = numOne + numTwo;
        break;

        case 2:
        result = numOne - numTwo;
        break;

        case 3:
        result = numOne / numTwo;
        break;

        case 4:
        result = numOne * numTwo;
        break;

    }
    
    return result;

}

/*

numToOper:
* This function takes in operNum, which is a number and then interprets it as a symbol.
* This is used for displaying the solutions for the game 24.

* Inputs: operNum ( An operator interpreted as a number.)

* Outputs: varOper ( the operator itself, like +,-,/,*)

*/
string numToOper(int operNum){

    string varOper;

    switch(operNum){
        case 1:
        varOper = '+';
        break;

        case 2:
        varOper = '-';
        break;

        case 3:
        varOper = '/';
        break;

        case 4:
        varOper = '*';
        break;

    }



    return varOper;

}

/*
puzzleChecker:
This function is how we check if the user is solving the puzzle the right way.
It takes in the first and second number of a operation and also the operator as a string.
it returns a result of the user's choice of operation.
After all operations are done, we check if the user got 24.

* Inputs: numOne(first number of the expression), numTwo(second number of the expression), oper(Operator of the expression, it decides what to do with the numbers.)

* Outputs: interResult( Based on the Oper, the numbers are calculated.)

*/
double puzzleChecker( double numOne,  double numTwo, char Oper) {

    double interResult;

    if (Oper == '+')
    interResult = numOne + numTwo;

    else if (Oper == '-')
    interResult = numOne - numTwo;

    else if (Oper == '*')
    interResult = numOne * numTwo;

    else if (Oper == '/')
    interResult = numOne / numTwo;

    return interResult;
}

/*
generateMenu:
* It displays the Introduction to the game 24.
* No inputs/outputs.

*/
void generateMenu(){
    cout << "Welcome to the game of Twenty Four." << endl;
    cout << "Combine the four numbers shown below," << endl;
    cout << "in the order shown below, using the operators" << endl;
    cout << "(+, -, *, / ) to yield the value 24. " << endl;
    cout << "**** Begin Debug Display ****" << endl;
}

int main()
{
    double result;
    double tempResult1, tempResult2, tempResult3;
    int count = 0;
    int startValue, endValue; // The values for user specified range
    int num1, num2, num3, num4; // These are the numbers for the randomly chosen puzzle
    
    string userOperators;
    string ansOper1, ansOper2, ansOper3; // Operators for the randomly chosen puzzle.

    // this is where a puzzle is chosen randomly. 
    srand(time(0));
    int randPuzzle = rand() % 3185;
    

    generateMenu();
    cout << "Enter the beginning solution to be printed: " ;
    cin >> startValue;

    cout << "Enter the end solution to be printed: " ;
    cin >> endValue;
    


    // This loop iterates through all possible combinations of the 4 numbers and 3 operators. 
    for (double i = 1 ; i <=9 ; i++){
        for (double j = 1; j <= 9; j++){
            for (double k = 1; k<= 9; k++){
                for (double l = 1; l<= 9; l++){
                    for (int a = 1; a<= 4; a++) {
                        for ( int b = 1; b <=4; b++){
                            for ( int c = 1; c <=4; c++){

                                result = resultCalculation(resultCalculation(resultCalculation(i,j,a),k,b),l,c); // Calculates all the possibilties of numbers and operators.
                                
                                if (result == 24){ // checks if result is 24 and displays the combination if it is in specified range.
                                    count++;
                                    if (count >= startValue && count <= endValue){
                                        cout << count << ":" << i  << numToOper(a)  << j  << numToOper(b) << k  << numToOper(c) << l  << "=24" << endl;
                                    }
                                
                                    if (count == randPuzzle){
                                        num1 = i;
                                        num2 = j;
                                        num3 = k;
                                        num4 = l;
                                        ansOper1 = numToOper(a);
                                        ansOper2 = numToOper(b);
                                        ansOper3 = numToOper(c);
                                    }
                                }



                            }
                        }

                    }

                    
                }
            }
           
        }

    }
    
    // Displays random puzzle and the start of the game.
    cout << "Puzzle chosen is #" <<randPuzzle << ":" << num1  << ansOper1  << num2  << ansOper2 << num3  << ansOper3 << num4  <<  endl;
    cout << "**** End of the Debug Display ****" << endl;
    cout << "The numbers to use are " << num1 << " " << num2 << " " << num3 << " " << num4 << endl;
    cout << "Enter the three operators to be used (+, -, * or / ):" << endl;
    cin >> userOperators;

    // checks to make sure the user enters 3 charecters.
    while(userOperators.size() != 3){
        cout << "invalid number of characters entered, please try again" << endl;
        cin >> userOperators;
        cout << endl;
    }
    
    // checks to make sure the user enters valid charecters.
    for (int i = 0; i <= 2; i++){
        if (userOperators.at(i) == '+' || userOperators.at(i) == '-' || userOperators.at(i) == '*' || userOperators.at(i) == '/'  ){
            continue;
        }

        else{
            cout << "invalid characters entered, please try again" << endl;
            cin >> userOperators;
        }
    }

    // Calculates user's choices of expressions.
    tempResult1 = puzzleChecker(num1, num2, userOperators.at(0));
    tempResult2 = puzzleChecker(tempResult1, num3, userOperators.at(1));
    tempResult3 = puzzleChecker(tempResult2, num4, userOperators.at(2));
    
    // Outputs user's work
    cout << num1 << " " << userOperators.at(0) << " " << num2 << " =" << tempResult1 << endl;
    cout << tempResult1 << " " << userOperators.at(1) << " " << num3 << " =" << tempResult2 << endl;
    cout << tempResult2 << " " << userOperators.at(2) << " " << num4 << " =" << tempResult3 << endl;
    
    // Checking if the user got it right.
    if (tempResult3 == 24){
        cout << "Well Done!" << endl;
    }

    else{
        cout << "incorrect: The correct answer was:" << endl;
        cout <<  num1 << ansOper1 << num2 << ansOper2 << num3 << ansOper3 << num4 << endl;

    }
    return 0;
}