# English Premier League Standings Simulator

This program simulates the English Premier League (EPL) standings based on data from the EPL results CSV file. It uses breadth-first search (BFS) to traverse a graph representing the teams and their matches, and updates the statistics of each team based on the match results.

## Usage

To use the program, first download the EPL results CSV file and save it in the same directory as the program. Then, compile and run the program using a C++ compiler.

When prompted, choose between searching by round or by date. If searching by round, enter the desired round number. If searching by date, enter the desired date in yyyy-mm-dd format.

The program will then calculate the statistics for all matches up to and including the chosen round or date, and output the league table.

## Classes

The program uses several C++ classes:

- `Match`: stores information about a single match, including the teams involved, the score, and the date
- `Team`: stores information about a single team, including the number of matches played, wins, draws, losses, goals for, goals against, goal difference, and points

## Standard Library Functions

The program uses several C++ standard library functions, including:
- `map`: Maps are associative containers that store elements in a mapped fashion. Each element has a key value and a mapped value. No two mapped values can have            the same key values.
- `getline`: reads a line of input from the CSV file
- `stringstream`: parses the input line into individual fields
- `setw`: sets the width of output columns in the league table

## Limitations

This program provides a simple but effective simulation of the EPL standings based on real-world data. However, it does have some limitations:

- It assumes that the input data is accurate and up-to-date
- It does not take into account tiebreakers or other factors that could impact the league standings

## Future Improvements

Some future improvements that could be made to this program include:

- Incorporating tiebreakers or other factors that could impact the league standings
- Creating a GUI or web interface to make the program more user-friendly
