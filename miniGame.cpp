#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

void board();
int compChoiceTic();
int checkwinner();
void whoWon();
void menu();
int computerChoice(int);
void outcome(int, int);
void playerMoves(int);
void computerMoves(int);
void welcomeMessage();
int rpcWinner (int, int);
void clearBoard();
bool hangWin(int);
int ticWinner();
void Info(int, string, string, int = -1);
void score(int RRR, int HM, int TTT, double& num);

//global variable so it can easily be accessed
char options[9] = {'1','2','3','4','5','6','7','8','9'};

enum location{
    MENU, TTT, RPS, HANGMAN, EXIT
};

string convert(location l);
//seting up enum to display where you are going to/from
string convert(location l){
    if(l == 0) return "Menu";
    else if(l == 1) return "Tic Tac Toe";
    else if(l == 2) return "Rock Paper Scissors";
    else if(l == 3) return "Hang-Man";
    else if(l == 4) return "Exit";
    else{
        return "Invalid number. Redirecting to Menu D:<";
    }
}

int main(){
    //opens file to store wins/losses/ties
    fstream userFile;
    userFile.open("Score.txt", ios::out);
    int compWinTic = 0;
    int userWinTic = 0;
    int tieTic = 0;
    int compWinRRR = 0;
    int userWinRRR = 0;
    int tieRRR = 0;
    int compWinHang = 0;
    int userWinHang = 0;
    string choices = "menu";
    location userLocation;
    int num = 0;

    while(choices == "menu"){
        cout << "You are currently chilling in " << convert(userLocation) << endl;
        cout << setfill('-') << setw(70) << '\n';
        welcomeMessage();
        cout << setfill('-') << setw(70) << '\n';
        //user validation
        do {

            if(cin.fail()){
                cout << "ERROR: wrong data type\n";
                cin.clear();
                cin.ignore(4096, '\n');
            }
            cout << "Enter a number 1-4: ";
            cin >> num;

        }while(num <= 0 || num > 4);

        //userLocation = static_cast<location>(num);
        cout << "------------------------------------------------------------------" << endl;

        //displays where you are going to and where you are going from
        cout << convert(userLocation) << " -----> ";
        userLocation = static_cast<location>(num);
        cout << convert(userLocation) << endl;

///////////////////////Tic Tac Toe//////////////////////////////
        string option = "yes";
        if(num == 1){
            int optionT = 1;
            while(optionT == 1){
                //call clearboard function incase user wants to play again
                clearBoard();
                //updates location
                userLocation = static_cast<location>(num);

                cout << "Welcome to my Tic Tac Toe!" << endl;
                board();
                int winner = -1;
                while(winner == -1){
                    int option = 0;
                    cout << endl;
                    //validation for user input
                    do {

                        if(cin.fail()){
                            cout << "ERROR: wrong data type\n";
                            cin.clear();
                            cin.ignore(4096, '\n');
                        }
                        cout << "Choose an spot: ";
                        cin >> option;

                    }while(option < 1 || option > 9);
                    //makes it so the user can't choose a spot already taken
                    while(options[option-1] == 'X' || options[option-1] == 'O'){
                        cout << "Error, that spot is already taken" << endl;
                        cout << "Choose a different spot: " << endl;
                        cin >> option;
                    }

                    playerMoves(option);
                    //if last move is player, break so computer doesn't try to move
                    if(options[0] != '1' && options[1] != '2' && options[2] != '3' && options[3] != '4' && options[4] != '5' && options[5] != '6' && options[6] != '7' && options[7] != '8' && options[8] != '9'){
                        break;
                    }
                    board();
                    //calls compChoiceTic for a number
                    int compMove = compChoiceTic();
                    //uses that number to move somewhere
                    computerMoves(compMove);

                    board();
                    cout << "The computer has chosen spot " << compMove << "!" << endl;
                    //checks if there is a winner, if so, will break out of while loop bc
                    //it will return -1
                    winner = checkwinner();

                }
                //displays the final board and who won
                board();
                whoWon();

                //adds a tic to the result of the game
                if(ticWinner() == 1){
                    userWinTic++;
                }
                if(ticWinner() == -1){
                    compWinTic++;
                }
                if(ticWinner() == 0){
                    tieTic++;
                }
                //displays a menu for you to choose what to do
                cout << endl;
                cout << "Play Again (1) " << endl;
                cout << "Go to Menu (2) " << endl;
                cout << "Exit (3) " << endl;
                //validate user input
                do {

                    if(cin.fail()){
                        cout << "ERROR: wrong data type\n";
                        cin.clear();
                        cin.ignore(4096, '\n');
                    }
                    cout << "Choose an option: ";
                    cin >> optionT;

                }while(optionT < 1 || optionT > 3);


                //assigns a number to the users choice so that the location can update
            }
            if(optionT == 1){
                num = 1;
            }
            if(optionT == 2){
                num = 0;
            }
            if(optionT == 3){
                num = 4;
            }
            //location updates here
            cout << setfill('-') << setw(70) << '\n';
            cout << convert(userLocation) << " -------> ";
            userLocation = static_cast<location>(num);
            cout << convert(userLocation) << endl;
        }

///////////////////////Rock Paper Scissors//////////////////////////////
        if(num == 2){
            int option = 1;
            while(option == 1){
                //generates a random number for the computer to choose from
                srand(time(0));
                int randNum = 1 + rand() % (3 - 1 + 1);
                int choice = 0;
                menu();
                //user validation
                do {

                    if(cin.fail()){
                        cout << "ERROR: wrong data type\n";
                        cin.clear();
                        cin.ignore(4096, '\n');
                    }
                    cout << "Enter your choice: ";
                    cin >> choice;
                    cout << choice;
                }while(choice < 1 || choice > 3);
                //calls a function that assigns the random number
                //(1-3) to rock, paper, or scissors

                computerChoice(randNum);
                cout << setfill('~') << setw(70) << '\n';
                //calls outcome function to determine a winner
                outcome(choice, randNum);
                cout << endl;
                //updates the win/loss/ties
                if(rpcWinner(choice, randNum) == 0){
                    tieRRR++;
                }
                if(rpcWinner(choice, randNum) == 1){
                    compWinRRR++;
                }
                if(rpcWinner(choice, randNum) == 2){
                    userWinRRR++;
                }
                //displays menu for user to choose what to do
                cout << "Play Again (1)" << endl;
                cout << "Menu (2)" << endl;
                cout << "Exit (3)" << endl;
                //validation for user input
                do {

                    if(cin.fail()){
                        cout << "ERROR: wrong data type\n";
                        cin.clear();
                        cin.ignore(4096, '\n');
                    }
                    cout << "Choose an option: ";
                    cin >> option;

                }while(option < 1 || option > 3);

                //cin >> option;
                cout << endl;
            }
            //assigns numbers for the location variable
            if(option == 1){
                num = 2;
            }
            if(option == 2){
                num = 0;
            }
            if(option == 3){
                num = 4;
            }
            cout << setfill('-') << setw(70) << '\n';
            cout << convert(userLocation) << " -------> ";
            userLocation = static_cast<location>(num);
            cout << convert(userLocation) << endl;
        }


///////////////////////////////Hang Man///////////////////////////////////////
        if(num == 3){
            const int ROW_SIZE = 5;
            const int COL_SIZE = 5;
            int option = 1;
            while(option == 1){
                cout << "Welcome to Hang-man! You have 5 strikes" << endl;
                cout << "I have 25 pre-installed words for you to guess from all with 8 letters!" << endl;
                cout << "You have 5 strikes" << endl;
                cout << endl;
                srand(time(0));
                //gets 2 random numbers to choose a random word from the 2D array
                int x = 0 + rand() % (4 - 0 + 1);
                int y = 0 + rand() % (4 - 0 + 1);
                string words[COL_SIZE][ROW_SIZE] = {
                        { "medieval", "casualty", "contract", "question", "discreet"},
                        { "parallel", "civilian", "imposter", "proposal", "engineer"},
                        { "physical", "composer", "implicit", "forecast", "twilight"},
                        { "momentum", "creation", "marathon", "aviation", "majority"},
                        { "tropical", "mushroom", "business", "elephant", "freshman"}

                };
                const int lists = 25;
                //used to print out contents
                string ListWords[lists] = {"medieval", "casualty", "contract", "question", "discreet",
                                           "parallel", "civilian", "imposter", "proposal", "engineer",
                                           "physical", "composer", "implicit", "forecast", "twilight",
                                           "momentum", "creation", "marathon", "aviation", "majority",
                                           "tropical", "mushroom", "business", "elephant", "freshman"
                };

                string word = words[x][y];
                int counter = 0;
                //gets the length of the word so the for loop won't go past the length
                int length = word.length();
                //use a cstring so I can access/modify specific indexes in the word
                char update[10] = "--------";
                int strike = 0;
                cout << update << endl;

                while(hangWin(counter) == 0){
                    //set up a test variable to compare to the update variable
                    char test[10];
                    //copies update variable to test
                    strcpy(test, update);
                    char letter;

                    cout << "Enter a letter: ";

                    cin >> letter;

                    for(int i = 0; i < length; i++){
                        //if the letter the user chooses is the same as the current
                        //index of the word, it will update the update variable so it
                        //displays the letters in the unknown word
                        if(word.find(letter)== word.find(word[i])){

                            update[i] = letter;
                            counter++;
                        }

                    }
                    //testing to see different instance of the update variable to see if anything changed
                    if(!strcmp(update, test)){
                        strike++;
                        cout << "Strike " << strike << " out of 5!" << endl;

                    }
                    //if the user has 5 strikes, they lose
                    if(strike == 5){
                        cout << "5 Strikes you're out!" << endl;
                        break;
                    }
                    cout << update << endl;

                }
                cout << endl;
                //determines who won
                if(strike == 5){
                    cout << "Computer Wins! " << endl;
                    cout << "The word was " << word << endl;
                    compWinHang++;
                }
                if(strike < 5){
                    cout << "User Wins! " << endl;
                    cout << "You made it with " << strike << " strikes" << endl;
                    userWinHang++;
                }
                //displays menu for user to choose from
                cout << "Play again? (1)" << endl;
                cout << "Go back to menu (2)" << endl;
                cout << "Exit (3) " << endl;
                cout << "See all words (4)" << endl;


                //validate user input
                do {

                    if(cin.fail()){
                        cout << "ERROR: wrong data type\n";
                        cin.clear();
                        cin.ignore(4096, '\n');
                    }
                    cout << "Choose an option: ";
                    cin >> option;
                    //update num which updates location variable based on what user chose
                }while(option < 1 || option > 4);

                if(option == 4){
                    for(string elem : ListWords){
                        cout << elem << endl;
                    }
                }
                //displays menu for user to choose from
                cout << "Play again? (1)" << endl;
                cout << "Go back to menu (2)" << endl;
                cout << "Exit (3) " << endl;
                cout << "See all words (4)" << endl;


                //validate user input
                do {

                    if(cin.fail()){
                        cout << "ERROR: wrong data type\n";
                        cin.clear();
                        cin.ignore(4096, '\n');
                    }
                    cout << "Choose an option: ";
                    cin >> option;
                    //update num which updates location variable based on what user chose
                }while(option < 1 || option > 4);


                //assigns num for location variable to update
                if(option == 1){
                    num = 3;
                }
                if(option == 2){
                    num = 0;
                }
                if(option == 3){
                    num = 4;
                }


            }
            //updates location variable
            cout << convert(userLocation) << " -------> ";
            userLocation = static_cast<location>(num);
            cout << convert(userLocation) << endl;

        }
///////////////////////////////Exit///////////////////////////////////////////////
        //will exit if the user chooses this option
        if(num == 4){
            break;
        }


///////////////////////////////////////////////////////////////////////
    }
    string survey = "";
    cout << "Thank you for playing! :D" << endl;
    //asks for a last-minute survey
    cout << "Before going, would you like to take a survey? (yes)" << endl;
    cout << "type yes if so" << endl;
    cin >> survey;

    if(survey == "yes"){
        string response = "";

        string name = "";
        int age = 0;
        int phoneNumber = 0;
        string game = "";

        //user input validate
        do {

            if(cin.fail()){
                cout << "ERROR: wrong data type\n";
                cin.clear();
                cin.ignore(4096, '\n');
            }
            cout << "What is your age: ";
            cin >> age;

        }while(age <= 0 || age > 100);

        cin.ignore();
        cout << "What is your name: ";
        getline(cin, name);
        cout << "What game do you want to see added?" << endl;
        getline(cin, game);
        //default argument of -1 in case the user doesn't feel comfortable entering their number
        cout << "Do you want to enter your Phone Number?" << endl;
        cin >> response;
        if(response == "no"){
            Info(age, name, game);
        }
        else if(response == "yes"){
            cout << "What is your number?" << endl;
            cin >> phoneNumber;
            Info(age, name, game, phoneNumber);
        }




        cout << "Thank you for taking the survey!" << endl;

    }
    //adds the stats into the file
    cout << "Now go look at the wins/losses/ties! " << endl;
    userFile << "---------------------------------" << endl;
    userFile << "Computer wins:" << endl;
    userFile << "Tic Tac Toe: " << compWinTic << endl;
    userFile << "Rock Paper Scissors: " << compWinRRR << endl;
    userFile << "Hang-man: " << compWinHang << endl;
    userFile << "---------------------------------" << endl;
    userFile << "User wins:" << endl;
    userFile << "Tic Tac Toe: " << userWinTic << endl;
    userFile << "Rock Paper Scissors: " << userWinRRR << endl;
    userFile << "Hang-man " << userWinHang << endl;
    userFile << "---------------------------------" << endl;
    userFile << "Ties:" << endl;
    userFile << "Tic Tac Toe: " << tieTic << endl;
    userFile << "Rock Paper Scissors: " << tieRRR << endl;
    userFile << "---------------------------------" << endl;
    userFile << endl;

    userFile.close();
    //displays the score the user got from how much they won
    //+1 for a win in Rock Paper Scissors
    //+2 for a win in Tic Tac Toe
    //+4 for a win in Hangman
    double result = 0;
    score(userWinRRR, userWinHang, userWinTic, result);
    cout << "Your score: " << result;
}
//takes in how many times the user won and assins that to the reference result
void score(int RRR, int HM, int TTT, double& result){
    result = RRR + (4*HM) + (2*TTT);
}


