#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <string_view>

using namespace std;

class CSVParser {
public:
    // Dividir línea CSV (maneja comillas y comas)
    static vector<string> split(string_view line, char delimiter = ',') {
        vector<string> tokens;
        string current;
        bool inQuotes = false;

        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == delimiter && !inQuotes) {
                tokens.push_back(trim(current));
                current.clear();
            } else {
                current += c;
            }
        }

        if (!current.empty()) {
            tokens.push_back(trim(current));
        }

        return tokens;
    }

private:
    // Eliminar espacios al inicio y final
    static string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }
};

#endif
