/****************************************************************************** 
Program 4: Restaurant Inspections
This program reads data from various files and displays analyticals based on the data.
Author: Sri Vishal Payaniappa
System: Visual Studio Code * On MacOS
Oct 28, 2023
*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Date Class
class Date{

    public:

    /*
    Breif: Sets Month.
    Param: Month to be set
    Returns : None
    */
    void setMonth(int newMonth){
        month = newMonth;
    }

    /*
    Breif: Gets Month.
    Param: None.
    Returns : Month.
    */
    int getMonth()const{
        return month;
    }

    /*
    Breif: Sets Day.
    Param: Day to be set.
    Return : None.
    */
    void setDay(int newDay){
        day = newDay;
    }

    /*
    Breif: Gets Day.
    Param: None.
    Returns : Day.
    */
    int getDay()const{
        return day;
    }

    /*
    Breif: Sets Year.
    Param: Year to be set.
    Return : None.
    */
    void setYear(int newYear){
        year = newYear;
    }

    /*
    Breif: Gets Year.
    Param: None.
    Returns : Year.
    */
    int getYear()const{
        return year;
    }
 
    private:
    int month;
    int day;
    int year;
};

// Restaurant Class
class Restaurant{

    public:
    // Name
    /*
    Breif: Sets Name.
    Param: Name to be set.
    Return : None.
    */
    void setName(string newName){
        name = newName;
    }
    
    /*
    Breif: Gets Name.
    Param: None.
    Returns : Name.
    */
    string getName()const{
        return name;
    }

    // Address
    /*
    Breif: Sets Address.
    Param: Address to be set.
    Return : None.
    */
    void setAddress(string newAddress){
        address = newAddress;
    }

    /*
    Breif: Gets Address.
    Param: None.
    Returns : Address.
    */
    string getAddress()const{
        return address;
    }
    
    // Date
    Date date;

    // Risk
    /*
    Breif: Sets Risk.
    Param: Risk to be set.
    Return : None.
    */
    void setRisk(string newRisk){
        risk = newRisk;
    }

    /*
    Breif: Gets Risk.
    Param: None.
    Returns : Risk.
    */
    string getRisk()const{
        return risk;
    }

    // Risk Inspec
    /*
    Breif: Sets Risk Inspection.
    Param: Risk Inspection to be set.
    Return : None.
    */
    void setRiskInspec(string newRiskInspec){
        riskInspec = newRiskInspec;
    }

    /*
    Breif: Gets Risk Inspection.
    Param: None.
    Returns : Risk Inspection.
    */
    string getRiskInspec()const{
        return riskInspec;
    }

    // Neighbourhood
    /*
    Breif: Sets Neighborhood.
    Param: Neighborhood to be set.
    Return : None.
    */
    void setNeighbourhood(string newNeighbourhood){
        neighbourhood = newNeighbourhood;
    }

    /*
    Breif: Gets Neighborhood.
    Param: None.
    Returns : Neighborhood.
    */
    string getNeighbourhood()const{
        return neighbourhood;
    }
    
    private:
    string name;
    string address;
    string risk;
    string riskInspec;
    string neighbourhood;



};

/*
Show Menu:
* displays the menu. 
*/ 
void showMenu(){

    cout << "Select a menu option: " << endl;
    cout << "   1. Display overall inspection information" << endl;
    cout << "   2. Display risk percentages" << endl;
    cout << "   3. Display passing numbers by neighborhood" << endl;
    cout << "   4. Search for restaurant by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: ";


}

/*
Unique Neighbourhood:

* Creates a vector of unique Neighbourhoods. 
* Inputs: Vector of all restaurants of type Restaurant.
* Outputs: Vector of strings of all the unqiue neighbourhoods.

*/ 
vector<string> uniqueNeighbourhood(const vector<Restaurant> &restaurants){
   
   vector <string> unqNeighs;
   int vecSize = restaurants.size();
    for(int i = 0; i < vecSize ; i++){
        bool present = false;
        for(int j = 0 ; j < unqNeighs.size() ; j++){
            if(restaurants.at(i).getNeighbourhood() == unqNeighs.at(j)){
               present = true;
               break;
            }
        }
        
        if (!present) {
            unqNeighs.push_back(restaurants.at(i).getNeighbourhood());
        }

    }

    return unqNeighs;
    
}

