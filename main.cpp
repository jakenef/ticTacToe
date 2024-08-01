#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

string getBoardString(string board[][3]) { // pass in a 2D array and gets it in string form
    stringstream buffer;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buffer << board[i][j] << " ";
        }
        buffer << endl;
    }
    return buffer.str();
}

void printBoard(string board[][3]) { // pass in a 2D array and print it out to the console
    cout << getBoardString(board);
}

bool isBoardFull(string board[][3]) { // checks if game is over because its a tie
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == "-") {
                return false;
            }
        }
    }
    return true;
}

void placeMarker(int whoPlayed, int x, int y,
                 string board[][3]) {
    // pass in the board, which player's turn (or if not a player's turn, make it empty
    //and coordinates then update board
    if (whoPlayed == 1) {
        board[x - 1][y - 1] = "X";
    } else if (whoPlayed == 2){
        board[x - 1][y - 1] = "O";
    }else{
        board[x-1][y-1] = "-";
    }
}

bool isIllegal(int x, int y, string board[][3]) { // makes sure that the coordinates don't replace an existing marker
    if (x < 1 || x > 3 || y < 1 || y > 3) {
        return true;
    }
    if (board[x - 1][y - 1] == "X" || board[x - 1][y - 1] == "O") {
        return true;
    } else {
        return false;
    }
}

bool threeInARow(string board[][3]) { // returns true if there are any three in a row on the board, false if otherwise
    int xInLine = 0;
    int oInLine = 0;
    for (int i = 0; i < 3; i++) { // check rows for three in a row!
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == "X") {
                xInLine++;
            } else if (board[i][j] == "O") {
                oInLine++;
            }
        }
        if (xInLine == 3 || oInLine == 3) { // counts the x's and o's and returns true if it finds 3
            return true;
        } else {
            xInLine = 0;
            oInLine = 0;
        }
    }
    for (int i = 0; i < 3; i++) { // check columns for three in a row!
        for (int j = 0; j < 3; j++) {
            if (board[j][i] == "X") {
                xInLine++;
            } else if (board[j][i] == "O") {
                oInLine++;
            }
        }
        if (xInLine == 3 || oInLine == 3) {
            return true;
        } else {
            xInLine = 0;
            oInLine = 0;
        }
    }
    for (int i = 0; i < 3; i++) { // checks one diagonal
        if (board[i][i] == "X") {
            xInLine++;
        } else if (board[i][i] == "O") {
            oInLine++;
        }
    }
    if (xInLine == 3 || oInLine == 3) {
        return true;
    } else {
        xInLine = 0;
        oInLine = 0;
    }
    int diagonalX = 0;
    for (int i = 2; i >= 0; i--) { // checks one diagonal
        if (board[i][diagonalX] == "X") {
            xInLine++;
        } else if (board[i][diagonalX] == "O") {
            oInLine++;
        }
        diagonalX++;
    }
    if (xInLine == 3 || oInLine == 3) {
        return true;
    } else {
        xInLine = 0;
        oInLine = 0;
    }
    return false;
}

/** Updates the gameboard with a marker for the computer's turn. checks if markers in empty
 * spaces would result in a win for either player.
 *
 * @param board 2D array for the game board
 */
void computerTurn(string board[][3]) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == "-"){
                placeMarker(2, i + 1, j + 1, board);
                if(threeInARow(board)){ //replace any empty space with computer's marker O and see if that wins the game
                    cout << "I'm going here: " << i + 1 << ", " << j + 1 << endl;
                    return;
                }else{
                    placeMarker(3, i + 1, j + 1, board); // if not, reset the board.
                }
                placeMarker(1, i + 1, j + 1, board);
                // replace empty spaces with user's marker X and
                //see if any cause a loss. if so, place computer marker O there to prevent it.
                if(threeInARow(board)){
                    cout << "I'm going here: " << i + 1 << ", " << j + 1 << endl;
                    placeMarker(2, i + 1, j + 1, board);
                    return;
                }else{ // if not, reset board.
                    placeMarker(3, i + 1, j + 1, board);
                }
            }
        }
    }
    int computerX = rand() % 3 + 1; // if no imminent win or loss, random placement
    int computerY = rand() % 3 + 1;
    do {
        computerX = rand() % 3 + 1;
        computerY = rand() % 3 + 1;
    } while (isIllegal(computerY, computerX, board));
    cout << "I'm going here: " << computerX << ", " << computerY << endl;
    placeMarker(2, computerY, computerX, board);
}

int main() {
    // initialization
    string gameBoard[3][3];
    int whoTurn = 0;
    int playerX = 0;
    int playerY = 0;
    bool gameOver = false;
    // Seeding rng for later use
    srand(time(0));
    for (int i = 0; i < 3; i++) { // makes new game board
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = "-";
        }
    }

    printBoard(gameBoard);
    cout << "Welcome to Tic-Tac-Toe! If you would like to go first, enter 1. "
            "If you would like to go second, enter 2." << endl;

    while(true) // stays in this loop until given correct input.
    {
        cin >> whoTurn;
        if(!cin.fail() && (whoTurn >= 1 && whoTurn <= 2))
            break;
        else
        {
            cin.clear();
            cin.ignore();
            cout << "Please try again." << endl;
        }
    }

    cout << "Let's begin!" << endl;
    if (whoTurn == 2) {
        placeMarker(2, rand() % 3 + 1, rand() % 3 + 1, gameBoard);
        whoTurn = 1;
    }
    printBoard(gameBoard);
    do { //game loop until game is over
        if (whoTurn == 1) {
            while(true) // stays in this loop until given correct input.
            {
                cout << "Place your marker by entering an x coordinate (1-3 to the right)." << endl;
                cin >> playerX;
                //TODO: jumps over y coordinate input if x is a string or whatnot, fix
                cout << "And a y coordinate (1-3 from top to bottom)." << endl;
                cin >> playerY;
                if(!cin.fail() && !isIllegal(playerY, playerX, gameBoard))
                    break;
                else
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Please try again." << endl;
                }
            }
            // if not an illegal move, program continues and gameBoard is updated
            placeMarker(1, playerY, playerX, gameBoard); // updates the gameBoard
            whoTurn = 2;// changes it to computer's turn
            printBoard(gameBoard);
            if (threeInARow(gameBoard)) {
                cout << "You win!" << endl;
                gameOver = true;
            }
        } else {
            cout << endl;
            computerTurn(gameBoard);
            whoTurn = 1;
            printBoard(gameBoard);
            if (threeInARow(gameBoard)) {
                cout << "I win!" << endl;
                gameOver = true;
            }
        }
        if (isBoardFull(gameBoard) && !gameOver) { // checks for tie
            cout << "It's a tie!" << endl;
            gameOver = true;
        }
    } while (!gameOver);
    cout << "Would you like to play again? Enter 1 for yes, 2 for no." << endl;
    while(true) // stays in this loop until given correct input.
    {
        cin >> whoTurn;
        if(!cin.fail() && (whoTurn >= 1 && whoTurn <= 2))
            break;
        else
        {
            cin.clear();
            cin.ignore();
            cout << "Please try again." << endl;
        }
    }
    if(whoTurn == 1){ // play again and again until user chooses not to
        main();
    }
    return 0;
}