//opens a survey text file to store the survey in
void Info(int age, string name, string game, int number){
    fstream Survey;
    Survey.open("Survey.txt", ios::out);
    Survey << "Age: " << age << endl;
    Survey << "Name: " << name << endl;
    Survey << "Wanted Game: " << game << endl;
    Survey << "Phone Number: " << number << endl;
    Survey.close();
}

//determines if the user got all 8 letters
bool hangWin(int count){
    if(count == 8){
        return 1;
    }
    else{
        return 0;
    }
}


//clears the board if the user wants to play Tic Tac Toe again
void clearBoard(){
    if(options[0] != '1'){
        options[0] = '1';
    }
    if(options[1] != '2'){
        options[1] = '2';
    }
    if(options[2] != '3'){
        options[2] = '3';
    }
    if(options[3] != '4'){
        options[3] = '4';
    }
    if(options[4] != '5'){
        options[4] = '5';
    }
    if(options[5] != '6'){
        options[5] = '6';
    }
    if(options[6] != '7'){
        options[6] = '7';
    }
    if(options[7] != '8'){
        options[7] = '8';
    }
    if(options[8] != '9'){
        options[8] = '9';
    }
}

//welcome message
void welcomeMessage(){
    cout << "Welcome to the human vs machine mini-games! Here are the options! " << endl;
    cout << setfill('-') << setw(70) << '\n';
    cout << "Each Tic Tac Toe win gives you 2 points" << endl;
    cout << "Each Rock Paper Scissors win gives you 1 point" << endl;
    cout << "Each Hangman win gives you 4 points" << endl;
    cout << setfill('-') << setw(70) << '\n';
    cout << "1. Tic Tac Toe" << endl;
    cout << "2. Rock Paper Scissors" << endl;
    cout << "3. Hangman" << endl;
    cout << "4. Exit" << endl << endl;
    cout << "What will it be human? " << endl;

}

