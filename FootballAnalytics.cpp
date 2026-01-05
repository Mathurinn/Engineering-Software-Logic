#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

class Player
{
private:
    string playerName;
    string teamName;
    int age;
    int goalsScored;
    int gamesPlayed;
    double salary;

public:
    Player();
    void setPlayer(string, string, int, int, int, double);
    string getPlayerName();
    string getTeamName();
    int getAge();
    int getGoalsScored();
    int getGames();
    double getSalary();
};

Player::Player()
{
    playerName = "";
    teamName = "";
    age = 0;
    goalsScored = 0;
    gamesPlayed = 0;
    salary = 0.0;
}

void Player::setPlayer(string pn, string tn, int ag, int gs, int gp, double sl)
{
    // Validate player name
    if (pn.empty())
    {
        playerName = "Unknown";
    }
    else
    {
        playerName = pn;
    }

    // Validate team name
    if (tn.empty())
    {
        teamName = "Unknown";
    }
    else
    {
        teamName = tn;
    }

    // Validate player age
    if (ag < 0)
    {
        age = 0;
    }
    else
    {
        age = ag;
    }

    // Validate goals scored
    if (gs < 0)
    {
        goalsScored = 0;
    }
    else
    {
        goalsScored = gs;
    }

    // Validate games played
    if (gp < 0)
    {
        gamesPlayed = 0;
    }
    else
    {
        gamesPlayed = gp;
    }

    // Validate salary
    if (sl < 0.0)
    {
        salary = 0.0;
    }
    else
    {
        salary = sl;
    }
}

string Player::getPlayerName()
{
    return playerName;
}

string Player::getTeamName()
{
    return teamName;
}

int Player::getAge()
{
    return age;
}

int Player::getGoalsScored()
{
    return goalsScored;
}

int Player::getGames()
{
    return gamesPlayed;
}

double Player::getSalary()
{
    return salary;
}

void fileRead(string fName, Player pl[], int sz);
void displayInfo(Player pl[], int sz);
string topScorer(Player pl[], int sz);
void detEfficiency(Player pl[], double ef[], int sz);
void writeEfficiencyReport(string fName, Player pl[], double ef[], int sz);
void detLowPaid(Player pl[], double& gs, int sz);
void oldPLayers(Player pl[], int& ga, int sz);

int main()
{
    double givenSalary = 0.0;
    int givenAge = 0;
    string fileName = "Player.csv";
    string dummy;
    int actualCount = 0;
    //Open the file to count the number of players that are inside

    ifstream countFile(fileName);

    if (!countFile)
    {
        cout << "Error: The file could not be opened... [" << fileName << "]" << endl;
    }
    else
    {
        getline(countFile, dummy);

        while (getline(countFile, dummy))
        {
            actualCount++;
        }

        countFile.close();
    }

    if (actualCount == 0)
    {
        cout << "Error: No data was found in the file [" << fileName << "]" << endl;
        return 1;
    }

    Player* players = new Player[actualCount];
    double* pEfficiency = new double[actualCount];

    fileRead(fileName, players, actualCount);
    displayInfo(players, actualCount);
    cout << endl;
    cout << "The top scorer for the 2024/25 season is: " << topScorer(players, actualCount) << endl << endl;

    //Display player efficiency
    detEfficiency(players, pEfficiency, actualCount);
    cout << "Player Efficiency:" << endl;
    cout << "------------------" << endl;
    for (int i = 0; i < actualCount; i++)
    {
        cout << players[i].getPlayerName() << " of " << players[i].getTeamName()
            << ": " << fixed << setprecision(2) << pEfficiency[i] << " goal(s) per game" << endl;
    }
    cout << endl;

    writeEfficiencyReport("EfficiencyReport.txt", players, pEfficiency, actualCount);

    //Determine and display players paid below a given amount
    cout << "Enter a salary amount to determine players paid below that amount: ";
    cin >> givenSalary;
    cout << endl;
    cout << "Players being paid below " << givenSalary << " GBP :" << endl;
    cout << "------------------------------------------------------" << endl;
    detLowPaid(players, givenSalary, actualCount);

    //Determine and display players older than a given age
    cout << endl;
    cout << "Enter a given age to determine players above that age: ";
    cin >> givenAge;
    cout << endl;
    cout << "Players above the given age of " << givenAge << ":" << endl;
    cout << "--------------------------------------------------" << endl;
    oldPLayers(players, givenAge, actualCount);

    delete[] players;
    delete[] pEfficiency;
    cout << "\nPress Enter to exit...";
    cin.ignore(1000, '\n');
    cin.get();
    return 0;
}

