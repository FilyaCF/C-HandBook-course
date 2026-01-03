#include <iostream>
#include <memory>
#include <map>
#include <vector>

struct ParticipantResults {
    std::string login;
    std::string team;
    std::map<std::string, int> scores;  // номер задачи -> баллы

    // ...

    ParticipantResults(const std::string& l, const std::string& te): login(l), team(te) {
    }

    ParticipantResults(const ParticipantResults&) = delete;
    ParticipantResults& operator = (const ParticipantResults&) = delete;
};

class Monitor {
private:
    std::map<std::string, std::shared_ptr<ParticipantResults>> participitants;
    std::map<std::string, std::vector<std::shared_ptr<ParticipantResults>>> teams;
    std::vector<std::shared_ptr<ParticipantResults>> allResults;
public:
    Monitor() = default;
    Monitor(const Monitor& other) = delete;
    void operator =(const Monitor& other) = delete;

    std::shared_ptr<ParticipantResults> RegisterParticipant(const std::string& login, const std::string& team) {
        if (participitants.count(login)) {
            throw std::invalid_argument("Participant is already registered");
        }
        allResults.push_back(std::make_shared<ParticipantResults>(login, team));
        participitants.insert(std::make_pair(login, allResults.back()));
        teams[team].push_back(allResults.back());
        return allResults.back();
    }

    std::shared_ptr<ParticipantResults> GetParticipantResults(const std::string& login) {
        return participitants.at(login);
    }

    const std::shared_ptr<ParticipantResults> GetParticipantResults(const std::string& login) const {
        return participitants.at(login);
    }

    std::vector<std::shared_ptr<ParticipantResults>> GetTeamResults(const std::string& team) const {
        return teams.at(team);
    }

    std::vector<std::shared_ptr<ParticipantResults>> GetAllResults() const {
        return allResults;
    }

    ~Monitor() = default;
};

int main() {
    Monitor monitor;

    {
        auto ptr = monitor.RegisterParticipant("Ivanov Ivan", "201-1");
        ptr->scores["A"] = 10;
        ptr->scores["B"] = 8;
    }

    {
        auto ptr = monitor.RegisterParticipant("Petrov Petr", "201-2");
        ptr->scores["A"] = 5;
        ptr->scores["C"] = 10;
    }

    auto ptr = monitor.GetParticipantResults("Ivanov Ivan");
    ptr->scores["Q"] = 100;

    // тут может быть аналогичный вызов monitor.GetTeamResults(team)
    for (const auto& result : monitor.GetAllResults()) {
        std::cout << result->login << "\t" << result->team << "\t";
        for (const auto& [problemId, score] : result->scores) {
            std::cout << problemId << ": " << score << "\t";
        }
        std::cout << "\n";
    }
}