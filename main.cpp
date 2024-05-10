#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <random>
#include <algorithm>
#include <tuple>
#include <memory>
#include <set>


class Team{
    std::string name;
    std::string city;
    int rating;
public:
    Team(const std::string& name_, const std::string& city_, int rating_) : name(name_), city(city_), rating(rating_) {}
    ~Team() { std::cout<<"";}

    const std::string &getName() const {
        return name;
    }

    const std::string &getCity() const {
        return city;
    }

    int getRating() const {
        return rating;
    }

    void setRating(int rating_) {
        Team::rating = rating_;
    }
};

class Player{
    std::string firstName, lastName;
    int age;
    std::string position;
    int overallRating;
    int pace, shooting, passing, dribbling, defending, physical;
    Team team;
    int goals, assists;
public:
    Player(std::string firstName_, std::string lastName_, std::string position_, const Team& team_) : firstName(firstName_),
                                                                                   lastName(lastName_),
                                                                                   age(18),
                                                                                   position(position_),
                                                                                   overallRating(10),
                                                                                   pace(10),
                                                                                   shooting(10),
                                                                                   passing(10),
                                                                                   dribbling(10),
                                                                                   defending(10),
                                                                                   physical(10),
                                                                                   team(team_),
                                                                                   goals(0),
                                                                                   assists(0)
    {std::cout<<"Player has been created"<<std::endl;}

    Player(const Player& other): firstName(other.firstName),
                                 lastName(other.lastName),
                                 age(other.age),
                                 position(other.position),
                                 overallRating(other.overallRating),
                                 pace(other.pace),
                                 shooting(other.shooting),
                                 passing(other.passing),
                                 dribbling(other.dribbling),
                                 defending(other.defending),
                                 physical(other.physical),
                                 team(other.team),
                                 goals(other.goals),
                                 assists(other.assists){
        std::cout<<"Your player has bees copied!"<<std::endl;
    }
    ~Player() { std::cout<<"The player has retired!"<<std::endl;}

    std::string getPosition() const {
        return position;
    }

    int getPace() const {
        return pace;
    }

    int getShooting() const {
        return shooting;
    }

    int getPassing() const {
        return passing;
    }

    int getDribbling() const {
        return dribbling;
    }

    int getDefending() const {
        return defending;
    }

    int getPhysical() const {
        return physical;
    }

    int getOverallRating() const{
        return overallRating;
    }

    int getGoals() const{
        return goals;
    }

    int getAssists() const{
        return assists;
    }

    void setGoals(int goals_){
        Player::goals = goals_;
    }

    void setAssists(int assists_){
        Player::assists = assists_;
    }

    void setTeam(const Team &team_){
        Player::team = team_;
    }

    void setPace(int pace);

    void setShooting(int shooting);

    void setPassing(int passing);

    void setDribbling(int dribbling);

    void setDefending(int defending);

    void setPhysical(int physical);


    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Name: " << player.firstName << " " << player.lastName << std::endl;
    os << "Age: " << player.age << std::endl;
    os << "Position: " << player.position << std::endl;
    os << "Team: " << player.team.getName() + " " + player.team.getCity() << std::endl;
    os << "Overall Rating: " << player.overallRating << std::endl;
    os << "Attributes:" << std::endl;
    os << std::setw(12) << std::left << "Pace:" << player.pace << std::endl;
    os << std::setw(12) << std::left << "Shooting:" << player.shooting << std::endl;
    os << std::setw(12) << std::left << "Passing:" << player.passing << std::endl;
    os << std::setw(12) << std::left << "Dribbling:" << player.dribbling << std::endl;
    os << std::setw(12) << std::left << "Defending:" << player.defending << std::endl;
    os << std::setw(12) << std::left << "Physical:" << player.physical << std::endl;
    os << std::setw(12) << std::left << "Goals:" << player.goals << std::endl;
    os << std::setw(12) << std::left << "Assists:" << player.assists << std::endl;
    return os;
}

void Player::setPace(int pace_) {
    Player::pace = pace_;
}

void Player::setShooting(int shooting_) {
    Player::shooting = shooting_;
}

void Player::setPassing(int passing_) {
    Player::passing = passing_;
}

