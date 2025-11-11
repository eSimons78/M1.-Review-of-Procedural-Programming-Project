#include <iostream>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

enum class RoundResult { ComputerWin, HumanWin, Draw };

string to_lower_copy(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c); });
    return s;
}

string prompt_player_choice() {
    while (true) {
        cout << "\nChoose one: rock, paper, scissors, or quit: ";
        string choice;
        if (!(cin >> choice)) {
            // input stream error; clear and continue
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        choice = to_lower_copy(choice);
        if (choice == "rock" || choice == "paper" || choice == "scissors" || choice == "quit") {
            return choice;
        }
        cout << "Invalid input. Please type exactly: rock, paper, scissors, or quit.\n";
    }
}

string int_to_choice(int n) {
    if (n == 1) return "rock";
    if (n == 2) return "paper";
    return "scissors"; // n == 3
}

int generate_computer_choice_1_to_3() {
    //  use random_device with a uniform_int_distribution
    static random_device rd;
    uniform_int_distribution<int> dist(1, 3);
    return dist(rd);
}

RoundResult decide_winner(const string& comp, const string& human) {
    if (comp == human) return RoundResult::Draw;

    // Rules:
    // rock beats scissors, scissors beats paper, paper beats rock
    if ((comp == "rock"     && human == "scissors") ||
        (comp == "scissors" && human == "paper")    ||
        (comp == "paper"    && human == "rock")) {
        return RoundResult::ComputerWin;
    } else {
        return RoundResult::HumanWin;
    }
}

void update_scores(RoundResult result, int& compScore, int& humanScore) {
    if (result == RoundResult::ComputerWin) ++compScore;
    else if (result == RoundResult::HumanWin) ++humanScore;
    // Draw: no score change
}

void print_round_summary(const string& comp, const string& human,
                         RoundResult result, int compScore, int humanScore) {
    cout << "You chose: " << human << " | Computer chose: " << comp << "\n";
    if (result == RoundResult::ComputerWin) cout << "→ Computer wins the round.\n";
    else if (result == RoundResult::HumanWin) cout << "→ You win the round!\n";
    else cout << "→ The round is a draw.\n";
    cout << "Score — You: " << humanScore << "  Computer: " << compScore << "\n";
}

void declare_tournament_winner(int compScore, int humanScore) {
    cout << "\n========== FINAL RESULTS ==========\n";
    cout << "Final Score — You: " << humanScore << "  Computer: " << compScore << "\n";
    if (humanScore > compScore)      cout << "Tournament winner: YOU \n";
    else if (compScore > humanScore) cout << "Tournament winner: COMPUTER \n";
    else                             cout << "Tournament result: DRAW \n";
}

int main() {
    cout << "Rock, Paper, Scissors — Tournament Mode\n";
    cout << "(Type exactly: rock, paper, scissors, or quit)\n";

    int compScore = 0, humanScore = 0;

    while (true) {
        // Per instructions: generate the computer's choice first (do not display yet)
        int n = generate_computer_choice_1_to_3();
        string comp = int_to_choice(n);

        string human = prompt_player_choice();
        if (human == "quit") break;

        cout << "Computer reveals...\n";
        RoundResult result = decide_winner(comp, human);
        update_scores(result, compScore, humanScore);
        print_round_summary(comp, human, result, compScore, humanScore);
    }

    declare_tournament_winner(compScore, humanScore);
    cout << "Thanks for playing!\n";
    return 0;
}
