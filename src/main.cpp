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

// ===================== T04 - splitLine, isInteger, loadProducts (Tram) =====================

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