void Player::setDribbling(int dribbling_) {
    Player::dribbling = dribbling_;
}

void Player::setDefending(int defending_) {
    Player::defending = defending_;
}

void Player::setPhysical(int physical_) {
    Player::physical = physical_;
}


class Championship{
    std::vector<Team> teams;
    std::string country;
public:
    Championship(const std::vector<Team> &teams_,const std::string& country_) : teams(teams_),
                                                                                                  country(country_){}
    ~Championship() { std::cout<<""; }

    const std::vector<Team> &getTeams() const {
        return teams;
    }

    void setTeams(const std::vector<Team> &teams_) {
        Championship::teams = teams_;
    }

    static bool compareTeamsByRating(const Team& team1, const Team& team2) {
        return team1.getRating() > team2.getRating(); // Sortare descrescătoare
    }



    virtual std::vector<int> generateForm() = 0;

    virtual void calculateStandings() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Championship& championship);
};

std::ostream& operator<<(std::ostream& os, const Championship& championship) {
    std::vector<Team> sortedTeams = championship.getTeams();
    std::sort(sortedTeams.begin(), sortedTeams.end(), [](const Team& a, const Team& b) {
        return a.getRating() > b.getRating(); // Sortăm echipele descrescător după rating
    });

    // Afișăm clasamentul
    os << "Championship Standings:" << std::endl;
    for (size_t i = 0; i < sortedTeams.size(); ++i) {
        os << i + 1 << ". " << sortedTeams[i].getName() << " " << sortedTeams[i].getCity() << " - " << sortedTeams[i].getRating() << " points" << std::endl;
    }

    return os;
}

class Superliga : public Championship{
public:
    explicit Superliga(const std::vector<Team> &teams) : Championship(teams, "Romania") {}
    ~Superliga() {std::cout<<"";}

    std::vector<int> generateForm() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(-10, 10);

        std::vector<int> randomNumbers;
        randomNumbers.reserve(getTeams().size());

        for (int i = 0; i < (int) getTeams().size(); ++i) {
            randomNumbers.push_back(dis(gen));
        }

        return randomNumbers;
    }

    void calculateStandings() override{
        std::vector<int> form = generateForm();
        std::vector<Team> chTeams = getTeams();
        for(int i = 0; i < (int) form.size(); i++){
            chTeams[i].setRating(chTeams[i].getRating() + form[i]);
        }
        std::sort(chTeams.begin(), chTeams.end(), compareTeamsByRating);

        setTeams(chTeams);
    }


};

class PlayOffSuperliga : public Superliga{
public:
    explicit PlayOffSuperliga(const std::vector<Team>& teams) : Superliga(teams) {}
    ~PlayOffSuperliga() { std::cout << ""; }
};

class PlayOutSuperliga : public Superliga {
public:
    explicit PlayOutSuperliga(const std::vector<Team>& teams) : Superliga(teams) {}
    ~PlayOutSuperliga() { std::cout << ""; }

};

class Liga2: public Championship{
public:
    explicit Liga2(const std::vector<Team> &teams)
            : Championship(teams, "Romania") {}
    ~Liga2() {std::cout<<"";}

    std::vector<int> generateForm() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(-7, 7);

        std::vector<int> randomNumbers;
        randomNumbers.reserve(getTeams().size());

        for (int i = 0; i < (int) getTeams().size(); ++i) {
            randomNumbers.push_back(dis(gen));
        }