/*
* Format Date
* Formats the Date to be displayed.
* Inputs: Any integer
* Outputs a string that adds a 0 in front of given number if needed.
*/
string formatDate(int date){

    string formatedDate;

    if(date <= 9){
        formatedDate = "0" + to_string(date);
        return formatedDate;
    }

    else{
        return to_string(date);
    }
}

/*
* Recent Date (Choice 1)
* Displays Basic Stats, and the most recent inspection date passing.
* Inputs: Vector of all restaurants of type Restaurant.
* Outputs: All the defined requirements of the User Choice (1) 
*/
void recentDate( const vector<Restaurant> &restaurants ){

    int vecSize = restaurants.size();
    int recentRestaurant = 0;
    int tempDay = 0;
    int tempMonth = 0;
    int tempYear = 0;

    for (int i = 0; i < vecSize; i++) {
        if (restaurants.at(i).getRiskInspec() == "Pass" || restaurants.at(i).getRiskInspec() == "Conditional") { 
        if (restaurants.at(i).date.getYear() > tempYear ||(restaurants.at(i).date.getYear() == tempYear && restaurants.at(i).date.getMonth() > tempMonth) ||(restaurants.at(i).date.getYear() == tempYear && restaurants.at(i).date.getMonth() == tempMonth && restaurants.at(i).date.getDay() > tempDay)) {
            tempYear = restaurants.at(i).date.getYear();
            tempMonth = restaurants.at(i).date.getMonth();
            tempDay = restaurants.at(i).date.getDay();
            recentRestaurant = i;
        }
    }
}
    
    cout << "Most recent passing inspection was of " << restaurants.at(recentRestaurant).getName() << " on "  << formatDate(tempMonth) << "-" << formatDate(tempDay) << "-" << formatDate(tempYear) << endl;
    cout << endl;
}

/*
* Calculate Risks (Choice 2)
* Displays All the percentages of risks.
* Inputs: number of high, low, and medium level of risks.
* Outputs: The percentages of risks. 
*/
void calculateRisks(int& high, int& medium, int& low ){

    double totalrisks = high + medium + low;
    double percentHigh = (high/totalrisks) * 100;
    double percentMedium = (medium/totalrisks) * 100;
    double percentLow = (low/totalrisks) * 100;

    cout << "High risk: " << fixed << setprecision(1) << percentHigh << "%" << endl;
    cout << "Medium risk: " << fixed << setprecision(1) << percentMedium << "%" << endl;
    cout << "Low risk: " << fixed << setprecision(1) << percentLow << "%" << endl;
    cout << endl;

}

/*
* Risks by Neighbourhoods (Choice 3)
* Displays All unique neighbourhoods and their respective Risk stats.
* Inputs: Vector of all restaurants of type Restaurant.
* Outputs: The table just like shown with all the neighbourhoods.
*/
void risksNeighbourhood(const vector<Restaurant> &restaurants){
    
    vector <string> neighbourhoods = uniqueNeighbourhood(restaurants);
    int neighbourhoodsSize = neighbourhoods.size();
    int vecSize = restaurants.size();

    cout << "Neighborhood               Passed Cond. Pass     Failed" << endl;
    cout << "============               ====== ==========     ======" << endl;
    for(int i = 0; i < neighbourhoodsSize; i++){
        int pass = 0;
        int conPass = 0;
        int fail = 0;
        int spacing = 0;
        for(int j = 0; j < vecSize; j++){
            if(neighbourhoods.at(i) == restaurants.at(j).getNeighbourhood()){
                if(restaurants.at(j).getRiskInspec() == "Pass"){
                    pass++;
                }
                
                else if(restaurants.at(j).getRiskInspec() == "Conditional"){
                    conPass++;
                }
                
                else if(restaurants.at(j).getRiskInspec() == "Fail"){
                    fail++;
                }
            }
        }
        spacing = 33 - neighbourhoods.at(i).length();
        cout << neighbourhoods.at(i) << setw(spacing) << pass << setw(11) <<  conPass << setw(11) << fail << endl;
    }

}

