//
// Created by Rui Pinto on 10/11/2019.
//

#include "NationalTeam.h"
#include "TechnicalTeam.h"
#include "../NecessaryFunctions_NameSpaces.h"
#include <iostream>
#include <new>
#include <limits>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/* Gets */

string NationalTeam::getName() const
{
    return name;
}

/* Sets */

string NationalTeam::setName(string &name)
{
    this->name = name;
    return name;
}

/* OtherWorker Methods */

bool NationalTeam::createOtherWorker()
{
    string auxName = readOperations::readString("Name:");

    Date birth = readOperations::readDate("Birth Date (DD/MM/YYYY):");

    string auxRole = readOperations::readString("Role:");

    unsigned int auxSalary = readOperations::readNumber<unsigned int>("Salary:");

    unsigned int id = getLastID(otherWorkers);

    cout << endl << "Are you sure you want to insert the following data? (Y|N)" << endl << endl;
    OtherWorker *oW = new OtherWorker(id, auxRole, auxSalary, auxName, birth);
    oW->header();
    oW->info();
    cout << endl << endl;
    string answer = readOperations::confirmAnswer();

    if(answer == "Y" || answer == "y")
    {
        addOtherWorker(oW);
        cout << "Data successfully inserted!" << endl;
        return true;
        /* In the future to save all info inside a file */
        //  ofstream out_stream("../Files/OtherWorkers.txt", ios::app);
        //  oW.info(out_stream);
    }
    cout << "Data not inserted." << endl;
    delete oW;
    return false;

    // NATIONALTEAM DESTRUCTOR SHOULD DESTRUCT ALL VECTORS BECAUSE THEY'RE ALLOCATED DYNAMICALLY
}

bool NationalTeam::readOtherWorkersFile(string filename) {
    ifstream f;
    f.open(filename);
    unsigned int id, salary;
    string name, aux;
    char delim = ' ';
    Date birthday;
    string function;
    if (f.is_open()) {
        while(!f.eof()) {
            getline(f, aux, delim);
            f >> id;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, name);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> birthday;
            getline(f, aux, delim);
            getline(f, function);
            getline(f, aux, delim);
            f >> salary;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux); // blank line

            OtherWorker* oW = new OtherWorker(id, function, salary, name, birthday);
            addOtherWorker(oW);

        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}

bool NationalTeam::deleteOtherWorker() {
    OtherWorker *oW = workerLookUp(otherWorkers);
    if(oW == NULL)
        return false;
    for (auto it = otherWorkers.begin(); it != otherWorkers.end(); it++) {
        if (*(*it) == *oW) {
            otherWorkers.erase(it);
            cout << endl << "Other Worker successfully removed!" << endl << endl;
            return true;
        }
    }
    return false;
}

bool NationalTeam::alterOtherWorker()
{
    bool toggle = true;
    int repetition = 0, option;

    cout << string(100, '\n');
//    cout << explorer << endl << endl;

    OtherWorker *person = workerLookUp(otherWorkers);
    if(person == NULL)
        return false;

    while (toggle)
    {
        if (repetition == 0)
        {
            cout << endl << "What do you want to change?\n";
            repetition++;
        }
        else
            cout << "Do you want to change anything else?\n";

        cout << "1. Name\n2. Role\n3. Birth Date\n4. Salary\n0. Back\n\n";
        cin >> option; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (option)
        {
            case 0:
            {
                toggle = false;
                break;
            }
            case 1:
            {
                cout << "Previous Name: " << person->getName() << endl;
                string auxName = readOperations::readString("New Name:");
                person->setName(auxName);
                break;
            }
            case 2:
            {
                cout << "Previous Role: " << person->getRole() << endl;
                string auxRole = readOperations::readString("New Role:");
                person->setRole(auxRole);
                break;
            }
            case 3:
            {
                cout << "Previous Birth Date: " << person->getDate() << endl;
                Date birth = readOperations::readDate("New Birth Date (DD/MM/YYYY):");
                person->setDate(birth);
                break;
            }
            case 4:
            {
                cout << "Previous Salary: " << person->getSalary() << endl;
                float auxSalary = readOperations::readNumber<float>("New Salary:");
                person->setSalary(auxSalary);
                break;
            }
        }
        if (toggle)
        {
            cout << endl << "Worker successfully altered!" << endl;
            // OtherWorkerInfoHasChanged = true;
        }
    }
    return true;
}

