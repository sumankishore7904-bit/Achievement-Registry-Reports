#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct Achievement {
    string student;
    string batch;
    string category;
    int year;
    string title;
};

const int MAX_RECORDS = 100000;

// Safely read an integer from the user.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Safely read a full line, including spaces.
string readText(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin >> ws, value);
    return value;
}

void displayRecord(const Achievement& a, int number = -1) {
    if (number >= 0) cout << number << ". ";
    cout << "Student: " << a.student
         << " | Batch: " << a.batch
         << " | Category: " << a.category
         << " | Year: " << a.year
         << " | Title: " << a.title << '\n';
}

void displayRecords(const vector<Achievement>& records,
                    const string& heading = "Matching Records") {
    cout << "\n=== " << heading << " ===\n";
    if (records.empty()) {
        cout << "No matching records found.\n";
        return;
    }
    for (size_t i = 0; i < records.size(); ++i) {
        displayRecord(records[i], static_cast<int>(i + 1));
    }
    cout << "Total records: " << records.size() << '\n';
}

bool validRecord(const Achievement& a) {
    return !a.student.empty() && !a.batch.empty() &&
           !a.category.empty() && !a.title.empty() && a.year > 0;
}

void addRecords(vector<Achievement>& records) {
    if (records.size() >= MAX_RECORDS) {
        cout << "Record limit reached (" << MAX_RECORDS << ").\n";
        return;
    }

    int count = readInt("How many records do you want to add? ");
    if (count <= 0) {
        cout << "Enter a positive number.\n";
        return;
    }
    if (count > MAX_RECORDS - static_cast<int>(records.size())) {
        cout << "That exceeds the maximum of " << MAX_RECORDS
             << " total records. You can add "
             << MAX_RECORDS - records.size() << " more.\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        Achievement a;
        cout << "\n--- Achievement " << i + 1 << " ---\n";
        a.student = readText("Student ID: ");
        a.batch = readText("Batch: ");
        a.category = readText("Category: ");
        a.year = readInt("Year: ");
        a.title = readText("Title: ");

        if (!validRecord(a)) {
            cout << "Invalid record; it was not saved. "
                 << "All text fields are required and year must be positive.\n";
            --i; // Let the user retry this record.
            continue;
        }
        records.push_back(a);
        cout << "Record added successfully.\n";
    }
}

vector<Achievement> searchStudent(const vector<Achievement>& records,
                                  const string& studentID) {
    vector<Achievement> result;
    copy_if(records.begin(), records.end(), back_inserter(result),
            [&](const Achievement& a) {
                return a.student == studentID;
            });
    return result;
}

vector<Achievement> filterCategory(const vector<Achievement>& records,
                                   const string& category) {
    vector<Achievement> result;
    copy_if(records.begin(), records.end(), back_inserter(result),
            [&](const Achievement& a) {
                return a.category == category;
            });
    return result;
}

vector<Achievement> filterBatch(const vector<Achievement>& records,
                                const string& batch) {
    vector<Achievement> result;
    copy_if(records.begin(), records.end(), back_inserter(result),
            [&](const Achievement& a) {
                return a.batch == batch;
            });
    return result;
}

vector<Achievement> filterYear(const vector<Achievement>& records,
                               int year) {
    vector<Achievement> result;
    copy_if(records.begin(), records.end(), back_inserter(result),
            [&](const Achievement& a) {
                return a.year == year;
            });
    return result;
}

void saveToFile(const vector<Achievement>& records, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& a : records) {
        file << a.student << '\n'
             << a.batch << '\n'
             << a.category << '\n'
             << a.year << '\n'
             << a.title << '\n';
    }
    cout << "Records saved successfully to " << filename << ".\n";
}

void loadFromFile(vector<Achievement>& records, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        // File may not exist yet on first run; fail silently or inform gently
        return;
    }
    records.clear();
    Achievement a;
    while (getline(file, a.student) &&
           getline(file, a.batch) &&
           getline(file, a.category) &&
           (file >> a.year)) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, a.title);
        if (validRecord(a)) {
            records.push_back(a);
        }
    }
    cout << "Loaded " << records.size() << " records from " << filename << ".\n";
}

int main() {
    vector<Achievement> records;
    const string defaultFilename = "achievements.txt";
    
    // Attempt to load existing records on startup
    loadFromFile(records, defaultFilename);

    int choice = 0;
    do {
        cout << "\n=== Student Achievement Management System ===\n"
             << "1. Add Records\n"
             << "2. View All Records\n"
             << "3. Search by Student ID\n"
             << "4. Filter by Category\n"
             << "5. Filter by Batch\n"
             << "6. Filter by Year\n"
             << "7. Save Records to File\n"
             << "8. Load Records from File\n"
             << "9. Exit\n";
        choice = readInt("Enter your choice (1-9): ");

        switch (choice) {
            case 1:
                addRecords(records);
                break;
            case 2:
                displayRecords(records, "All Records");
                break;
            case 3: {
                string id = readText("Enter Student ID to search: ");
                auto res = searchStudent(records, id);
                displayRecords(res, "Search Results for Student: " + id);
                break;
            }
            case 4: {
                string cat = readText("Enter Category to filter: ");
                auto res = filterCategory(records, cat);
                displayRecords(res, "Records in Category: " + cat);
                break;
            }
            case 5: {
                string batch = readText("Enter Batch to filter: ");
                auto res = filterBatch(records, batch);
                displayRecords(res, "Records for Batch: " + batch);
                break;
            }
            case 6: {
                int yr = readInt("Enter Year to filter: ");
                auto res = filterYear(records, yr);
                displayRecords(res, "Records for Year: " + to_string(yr));
                break;
            }
            case 7: {
                string fname = readText("Enter filename to save (press Enter for default 'achievements.txt'): ");
                if (fname.empty()) fname = defaultFilename;
                saveToFile(records, fname);
                break;
            }
            case 8: {
                string fname = readText("Enter filename to load (press Enter for default 'achievements.txt'): ");
                if (fname.empty()) fname = defaultFilename;
                loadFromFile(records, fname);
                break;
            }
            case 9:
                // Auto-save on exit for convenience
                saveToFile(records, defaultFilename);
                cout << "Data saved. Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please choose a number between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
