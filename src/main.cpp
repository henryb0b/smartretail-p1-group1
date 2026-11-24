// =============================================================================
//  MiiN-SmartRetail - Project P1: Smart Shelf Monitor
//  Fundamentals of Programming (C++17)
//
//  Usage:
//    p1 <data_folder> [store_id] [product_id] [--export <file.csv>] [--compare <old_file.csv>]
//    e.g. p1 data/sample S001 P003 --export alerts.csv
//
//  Build:
//    g++ -std=c++17 -Wall -Wextra src/main.cpp -o bin/p1
//
//  Allowed toolbox (sessions 1-7): functions, struct, vector, string, ifstream/getline,
//  hand-written sorting/searching. NO class, pointer, new/delete, map/set, exception,
//  template, lambda, std::sort.
// =============================================================================
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// ===================== T02 - Structs (Hoang) =====================

// One line of products.csv
struct Product {
    std::string id;
    std::string name;
    std::string category;
    std::string brand;
    long long price = 0;    // VND
    double rating = 0.0;
};

// One line of inventory.csv
struct StockItem {
    std::string storeId;
    std::string productId;
    int stock = 0;
};

// One alert of the store being checked
struct Alert {
    std::string storeId;
    std::string productId;
    std::string name;
    int stock = 0;
    int level = 0;          // 1 = OUT OF STOCK, 2 = CRITICAL, 3 = LOW STOCK
};

// Statistics of one category
struct CategoryStat {
    std::string category;
    int products = 0;
    int alerts = 0;
};

// Command-line options
struct Options {
    std::string dataDir;
    std::string storeId = "S001";   // default from the brief
    std::string productId;          // empty = skip the search part
    std::string exportPath;         // empty = do not write a file
    std::string comparePath;        // empty = do not compare
};

// ===================== T02 - parseArgs (Hoang) =====================

// Reads: <data_folder> [store_id] [product_id] [--export <file>] [--compare <file>]
// Returns true and fills opt when the arguments are valid.
// Returns false (and prints the reason to std::cerr) when they are not.
bool parseArgs(const std::vector<std::string>& args, Options& opt) {
    int n = static_cast<int>(args.size());

    if (n < 1) {
        std::cerr << "Error: missing data folder\n";

        return false;
    }

    opt.dataDir = args[0];

    int positional = 0;     // how many of store_id, product_id have been read

    for (int i = 1; i < n; ++i) {
        if (args[i] == "--export" || args[i] == "--compare") {
            if (i + 1 >= n) {
                std::cerr << "Error: " << args[i] << " needs a file name\n";

                return false;
            }

            if (args[i] == "--export") {
                opt.exportPath = args[i + 1];
            }
            else {
                opt.comparePath = args[i + 1];
            }

            ++i;            // skip the file name just read
        }
        else if (args[i].size() >= 2 && args[i].substr(0, 2) == "--") {
            std::cerr << "Error: unknown option " << args[i] << '\n';

            return false;
        }
        else if (positional == 0) {
            opt.storeId = args[i];
            ++positional;
        }
        else if (positional == 1) {
            opt.productId = args[i];
            ++positional;
        }
        else {
            std::cerr << "Error: too many arguments: " << args[i] << '\n';

            return false;
        }
    }

    return true;
}

// ===================== T03 - stockLevel, statusName (Thong) =====================

// Returns priority level for a stock value:
//   stock == 0      -> 1 (OUT OF STOCK, highest priority)
//   1 <= stock <= 2 -> 2 (CRITICAL)
//   3 <= stock <= 5 -> 3 (LOW STOCK)
//   stock > 5       -> 0 (no alert / AVAILABLE)
int stockLevel(int stock) {
    int level;

    if (stock == 0) {
        level = 1;
    }
    else if (stock <= 2) {
        level = 2;
    }
    else if (stock <= 5) {
        level = 3;
    }
    else {
        level = 0;
    }

    return level;
}

// Returns the status label for a priority level:
//   1 -> "OUT OF STOCK"
//   2 -> "CRITICAL"
//   3 -> "LOW STOCK"
//   0 (or other) -> "AVAILABLE"
std::string statusName(int level) {
    std::string name;

    if (level == 1) {
        name = "OUT OF STOCK";
    }
    else if (level == 2) {
        name = "CRITICAL";
    }
    else if (level == 3) {
        name = "LOW STOCK";
    }
    else {
        name = "AVAILABLE";
    }

    return name;
}

// ===================== T04 - splitLine, isInteger, loadProducts (Tram) =====================
// Check whether string s is a valid non-negative integer.
bool isInteger(const std::string& s) {
    if (s.empty()) {
        return false;
    }

    int i = 0;
    while (i < static_cast<int>(s.size())) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
        i = i + 1;
    }

    return true;
}

// Separate a line of CSV data by commas ',' and remove the '\r' at the end of the line if present.
std::vector<std::string> splitLine(std::string line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    std::vector<std::string> cols;
    std::string current = "";
    int i = 0;

    while (i < static_cast<int>(line.size())) {
        if (line[i] == ',') {
            cols.push_back(current);
            current = "";
        } else {
            current += line[i];
        }
        i = i + 1;
    }

    cols.push_back(current);
    return cols;
}