        return randomNumbers;
    }

    void calculateStandings() override{
        std::vector<int> form = generateForm();
        std::vector<Team> chTeams = getTeams();
        for(int i = 0; i < (int) form.size(); i++){
            chTeams[i].setRating(chTeams[i].getRating() + form[i]);
        }
        std::sort(chTeams.begin(), chTeams.end(), compareTeamsByRating);

        setTeams(chTeams);
    }

    static void promotion(Superliga& superliga, Liga2& liga2) {

        std::vector<Team> superligaTeams = superliga.getTeams();

        std::vector<Team> liga2Teams = liga2.getTeams();

        std::sort(superligaTeams.begin(), superligaTeams.end(), [](const Team& a, const Team& b) {
            return a.getRating() > b.getRating();
        });

        std::sort(liga2Teams.begin(), liga2Teams.end(), [](const Team& a, const Team& b) {
            return a.getRating() > b.getRating();
        });

        // Extragem ultimele trei echipe din Superliga și le adăugăm în Liga2
        for (int i = 0; i < 3; i++) {
            superligaTeams.back().setRating(superligaTeams.back().getRating()-5);
            liga2Teams.push_back(superligaTeams.back());
            superligaTeams.pop_back();
        }

        // Extragem primele trei echipe din Liga2 și le adăugăm în Superliga
        for (int i = 0; i < 3; i++) {
            liga2Teams.front().setRating(liga2Teams.front().getRating()+5);
            superligaTeams.push_back(liga2Teams.front());
            liga2Teams.erase(liga2Teams.begin()); // Ștergem echipele promovate din Liga2
        }

        superliga.setTeams(superligaTeams);
        liga2.setTeams(liga2Teams);
    }


};

class PlayOffLiga2 : public Liga2{
public:
    explicit PlayOffLiga2(const std::vector<Team>& teams) : Liga2(teams) {}
    ~PlayOffLiga2() { std::cout << ""; }
};

class PlayOut1Liga2 : public Liga2{
public:
    explicit PlayOut1Liga2(const std::vector<Team>& teams) : Liga2(teams) {}
    ~PlayOut1Liga2() { std::cout << ""; }
};

class PlayOut2Liga2 : public Liga2{
public:
    explicit PlayOut2Liga2(const std::vector<Team>& teams) : Liga2(teams) {}
    ~PlayOut2Liga2() { std::cout << ""; }
};

class Card{
    int value;
    std::string suit;
public:
    Card(int value_, const std::string &suit_) : value(value_), suit(suit_) {}

    int getValue() const {
        return value;
    }

    std::string changeValue() const {
        if(value == 11){
            return ("A");
        }
        if(value == 12){
            return ("J");
        }
        if(value == 13){
            return ("Q");
        }
        if(value == 14){
            return ("K");
        }
        return std::to_string(value);
    }

    std::tuple<int,int> events(Player& player, int weight){
        int goals, assists = 0;
        if(value == 9){
            std::cout<<"Your player scored "<<weight*5<<" goal(s)!"<<std::endl;
            player.setGoals(player.getGoals() + weight*5);
            player.setShooting(player.getShooting() + weight*2);
            goals += weight*5;
        }
        if(value == 10){
            std::cout<<"Your player assisted "<<weight*5<<" goal(s)!"<<std::endl;
            player.setAssists(player.getAssists() + weight*5);
            player.setPassing(player.getPassing() + weight*2);
            assists += weight*5;
        }
        if(value == 11){
            std::cout<<"Your player made "<<weight*5<<" runs in the final third, which resulted in him getting an extra " << weight <<" assist(s)!"<<std::endl;
            player.setAssists(player.getAssists() + weight);
            player.setPace(player.getPace() + weight*2);
            assists += weight;
        }
        if(value == 12){
            std::cout<<"Your player made "<<weight*5<<" successful dribbles, which resulted in him scoring an extra " << weight << " goal(s)!"<<std::endl;
            player.setGoals(player.getGoals() + weight);
            player.setDribbling(player.getDribbling() + weight*2);
            goals += weight;
        }
        if(value == 13){
            std::cout<<"Your player made "<<weight*5<<" successful tackles!"<<std::endl;
            player.setDefending(player.getDefending() + weight*2);
        }
        if(value == 14){
            std::cout<<"Your player won "<<weight*5<<" duels!"<<std::endl;
            player.setPhysical(player.getPhysical() + weight*2);
        }
        if(value == 8){
            std::cout<<"Your player missed "<<weight<<" games due to suspensions! This will surely affect his stats!"<<std::endl;
            player.setShooting(player.getShooting() - weight/2);
            player.setPassing(player.getPassing() - weight/2);
            player.setPace(player.getPace() - weight/2);
            player.setDribbling(player.getDribbling() - weight/2);
            player.setDefending(player.getDefending() - weight/2);
            player.setPhysical(player.getPhysical() - weight/2);
        }
        if(value == 7){
            std::cout<<"Your player missed "<<weight*3<<" games due to injury! This will surely affect his stats!"<<std::endl;
            player.setShooting(player.getShooting() - weight);
            player.setPassing(player.getPassing() - weight);
            player.setPace(player.getPace() - weight);
            player.setDribbling(player.getDribbling() - weight);
            player.setDefending(player.getDefending() - weight);
            player.setPhysical(player.getPhysical() - weight);
        }
        return std::make_tuple(goals, assists);
    }


