# 🏆 Achievement Registry and Reports

A C++17-based student achievement management system that stores student achievements and generates reports by student, batch, category, and academic year. It supports indexed searching, year-range queries, pivot reports, and CSV export.

## 📌 Problem Statement

Educational institutions need an efficient way to store student achievements and generate reports based on different criteria. This project provides a registry system designed to organize achievement records and generate useful summaries efficiently.

## ✨ Features

- **Achievement Registry:** Stores student ID, batch, category, academic year, and achievement title.
- **Student Reports:** Retrieves achievements associated with a particular student.
- **Category Reports:** Counts achievements by category and lists participating students.
- **Batch Reports:** Generates achievement counts for a specific batch.
- **Year Reports:** Retrieves achievements for a particular academic year.
- **Year-Range Queries:** Searches achievements across an inclusive range of years.
- **Pivot Report:** Summarizes achievement counts by batch, category, and year.
- **Indexed Searching:** Uses hash-map indexes for student, batch, and category, plus an ordered year index.
- **CSV Export:** Exports achievement records to a CSV file.
- **Empty-Report Handling:** Displays a message when no matching records exist.
- **Scalability:** Designed to handle up to 100,000 achievement records.

## 🛠️ Technologies Used

- **Language:** C++
- **Standard:** C++17
- **Data Structures:** Vector, unordered map, ordered map, and set
- **Algorithms:** Sorting, indexed lookup, and aggregation
- **File Handling:** CSV file export

## 📂 Project Structure

```text
Achievement-Registry-Reports/
├── achievement_registry_fixed.cpp
└── README.md
```

## 🚀 Getting Started

### Option 1: Run Online

1. Open [OnlineGDB C++ Compiler](https://www.onlinegdb.com/online_c++_compiler).
2. Copy the source code from `achievement_registry_fixed.cpp` into the editor.
3. Select C++17 if available.
4. Enter the sample input in the standard input box.
5. Click **Run** to execute the program.

### Option 2: Run Locally

Install a C++17-compatible compiler, such as GCC or MinGW-w64.

Compile the program:

```bash
g++ -std=c++17 -O2 -Wall -Wextra achievement_registry_fixed.cpp -o registry
```

Run on Linux or macOS:

```bash
./registry
```

Run on Windows PowerShell:

```powershell
.\registry.exe
```

## 📥 Input Format

The first line contains the number of achievement records, `N`.

Each following record contains five whitespace-separated fields:

```text
student_id batch category year title
```

Example input:

```text
4
S1 B2023 HACKATHON 2026 SmartBin
S1 B2023 CERTIFICATION 2025 AWS
S2 B2024 SPORTS 2026 Chess
S3 B2023 HACKATHON 2026 AIQuest
REPORT STUDENT S1
REPORT CATEGORY HACKATHON
REPORT BATCH B2023
```

**Note:** The current input format treats each field as a single token. Use underscores instead of spaces in titles or other fields.

## 🔎 Supported Commands

| Command | Description |
|---|---|
| `REPORT STUDENT S1` | Displays achievements for student S1 |
| `REPORT CATEGORY HACKATHON` | Counts achievements in the HACKATHON category and lists participating students |
| `REPORT BATCH B2023` | Displays the total number of records in batch B2023 |
| `REPORT YEAR 2026` | Displays records for year 2026 |
| `REPORT YEAR 2025 2026` | Queries records from 2025 through 2026 |
| `REPORT YEAR_RANGE 2025 2026` | Alternative year-range query |
| `REPORT RANGE 2025 2026` | Alternative year-range query |
| `REPORT PIVOT` | Generates the batch-category-year pivot report |
| `PIVOT` | Alternative pivot command |
| `EXPORT achievements.csv` | Exports records to a CSV file |
| `CSV achievements.csv` | Alternative CSV export command |
| `COUNT STUDENT S1` | Counts records belonging to student S1 |
| `COUNT BATCH B2023` | Counts records belonging to batch B2023 |
| `COUNT CATEGORY HACKATHON` | Counts records in the HACKATHON category |
| `EXIT` | Stops command processing |

## 📊 Example Reports

For the sample records above, the following report commands produce these key results.

### Student Report

Command:

```text
REPORT STUDENT S1
```

Expected report line:

```text
S1: AWS(2025) SmartBin(2026)
```

### Category Report

Command:

```text
REPORT CATEGORY HACKATHON
```

Expected report line:

```text
HACKATHON: 2 (S1, S3)
```

### Batch Report

Command:

```text
REPORT BATCH B2023
```

Expected report line:

```text
B2023: 3
```

## ⚙️ Data Structures and Efficiency

| Data structure | Purpose |
|---|---|
| `vector<Achievement>` | Stores the complete achievement registry |
| `unordered_map<string, vector<int>>` for students | Maps student IDs to record positions |
| `unordered_map<string, vector<int>>` for batches | Maps batches to record positions |
| `unordered_map<string, vector<int>>` for categories | Maps categories to record positions |
| `map<int, vector<int>>` for years | Maintains years in sorted order for year and range queries |
| `map` and `set` for pivot generation | Groups and counts achievements by batch, category, and year |

### Complexity Overview

- Student, batch, and category index lookup: expected **O(1)** to find the index, plus the cost of processing matching records.
- Year lookup: **O(log Y)** to find a year, where `Y` is the number of distinct years, plus the cost of processing matching records.
- Year-range query: **O(log Y + K)**, where `K` is the number of records processed in the requested range.
- Pivot report: aggregation over all records, with additional map and set operations.
- CSV export: **O(N)** records written.

## 🧪 Testing

Test the program using:

- Multiple achievements for the same student.
- Different batches and categories.
- Exact-year and year-range queries.
- Queries that return no matching records.
- Pivot reports across multiple years.
- CSV export and file creation.
- Large inputs containing up to 100,000 records.

## 📤 Deliverables

- `achievement_registry_fixed.cpp` — C++17 registry implementation.
- `README.md` — project documentation, usage instructions, and supported commands.

## 🔮 Future Improvements

- Support titles and field values containing spaces.
- Add record editing and deletion.
- Import existing records from CSV files.
- Add persistent storage between program executions.
- Provide additional analytics and report formats.

## 👨‍💻 Conclusion

The Achievement Registry and Reports project demonstrates the use of C++ data structures, indexed searching, sorted indexes, reporting, aggregation, and file handling to manage student achievements efficiently.

**Project status:** Console-based C++17 implementation.
