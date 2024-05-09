#include<iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <algorithm>
#include <tuple>


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
public:
    Player(std::string firstName_, std::string lastName_, std::string position_, const Team& team_) : firstName(firstName_),
                                                                                   lastName(lastName_),
                                                                                   age(18),
                                                                                   position(position_),
                                                                                   overallRating(2),
                                                                                   pace(1),
                                                                                   shooting(1),
                                                                                   passing(1),
                                                                                   dribbling(1),
                                                                                   defending(1),
                                                                                   physical(1),
                                                                                   team(team_)
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
                                 team(other.team){
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
    return os;
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
        std::uniform_int_distribution<> dis(-5, 5);

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
        std::cout << "What is your player position?" << std::endl;
        std::cout << "You can choose from these positions:" << std::endl;
        std::cout << "RB, LB, CB, CDM, CM, CAM, RW, LW, ST" << std::endl;
        std::cin >> pos;

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

    std::cout<<std::endl;
    std::cout<<"sezonul 1"<<std::endl;

    auto [ploff, plout] = Game::superligaStandingCalculator(superliga);
    std::cout<<"Liga1"<<std::endl;

    std::cout<<std::endl;
    std::cout<<ploff<<std::endl<<std::endl;
    std::cout<<plout<<std::endl<<std::endl;

    auto [pl2off, pl2out1, pl2out2] = Game::liga2StandingCalculator(liga2);
    std::cout<<"Liga2"<<std::endl;

    std::cout<<pl2off<<std::endl<<std::endl;
    std::cout<<pl2out1<<std::endl<<std::endl;
    std::cout<<pl2out2<<std::endl<<std::endl;

    Liga2::promotion(superliga, liga2);

    std::cout<<"sezonul 2"<<std::endl;

    auto [ploffx, ploutx] = Game::superligaStandingCalculator(superliga);
    std::cout<<"Liga1"<<std::endl;

    std::cout<<std::endl;
    std::cout<<ploffx<<std::endl<<std::endl;
    std::cout<<ploutx<<std::endl<<std::endl;

    auto [pl2offx, pl2out1x, pl2out2x] = Game::liga2StandingCalculator(liga2);
    std::cout<<"Liga2"<<std::endl;

    std::cout<<pl2offx<<std::endl<<std::endl;
    std::cout<<pl2out1x<<std::endl<<std::endl;
    std::cout<<pl2out2x<<std::endl<<std::endl;


    std::cout<<Game::overallRatingCalculator(player);

    return 0;
}

