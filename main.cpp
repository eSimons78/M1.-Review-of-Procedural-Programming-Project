
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// ----- Global constants -----
const int NUM_TESTS = 5;       // Change this if your file has a different # of tests
const int MAX_STUDENTS = 200;  // Capacity for partially filled arrays

// ----- Function prototypes -----
int  readData(ifstream& in, string names[], int scores[][NUM_TESTS], int maxStudents);
void calcAverages(const int scores[][NUM_TESTS], int studentCount, double averages[]);
char letterFromAverage(double avg);
void printReport(const string names[], const double averages[], int studentCount);

int main(int argc, char* argv[]) {
    // 1) Open input file (use argument if provided, else default)
    string filename = (argc > 1) ? string(argv[1]) : string("StudentGrades.txt");
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: Could not open input file: " << filename << "\n";
        cerr << "Make sure the file exists and the path is correct." << endl;
        return 1;
    }

    // 2) Declare parallel arrays (partially filled)
    string names[MAX_STUDENTS];
    int    scores[MAX_STUDENTS][NUM_TESTS] = {0};
    double averages[MAX_STUDENTS] = {0.0};

    // 3) Read data
    int studentCount = readData(fin, names, scores, MAX_STUDENTS);
    fin.close();

    if (studentCount == 0) {
        cerr << "No valid student records were read. Exiting." << endl;
        return 0;
    }

    // 4) Compute averages
    calcAverages(scores, studentCount, averages);

    // 5) Produce formatted report
    printReport(names, averages, studentCount);

    return 0;
}

// Reads lines: <name> <score1> <score2> ... <scoreNUM_TESTS>
// Fills parallel arrays and returns number of students read.
int readData(ifstream& in, string names[], int scores[][NUM_TESTS], int maxStudents) {
    int count = 0;
    while (count < maxStudents && (in >> names[count])) {
        bool ok = true;
        for (int j = 0; j < NUM_TESTS; ++j) {
            if (!(in >> scores[count][j])) {
                ok = false; // incomplete line; stop reading this record
                break;
            }
        }
        if (!ok) {
            // If the line was incomplete, discard the partial record and stop.
            break;
        }
        ++count;
    }
    return count;
}

// Compute per-student averages from the scores matrix
void calcAverages(const int scores[][NUM_TESTS], int studentCount, double averages[]) {
    for (int i = 0; i < studentCount; ++i) {
        int sum = 0;
        for (int j = 0; j < NUM_TESTS; ++j) {
            sum += scores[i][j];
        }
        averages[i] = static_cast<double>(sum) / NUM_TESTS;
    }
}

// Map numeric average to letter grade per assignment scale
char letterFromAverage(double avg) {
    if (avg >= 90.0) return 'A';
    if (avg >= 80.0) return 'B';
    if (avg >= 70.0) return 'C';
    if (avg >= 60.0) return 'D';
    return 'F';
}

// Print aligned report: Name, Average, Letter Grade
void printReport(const string names[], const double averages[], int studentCount) {
    const int NAME_W = 12;
    const int AVG_W  = 8;

    cout << left << setw(NAME_W) << "Student" << right << setw(AVG_W) << "Average" << "  Grade\n";
    cout << string(NAME_W + AVG_W + 8, '-') << "\n";

    cout << fixed << setprecision(1);
    for (int i = 0; i < studentCount; ++i) {
        char g = letterFromAverage(averages[i]);
        cout << left << setw(NAME_W) << names[i]
             << right << setw(AVG_W) << averages[i]
             << "  " << g << '\n';
    }
}