//assings X to the spot the user chooses
void playerMoves(int option){
    if(option == 1){
        options[0] = 'X';
    }
    if(option == 2){
        options[1] = 'X';
    }
    if(option == 3){
        options[2] = 'X';
    }
    if(option == 4){
        options[3] = 'X';
    }
    if(option == 5){
        options[4] = 'X';
    }
    if(option == 6){
        options[5] = 'X';
    }
    if(option == 7){
        options[6] = 'X';
    }
    if(option == 8){
        options[7] = 'X';
    }
    if(option == 9){
        options[8] = 'X';
    }
}
//assigns O to the spot the computer chooses
void computerMoves(int compMove){


    if(compMove == 1){
        options[0] = 'O';
    }
    if(compMove == 2){
        options[1] = 'O';
    }
    if(compMove == 3){
        options[2] = 'O';
    }
    if(compMove == 4){
        options[3] = 'O';
    }
    if(compMove == 5){
        options[4] = 'O';
    }
    if(compMove == 6){
        options[5] = 'O';
    }
    if(compMove == 7){
        options[6] = 'O';
    }
    if(compMove == 8){
        options[7] = 'O';
    }
    if(compMove == 9){
        options[8] = 'O';
    }
}
//return 1 if player wins
//return -1 if computer wins
//return 0 if tie
int ticWinner(){
    if(options[0] == 'X' && options[1] == 'X' && options[2] == 'X' ){
        return 1;
    }
    else if(options[3] == 'X' && options[4] == 'X' && options[5] == 'X' ){
        return 1;
    }
    else if(options[6] == 'X' && options[7] == 'X' && options[8] == 'X' ){
        return 1;
    }
    else if(options[0] == 'X' && options[3] == 'X' && options[6] == 'X' ){
        return 1;
    }
    else if(options[1] == 'X' && options[4] == 'X' && options[7] == 'X' ){
        return 1;
    }
    else if(options[2] == 'X' && options[5] == 'X' && options[8] == 'X' ){
        return 1;
    }
    else if(options[0] == 'X' && options[4] == 'X' && options[8] == 'X' ){
        return 1;
    }
    else if(options[2] == 'X' && options[4] == 'X' && options[6] == 'X' ){
        return 1;
    }


    else if(options[0] == 'O' && options[1] == 'O' && options[2] == 'O' ){
        return -1;
    }
    else if(options[3] == 'O' && options[4] == 'O' && options[5] == 'O' ){
        return -1;
    }
    else if(options[6] == 'O' && options[7] == 'O' && options[8] == 'O' ){
        return -1;
    }
    else if(options[0] == 'O' && options[3] == 'O' && options[6] == 'O' ){
        return -1;
    }
    else if(options[1] == 'O' && options[4] == 'O' && options[7] == 'O' ){
        return -1;
    }
    else if(options[2] == 'O' && options[5] == 'O' && options[8] == 'O' ){
        return -1;
    }
    else if(options[0] == 'O' && options[4] == 'O' && options[8] == 'O' ){
        return -1;
    }
    else if(options[2] == 'O' && options[4] == 'O' && options[6] == 'O' ){
        return -1;
    }
    else{
        return 0;
    }
}
//goes through all possibilites of winning and displays who won
void whoWon(){
    if(options[0] == 'X' && options[1] == 'X' && options[2] == 'X' ){
        cout << "Player won!";
    }
    else if(options[3] == 'X' && options[4] == 'X' && options[5] == 'X' ){
        cout << "Player won!";
    }
    else if(options[6] == 'X' && options[7] == 'X' && options[8] == 'X' ){
        cout << "Player won!";
    }
    else if(options[0] == 'X' && options[3] == 'X' && options[6] == 'X' ){
        cout << "Player won!";
    }
    else if(options[1] == 'X' && options[4] == 'X' && options[7] == 'X' ){
        cout << "Player won!";
    }
    else if(options[2] == 'X' && options[5] == 'X' && options[8] == 'X' ){
        cout << "Player won!";
    }
    else if(options[0] == 'X' && options[4] == 'X' && options[8] == 'X' ){
        cout << "Player won!";
    }
    else if(options[2] == 'X' && options[4] == 'X' && options[6] == 'X' ){
        cout << "Player won!";
    }


    else if(options[0] == 'O' && options[1] == 'O' && options[2] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[3] == 'O' && options[4] == 'O' && options[5] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[6] == 'O' && options[7] == 'O' && options[8] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[0] == 'O' && options[3] == 'O' && options[6] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[1] == 'O' && options[4] == 'O' && options[7] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[2] == 'O' && options[5] == 'O' && options[8] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[0] == 'O' && options[4] == 'O' && options[8] == 'O' ){
        cout << "Computer won!";
    }
    else if(options[2] == 'O' && options[4] == 'O' && options[6] == 'O' ){
        cout << "Computer won!";
    }
    else{
        cout << "It was a tie!";
    }
}
//checks if there is a winner
int checkwinner(){
    if (options[0] == options[1] && options[1] == options[2])
        return 1;
    else if (options[3] == options[4] && options[4] == options[5])

        return 1;
    else if (options[6] == options[7] && options[7] == options[8])

        return 1;
    else if (options[0] == options[3] && options[3] == options[6])

        return 1;
    else if (options[1] == options[4] && options[4] == options[7])

        return 1;
    else if (options[2] == options[5] && options[5] == options[8])

        return 1;
    else if (options[0] == options[4] && options[4] == options[8])

        return 1;
    else if (options[2] == options[4] && options[4] == options[6])

        return 1;
    else if (options[0] != '1' && options[1] != '2' && options[2] != '3'
             && options[3] != '4' && options[4] != '5' && options[5] != '6'
             && options[6] != '7' && options[7] != '8' && options[8] != '9')

        return 0;

    else{

        return -1;
    }
}
//strategy for what number the computer will choose
int compChoiceTic(){


    srand(time(0));
    int x = 1 + rand() % (9 - 1 + 1);
    //defense strategy

    if(options[0] == 'X' && options[1] == 'X'){
        x = 3;
    }
    else if(options[3] == 'X' && options[4] == 'X' ){
        x = 6;
    }
    else if(options[6] == 'X' && options[7] == 'X' ){
        x = 9;
    }
    else if(options[2] == 'X' && options[1] == 'X'){
        x = 1;
    }
    else if(options[5] == 'X' && options[4] == 'X'){
        x = 4;
    }
    else if(options[8] == 'X' && options[7] == 'X'){
        x = 7;
    }
    else if(options[0] == 'X' && options[3] == 'X'){
        x = 7;
    }
    else if(options[1] == 'X' && options[4] == 'X'){
        x = 8;
    }
    else if(options[2] == 'X' && options[5] == 'X'){
        x = 9;
    }
    else if(options[6] == 'X' && options[3] == 'X'){
        x = 1;
    }
    else if(options[1] == 'X' && options[4] == 'X'){
        x = 8;
    }
    else if(options[2] == 'X' && options[5] == 'X'){
        x = 9;
    }
    else if(options[0] == 'X' && options[4] == 'X'){
        x = 9;
    }
    else if(options[8] == 'X' && options[4] == 'X'){
        x = 1;
    }
    else if(options[2] == 'X' && options[4] == 'X'){
        x = 7;
    }
    else if(options[6] == 'X' && options[4] == 'X'){
        x = 3;
    }
    else if(options[0] == 'X' && options[2] == 'X'){
        x = 2;
    }
    else if(options[3] == 'X' && options[5] == 'X'){
        x = 5;
    }
    else if(options[6] == 'X' && options[8] == 'X'){
        x = 8;
    }
    else if(options[0] == 'X' && options[6] == 'X'){
        x = 4;
    }
    else if(options[1] == 'X' && options[7] == 'X'){
        x = 5;
    }
    else if(options[2] == 'X' && options[8] == 'X'){
        x = 6;
    }
    else if(options[0] == 'X' && options[8] == 'X'){
        x = 5;
    }
    else if(options[2] == 'X' && options[6] == 'X'){
        x = 5;
    }

    //offense strategy

    if( (options[0] == 'O' && options[1] == 'O') && options[2] == '3'){
        x = 3;
    }
    else if( (options[3] == 'O' && options[4] == 'O') && options[5] == '6' ){
        x = 6;
    }
    else if( (options[6] == 'O' && options[7] == 'O') && options[8] == '9' ){
        x = 9;
    }
    else if( (options[2] == 'O' && options[1] == 'O') && options[0] == '1'){
        x = 1;
    }
    else if( (options[5] == 'O' && options[4] == 'O') && options[3] == '4'){
        x = 4;
    }
    else if( (options[8] == 'O' && options[7] == 'O') && options[6] == '7'){
        x = 7;
    }
    else if( (options[0] == 'O' && options[3] == 'O') && options[7] == '7'){
        x = 7;
    }
    else if( (options[1] == 'O' && options[4] == 'O') && options[7] == '8'){
        x = 8;
    }
    else if( (options[2] == 'O' && options[5] == 'O') && options[8] == '9'){
        x = 9;
    }
    else if( (options[6] == 'O' && options[3] == 'O') && options[0] == '1'){
        x = 1;
    }
    else if( (options[7] == 'O' && options[4] == 'O') && options[1] == '2'){
        x = 8;
    }
    else if( (options[8] == 'O' && options[5] == 'O') && options[2] == '3'){
        x = 9;
    }
    else if( (options[0] == 'O' && options[4] == 'O') && options[8] == '9'){
        x = 9;
    }
    else if( (options[8] == 'O' && options[4] == 'O') && options[0] == '1'){
        x = 1;
    }
    else if( (options[2] == 'O' && options[4] == 'O') && options[6] == '7'){
        x = 7;
    }
    else if( (options[6] == 'O' && options[4] == 'O') && options[2] == '3'){
        x = 3;
    }
    else if( (options[0] == 'O' && options[2] == 'O') && options[1] == '2'){
        x = 2;
    }
    else if( (options[3] == 'O' && options[5] == 'O') && options[4] == '5'){
        x = 5;
    }
    else if( (options[6] == 'O' && options[8] == 'O') && options[7] == '8'){
        x = 8;
    }
    else if( (options[0] == 'O' && options[6] == 'O') && options[3] == '4'){
        x = 4;
    }
    else if( (options[1] == 'O' && options[7] == 'O') && options[4] == '5'){
        x = 5;
    }
    else if( (options[2] == 'O' && options[8] == 'O') && options[5] == '6'){
        x = 6;
    }
    else if( (options[0] == 'O' && options[8] == 'O') && options[4] == '5'){
        x = 5;
    }
    else if( (options[2] == 'O' && options[6] == 'O') && options[4] == '5'){
        x = 5;
    }

        //if no strategies available, just picks a random number
    else{
        while(options[x-1] == 'X' || options[x-1] == 'O'){
            x = 1 + rand() % (9 - 1 + 1);
        }
    }






    return x;

}
//creates the board
void board(){

    cout << "~~~~~~~~~~~~~~~~~~" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << options[0] << "  |  " << options[1] << "  |  " << options[2] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << options[3] << "  |  " << options[4] << "  |  " << options[5] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << options[6] << "  |  " << options[7] << "  |  " << options[8] << endl;
    cout << "     |     |     " << endl;
    cout << "~~~~~~~~~~~~~~~~~~" << endl;

}