void NationalTeam::addOtherWorker(OtherWorker *oW)
{
    otherWorkers.push_back(oW);
}

vector<OtherWorker*>& NationalTeam::getOtherWorkers()
{
    return otherWorkers;
}

void NationalTeam::displayOtherWorkers() const {
    OtherWorker::header();
    for(auto &worker: otherWorkers)
    {
        worker->info();
        cout << endl;
    }
}

void NationalTeam::displaySoccerPlayers() const
{
    SoccerPlayer::header();
    for(auto &player: players)
    {
        player->info();
        cout << endl;
    }

}

/* SoccerPlayer Methods */

bool NationalTeam::readSoccerPlayersFile(string filename) {
    ifstream f;
    f.open(filename);
    unsigned int id, daysActive;
    string name, position, club, aux;
    char delim = ' ';
    Date birthday;
    unsigned short weight, height;
    unsigned long marketPrice;
    if (f.is_open()) {
        while(!f.eof()) {
            getline(f, aux, delim);
            f >> id;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, name);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> birthday;
            getline(f, aux, delim);
            getline(f, position);
            getline(f, aux, delim);
            getline(f, club);
            getline(f, aux, delim);
            f >> weight;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> height;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> marketPrice;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> daysActive;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, '\n');  // blank line

            SoccerPlayer* sP = new SoccerPlayer(id, name, birthday, position,
                    club, weight, height, marketPrice, daysActive);
            addSoccerPlayer(sP);

        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }

}

void NationalTeam::addSoccerPlayer(SoccerPlayer *sP) {
    players.push_back(sP);
}

bool NationalTeam::createSoccerPlayer()
{
    string auxName = readOperations::readString("Name:");
    Date birth = readOperations::readDate("Birth Date (DD/MM/YYYY):");
    string auxPosition = readOperations::readString("Position:");
    string auxClub = readOperations::readString("Club:");
    unsigned short auxWeight =  readOperations::readNumber<unsigned short>("Weight (KG):");
    unsigned short auxHeight = readOperations::readNumber<unsigned short>("Height (CM):");
    unsigned long marketPrice = readOperations::readNumber<unsigned long>("Market Price:");
    unsigned int daysActive = readOperations::readNumber<unsigned int>("Days Active:");

    unsigned int id = getLastID(players);

    cout << endl << "Are you sure you want to insert the following data? (Y|N)" << endl << endl;
    SoccerPlayer *sP = new SoccerPlayer(id, auxName, birth, auxPosition, auxClub, auxWeight, auxHeight, marketPrice, daysActive);
    sP->header();
    sP->info();
    cout << endl << endl;
    string answer = readOperations::confirmAnswer();

    if(answer == "Y" || answer == "y")
    {
        addSoccerPlayer(sP);
        cout << "Data successfully inserted!" << endl;
        return true;
        /* In the future to save all info inside a file */
        //  ofstream out_stream("../Files/OtherWorkers.txt", ios::app);
        //  oW.info(out_stream);
    }
    cout << "Data not inserted." << endl;
    delete sP;
    return false;

    // NATIONALTEAM DESTRUCTOR SHOULD DESTRUCT ALL VECTORS BECAUSE THEY'RE ALLOCATED DYNAMICALLY
}

