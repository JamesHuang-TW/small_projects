#include <iostream>
#include <string>
#include <vector>
#include <limits> //max

using std::cout;
using std::cin;
using std::string;
using std::vector;

int sz;
string n1, n2;
int blockLen = 4;

vector<vector<string>> constructSpaceVector(int sz) {
    vector<vector<string>> space(sz, vector<string>(sz));
    for (int i = 0; i < sz; ++i) {
        int diff = 0;
        for (auto it = space[i].begin(); it != space[i].end(); ++it, ++diff) {
            *it = std::to_string(1 + i * sz + diff);
        }
    }
    return space;
}

void choosePosition(vector<vector<string>>& space,
                    string& token1, string& token2, string& winner,
                    vector<int>& rows, vector<int>& cols, int diag, int anti_diag) {
    int digit;
    cout << "Player " + (token1 == "x" ? n1 : n2) << ", please enter a number between 1 and " << sz*sz <<".\n";
    if (!(cin >> digit) || digit < 1 || digit > sz*sz) {
        std::cerr << "Invalid input\n";
        // if we don't reset the state of istream, we will see an infinite loop
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    --digit;
    int row = digit / sz;
    int col = digit % sz;
    if (space[row][col] != token1 && space[row][col] != token2) {
        space[row][col] = token1;
        int diff = (token1 == "x") ? 1 : -1;
        rows[row] += diff;
        cols[col] += diff;
        if (row == col) {
            diag += diff;
        }
        if (row + col == sz - 1) {
            anti_diag += diff;
        }

        if (abs(rows[row]) == sz || abs(cols[col]) == sz || abs(diag) == sz || abs(anti_diag) == sz) {
            winner = (token1 == "x") ? n1 : n2;
            cout << winner << " wins!\n";
        }
        std::swap(token1, token2);
    }
    else {
        std::cerr << "There is no empty space!\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/*
In the draw function, for simplicity, I choose to write draw first/second/third row separately. 
There is a unified way to reduce the replicated code in them.
*/
void drawFirstRow() {
    for (int i = 0; i < sz - 1; ++i) {
        cout << "    |";
    }
    cout << "    \n";
}

void drawSecondRow(int r, const vector<vector<string>>& space) {
    for (int i = 0; i < sz; ++i) {
        string toPrint(blockLen - 1 - space[r][i].length(), ' ');
        toPrint += space[r][i];
        string end = (i == sz - 1) ? "\n" : " |";
        cout << toPrint << end;
    }
}

void drawThirdRow() {
    for (int i = 0; i < sz - 1; ++i) {
        cout << "____|";
    }
    cout << "____\n";
}

void drawBoard(const vector<vector<string>>& space) { // how to extend it to general size?
    for (int r = 0; r < sz - 1; ++r) {
        drawFirstRow();
        drawSecondRow(r, space);
        drawThirdRow();
    }
    drawFirstRow();
    drawSecondRow(sz - 1, space);
    drawFirstRow(); // last row
}

int main() {
    cout << "Please choose a number from 3 to 7 to be the size of board.\n";
    cin >> sz;
    cout << "sz = " << sz << '\n';
    cout << "Enter the name of first player : \n";
    cin >> n1;
    while (n2.empty() || n2 == n1) {
        cout << "Enter the name of second player: \n";
        cin >> n2;
        if (n1 == n2) {
            std::cerr << "This name has been used. Please choose another one.\n";
        }
    }
    cout << '\"' << n1 << '\"' << " is the first player : \n";
    cout << '\"' << n2 << '\"' << " is the second player : \n";

    vector<vector<string>> space = constructSpaceVector(sz);
    string token1 = "x"; // n1
    string token2 = "o"; // n2
    string winner = "";

    vector<int> rows(sz, 0), cols(sz, 0);
    int diag = 0;
    int anti_diag = 0;

    while (winner.empty()) {
        drawBoard(space);
        choosePosition(space, token1, token2, winner, rows, cols, diag, anti_diag);
    }

    return 0;
}
