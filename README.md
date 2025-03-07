# COVID-19-Analysis-Tool
This C++ program processes a CSV dataset containing COVID-19 case data by country and state. It provides functionality to: 
- Store unique country names in a set.
- Map country and state-level case counts using a nested map.
- Process commands to retrieve case counts.
## Features
- Reads a CSV File and processes country and state COVID-19 case counts.
- Handles countries with multi-word names.
- Supports command-based querying.

## Usage
### ***Compile the program***
```sh
g++ -o covid_processor main.cpp
```
### ***Run Program***
```sh
./covid_proceessor confirmed_cases.csv commands.txt
```

## File Format
- confirmed_cases.csv: Contains COVID-19 data with country and state names.
- commands.txt: Contains commands like found in commands_sample.txt, which instruct the program on what data to retrieve.

## Technologies Used
- C++
- Standard Library (set, map, ifstream, sstream)

## Author 
Alyana Barbosa