bool NationalTeam::alterSoccerPlayer()
{
    bool toggle = true;
    int repetition = 0, option;

    cout << string(100, '\n');
//    cout << explorer << endl << endl;

    SoccerPlayer *person = workerLookUp(players);
    if(person == NULL)
        return false;

    while (toggle)
    {
        if (repetition == 0)
        {
            cout << endl << "What do you want to change?\n";
            repetition++;
        }
        else
            cout << "Do you want to change anything else?\n";

        cout << "1. Name\n2. Birth Date\n3. Position\n4. Club\n5. Weight\n6. Height\n7. Market Price\n8. Days Active\n0. Back\n\n";
        cin >> option; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

        switch (option)
        {
            case 0:
            {
                toggle = false;
                break;
            }
            case 1: /* Name */
            {
                cout << "Previous Name: " << person->getName() << endl;
                string auxName = readOperations::readString("New Name:");
                person->setName(auxName);
                break;
            }
            case 2: /* Birth Date */
            {
                cout << "Previous Birth Date: " << person->getDate() << endl;
                Date birth = readOperations::readDate("New Birth Date (DD/MM/YYYY):");
                person->setDate(birth);
                break;
            }
            case 3: /* Position */
            {
                cout << "Previous Position: " << person->getPosition() << endl;
                string auxPosition = readOperations::readString("New Position:");
                person->setPosition(auxPosition);
                break;
            }
            case 4: /* Club */
            {
                cout << "Previous Club: " << person->getClub() << endl;
                string auxClub = readOperations::readString("New Club:");
                person->setClub(auxClub);
                break;
            }
            case 5: /* Weight */
            {
                cout << "Previous Weight: " << person->getWeight() << endl;
                unsigned short auxWeight = readOperations::readNumber<unsigned short>("New Weight (KG):");
                person->setWeight(auxWeight);
                break;
            }
            case 6: /* Height */
            {
                cout << "Previous Height: " << person->getHeight() << endl;
                unsigned short auxHeight = readOperations::readNumber<unsigned short>("New Height (CM):");
                person->setHeight(auxHeight);
                break;
            }
            case 7: /* MarketPrice */
            {
                cout << "Previous Market Price: " << person->getMarketPrice() << endl;
                unsigned long auxMarketPrice = readOperations::readNumber<unsigned long>("New Market Price:");
                person->setMarketPrice(auxMarketPrice);
                break;
            }
            case 8: /* Days Active */
            {
                cout << "Previous Days Active: " << person->getDaysActive() << endl;
                unsigned int auxDaysActive = readOperations::readNumber<unsigned int>("New Days Active:");
                person->setDaysActive(auxDaysActive);
                break;
            }
        }
        if (toggle)
        {
            cout << endl << "Player successfully altered!" << endl;
            // OtherWorkerInfoHasChanged = true;
        }
    }
    return true;
}

bool NationalTeam::deleteSoccerPlayer(){
    SoccerPlayer *sP = workerLookUp(players);
    if(sP == NULL)
        return false;
    for (auto it = players.begin(); it != players.end(); it++) {
        if (*(*it) == *sP) {
            players.erase(it);
            cout << endl << "Soccer Player successfully removed!" << endl << endl;
            return true;
        }
    }
    return false;
}

/* Games */

bool NationalTeam::createGame() {
    unsigned int id = getLastID(games);
    Date date = readOperations::readDate("Game date:");
    string city = readOperations::readString("City:");
    string country = readOperations::readString("Country:");
    string oppositeTeam = readOperations::readString("Opposite Team:");
    string oppositeTeamParticipantsString = readOperations::readString("Opposite Team Participants: (in the format player1, player2, etc.)");
    // STILL NEED TO CHECK IF THE INPUT WAS CORRECT!!!!!!
    vector<string> oppositeTeamParticipants = generalFunctions::separate_string(oppositeTeamParticipantsString, ',');

    string refereeingTeamString = readOperations::readString("Refereeing Team: (in the format referee1, referee2, etc.)");
    // STILL NEED TO CHECK IF THE INPUT WAS CORRECT!!!!!!
    vector<string> refereeingTeam = generalFunctions::separate_string(refereeingTeamString, ',');

    GameStats* gameStats = createGameStatistics(id);

    // NEED TO CREATE INDIVIDUAL STATISTICS
    return true;
}

void NationalTeam::addGame(Game* game) {
    games.push_back(game);
}