/*
* Recent Date (Choice 4)
* Searches for Restaurants based on the search query.
* Inputs: Vector of all restaurants of type Restaurant.
* Outputs: Results of the Search along with the address, date of inspection, and Inspection Results.
*/
void searchRestraunt(const vector<Restaurant> &restaurants){

    int vecSize = restaurants.size();
    string userInput;
    string month = "";
    string day = "";

    cout << "Enter restaurant to search for: ";
    cin >> userInput;
    
    // Changes input to uppercase.
    int inputSize = userInput.size();
    for (int i = 0; i < inputSize; i++) {
    userInput[i] = toupper(userInput[i]);
    }
    // cout << userInput;

    for(int i = 0; i < vecSize; i++){

        if(restaurants.at(i).getName().find(userInput) != string::npos ){        
            cout << "Restaurant: " << restaurants.at(i).getName() << endl;
            cout << "Address: " << restaurants.at(i).getAddress() << endl;
            cout << "Inspection Date: " << formatDate(restaurants.at(i).date.getMonth())  << "-" << formatDate(restaurants.at(i).date.getDay()) << "-" << formatDate(restaurants.at(i).date.getYear()) << endl;
            cout << "Inspection Result: " << restaurants.at(i).getRiskInspec() << endl;
            cout << endl;
        }
        
    }
}


int main(){

    // Variables
    string userFile = "near-uic.txt";   //"near-uic.txt" ; "belmont-cragin.txt"
    string tempLine;

    int userInput = 0;
    int numrestaurants = 0;
    int numPass = 0;
    int numH = 0;
    int numM = 0;
    int numL = 0;

    ifstream inFS;

    // Menu
    cout << "Enter the data file to use: ";
    cin >> userFile;
    
    inFS.open(userFile);
    
    vector <Restaurant> restaurants; // Vector of Restaurant Objects
    Restaurant tempRestraunt;

    // Start Reading and Exatracting Data from File.
    
    while(!inFS.eof()){
    for(int i = 0; i < 6; i++){

        switch(i){

            case 0: // Name
            getline(inFS, tempLine, ',');
            tempRestraunt.setName(tempLine);
            numrestaurants++;
            break;

            case 1: // Address
            getline(inFS, tempLine, ',');
            tempRestraunt.setAddress(tempLine);
            break;

            case 2: // Date
            getline(inFS, tempLine, ',');
            tempRestraunt.date.setMonth(stoi(tempLine.substr(0,2)));
            tempRestraunt.date.setDay(stoi(tempLine.substr(3,2)));
            tempRestraunt.date.setYear(stoi(tempLine.substr(6,4)));
            break;

            case 3: // Risk
            getline(inFS, tempLine, ',');
            tempRestraunt.setRisk(tempLine);

            if(tempLine == "H"){
                numH++;
            }
            if (tempLine == "M")
            {
                numM++;
            }
            if (tempLine == "L")
            {
                numL++;
            }
            break;

            case 4: // Risk Inspection
            getline(inFS, tempLine, ',');
            tempRestraunt.setRiskInspec(tempLine);
            if(tempLine == "Pass" || tempLine == "Conditional"){
                numPass++;
            }
            break;

            case 5: // Neighbourhood
            getline(inFS, tempLine);
            tempRestraunt.setNeighbourhood(tempLine);
            break;

            default:
            break;
            }
        }
    restaurants.push_back(tempRestraunt); // Each Object is pushed back after it's fully created.
    }

    inFS.close();
    bool loopOn = true;
    
    // User Menu
    while (loopOn){

        showMenu();
        cin >> userInput;
        cout << endl;

        if(userInput == 1){ // USER CHOICE : 1
            cout << "Number of restaurants: " << numrestaurants << endl;
            cout << "Number that pass: " << numPass << endl;
            recentDate(restaurants);
        }

        else if (userInput == 2){ // USER CHOICE : 2
            calculateRisks(numH,numM,numL);
        }

        else if (userInput == 3){ // USER CHOICE : 3
            risksNeighbourhood(restaurants);
        }

        else if (userInput == 4){ // USER CHOICE : 4
            searchRestraunt(restaurants);
        }
        
        else if (userInput == 5){ // USER CHOICE : 5
            loopOn = false;
            break;
        }
        else{
            loopOn = false;
            break;
        }
 
    }
    return 0;
}