//displays the menu for Rock Paper Scissors
void menu(){
    cout << "Pick your move!" << endl;
    cout << "1. Rock" << endl;
    cout << "2. Paper" << endl;
    cout << "3. Scissors" << endl;
}

//gets called to display what the computer chooses
int computerChoice(int compNum){
    if(compNum == 1){
        cout << "The computer has chosen Rock!" << endl;
    }
    else if(compNum == 2){
        cout << "The computer has chosen paper!" << endl;
    }
    if(compNum == 3){
        cout << "The computer has chosen Scissors!" << endl;
    }
    return compNum;

}

//determines who is the winner for rock paper scissors
//goes through all possibilities
int rpcWinner (int userNumber, int computerNumber){
    if(userNumber == computerNumber){
        return 0;
    }
    else if(  (userNumber == 1 && computerNumber == 2)   || (userNumber == 2 && computerNumber == 3) || (userNumber == 3 && computerNumber == 1)  ){
        return 1;
    }
    else if(    (userNumber == 1 && computerNumber == 3) || (computerNumber == 2 && userNumber == 1) || (userNumber == 2 && computerNumber == 1) ||
                (userNumber == 3 && computerNumber == 2) ) {
        return 2;
    }
    else{
        return -1;

    }
}

//determines the outcome by recieiving the user and computer options
void outcome(int userNumber, int computerNumber){
    if(userNumber == computerNumber){
        cout << "The game was a tie! Fight me again human!" << endl;
    }
    else if(  (userNumber == 1 && computerNumber == 2)   || (userNumber == 2 && computerNumber == 3) || (userNumber == 3 && computerNumber == 1)  ){
        cout << "The winner is the computer!" << endl;
    }
    else if(    (userNumber == 1 && computerNumber == 3) || (computerNumber == 2 && userNumber == 1) || (userNumber == 2 && computerNumber == 1) ||
                (userNumber == 3 && computerNumber == 2) ) {
        cout << "The winner is the user player!" << endl;
    }

}
//
// Created by Oliver Lokhandwala on 2/9/22.
//