// NOT TESTED YET!!!
bool NationalTeam::readGamesFile(std::string filename) {
    ifstream f;
    f.open(filename);
    string aux, city, country, stadium, oppositeTeam;
    char delim = ' ';
    unsigned int id, gameStatisticsId;
    Date date;
    vector<string> oppositeTeamParticipants;
    vector<string> refereeingTeam;
    GameStats* gameStatsPtr;
    vector<string> individualStatsVectorString;
    vector<int> individualStatsVectorInt;
    vector<IndividualStatistics *> individualStatistics;

    if (f.is_open()) {
        while(!f.eof()) {
            getline(f, aux, delim);
            f >> id;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> date;
            getline(f, aux, delim);
            getline(f, country);
            getline(f, aux, delim);
            getline(f, stadium);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, oppositeTeam);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux);
            oppositeTeamParticipants = generalFunctions::separate_string(aux, ',');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux);
            refereeingTeam = generalFunctions::separate_string(aux, ',');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> gameStatisticsId;
            f.clear();
            f.ignore(1000, '\n');
            gameStatsPtr = getByID(gameStats, gameStatisticsId);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux);
            individualStatsVectorString = generalFunctions::separate_string(aux, ',');
            individualStatsVectorInt = generalFunctions::convert_vector_str_to_int(individualStatsVectorString);
            for (auto &x: individualStatsVectorInt) {
                individualStatistics.push_back(getByID(individualStatistics, x));
            }

            Game* game = new Game(id, date, city, country, stadium, oppositeTeam, oppositeTeamParticipants,
                              refereeingTeam, gameStatsPtr, individualStatistics);
            addGame(game);

            }
            f.close();
            return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }

}

/* Calls */

bool sortPlayers(const SoccerPlayer* player1, const SoccerPlayer* player2)
{
    return player1->getId() < player2->getId();
}


bool NationalTeam::createCall()
{

    unsigned int counter = 0;
    vector<SoccerPlayer*> auxSoccerPlayers;
    unsigned int numPlayers = 0;

    while(true)
    {
        numPlayers = readOperations::readNumber<unsigned int>("Number of Players to Insert (12 - 24):");
        if(numPlayers < 12 || numPlayers > 24)
            cout << "Please Insert a Value Between 12 and 24." << endl;
        else
            break;
    }

    cout << endl << endl << "1 - Player Selection:" << endl;

    while(counter != numPlayers)
    {
        SoccerPlayer* player = workerLookUp(players);
        if(player == NULL)
            return false;



        sort(auxSoccerPlayers.begin(), auxSoccerPlayers.end(), sortPlayers);
        if(binary_search(auxSoccerPlayers.begin(), auxSoccerPlayers.end(), player, sortPlayers))
        {
            cout << endl << "Player Already Inserted! Try again..." << endl;
            continue;
        }
        else
        {
            auxSoccerPlayers.push_back(player);
            player->header();
            for(auto &x: auxSoccerPlayers)
            {
                x->info();
                cout << endl;
            }
        }

        createInfCalls(player->getId());
        counter++;
        cout << endl << "Players Remaining Inserted [ " << (numPlayers - counter) << " ]: " <<  endl << endl;

    }

    string competition = readOperations::readString("Competition:");
    Date begDate, endDate;
    do
    {
        begDate = readOperations::readDate("Arrive Date (DD/MM/YYYY):");
        endDate = readOperations::readDate("Left Date (DD/MM/YYYY):");
        if(endDate <= begDate)
            std::cout << "First Date Has To Be Less Than or Equal To The Second! Try again..." << std::endl << std::endl;
    } while(!(begDate <= endDate));
    int housing_food = readOperations::readNumber<int>("Housing and Food Costs:");

    return true;

}


/* Game Statistics */

void NationalTeam::addGameStatistics(GameStats* gStats) {
    gameStats.push_back(gStats);
}