    virtual void printAsciiArt() const = 0;


};



class Spades : public Card{
public:
    explicit Spades(const int value) : Card(value, "spades") {}
    ~Spades() = default;

    void printAsciiArt() const override {
        if(getValue() == 10){
            std::cout<<" ____ \n|" + changeValue() + "  |\n| /\\ |\n|(__)|\n| /" + changeValue() + "|\n";
        } else{
            std::cout<<" ____ \n|" + changeValue() + "   |\n| /\\ |\n|(__)|\n| /\\" + changeValue() + "|\n";
        }
    }


};

class Hearts : public Card{
public:
    explicit Hearts(const int value) : Card(value, "hearts") {}
    ~Hearts() = default;

    void printAsciiArt() const override {
        if(getValue() == 10){
            std::cout<<" ____ \n|" + changeValue() + "  |\n|(\\/)|\n| \\/ |\n|  " + changeValue() + "|\n";
        } else{
            std::cout<<" ____ \n|" + changeValue() + "   |\n|(\\/)|\n| \\/ |\n|   " + changeValue() + "|\n";
        }
    }
};

class Diamonds : public Card{
public:
    explicit Diamonds(const int value) : Card(value, "diamonds") {}
    ~Diamonds() = default;

    void printAsciiArt() const override {
        if(getValue() == 10){
            std::cout<<" ____ \n|"+ changeValue()+"  |\n| /\\ |\n| \\/ |\n|  "   + changeValue() + "|\n";
        } else{
            std::cout<<" ____ \n|"+ changeValue()+"   |\n| /\\ |\n| \\/ |\n|   "   + changeValue() + "|\n";
        }
    }
};
class Clubs : public Card{
public:
    explicit Clubs(const int value) : Card(value, "clubs") {}
    ~Clubs() = default;

    void printAsciiArt() const override {
        if(getValue() == 10){
            std::cout<<" ____ \n|" + changeValue() + "  |\n| &  |\n|&|& |\n|  " + changeValue() + "|\n";
        } else{
            std::cout<<" ____ \n|" + changeValue() + "   |\n| &  |\n|&|& |\n|   " + changeValue() + "|\n";
        }
    }
};

class CardGame{
public:


    static std::vector<std::shared_ptr<Card>> initializeDeck() {
        std::vector<std::shared_ptr<Card>> deck;
        for (int i = 7; i <= 14; i++) {
            deck.push_back(std::make_shared<Clubs>(i));
            deck.push_back(std::make_shared<Hearts>(i));
            deck.push_back(std::make_shared<Spades>(i));
            deck.push_back(std::make_shared<Diamonds>(i));
        }
        return deck;
    }


    static void shuffleDeck(std::vector<std::shared_ptr<Card>>& deck) {
        std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device()()));
    }

//    static void printCard(const std::shared_ptr<Card>& card) {
//        card->printAsciiArt();
//    }



    static std::vector<std::shared_ptr<Card>> extractCards(){
        std::vector<std::shared_ptr<Card>> playerDeck;
        std::vector<std::shared_ptr<Card>> deck = initializeDeck();
        shuffleDeck(deck);
        int choice;
        for(int i = 0; i < 5; i++){
            std::cout<<"Choose a card from the deck! (Number from 0 to 31)"<<std::endl;
            std::cin>>choice;
            while(choice < 0 || choice >(int) deck.size()){
                std::cerr<<"Invalid choice!"<<std::endl;
                std::cin>>choice;
            }
            playerDeck.push_back(deck[choice]);
            deck[choice]->printAsciiArt();
            shuffleDeck(deck);
        }
        return playerDeck;
    }

    static void training(Player& player, std::vector<std::shared_ptr<Card>>& playerDeck){
        for(const auto& card : playerDeck) {
            if(auto clubsCard = dynamic_cast<Clubs*>(card.get())) {

                clubsCard->events(player,1);

            } else if(auto spadesCard = dynamic_cast<Spades*>(card.get())) {

                spadesCard->events(player,2);

            } else if(auto diamondsCard = dynamic_cast<Diamonds*>(card.get())) {

                diamondsCard->events(player,3);

            } else if(auto heartsCard = dynamic_cast<Hearts*>(card.get())) {

                heartsCard->events(player,4);

            }
        }
    }

};


