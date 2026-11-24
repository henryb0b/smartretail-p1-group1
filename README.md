
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

## Run Instructions

After completing the implementation:

```bash
./bin/p1 <data_folder> [store_id] [product_id] [--export <file.csv>] [--compare <old_file.csv>]
./bin/p1 data/sample S001 P003
```

## Git Workflow

1. Update the main branch using `git pull`.
2. Create a feature branch for each task.
3. Implement the assigned task.
4. Add a flowchart + pseudocode for coding tasks in `docs/flowcharts/`.
5. Build and test the program.
6. Commit changes with a meaningful message.
7. Push the feature branch to GitHub.
8. Create a Pull Request.
9. Request review from the assigned reviewer.
10. Merge only after approval, then delete the branch

Do not commit directly to `main`.

## Task Assignment table

| ID | Task | Function / file | Assignee | Reviewer | Flowchart | PR |
|---|---|---|---|---|---|---|
| T01 | Repo skeleton | .gitignore, PR template, README | Hoang (henryb0b) | Tram (thaotram72) | not needed | #1 |
| T02 | main.cpp skeleton, structs, CLI args | Product, StockItem, Alert, CategoryStat, parseArgs, main | Hoang (henryb0b) | Thong (vthonq) | yes | #2 |
| T03 | Stock classification (core) | Core function stockLevel, statusName | Thong (vthonq) | Hoang (henryb0b) | yes | #3 |
| T04 | Read products.csv | splitLine, isInteger, loadProducts | Tram (thaotram72) | Thong (vthonq) | yes | #8 |
| T05 | Sort catalogue + recursive binary search | sortProducts, findProduct, binarySearch | Hoang (henryb0b) | Tram (thaotram72) | yes | |
| T06 | Read inventory.csv | loadStock | Tram (thaotram72) | Hoang (henryb0b) | yes | |
| T07 | Store table + summary | printStoreTable, countByLevel | Thong (vthonq) | Tram (thaotram72) | yes | |
| T08 | Category statistics | addCategory, printCategories | Thong (vthonq) | Hoang (henryb0b) | yes | |
| T09 | Build and sort alerts | buildAlerts, sortAlerts, comesBefore | Tram (thaotram72) | Thong (vthonq) | yes | |
| T10 | In stock at other stores | availableElsewhere | Hoang (henryb0b) | Thong (vthonq) | yes | |
| T11 | Search one product | searchProduct | Hoang (henryb0b) | Tram (thaotram72) | yes | |
| T12 | Chain summary | printChain | Tram (thaotram72) | Hoang (henryb0b) | yes | |
| T13 | Export alerts | exportAlerts | Hoang (henryb0b) | Thong (vthonq) | yes | |
| T14 | Extension --compare | compareAlerts | Tram (thaotram72) | Hoang (henryb0b) | yes | |
| T15 | Architecture | docs/architecture.md | Hoang (henryb0b) | Tram (thaotram72) | not needed | |
| T16 | Test cases | tests/test_cases.md, tests/expected/ | Thong (vthonq) | Tram (thaotram72) | not needed | |
| T17 | Slides | docs/slides.pdf | Tram (thaotram72) | Thong (vthonq) | not needed | |
| T18 | Final README + tag final | README.md | Hoang (henryb0b) | Thong (vthonq) | not needed | |
| T19 | M1 coordination: task table, PR template, folders | README.md, .github, tests/, docs/images/ | Hoang (henryb0b) | Tram (thaotram72) | not needed | #4 |

## AI Tools Declaration

AI assistance must be declared in Pull Requests.

All team members are responsible for understanding and verifying their own code.

## Project Status

| Milestone | Deadline | Requirements | Status |
|---|---|---|---|
| M1 – Team setup | Sat 21/11, 23:59 | Public repo, locked `main`, invitations, Google Sheet, repo skeleton + PR template, task assignment table (core function owner) | In review: T19 |
| M2 – Struct + flowchart | Thu 03/12, 23:59 | Read CSV files into vectors of structs, skip bad lines with warnings; core function flowchart + pseudocode; draft `docs/architecture.md`; each member ≥ 1 merged code PR | Core function flowchart done (T03) |
| M3 – Sample correct | Sun 06/12, 23:59 | `data/sample` matches expected output (TC01); `tests/test_cases.md` TC01–TC07 with Expected; each member ≥ 2 merged code PRs | Not started |
| FINAL – Tag `final` | Wed 09/12, 23:59 | Tag `final` on `main`; all 4 products; Actual column filled; `docs/slides.pdf` | Not started |
| REPORT – Presentation & cross viva | TBA (in class) | 5–10 min presentation + demo on `data/full`; cross viva | – |

- Done: T01 (#1), T02 (#2), T03 (#3)
- In review: T19
- Next (M2): T04, T05, T06, draft `docs/architecture.md`