GameStats* NationalTeam::createGameStatistics(unsigned int gameID) {
    unsigned short goals = readOperations::readNumber<unsigned short>("Goals:");
    unsigned short oppositionGoals = readOperations::readNumber<unsigned short>("Opposing Team Goals:");
    unsigned short shots = readOperations::readNumber<unsigned short>("Shots:");
    unsigned short oppositionShots = readOperations::readNumber<unsigned short>("Opposing Team shots:");
    unsigned short shotsTarget = readOperations::readNumber<unsigned short>("Shots on Target:");
    unsigned short oppositionShotsTarget = readOperations::readNumber<unsigned short>("Opposing Team Shots on Target:");
    unsigned short possession = readOperations::readNumber<unsigned short>("Possession:");
    unsigned short passes = readOperations::readNumber<unsigned short>("Passes:");
    unsigned short oppositionPasses = readOperations::readNumber<unsigned short>("Opposing Team passes:");
    unsigned short passAccuracy = readOperations::readNumber<unsigned short>("Pass Accuracy:");
    unsigned short oppositionPassAccuracy = readOperations::readNumber<unsigned short>("Opposing Team Pass Accuracy:");
    unsigned short fouls = readOperations::readNumber<unsigned short>("Fouls:");
    unsigned short oppositionFouls = readOperations::readNumber<unsigned short>("Opposing Team Fouls:");
    unsigned short yellowCards = readOperations::readNumber<unsigned short>("Yellow Cards:");
    unsigned short oppositionYellowCards = readOperations::readNumber<unsigned short>("Opposing Yellow Cards:");
    unsigned short redCards = readOperations::readNumber<unsigned short>("Red Cards:");
    unsigned short oppositionRedCards = readOperations::readNumber<unsigned short>("Opposing Team Red Cards:");
    unsigned short offsides = readOperations::readNumber<unsigned short>("Offsides:");
    unsigned short oppositionOffsides = readOperations::readNumber<unsigned short>("Opposing Team Offsides:");
    unsigned short corners = readOperations::readNumber<unsigned short>("Corners:");
    unsigned short oppositionCorners = readOperations::readNumber<unsigned short>("Opposing Team Corners:");
    unsigned short injuries = readOperations::readNumber<unsigned short>("Injuries:");
    unsigned short oppositionInjuries = readOperations::readNumber<unsigned short>("Opposing Team Injuries:");

    cout << endl << "Are you sure you want to insert the following data? (Y|N)" << endl << endl;
    GameStats *gStats = new GameStats(gameID, goals, oppositionGoals, shots, oppositionShots, shotsTarget, oppositionShotsTarget,
                                      possession, passes, oppositionPasses, passAccuracy, oppositionPassAccuracy, fouls, oppositionFouls, offsides, oppositionOffsides,
                                      corners, oppositionCorners, yellowCards, oppositionYellowCards, redCards, oppositionRedCards, injuries, oppositionInjuries);
    gStats->info(cout);
    string answer = readOperations::confirmAnswer();

    if(answer == "Y" || answer == "y")
    {
        addGameStatistics(gStats);
        cout << "Data successfully inserted!" << endl;
        return gStats;
        /* In the future to save all info inside a file */
        //  ofstream out_stream("../Files/OtherWorkers.txt", ios::app);
        //  oW.info(out_stream);
    }
    cout << "Data not inserted." << endl;
    delete gStats;
    return NULL;
}

