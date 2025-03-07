#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <string>

// Edge Case for countries with two part names in quotations.
std::string CountryNameEdgeCase(const std::string &country) {
    std::stringstream ss(country);
    std::string normalName;
    char c;

    if (ss.peek() == '"') {
        ss.get();
        while (ss.peek() != '"' && ss.peek() != std::char_traits<char>::eof()) {
            c = ss.get();
            normalName += c;
        }
        ss.get();
    } else {
        normalName = country;
    }

    if (normalName == "Korea, South") return "South Korea";
    if (normalName == "Korea, North") return "North Korea";
    if (normalName == "United States") return "US";
    return normalName;
}

// set method.
void set(std::set<std::string> &myset, const std::string &file) {
    std::ifstream dataset(file);
    std::string line;

    // Skip header
    std::getline(dataset, line);

    while (std::getline(dataset, line)) {
        std::stringstream info(line);
        std::string FIPS, Admin2, state, country;

        std::getline(info, FIPS, ',');
        std::getline(info, Admin2, ',');
        std::getline(info, state, ',');
        std::getline(info, country, ',');

        // Normalize and add country to the set
        country = CountryNameEdgeCase(country);

        myset.insert(country);
    }
}

void map(std::map<std::string, std::map<std::string, int>> &mymap, const std::string &file) {
    std::ifstream dataset(file);
    std::string line;

    // Skip header
    std::getline(dataset, line);

    while (std::getline(dataset, line)) {
        std::stringstream info(line);
        std::string FIPS, Admin2, state, country, Last_Update, Lat, Long_, Confirmed;

        std::getline(info, FIPS, ',');
        std::getline(info, Admin2, ',');
        std::getline(info, state, ',');
        std::getline(info, country, ',');
        std::getline(info, Last_Update, ',');
        std::getline(info, Lat, ',');
        std::getline(info, Long_, ',');
        std::getline(info, Confirmed, ',');
        
        // check if row is empty.
        if (country.empty() || Confirmed.empty()) continue;

        // Normalize country name
        country = CountryNameEdgeCase(country);

        // Parse cases
        int case_count = Confirmed.empty() ? 0 : std::stoi(Confirmed);

        if (state.empty()) {
            mymap[country][country] += case_count; // Add directly to country total
        } else {
            // for state-level and sum duplicate data
            if (mymap[country].find(state) != mymap[country].end()) {
                mymap[country][state] += case_count;
            } else {
                mymap[country][state] += case_count;
               } 
            mymap[country][country] += case_count; // Add to country total
        }
    }
}

int main(int argc, char *argv[]) {
   /* if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dataset.csv> <commands.txt>" << std::endl;
        return 1;
    }
*/
    std::string dataset_file = argv[1];
    std::string commands_file = argv[2];

    std::set<std::string> myset;
    std::map<std::string, std::map<std::string, int>> mymap;

    // Populate data structures
    set(myset, dataset_file);
    map(mymap, dataset_file);

    // Process commands
    std::ifstream commandlist(commands_file);
    std::string command;

    while (std::getline(commandlist, command)) {
        if (command.find("set ") == 0) {
            std::string country = command.substr(4);
            country = CountryNameEdgeCase(country); // Normalize
            std::cout << (myset.count(country) ? 1 : 0) << std::endl;
        } else if (command.find("map ") == 0) {
            std::string args = command.substr(4);
            size_t delim = args.find(';');
            if (delim == std::string::npos) {
                std::string country = args;
                country = CountryNameEdgeCase(country); // Normalize
                if (mymap.count(country)) {
                    std::cout << mymap[country][country] << std::endl;
                } else {
                    std::cout << -1 << std::endl;
                }
            } else {
                std::string country = args.substr(0, delim);
                std::string state = args.substr(delim + 1);
                country = CountryNameEdgeCase(country); // Normalize
                if (mymap.count(country) && mymap[country].count(state)) {
                    std::cout << mymap[country][state] << std::endl;
                } else {
                    std::cout << -1 << std::endl;
                }
            }
        }
    }

    return 0;
}

