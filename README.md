
# SmartRetail P1 – Group 1

## Project Overview

SmartRetail P1 is a C++17 group project that monitors retail inventory, identifies low-stock products, and generates inventory alerts across multiple stores.

## Team Members

| Member | GitHub Username | Role |
|---|---|---|
| Bui Viet Hoang | henryb0b | Team Leader |
| Nguyen Van Viet Thong | vthonq | Member |
| Phan Nhat Thao Tram | thaotram72 | Member |

## Project Structure

- `src/` – C++ source code
- `data/sample/` – Sample dataset
- `data/full/` – Full dataset
- `data/edge/` – Edge-case datasets
- `docs/` – Project documentation
- `docs/flowcharts/` – Flowcharts
- `tests/` – Test cases
- `bin/` – Compiled programs (not committed)
- `.github/` – Pull Request templates

## Requirements

- C++17
- Git and GitHub
- VS Code or another C++ editor
- C++ compiler (g++ or compatible Clang)

## Build Instructions

Run from the repository root:

```bash
mkdir -p bin
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bin/p1
```

Note: `src/main.cpp` will be created in task T02.

## Run Instructions

After completing the implementation:

```bash
./bin/p1 data/sample S001 P003
```

## Git Workflow

1. Update the main branch using `git pull`.
2. Create a feature branch for each task.
3. Implement the assigned task.
4. Add a flowchart for coding tasks.
5. Build and test the program.
6. Commit changes with a meaningful message.
7. Push the feature branch to GitHub.
8. Create a Pull Request.
9. Request review from the assigned reviewer.
10. Merge only after approval.

Do not commit directly to `main`.

## Task Assignment

Task assignments T01–T18 are maintained in the group's task allocation document.

This section will be updated with the full task table and Pull Request links.

## AI Tools Declaration

AI assistance must be declared in Pull Requests.

Current usage:
- ChatGPT: Assisted with Git/GitHub setup, repository structure, and documentation templates.

All team members are responsible for understanding and verifying their own code.

## Project Status

- T01: Repository setup – In progress
- T02–T18: Pending or assigned according to the task allocation document
