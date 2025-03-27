#include "header.h"
void GetRowCol();                    // Row and Col of the full screen page
void enterUserName();                // Log in page
void addUser(const char *username);  // Add User
bool IsInList(const char *username); // Check if User already exist
void menu();
int setDificulty();
void displayGrid(int x, int y);
bool isInPreSet(int row, int col);       // Check if index is already set
bool isValid(int row, int col, int num); // Check the number is valid

void displayTimer(int minutes, int seconds, int x, int y);
void countdownTimer(int minutes, int x, int y, bool &timeUp);

void displayWrongMoves(int wrongMoves, int x, int y);
void displayScore(int score, int x, int y);

bool isGameComplete(); // Check if the game is complete
void resetGrid();
void afterGameStatus(bool won); // Display the status of the game
void displayPauseMenu(int minutes, int seconds);

void SaveGameScore(int minutes, int seconds);
void loadUsers();
void clearSavedScore();

bool compareUsers(const User &a, const User &b);
void displayLeaderboard();

void mainGame(int minutes, int seconds);

int main()
{
    clearSavedScore();
    if (!alreadyGotRowCol)
    {
        GetRowCol();
    }
    enterUserName();
    getch();
    return 0;
}
// definitions
//----------------------------------------------------------------
void GetRowCol()
{
    cursor_to_pos(get_window_rows() / 2, get_window_cols() / 2 + 15);
    change_color_rgb(0, 255, 166);
    cout << "Press Any Key";
    reset_color();
    getch();
    clear_screen();
    rows = get_window_rows();
    columns = get_window_cols();
    alreadyGotRowCol = true;
}
//----------------------------------------------------------------
bool IsInList(const char *username)
{
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(usernames[i], username) == 0)
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------
void addUser(const char *username)
{
    if (!IsInList(username) && strlen(username) > 0)
    {
        strcpy(usernames[userCount], username);
        userCount++;
        cursor_to_pos(rows / 2 + 5, columns / 2 - 10);
        change_color_rgb(4, 217, 0);
        cout << "User added successfully!" << endl;
        delay(1000);
        clear_screen();
        menu();
    }
    else
    {
        cursor_to_pos(rows / 2 + 5, columns / 2 - 10);
        change_color_rgb(255, 0, 0);
        cout << "User already exists or UserName is empty." << endl;
        delay(2000);
        clear_screen();
        enterUserName();
    }
}
//----------------------------------------------------------------
void enterUserName()
{
    cursor_to_pos(rows / 2, columns / 2 - 10);
    change_color_rgb(128, 0, 255);

    cout << "Enter your UserName:";

    cursor_to_pos(rows / 2 + 1, columns / 2 - 30);

    cout << "(your UserName can not contain spaces or special characters)";
    reset_color();

    cursor_to_pos(rows / 2 + 3, columns / 2 - 3);
    change_color_rgb(255, 0, 195);

    cin >> userName;
    reset_color();
    addUser(userName.c_str());
}
//----------------------------------------------------------------
int setDificulty()
{
    int dificulty;
    cursor_to_pos(10, columns / 2 - 10);
    change_color_rgb(194, 20, 120);
    cout << "Choose Difficulty:";
    reset_color();
    cursor_to_pos(rows / 3, columns / 2 - 10);
    change_color_rgb(18, 214, 0);
    cout << "1: Easy";
    reset_color();
    cursor_to_pos(rows / 3 + 2, columns / 2 - 10);
    change_color_rgb(23, 35, 255);
    cout << "2: Medium";
    reset_color();
    cursor_to_pos(rows / 3 + 4, columns / 2 - 10);
    change_color_rgb(255, 0, 0);
    cout << "3: Hard";
    reset_color();
    cursor_to_pos(rows / 3 + 6, columns / 2 - 10);
    change_color_rgb(255, 0, 195);
    cin >> dificulty;
    reset_color();
    return dificulty;
}
//----------------------------------------------------------------
void displayGrid(int x, int y)
{
    clear_screen();
    // for numbers
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            cursor_to_pos(y + i + i / 3 + 1, x + j * 2 + j / 3 * 2 + 1);
            if (gridSuduko[i][j] == 0)
            {
                cout << ".";
            }
            else
            {
                cout << gridSuduko[i][j];
            }
        }
    }
    // for spaces
    for (int i = 0; i <= GRID_SIZE; ++i)
    {
        if (i % 3 == 0)
        {
            for (int j = 0; j <= GRID_SIZE * 2 + 2; ++j)
            {
                cursor_to_pos(y + i + i / 3, x + j);
                cout << " ";
            }
        }
    }
    for (int j = 0; j <= GRID_SIZE; ++j)
    {
        if (j % 3 == 0)
        {
            for (int i = 0; i <= GRID_SIZE + 2; ++i)
            {
                cursor_to_pos(y + i, x + j * 2 + j / 3 * 2);
                cout << " ";
            }
        }
    }
}
//----------------------------------------------------------------
bool isInPreSet(int row, int col)
{
    if (Pregrid[row][col] != 0)
    {
        return true;
    }
    return false;
}
//----------------------------------------------------------------
bool isValid(int row, int col, int num)
{
    if (isInPreSet(row, col))
    {
        return false;
    }

    // Check if the number is already in the row or column
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        if (gridSuduko[row][i] == num || gridSuduko[i][col] == num)
        {
            return false;
        }
    }
    // Check if the number is in the 3x3 sub SUDUKO
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (gridSuduko[i + startRow][j + startCol] == num)
            {

                return false;
            }
        }
    }
    return true;
}
//----------------------------------------------------------------
void displayTimer(int minutes, int seconds, int x, int y)
{
    cursor_to_pos(y, x);
    change_color_rgb(255, 255, 0);
    // MM:SS
    cout << (minutes < 10 ? "0" : "") << minutes << ":"
         << (seconds < 10 ? "0" : "") << seconds;
    reset_color();
}
//----------------------------------------------------------------
void displayWrongMoves(int wrongMoves, int x, int y)
{
    cursor_to_pos(y, x);
    change_color_rgb(255, 0, 0);
    cout << "Wrong Moves: " << wrongMoves;
    reset_color();
}
//----------------------------------------------------------------
void countdownTimer(int minutes, int x, int y, bool &timeUp)
{
    int seconds = 0;
    time_t startTime = time(NULL);
    while (minutes > 0 || seconds > 0)
    {
        time_t currentTime = time(NULL);
        if (currentTime - startTime >= 1) // one second has passed
        {
            startTime = currentTime; // Update the start time
            if (seconds == 0)
            {
                minutes--;
                seconds = 59; // Reset the seconds
            }
            else
            {
                seconds--;
            }
            displayTimer(minutes, seconds, x, y);
        }
    }
    timeUp = true; // 00:00
}
//----------------------------------------------------------------
void displayScore(int score, int x, int y)
{
    cursor_to_pos(y, x);
    change_color_rgb(0, 255, 0);
    cout << "Score: " << score;
    reset_color();
}
//----------------------------------------------------------------
bool isGameComplete()
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (gridSuduko[i][j] != completedSuduko[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
//----------------------------------------------------------------
void afterGameStatus(bool won)
{
    delay(1000);
    clear_screen();
    cursor_to_pos(rows / 2, columns / 2 - 10);
    if (won)
    {
        change_color_rgb(0, 255, 0);
        cout << "You have won!";
        reset_color();
    }
    else
    {
        change_color_rgb(255, 0, 0);
        cout << "You Lost!";
        reset_color();
    }
    cursor_to_pos(rows / 2 + 2, columns / 2 - 10);
    change_color_rgb(255, 0, 195);
    cout << "Score: " << score;
    cursor_to_pos(rows / 2 + 4, columns / 2 - 10);
    cout << "Right Moves: " << rightMoves;
    cursor_to_pos(rows / 2 + 6, columns / 2 - 10);
    cout << "Wrong Moves: " << wrongMoves;
    cursor_to_pos(rows / 2 + 8, columns / 2 - 10);
    cout << "Press any key to continue...";
    getch();
    clear_screen();
    menu();
}
//----------------------------------------------------------------
void SaveGameScore(int minutes, int seconds)
{
    FILE *file = fopen("SavedScore.txt", "a"); // append mode
    if (file == NULL)
    {
        cout << "Error!" << endl;
        return;
    }
    fprintf(file, "Username: %s\n", userName.c_str());
    fprintf(file, "Score: %d\n", score);
    fprintf(file, "Right Moves: %d\n", rightMoves);
    fprintf(file, "Wrong Moves: %d\n", wrongMoves);
    fprintf(file, "Time Remaining: %d:%d\n", minutes, seconds);
    fprintf(file, "-------------------------\n");
    fclose(file);
}
//----------------------------------------------------------------
void clearSavedScore()
{
    ofstream file("SavedScore.txt", ofstream::out | ofstream::trunc); // truncated
    if (!file.is_open())
    {
        cout << "Error!" << endl;
        return;
    }
    file.close();
}
//----------------------------------------------------------------
void loadUsers()
{
    ifstream file("SavedScore.txt");
    if (!file.is_open())
    {
        cursor_to_pos(4, columns / 2 - 10);
        change_color_rgb(255, 0, 0);
        cout << "Error!" << endl;
        reset_color();
        return;
    }
    string line;
    userCount = 0;
    // Read line by line
    while (getline(file, line) && userCount < MAX_USERS)
    {
        if (line.empty())
            continue; // Skip if empty
        if (line.find("Username: ") != 0)
            continue; // Skip if line does not start with "Username: "

        strcpy(users[userCount].name, line.substr(10).c_str()); // remove "Username: "
        getline(file, line);

        if (line.find("Score: ") != 0)
            continue;
        users[userCount].score = stoi(line.substr(7));

        getline(file, line);
        if (line.find("Right Moves: ") != 0)
            continue;
        users[userCount].rightMoves = stoi(line.substr(13));

        getline(file, line);
        if (line.find("Wrong Moves: ") != 0)
            continue;
        users[userCount].wrongMoves = stoi(line.substr(13));

        getline(file, line);
        if (line.find("Time Remaining: ") != 0)
            continue;
        int minutes = stoi(line.substr(16, line.find(':') - 16)); // Extract minutes
        int seconds = stoi(line.substr(line.find(':') + 1));      // Extract seconds
        users[userCount].remainingTime = minutes * 60 + seconds;

        userCount++;
        getline(file, line); // Skip "-------------------------"
    }
    file.close();
}
//----------------------------------------------------------------
bool compareUsers(const User &a, const User &b)
{
    if (a.score != b.score)
        return a.score > b.score;
    return a.remainingTime > b.remainingTime;
}
//----------------------------------------------------------------
void displayLeaderboard()
{
    loadUsers();
    sort(users, users + userCount, compareUsers);

    cursor_to_pos(2, columns / 2 - 10);
    change_color_rgb(255, 255, 0);
    cout << "Leaderboard";
    reset_color();

    int y = 4;
    for (int i = 0; i < userCount; ++i)
    {
        cursor_to_pos(y, 8);
        change_color_rgb(0, 255, 255);
        cout << "Username: " << users[i].name;
        cursor_to_pos(y + 1, 8);
        change_color_rgb(0, 255, 0);
        cout << "Score: " << users[i].score;
        cursor_to_pos(y + 2, 8);
        change_color_rgb(28, 20, 255);
        cout << "Right Moves: " << users[i].rightMoves;
        cursor_to_pos(y + 3, 8);
        change_color_rgb(255, 0, 0);
        cout << "Wrong Moves: " << users[i].wrongMoves;
        cursor_to_pos(y + 4, 8);
        change_color_rgb(255, 165, 0);
        cout << "Time Remaining: " << users[i].remainingTime / 60 << ":" << users[i].remainingTime % 60;
        reset_color();
        y += 6;
    }

    cursor_to_pos(y + 2, 8);
    change_color_rgb(255, 255, 255);
    cout << "Press any key to return to menu...";
    reset_color();
    getch();
    clear_screen();
    menu();
}
//----------------------------------------------------------------
void displayPauseMenu(int minutes, int seconds)
{
    clear_screen();
    cursor_to_pos(rows / 2, columns / 2 - 10);
    change_color_rgb(255, 255, 0);
    cout << "Game Paused";
    reset_color();
    cursor_to_pos(rows / 2 + 2, columns / 2 - 10);
    change_color_rgb(0, 247, 255);
    cout << "Press S to save the progress";
    reset_color();
    cursor_to_pos(rows / 2 + 4, columns / 2 - 10);
    change_color_rgb(15, 211, 255);
    cout << "Press q to return to the main menu";
    reset_color();
    cursor_to_pos(rows / 2 + 6, columns / 2 - 10);
    change_color_rgb(166, 0, 255);
    cout << "Press ESC to resume";
    reset_color();

    int key = _getch();
    if (key == 'S' || key == 's')
    {
        SaveGameScore(minutes, seconds);
        cursor_to_pos(rows / 2 + 6, columns / 2 - 10);
        change_color_rgb(0, 255, 0);
        cout << "Game saved successfully!";
        reset_color();
        delay(1000);
        clear_screen();
        menu();
    }
    if (key == 'q' || key == 'Q')
    {
        clear_screen();
        afterGameStatus(false);
        score = 0;
        wrongMoves = 0;
        rightMoves = 0;
        resetGrid();
    }
}
//----------------------------------------------------------------
void resetGrid()
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            gridSuduko[i][j] = Pregrid[i][j];
        }
    }
}
//----------------------------------------------------------------
void mainGame(int difficulty)
{
    resetGrid();
    alreadyGotHint = false;
    score = 0;
    wrongMoves = 0;
    rightMoves = 0;
    int x = 10, y = 5; // starting position
    int timerX = x + GRID_SIZE * 2 + GRID_SIZE / 3 * 2 + 5;
    int timerY = y;
    int scoreX = x + GRID_SIZE * 2 + GRID_SIZE / 3 * 2 + 5;
    int scoreY = y + 2;
    int row = 0, col = 0;
    int minutes = (difficulty == 1) ? 5 : (difficulty == 2) ? 3
                                                            : 2;
    int seconds = 0;
    bool timeUp = false;
    bool paused = false;
    time_t startTime = time(NULL);

    displayGrid(x, y);
    displayTimer(minutes, seconds, timerX, timerY);
    displayScore(score, scoreX, scoreY);
    displayWrongMoves(wrongMoves, scoreX, scoreY + 2);
    cursor_to_pos(y + row + row / 3 + 1, x + col * 2 + col / 3 * 2 + 1); //(6, 11)
    change_color_rgb(255, 0, 0);
    if (gridSuduko[row][col] == 0)
    {
        cout << '0';
    }
    else
    {
        cout << (char)(gridSuduko[row][col] + '0'); // Display the number(char)
    }
    reset_color();

    while (!timeUp)
    {
        if (!paused)
        {
            time_t currentTime = time(NULL);
            if (currentTime - startTime >= 1)
            {
                startTime = currentTime;
                if (seconds == 0)
                {
                    if (minutes == 0)
                    {
                        timeUp = true;
                        break;
                    }
                    minutes--;
                    seconds = 59;
                }
                else
                {
                    seconds--;
                }
                displayTimer(minutes, seconds, timerX, timerY);
            }
        }

        if (_kbhit())
        {
            int key = _getch();
            if (key == 27) // ESC
            {
                paused = !paused;
                if (paused)
                {
                    displayPauseMenu(minutes, seconds);
                }
                else
                {
                    clear_screen();
                    displayGrid(x, y);
                    displayTimer(minutes, seconds, timerX, timerY);
                    displayScore(score, scoreX, scoreY);
                    displayWrongMoves(wrongMoves, scoreX, scoreY + 2);
                    cursor_to_pos(y + row + row / 3 + 1, x + col * 2 + col / 3 * 2 + 1);
                    change_color_rgb(255, 0, 0);
                    if (gridSuduko[row][col] == 0)
                    {
                        cout << '0';
                    }
                    else
                    {
                        cout << (char)(gridSuduko[row][col] + '0'); // Display the number(char)
                    }
                    reset_color();
                }
            }
            else if (!paused)
            {
                if (key == 'q')
                {
                    clear_screen();
                    afterGameStatus(false);
                    score = 0;
                    wrongMoves = 0;
                    rightMoves = 0;
                    resetGrid();
                    break;
                }
                if (key == 224) // Arrow keys
                {
                    key = _getch();
                    switch (key)
                    {
                    case 72: // Up
                        if (row > 0)
                            row--;
                        break;
                    case 80: // Down
                        if (row < GRID_SIZE - 1)
                            row++;
                        break;
                    case 75: // Left
                        if (col > 0)
                            col--;
                        break;
                    case 77: // Right
                        if (col < GRID_SIZE - 1)
                            col++;
                        break;
                    }
                }
                else if (key == 'u') // Undo
                {
                    if (!isInPreSet(row, col))
                    {
                        if (gridSuduko[row][col] != 0)
                        {
                            if (gridSuduko[row][col] != completedSuduko[row][col])
                            {
                                score++;
                                wrongMoves--;
                            }
                            else
                            {
                                score--;
                                rightMoves--;
                                wrongMoves++;
                            }
                            gridSuduko[row][col] = 0;
                            clear_screen();
                            displayGrid(x, y);
                        }
                    }
                }
                else if (key == 'h')
                {
                    if (!isInPreSet(row, col) && !alreadyGotHint)
                    {
                        if (gridSuduko[row][col] == 0)
                        {
                            score++;
                            rightMoves++;
                            gridSuduko[row][col] = completedSuduko[row][col];
                            clear_screen();
                            displayGrid(x, y);
                            alreadyGotHint = true;
                        }
                    }
                }

                else if (key >= '1' && key <= '9')
                {
                    int num = key - '0'; // char to int
                    if (!isInPreSet(row, col))
                    {
                        if (isValid(row, col, num))
                        {
                            gridSuduko[row][col] = num;
                            if (gridSuduko[row][col] == completedSuduko[row][col])
                            {
                                score++;
                                rightMoves++;
                            }
                            else
                            {
                                score--;
                                wrongMoves++;
                            }
                        }
                    }
                }
                // Always display
                displayGrid(x, y);
                displayTimer(minutes, seconds, timerX, timerY);
                displayScore(score, scoreX, scoreY);
                displayWrongMoves(wrongMoves, scoreX, scoreY + 2);
                cursor_to_pos(y + row + row / 3 + 1, x + col * 2 + col / 3 * 2 + 1);
                change_color_rgb(255, 0, 0);
                if (gridSuduko[row][col] == 0)
                {
                    cout << '0';
                }
                else
                {
                    cout << (char)(gridSuduko[row][col] + '0'); // Display the number(char)
                }
                reset_color();

                if (wrongMoves == 5)
                {
                    clear_screen();
                    cursor_to_pos(rows / 2, columns / 2 - 10);
                    change_color_rgb(255, 0, 0);
                    cout << "You have made 5 wrong moves!";
                    reset_color();
                    delay(2000);
                    afterGameStatus(false);
                }

                if (isGameComplete())
                {
                    afterGameStatus(true);
                }
            }
        }
    }

    if (timeUp)
    {
        clear_screen();
        cursor_to_pos(rows / 2, columns / 2 - 10);
        change_color_rgb(255, 0, 0);
        cout << "Time's up!";
        reset_color();
        delay(2000);
        afterGameStatus(false);
    }
}
//----------------------------------------------------------------
void playAsavedgame()
{
    cursor_to_pos(rows / 2, columns / 2 - 10);
    change_color_rgb(255, 255, 0);
    cout << "In Progress...";
    reset_color();
    cursor_to_pos(rows / 2 + 2, columns / 2 - 10);
    change_color_rgb(255, 0, 0);
    cout << "Press any key to return to menu...";
    reset_color();
    getch();
    clear_screen();
    menu();
}
//----------------------------------------------------------------
void menu()
{
    int choice;
    cursor_to_pos(2, columns / 2 - 10);
    change_color_rgb(255, 255, 0);
    cout << "IN HIS SUBLIME NAME";
    reset_color();
    cursor_to_pos(4, columns / 2 - 10);
    change_color_rgb(0, 255, 0);
    cout << "let's play sudoku!";
    reset_color();
    cursor_to_pos(6, columns / 2 - 10);
    change_color_rgb(85, 81, 193);
    cout << "<Game Options>";
    reset_color();
    cursor_to_pos(6, 8);
    change_color_rgb(115, 97, 40);
    cout << "You are Logged in as " << userName;
    reset_color();
    cursor_to_pos(8, 8);
    change_color_rgb(255, 0, 0);
    cout << "1: Start a New Game";
    cursor_to_pos(10, 8);
    cout << "2: Play a Saved Game";
    cursor_to_pos(12, 8);
    cout << "3: Leaderboard";
    cursor_to_pos(14, 8);
    cout << "4: Exit the Game";
    reset_color();
    cursor_to_pos(17, 8);
    cout << "press a number from 1 to 4: ";
    cursor_to_pos(18, 8);
    change_color_rgb(255, 0, 0);
    change_color_rgb(255, 0, 195);
    cin >> choice;
    reset_color();
    clear_screen();
    if (choice == 1)
    {
        int difficulty = setDificulty();
        clear_screen();
        mainGame(difficulty);
        getch();
    }
    else if (choice == 2)
    {
        playAsavedgame();
    }
    else if (choice == 3)
    {
        displayLeaderboard();
    }
    else if (choice == 4)
    {
        enterUserName();
    }
    else
    {
        cursor_to_pos(rows / 2, columns / 2 - 10);
        change_color_rgb(255, 0, 0);
        cout << "Invalid choice!" << endl;
        delay(1000);
        clear_screen();
        menu();
    }
}
// The end :))