// Convert a string to a long long value (as in, has passed isInteger))
long long parsePrice(const std::string& s) {
    long long value = 0;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        int digit = s[i] - '0';
        value = value * 10 + digit;
    }
    return value;
}

// Validate and convert the rating (non-negative number in [0.0, 5.0], supporting one or more decimal places)
bool parseRating(const std::string& s, double& outRating) {
    if (s.empty()) {
        return false;
    }

    int dotCount = 0;
    int digitCount = 0;
    int i = 0;

    while (i < static_cast<int>(s.size())) {
        if (s[i] == '.') {
            dotCount = dotCount + 1;
            if (dotCount > 1) {
                return false;
            }
        } else if (s[i] >= '0' && s[i] <= '9') {
            digitCount = digitCount + 1;
        } else {
            return false;
        }
        i = i + 1;
    }

    if (digitCount == 0) {
        return false;
    }

    double parsed = 0.0;
    bool afterDot = false;
    double decimalPlace = 0.1;
    i = 0;

    while (i < static_cast<int>(s.size())) {
        if (s[i] == '.') {
            afterDot = true;
        } else {
            int digit = s[i] - '0';
            if (!afterDot) {
                parsed = parsed * 10.0 + static_cast<double>(digit);
            } else {
                parsed = parsed + static_cast<double>(digit) * decimalPlace;
                decimalPlace = decimalPlace * 0.1;
            }
        }
        i = i + 1;
    }

    if (parsed < 0.0 || parsed > 5.0) {
        return false;
    }

    outRating = parsed;
    return true;
}

// Check for duplicate product_id (keep the first record)
bool hasDuplicateID(const std::string& productId, const std::vector<Product>& products) {
    for (int i = 0; i < static_cast<int>(products.size()); i++) {
        if (products[i].id == productId) {
            return true;
        }
    }
    return false;
}

// Read products.csv, validate the data, flag any erroneous rows, and load the data into the products table.
bool loadProducts(const std::string& path, std::vector<Product>& products) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << path << "\n";
        return false;
    }

    int lineNumber = 1;
    std::string line;

    if (!std::getline(file, line)) {
        file.close();
        return true;
    }

    while (std::getline(file, line)) {
        lineNumber = lineNumber + 1;
        std::vector<std::string> cols = splitLine(line);

        if (cols.size() != 6) {
            std::cerr << "Warning (line " << lineNumber << "): expected 6 columns, got "
                      << cols.size() << ". Row skipped.\n";
            continue;
        }

        bool validPrice = isInteger(cols[4]);
        double parsedRating = 0.0;
        bool validRating = parseRating(cols[5], parsedRating);
        bool isDuplicateID = hasDuplicateID(cols[0], products);

        if (!cols[0].empty() && validPrice && validRating && !isDuplicateID) {
            Product p;
            p.id = cols[0];
            p.name = cols[1];
            p.category = cols[2];
            p.brand = cols[3];
            p.price = parsePrice(cols[4]);
            p.rating = parsedRating;
            products.push_back(p);
        } else {
            std::cerr << "Warning (line " << lineNumber << "): invalid product data. Row skipped.\n";
        }
    }

    file.close();
    return true;
}

// ===================== T05 - sortProducts, findProduct, binarySearch (Hoang) =====================

// ===================== T06 - loadStock (Tram) =====================

// ===================== T07 - printStoreTable, Summary (Thong) =====================

// ===================== T08 - addCategory, printCategories (Thong) =====================

// ===================== T09 - buildAlerts, sortAlerts (Tram) =====================

// ===================== T10 - availableElsewhere (Hoang) =====================

// ===================== T11 - searchProduct (Hoang) =====================

// ===================== T12 - printChain (Tram) =====================

// ===================== T13 - exportAlerts (Hoang) =====================

// ===================== T14 - compareAlerts (Tram) =====================

// ===================== main =====================

int main(int argc, char* argv[]) {
        // Copy argv into a vector so other functions do not use pointers.
    std::vector<std::string> args;

    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    Options opt;

    if (!parseArgs(args, opt)) {
        std::cerr << "Usage: p1 <data_folder> [store_id] [product_id] "
                  << "[--export <file.csv>] [--compare <old_file.csv>]\n";

        return 1;
    }

    // Temporary output to check T02; later tasks replace it with the real report.
    std::cout << "Data folder : " << opt.dataDir << '\n';
    std::cout << "Store       : " << opt.storeId << '\n';
    std::cout << "Product     : " << (opt.productId.empty() ? "(none)" : opt.productId) << '\n';
    std::cout << "Export      : " << (opt.exportPath.empty() ? "(none)" : opt.exportPath) << '\n';
    std::cout << "Compare     : " << (opt.comparePath.empty() ? "(none)" : opt.comparePath) << '\n';

    return 0;
}