class Game{

public:

    static std::vector<Team> generateRandomTeams( std::vector<Team> teams, int indexStart, int indexEnd) {
        // Crează un motor de generare a numerelor aleatoare
        std::random_device rd;
        std::mt19937 gen(rd());

        // Definește distribuția uniformă pentru indexul echipei
        std::uniform_int_distribution<> dis(indexStart, indexEnd);

        // Generează trei indici aleatori
        int index1 = dis(gen);
        int index2 = dis(gen);
        int index3 = dis(gen);

        // Creează vectorul cu cele trei echipe aleatoare
        std::vector<Team> randomTeams;
        randomTeams.push_back(teams[index1]);
        randomTeams.push_back(teams[index2]);
        randomTeams.push_back(teams[index3]);

        return randomTeams;
    }

    static Player inputPlayer(const std::vector<Team>& randomTeams) {
        std::string fName, lName, pos;
        std::cout << "What is your player first name?" << std::endl;
        std::cin >> fName;
        std::cout << "What is your player last name?" << std::endl;
        std::cin >> lName;

        std::set<std::string> validPositions = {"RB", "LB", "CB", "CDM", "CM", "CAM", "RW", "LW", "ST"};

        bool validPosition = false;
        do {
            std::cout << "What is your player position?" << std::endl;
            std::cout << "You can choose from these positions:" << std::endl;
            std::cout << "RB, LB, CB, CDM, CM, CAM, RW, LW, ST" << std::endl;
            std::cin >> pos;

            std::transform(pos.begin(), pos.end(), pos.begin(), ::toupper);

            if (validPositions.find(pos) != validPositions.end()) {
                validPosition = true;
            } else {
                std::cerr << "Invalid position! Please choose from the provided options." << std::endl;
            }
        } while (!validPosition);

        int teamChoice;
        do {

            std::cout << "Choose one of the following teams:" << std::endl;
            for (size_t i = 0; i < randomTeams.size(); ++i) {
                std::cout << i + 1 << ". " << randomTeams[i].getName() << " " << randomTeams[i].getCity() << " (" << randomTeams[i].getRating() << ")" << std::endl;
            }


            std::cout << "Enter your choice (1-3): ";
            std::cin >> teamChoice;

            if (teamChoice < 1 || teamChoice > 3) {
                std::cerr << "Invalid choice! Please choose again." << std::endl;
            }
        } while (teamChoice < 1 || teamChoice > 3);


        Player player(fName, lName, pos, randomTeams[teamChoice - 1]);
        return player;
    }

    static int overallRatingCalculator(Player& player){
        if(player.getPosition() == "RB" || player.getPosition() == "LB"){
            return ceil(0.3 * player.getPace() + 0.3 * player.getDefending() + 0.2 * player.getPhysical() + 0.1 * player.getPassing() + 0.1 * player.getDribbling());
        }
        if(player.getPosition() == "CB"){
            return ceil(0.5 * player.getDefending() + 0.4 * player.getPhysical() + 0.1 * player.getPassing());
        }
        if(player.getPosition() == "CDM"){
            return ceil(0.4 * player.getDefending() + 0.4 *player.getPassing() + 0.2 * player.getPhysical());
        }
        if(player.getPosition() == "CM"){
            return ceil(0.4 * player.getPassing() + 0.1 * player.getPace() + 0.1*player.getPhysical() + 0.1 * player.getDefending() +
                        0.2 * player.getDribbling() + 0.1 * player.getShooting());
        }
        if(player.getPosition() == "CAM"){
            return ceil(0.5 * player.getDribbling() + 0.3 * player.getPassing() + 0.2 * player.getShooting());
        }
        if(player.getPosition() == "ST"){
            return ceil(0.7 * player.getShooting() + 0.1 * player.getPhysical() + 0.1 * player.getPace() + 0.1 * player.getDribbling());
        }
        if(player.getPosition() == "RW" || player.getPosition() == "LW"){
            return ceil(0.5 * player.getPace() + 0.3 * player.getDribbling() + 0.1 * player.getPassing() + 0.1 * player.getShooting());
        }
    }

