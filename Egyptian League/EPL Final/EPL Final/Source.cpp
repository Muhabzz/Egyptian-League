// EPL Project Code  :
/*                          CREADITS :
* 
 Mohab Nasser Abdelkader       23013228
 Menna Khaled Abdelrehim       23012753
 Nada Mohamed Zain Alabdin     23012744 
 Manar Abdelbaky Hassan        23012850          
 Malak Hussien Mohamed         23017854
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib> 
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"


// Define some common colors From #include <cstdlib> 

using namespace std;

// Function To Set Colours in Main Function 
void setColor(const string& color)
{
    cout << color;
}

// Utility function to trim spaces
/*
Delete Any Space Founed In The String
*/

string manualTrim(const string& str)
{
    int first = str.find_first_not_of(" \t");//   "M"oha"b"          First == 3 -- Last = 7
    // Finding the first is space ( ) = string::npos
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1)); // 7 - 3 + 1 = (5) Number Of Characters 
}

// First LinkedList
// for : 
// Player Node Class
class PlayerNode {
public:
    int id; // Number Of Everyplayer
    string name;
    string position;
    string salary;
    int age;
    PlayerNode* next; // To Move for Everyplayer
    // Basic Counstructor 
    PlayerNode(int p_id, string p_name, string p_position, string p_salary, int p_age)
    {
        id = p_id;
        name = p_name;
        position = p_position;
        salary = p_salary;
        age = p_age;
        next = nullptr;
    }
};
// Second Linkedlist
// for :
// Team Node Class
class TeamNode {
private:
    int id;
    string name;
    string owner;
    PlayerNode* playerList; // Head
    TeamNode* next;

public:
    TeamNode(int t_id, string t_name, string t_owner)
    {
        id = t_id;
        name = t_name;
        owner = t_owner;
        playerList = nullptr;
        next = nullptr;
    }

    double totalSalary = 0.0;

    int getID() const { return id; }
    string getName() const { return name; }
    string getOwner() const { return owner; }
    void setNext(TeamNode* nextNode) { next = nextNode; }
    TeamNode* getNext() const { return next; }
    PlayerNode* getPlayerList() const { return playerList; }
    void setPlayerList(PlayerNode* newPlayerList) { playerList = newPlayerList; }

    // Setters to update team information
    void setName(const string& newName) { name = newName; }
    void setOwner(const string& newOwner) { owner = newOwner; }

    // Functions To Display It In Code : 

    void addPlayer(int p_id, string p_name, string p_position, string p_salary, int p_age) {
        PlayerNode* newPlayer = new PlayerNode(p_id, p_name, p_position, p_salary, p_age);
        if (!playerList) {
            playerList = newPlayer; // Head = newnode --> Insert First
        }
        else {
            PlayerNode* temp = playerList;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newPlayer; // Insert At End
        }
    }
    float calculateAverageAge() {
        if (playerList == NULL) {
            return 0.0;
        }
        int totalAge = 0;
        int count = 0;
        PlayerNode* temp = playerList;
        while (temp != NULL) {
            totalAge += temp->age;
            count++;
            temp = temp->next;
        }
        return (float)totalAge / count;
    }
 