bool NationalTeam::readGameStatisticsFile(std::string filename) {
    ifstream f;
    f.open(filename);
    string aux;
    char delim = ' ';
    unsigned int gameId;
    unsigned short goals, oppositionGoals, shots, oppositionShots, shotsTarget, oppositionShotsTarget, possession,
            passes, oppositionPasses, passAccuracy, oppositionPassAccuracy, fouls, oppositionFouls, yellowCards, oppositionYellowCards,
            redCards, oppositionRedCards, offsides, oppositionOffsides, corners, oppositionCorners, injuries, oppositionInjuries;

    if (f.is_open()) {
        while (!f.eof()) {
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> gameId;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> goals;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionGoals;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> shots;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionShots;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> shotsTarget;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionShotsTarget;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> possession;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> passes;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionPasses;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> passAccuracy;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionPassAccuracy;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> fouls;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionFouls;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> yellowCards;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionYellowCards;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> redCards;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionRedCards;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> offsides;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionOffsides;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> corners;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionFouls;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> injuries;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> oppositionInjuries;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, '\n');  // blank line

            GameStats* gStats = new GameStats(gameId, goals, oppositionGoals, shots, oppositionShots, shotsTarget, oppositionShotsTarget,
                    possession, passes, oppositionPasses, passAccuracy, oppositionPassAccuracy,fouls, oppositionFouls, offsides, oppositionOffsides,
                    corners, oppositionCorners, yellowCards, oppositionYellowCards, redCards, oppositionRedCards, injuries, oppositionInjuries);
            addGameStatistics(gStats);

        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}


/* Individual Statistics */

void NationalTeam::addIndividualStatistic(IndividualStatistics* iStat) {
    individualStats.push_back(iStat);
}

IndividualStatistics *NationalTeam::createIndividualStatistics(unsigned int gameID, unsigned int playerID) {
    unsigned int id = getLastID(individualStats);
    unsigned short goals = readOperations::readNumber<unsigned short>("Goals:");
    unsigned short assists = readOperations::readNumber<unsigned short>("Assists:");
    unsigned short shots = readOperations::readNumber<unsigned short>("Shots:");
    unsigned short shotsTarget = readOperations::readNumber<unsigned short>("Shots on Target:");
    unsigned short passes = readOperations::readNumber<unsigned short>("Passes:");
    unsigned short travelledDistance = readOperations::readNumber<unsigned short>("Travelled Distance (in Km):");
    unsigned short playedMinutes = readOperations::readNumber<unsigned short>("Played Minutes:");
    unsigned short yellowCards = readOperations::readNumber<unsigned short>("Yellow Cards:");
    unsigned short redCards = readOperations::readNumber<unsigned short>("Red Cards:");
    unsigned short fouls = readOperations::readNumber<unsigned short>("Fouls:");
    bool injured;
    bool validInjured;
    do {
        string injuredString = readOperations::readString("Injured? (true / false)");
        if (injuredString == "false") {
            injured = false;
            validInjured = true;
        }
        else if (injuredString == "true") {
            injured = true;
            validInjured = true;
        }
        else
            validInjured = false;
    } while (!validInjured);

    IndividualStatistics* iStat = new IndividualStatistics(id, playerID, gameID, goals, assists, passes, shots,
                                                           shotsTarget, travelledDistance, playedMinutes, yellowCards, redCards, fouls, injured);

    addIndividualStatistic(iStat);

    return iStat;
}

// TO DO
bool NationalTeam::alterIndividualStatistic() {
    bool toggle = true;
    int repetition = 0, option;

    cout << string(100, '\n');
//    cout << explorer << endl << endl;

    int id;
    IndividualStatistics* iStat = getByID(individualStats, id);

    return true;
}

bool NationalTeam::readIndividualStatisticsFile(std::string filename) {
    ifstream f;
    f.open(filename);
    string aux, injuredString;
    char delim = ' ';
    unsigned int id, playerID, gameID;
    unsigned short goals, assists, shots, shotsTarget, passes, travelledDistance, playedMinutes, yellowCards, redCards, injured, fouls;

    if (f.is_open()) {
        while (!f.eof()) {
            getline(f, aux, delim);
            f >> id;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> playerID;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> gameID;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> goals;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> assists;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> shots;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> shotsTarget;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            f >> passes;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> playedMinutes;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> yellowCards;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, aux, delim);
            f >> redCards;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, delim);
            getline(f, injuredString);
            if (injuredString == "false")
                injured = false;
            else
                injured = true;
            getline(f, aux, delim);
            f >> fouls;
            f.clear();
            f.ignore(1000, '\n');
            getline(f, aux, '\n');  // blank line

            IndividualStatistics* iStats = new IndividualStatistics(id, playerID, gameID, goals, assists,
                    passes, shots, shotsTarget, travelledDistance, playedMinutes, yellowCards, redCards,
                    fouls, injured);
            addIndividualStatistic(iStats);

        }
        f.close();
        return true;
    }
    else {
        cerr << "Error reading the file " << filename << endl;
        return false;
    }
}


/* InfCalls */

bool NationalTeam::createInfCalls(unsigned int sPId)
{
    cout << endl;
    Date arriveDate, leftDate;
    do
    {
        arriveDate = readOperations::readDate("Arrive Date (DD/MM/YYYY):");
        leftDate = readOperations::readDate("Left Date (DD/MM/YYYY):");
        if(leftDate <= arriveDate)
            std::cout << "First Date Has To Be Less Than or Equal To The Second! Try again..." << std::endl << std::endl;
    } while(!(arriveDate <= leftDate));

    unsigned int id = getLastID(players);

    cout << endl << "Are you sure you want to insert the following data? (Y|N)" << endl << endl;
    InfCall* inf = new InfCall(id, sPId, arriveDate, leftDate);

    string answer = readOperations::confirmAnswer();

    if(answer == "Y" || answer == "y")
    {
        addInfCalls(inf);
        return true;

    }
    cout << "Data not inserted..." << endl;
    delete inf;
    return false;
}

void NationalTeam::addInfCalls(InfCall *inf)
{
    infCalls.push_back(inf);
}