    static std::tuple<PlayOffSuperliga, PlayOutSuperliga> superligaStandingCalculator(Superliga& superliga){
        superliga.calculateStandings();
        std::vector<Team> playOff;
        for(int i = 0; i < 6; i++){
            playOff.push_back(superliga.getTeams()[i]);
        }
        std::vector<Team> playOut;
        for(int i = 6; i < 16; i++){
            playOut.push_back(superliga.getTeams()[i]);
        }
        PlayOffSuperliga ploff(playOff);
        PlayOutSuperliga plout(playOut);

        return std::make_tuple(ploff,plout);
    }

    static std::tuple<PlayOffLiga2, PlayOut1Liga2, PlayOut2Liga2> liga2StandingCalculator(Liga2& liga2){
        liga2.calculateStandings();
        std::vector<Team> playOff;
        for(int i = 0; i < 6; i++){
            playOff.push_back(liga2.getTeams()[i]);
        }

        std::vector<Team> playOut1;
        std::vector<Team> playOut2;
        for(int i = 6; i < 20; i++){
            if(i % 2 == 0){
                playOut1.push_back(liga2.getTeams()[i]);
            } else{
                playOut2.push_back(liga2.getTeams()[i]);
            }
        }
        PlayOffLiga2 pl2off(playOff);
        PlayOut1Liga2 pl2out1(playOut1);
        PlayOut2Liga2 pl2out2(playOut2);

        return std::make_tuple(pl2off,pl2out1,pl2out2);
    }

    static bool printStandings(PlayOffSuperliga& ploff,PlayOutSuperliga& plout,
                               PlayOffLiga2& pl2off, PlayOut1Liga2& pl2out1, PlayOut2Liga2& pl2out2){
        std::string choice;
        std::cout<<std::endl;
        std::cout<<"Press 1 to display the Superliga PlayOff Table"<<std::endl;
        std::cout<<"Press 2 to display the Superliga PlayOut Table"<<std::endl;
        std::cout<<"Press 3 to display the Liga2 PlayOff Table"<<std::endl;
        std::cout<<"Press 4 to display the Liga2 PlayOut Table Series 1"<<std::endl;
        std::cout<<"Press 5 to display the Liga2 PlayOut Table Series 2"<<std::endl;
        std::cout << "Press 0 to stop" << std::endl;

        std::cin>>choice;
        if(choice == "1"){
            std::cout<<"Superliga PlayOff Table 2023/24"<<std::endl;
            std::cout<<ploff<<std::endl;
        }
        else if(choice == "2"){
            std::cout<<"Superliga PlayOut Table 2023/24"<<std::endl;
            std::cout<<plout<<std::endl;
        }
        else if(choice == "3"){
            std::cout<<"Liga2 PlayOff Table 2023/24"<<std::endl;
            std::cout<<pl2off<<std::endl;
        }
        else if(choice == "4"){
            std::cout<<"Liga2 PlayOut Table Series 1 2023/24"<<std::endl;
            std::cout<<pl2out1<<std::endl;
        }
        else if(choice == "5"){
            std::cout<<"Liga2 PlayOut Table Series 2 2023/24"<<std::endl;
            std::cout<<pl2out2<<std::endl;
        }else if (choice == "0") {
            return false; // Oprirea afisarii
        } else {
            std::cerr << "Invalid choice! Please choose a valid option." << std::endl;
        }
        return true;

    }