void fileRead(string fName, Player pl[], int sz)
{
    string line;
    int i = 0;
    ifstream inFile(fName);
    if (inFile.bad())
    {
        cout << "The file couldn't be opened..." << endl;
    }
    else
    {
        getline(inFile, line); // skip header
        while (getline(inFile, line) && i < sz)
        {
            int pos = 0;
            string playerName, teamName;
            int goals = 0, age = 0, games = 0;
            double playerSalary = 0.0;

            // Parse player name
            pos = line.find(',');
            playerName = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Parse team name
            pos = line.find(',');
            teamName = line.substr(0, pos);
            line.erase(0, pos + 1);

            // Goals scored
            pos = line.find(',');
            goals = atoi(line.substr(0, pos).c_str());
            line.erase(0, pos + 1);

            // Age
            pos = line.find(',');
            age = atoi(line.substr(0, pos).c_str());
            line.erase(0, pos + 1);

            // Games played
            pos = line.find(',');
            games = atoi(line.substr(0, pos).c_str());
            line.erase(0, pos + 1);

            // Salary
            playerSalary = atof(line.c_str());

            pl[i].setPlayer(playerName, teamName, age, goals, games, playerSalary);
            i++;
        }
    }
}

void displayInfo(Player pl[], int sz)
{
    cout << endl;
    cout << "Player Information:" << endl;
    cout << "--------------------" << endl;
    cout << left << setw(20) << "Name" << setw(15) << "Team"
        << setw(10) << "Goals" << setw(8) << "Age" << "Salary (GBP)" << endl;

    for (int i = 0; i < sz; i++)
    {
        cout << left << setw(20) << pl[i].getPlayerName()
            << setw(15) << pl[i].getTeamName()
            << setw(10) << pl[i].getGoalsScored()
            << setw(8) << pl[i].getAge()
            << fixed << setprecision(2) << pl[i].getSalary() << endl;
    }
}

string topScorer(Player pl[], int sz)
{
    int highest = pl[0].getGoalsScored();
    int index = 0;

    for (int i = 1; i < sz; i++)
    {
        if (pl[i].getGoalsScored() > highest)
        {
            highest = pl[i].getGoalsScored();
            index = i;
        }
    }
    return pl[index].getPlayerName();
}

void detEfficiency(Player pl[], double ef[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        if (pl[i].getGames() != 0)
        {
            ef[i] = double(pl[i].getGoalsScored()) / pl[i].getGames();
        }
        else
        {
            ef[i] = 0.0;
        }
    }
}

void writeEfficiencyReport(string fName, Player pl[], double ef[], int sz)
{
    ofstream outFile(fName);

    if (!outFile)
    {
        cout << "Error: The file could not be created... [" << fName << "]" << endl;
        return;
    }
    else
    {
        outFile << "PLAYER EFFICIENCY REPORT (2024/2025)" << endl;
        outFile << "====================================" << endl;
        outFile << left << setw(20) << "Name" << setw(15) << "Team" << "Goals/Game" << endl;
        outFile << "------------------------------------" << endl;

        for (int i = 0;i < sz;i++)
        {
            if (pl[i].getGames() > 0)
            {
                outFile << left << setw(20) << pl[i].getPlayerName()
                    << setw(15) << pl[i].getTeamName() << fixed << setprecision(2) << ef[i] << endl;
            }
        }
    }

    outFile.close();
    cout << "Efficiency Report successfully saved to " << fName << endl;
}

void detLowPaid(Player pl[], double& gs, int sz)
{
    bool playerFound = false;
    for (int i = 0; i < sz; i++)
    {
        if (pl[i].getSalary() < gs)
        {
            playerFound = true;
            cout << pl[i].getPlayerName() << " of " << pl[i].getTeamName()
                << ": " << fixed << setprecision(2) << pl[i].getSalary() << " GBP" << endl;
        }
    }
    if (!playerFound)
    {
        cout << "No players found below " << gs << " GBP" << endl;
    }
}

void oldPLayers(Player pl[], int& ga, int sz)
{
    bool playerFound = false;
    for (int i = 0; i < sz; i++)
    {
        if (pl[i].getAge() > ga)
        {
            playerFound = true;
            cout << pl[i].getPlayerName() << " of " << pl[i].getTeamName()
                << ": " << pl[i].getAge() << " years old" << endl;
        }
    }
    if (!playerFound)
    {
        cout << "No players found above age " << ga << endl;
    }
}