    // Calculate the total salaries of players in the team
    void calculateTeamSalaries() {
        totalSalary = 0;

        PlayerNode* temp = playerList;
        while (temp) {
            // Convert the salary string to a double (adjust as needed) -- Salary in code = String
            double salaryValue = stod(temp->salary);
            totalSalary += salaryValue;
            temp = temp->next;
        }
    }
    void displayTeamsByAverageAge(TeamNode* head){
        TeamNode* temp = head;

        cout << "Teams sorted by average age of players:" << endl;
        while (temp != NULL) {
            cout << temp->name << " : Average Age: " << temp->calculateAverageAge() << endl;
            temp = temp->next;
        }
    }
    // Function to remove a player by ID
    void removePlayer(int playerID) {
        PlayerNode* temp = playerList; // Head
        PlayerNode* prev = nullptr; // Previous of head

        while (temp != nullptr) {
            if (temp->id == playerID) {
                if (prev == nullptr) {  // Player is the first one
                    playerList = temp->next; // Traverse to head
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
                cout << "Player with ID " << playerID << " removed." << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Player with ID " << playerID << " not found." << endl;
    }

    void displayPlayersSortedBySalary() {
        if (!playerList) {
            cout << "Error: No players in the team!" << endl;
            return;
        }

        // Convert the linked list to a vector for sorting
        vector<PlayerNode*> players;

        for (PlayerNode* current = playerList; current; current = current->next)
        {
            players.push_back(current);
        }

        // Sorting the players by salary using swap inside a loop
        for (size_t i = 0; i < players.size(); ++i) {
            for (size_t j = i + 1; j < players.size(); ++j) {
                // Compare salaries and swap if necessary
                if (stod(players[i]->salary) > stod(players[j]->salary)) {
                    swap(players[i], players[j]);
                }
            }
        }

        // Display the sorted players
        cout << "Players in team " << name << " sorted by salary:" << endl;
        for (const auto& player : players) {
            cout << "  Player ID: " << player->id << endl;
            cout << "  Name: " << player->name << endl;
            cout << "  Position: " << player->position << endl;
            cout << "  Age: " << player->age << endl;
            cout << "  Salary: " << player->salary << "m" << endl;
            cout << "-------------------------" << endl;
        }
    }
};

// Global vector to hold all teams (pointers) using STLS

vector<TeamNode*> teams;

// Egyptian League Class
class EgyptianLeague {
    //private:
public:
    TeamNode* selectedTeam;
    EgyptianLeague()
    {
        selectedTeam = nullptr;
    }
    void sortTeamsByAverageAge() {
        // Sorting the teams by average age
        for (size_t i = 0; i < teams.size(); ++i) {
            for (size_t j = i + 1; j < teams.size(); ++j) {
                if (teams[i]->calculateAverageAge() > teams[j]->calculateAverageAge()) {
                    // Swap the teams if their average age is in the wrong order
                    swap(teams[i], teams[j]);
                }
            }
        }

        // Now, display the teams' average age after sorting
        cout << "\nAverage age of players by team after sorting:" << endl;
        for (int i = 0; i < teams.size(); ++i) {
            cout << "Team: " << teams[i]->getName()
                << " - Average Age: " << teams[i]->calculateAverageAge() << endl;
        }
    }

    // Function to add a new player to a selected team
    void addPlayerToSelectedTeam() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        int p_id, p_age;
        string p_name, p_position, p_salary;

        cout << "Enter Player ID: ";
        cin >> p_id;
        cin.ignore();  // Ignore the newline after reading integer
        cout << "Enter Player Name: ";
        getline(cin, p_name);
        cout << "Enter Player Position: ";
        getline(cin, p_position);
        cout << "Enter Player Salary (e.g., 1m for millions, 100k for thousands): ";
        getline(cin, p_salary);
        cout << "Enter Player Age: ";
        cin >> p_age;

        selectedTeam->addPlayer(p_id, p_name, p_position, p_salary, p_age);
        cout << "Player added to " << selectedTeam->getName() << endl;
    }
    // Function to remove a player by player ID
    void removePlayerFromSelectedTeam() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        int playerId;
        cout << "Enter Player ID to remove: ";
        cin >> playerId;

        PlayerNode* prev = nullptr;
        PlayerNode* current = selectedTeam->getPlayerList(); // HEAD

        while (current!=NULL) {
            if (current->id == playerId) {
                if (prev) { // If The Player not the head
                    prev->next = current->next;
                }
                else {
                    // If the player to be removed is the head of the list
                    selectedTeam->setPlayerList(current->next); // Currentt = current -> next and delete current
                }

                delete current;  // Free the memory for the removed player
                cout << "Player with ID " << playerId << " removed." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Player with ID " << playerId << " not found." << endl;
    }
    // Function to display data of a player by player ID
    void displayPlayerData() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        int playerId;
        cout << "Enter Player ID to display: ";
        cin >> playerId;

        PlayerNode* current = selectedTeam->getPlayerList();
        while (current) {
            if (current->id == playerId) {
                cout << "Player ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Position: " << current->position << endl;
                cout << "Salary: " << current->salary << endl;
                cout << "Age: " << current->age << endl;
                return;
            }
            current = current->next;
        }

        cout << "Player with ID " << playerId << " not found." << endl;
    }
    // Function to search for a team by name
    void searchTeamByName() {
        string teamName;
        cout << "Enter Team Name to search: ";
        cin.ignore(); // Ignore any leftover newline character
        getline(cin, teamName);

        for (auto& team : teams) {
            if (team->getName() == teamName) {
                cout << "Team found!" << endl;
                cout << "Team ID: " << team->getID() << endl;
                cout << "Team Name: " << team->getName() << endl;
                cout << "Team Owner: " << team->getOwner() << endl;
                return;
            }
        }

        cout << "Team with name '" << teamName << "' not found." << endl;
    }
    // Function to update team information (name and owner)
    void updateTeamInformation() 
    {
        if (!selectedTeam)
        {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        string newName, newOwner;
        cout << "Enter new Team Name: ";
        cin.ignore();
        getline(cin, newName);
        cout << "Enter new Team Owner: ";
        getline(cin, newOwner);

        selectedTeam->setName(newName);   // Assuming you have a setter function for name
        selectedTeam->setOwner(newOwner); // Assuming you have a setter function for owner

        cout << "Team information updated successfully!" << endl;
    }


    // Add a new team
    void addTeam(int id, string name, string owner) {
        TeamNode* newTeam = new TeamNode(id, name, owner);
        teams.push_back(newTeam);
        cout << "Team added successfully!" << endl;
    }

    // Display all teams
    void displayTeams()
    {
        if (teams.empty()) {
            cout << "No teams available." << endl;
            return;
        }

        cout << "Teams and Their average ages :" << endl;
        for (const auto& team : teams)
        {
            PlayerNode* player = team->getPlayerList();

            cout << "Team Name: " << team->getName() << endl;
            cout << "Team Rank : " << team->getID() << endl;
            cout << "Team Coach : " << team->getOwner() << endl;
            cout << "-------------------------" << endl;
        }
    };

    // Display players of the selected team
    void displaySelectedTeamPlayers() {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        cout << "Team Name: " << selectedTeam->getName() << endl;
        cout << "Players:" << endl;

        if (!selectedTeam->getPlayerList()) {
            cout << "  No players in this team." << endl;
            return;
        }

        PlayerNode* player = selectedTeam->getPlayerList();
        while (player) {
            cout << "  Player Number : " << player->id << " "
                << " , Name : " << player->name << " "
                << " , Position : " << player->position << " "
                << " , Salary : " << player->salary << " "
                << " , Age : " << player->age << endl;
            player = player->next;
        }
    }


    // Select a team by ID
    void selectTeamById(int id)
    {
        if (teams.empty()) {
            cout << "No teams available to delete." << endl;
            return;
        }

        for (const auto& team : teams) {
            if (team->getID() == id) {
                selectedTeam = team;
                cout << "Selected Team: " << team->getName() << " (ID: " << team->getID() << ")" << endl;
                displaySelectedTeamPlayers();
                return;
            }
        }
        cout << "Team with ID " << id << " not found." << endl;
        selectedTeam = nullptr;
    }
    void deleteTeam(int teamId) {
        if (teams.empty()) {
            cout << "No teams available to delete." << endl;
            return;
        }

        // Iterator للتنقل بين الفرق
        auto it = teams.begin();
        while (it != teams.end()) {
            if ((*it)->getID() == teamId) { // لو ID الفريق متوافق
                cout << "Deleting team: " << (*it)->getName() << endl;

                // حذف الفريق واللاعبين المرتبطين به
                delete* it; // تحرير الذاكرة
                it = teams.erase(it); // إزالة الفريق من القائمة

                cout << "Team deleted successfully!" << endl;
                return;
            }
            ++it;
        }

        // لو الفريق مش موجود
        cout << "Team with ID " << teamId << " not found." << endl;
    }

    void searchPlayerByName()
    {
        if (!selectedTeam) {
            cout << "No team selected. Please select a team first!" << endl;
            return;
        }

        string playerName;
        cout << "Enter Player Name to search: ";
        cin.ignore();
        getline(cin, playerName);

        PlayerNode* current = selectedTeam->getPlayerList();

        while (current) {
            if (current->name == playerName) {
                cout << "Player found!" << endl;
                cout << "Player ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Position: " << current->position << endl;
                cout << "Salary: " << current->salary << endl;
                cout << "Age: " << current->age << endl;
                return;
            }
            current = current->next;
        }

        cout << "Player with name '" << playerName << "' not found." << endl;
    }


    //                     LOADING Department


    // Load teams from file
    // Same As Load Players From File


    void loadTeamsFromFile()
    {
        ifstream file("teams.txt");
        if (!file) {
            cout << "Error: File not found!" << endl;
            return;
        }

        string line, name, owner;
        int id;
        while (getline(file, line))
        {
            // We use manualTrim ( + 1 ) to get anything after the coloum : 
            if (line.empty()) continue;

            if (line.find("Team name") != string::npos)
            {
                // To Remove anyspaces
                name = manualTrim(line.substr(line.find(":") + 1));
            }
            else if (line.find("Team id") != string::npos)
            {
                id = stoi(line.substr(line.find(":") + 1));
            }
            else if (line.find("Team Owner") != string::npos) {
                owner = manualTrim(line.substr(line.find(":") + 1));

                // Add team
                TeamNode* newTeam = new TeamNode(id, name, owner);
                teams.push_back(newTeam);

                // Load players for this team (assuming filenames are like "teamname.txt")

                string fileName = name + ".txt"; // Create filename dynamically
                loadPlayersFromFile(newTeam, fileName);
            }
        }
        file.close();
        cout << "Teams and players loaded successfully!" << endl;
    }

    // Function to load players from a team-specific file
    // using library fstream
    void loadPlayersFromFile(TeamNode* team, const string& fileName) {
        ifstream file(fileName);
        if (!file) {
            cout << "Error: Unable to open file " << fileName << "!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // Parse the line (ID, Name, Position, Age, Salary)
            stringstream ss(line);
            string idStr, name, position, ageStr, salaryStr;
            // 1,Mohamed Elshenawy,GK,31,2
            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, position, ',');
            getline(ss, ageStr, ',');
            getline(ss, salaryStr, ',');

            if (idStr.empty() || name.empty() || position.empty() || ageStr.empty() || salaryStr.empty()) {
                continue;
            }

            int id = stoi(idStr);
            int age = stoi(ageStr);
            double salary = stod(salaryStr);

            if (salary < 10) salary *= 1'000'000;

            team->addPlayer(id, name, position, to_string(salary / 1'000'000) + "m", age);
        }

        cout << "Players loaded successfully for team: " << team->getName() << endl;
        file.close();
    }

    // Destructor to free all teams from Memory
    ~EgyptianLeague() 
    {
        for (auto team : teams) // Iterator 34an y3dy 3 kol el teams
        {
            delete team;
        }
        teams.clear();
    }
};

// Main Function
int main() {
    EgyptianLeague league;
    int choice;
    do {
        // Clear the screen (use "cls" for Windows)
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // Display the menu with colors
        setColor(CYAN);
        cout << "\n" << string(40, '=') << endl;
        cout << "     === Egyptian League Management System ===            " << endl;
        cout << string(40, '=') << RESET << endl;

        setColor(YELLOW);
        cout << "1. Load teams from file" << endl;
        cout << "2. Add a new team" << endl;
        cout << "3. Display all teams" << endl;
        cout << "4. Select a team by ID" << endl;
        cout << "5. Exit" << endl;
        cout << "6. Load players from file" << endl;
        cout << "7. Add a new player to selected team" << endl;
        cout << "8. Remove a player from selected team" << endl;
        cout << "9. Display player data" << endl;
        cout << "10. Search for a team by name" << endl;
        cout << "11. Update team information" << endl;
        cout << "12.Display TeamsByAverageAge" << endl;
        cout << "13. Display players of the selected team sorted by salary" << endl;
        cout << "14. Enter Team ID to delete" << endl;
        cout << "15. Search for Player By Name" << endl;

        setColor(RESET);


        setColor(GREEN);
        cout << "Enter your choice: ";
        cin >> choice;
        setColor(RESET);

        switch (choice) {


        case 1:
            setColor(BLUE);
            cout << "Loading teams from file..." << RESET << endl;
            league.loadTeamsFromFile();
            break;
        case 2: {
            int id;
            string name, owner;
            setColor(BLUE);
            cout << "Enter Team ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Team Name: ";
            getline(cin, name);
            cout << "Enter Team Owner: ";
            getline(cin, owner);
            league.addTeam(id, name, owner);
            setColor(GREEN);
            cout << "Team added successfully!" << RESET << endl;
            break;
        }
        case 3:
            setColor(BLUE);
            cout << "Displaying all teams..." << RESET << endl;
            league.displayTeams();
            break;
        case 4: {
            int id;
            setColor(BLUE);
            cout << "Enter Team ID to select: ";
            cin >> id;
            league.selectTeamById(id);
            break;
        }
        case 5:
            setColor(RED);
            cout << "Exiting... Goodbye!" << RESET << endl;
            break;
        case 6: {
            int teamId;
            setColor(BLUE);
            cout << "Enter Team ID to load players: ";
            cin >> teamId;
            TeamNode* team = nullptr;
            for (auto& t : teams)
            {
                if (t->getID() == teamId)
                {
                    team = t;
                    break;
                }
            }
            if (team) {
                league.loadPlayersFromFile(team, team->getName() + ".txt");
            }
            else
            {
                cout << "Team not found!" << endl;
            }
            break;
        }
        case 7:
            league.addPlayerToSelectedTeam();
            break;
        case 8:
            league.removePlayerFromSelectedTeam();
            break;
        case 9:
            league.displayPlayerData();
            break;
        case 10:
            league.searchTeamByName();
            break;
        case 11:
            league.updateTeamInformation();
            break;
        case 12:
            league.sortTeamsByAverageAge();
            break;
        case 13: {
            if (!league.selectedTeam) {
                cout << "No team selected. Please select a team first!" << endl;
                break;
            }
            league.selectedTeam->displayPlayersSortedBySalary();
            break;
        }
        case 14: {
            int teamId;
            cout << "Enter Team ID to delete: ";
            cin >> teamId;
            league.deleteTeam(teamId);
            break;
        }
        case 15 :
        {
            league.searchPlayerByName();
        }
        default:
            setColor(RED);
            cout << "Invalid choice! Please try again." << RESET << endl;
        }

        // Pause for the user to read output
        setColor(YELLOW);
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        setColor(RESET);

    } while (choice != 5);

    return 0;
}