    static void transferOffer(Superliga& superliga, Liga2& liga2, Player& player){
        std::vector<Team> teams = {};
        teams.insert(teams.end(), superliga.getTeams().begin(), superliga.getTeams().end());
        teams.insert(teams.end(),liga2.getTeams().begin(),liga2.getTeams().end());

        int startIndex;
        for(int i = 0; i < (int) teams.size(); i++){
            if(teams[i].getRating() <= player.getOverallRating()){
                startIndex = i;
                break;
            }
        }

        std::vector<Team> randomTeams = generateRandomTeams(teams,startIndex, startIndex+4);

        std::cout<<std::endl;
        std::cout << "Choose one of the following teams to transfer to:" << std::endl;
        for (size_t i = 0; i < randomTeams.size(); ++i) {
            std::cout << i + 1 << ". " << randomTeams[i].getName() << " " << randomTeams[i].getCity() << " (" << randomTeams[i].getRating() << ")" << std::endl;
        }

        int choice;
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        if (choice >= 1 && choice <= 3) {
            Team chosenTeam = randomTeams[choice - 1];
            std::cout << "You have chosen to transfer to: " << chosenTeam.getName() << " " << chosenTeam.getCity() << std::endl;

            player.setTeam(chosenTeam);
        } else {
            std::cerr << "Invalid choice! Transfer canceled." << std::endl;
        }
    }

    static void simSeason(Superliga& superliga, Liga2& liga2){
        superliga.calculateStandings();
        liga2.calculateStandings();
        auto [ploff, plout] = Game::superligaStandingCalculator(superliga);
        auto [pl2off, pl2out1, pl2out2] = Game::liga2StandingCalculator(liga2);
        bool continueDisplay = true;
        while (continueDisplay) {
            continueDisplay = Game::printStandings(ploff, plout, pl2off, pl2out1, pl2out2);
        }
    }

//    static void simulateSeasons(Superliga& superliga, Liga2& liga2){
//        for(int i = 0; i< 15; i++){
//
//        }
//    }



};

int main(){

    std::vector<Team> teams1 = {Team("FCSB","Bucharest",80),
                                Team("Universitatea","Craiova",80),
                                Team("CFR","Cluj",80),
                                Team("Farul","Constanta",80),
                                Team("Sepsi","Sf-Gheorghe",70),
                                Team("Rapid","Bucharest",70),
                                Team("UTA","Arad",70),
                                Team("Otelul","Galati",70),
                                Team("Hermannstadt","Sibiu",50),
                                Team("U","Cluj",50),
                                Team("Petrolul","Ploiesti",50),
                                Team("FC","Botosani",50),
                                Team("FC","Voluntari",40),
                                Team("Poli","Iasi",40),
                                Team("Dinamo","Bucharest",40),
                                Team("FCU","Craiova",40),
                                };
    Superliga superliga(teams1);

    std::vector<Team> teams2 = {Team("Unirea","Slobozia",30),
                                Team("Corvinul","Hunedoara",30),
                                Team("CSC","Selimbar",30),
                                Team("Gloria","Buzau",30),
                                Team("CS","Mioveni",30),
                                Team("Csikszereda","Miercurea-Ciuc",30),
                                Team("CSM","Resita",20),
                                Team("Ceahlaul","Piatra-Neamt",20),
                                Team("FC Arges","Pitesti",20),
                                Team("Metaloglobus","Bucharest",10),
                                Team("CSC","Dumbravita",10),
                                Team("Unirea","Dej",10),
                                Team("FCM","Alexandria",10),
                                Team("CSA Steaua","Bucharest",20),
                                Team("Concordia","Chiajna",20),
                                Team("Chindia","Targoviste",20),
                                Team("CSM","Slatina",10),
                                Team("Viitorul","Targu-Jiu",10),
                                Team("CS","Tunari",10),
                                Team("Progresul","Spartac",10),
                                };

    Liga2 liga2(teams2);

    Player player = Game::inputPlayer(Game::generateRandomTeams(teams2,7,20));
    // se aleg 3 echile dintre cele mai slabe, iar jucatorul selecteaza una din ele
    std::cout<< player;


    Game::simSeason(superliga, liga2);


    std::cout<<Game::overallRatingCalculator(player);

    std::vector<std::shared_ptr<Card>> playerDeck = CardGame::extractCards();
    CardGame::training(player,playerDeck);

    Game::transferOffer(superliga, liga2, player);

    std::cout<<std::endl;
    std::cout<<player;
    std::cout<<std::endl;



    Liga2::promotion(superliga, liga2);
    Game::simSeason(superliga, liga2);

    return 0;
}

