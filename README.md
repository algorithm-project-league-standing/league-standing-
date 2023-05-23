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

## Time Complexity

The time complexity of this program is `O(V + E log V)`, where V is the number of teams and E is the total number of matches played. This complexity comes from the following steps:

* Reading the input from file: `O(E log V)`
* BFS traversal of the graph: `O(V + E)`
* Sorting of teams based on their statistics: `O(V * log(V))`

Specifically, in reading the input from file, we map every team with a number and we use the function `find()` which takes a time `O(log V)` to search for the team needed to be mapped, so the total time to iterate over all matches is `O(E log V)`.

In the BFS traversal, each node in the graph is visited exactly once, and each edge is examined once to update the statistics of both teams involved in the match. Therefore, the time complexity of the BFS traversal is `O(V + E)`.

In the sorting step, the program sorts all V teams based on their statistics using the sort function, which compares each team's points, goal difference and goals for in that order. The sorting is done using the C++ standard library sort function, which has a worst-case time complexity of `O(V * log(V))`. However, in practice, the number of teams in the EPL is relatively small (20 teams as of 2021), so the sorting step is not likely to be a bottleneck in the program's performance.

Overall, the time complexity of this program should be sufficient for processing the EPL results CSV file, even if it contains several years' worth of data.

## Future Improvements

Some future improvements that could be made to this program include:

- Incorporating tiebreakers or other factors that could impact the league standings
- Creating a GUI or web interface to make the program more user-friendly

## Conclusion

This program provides an efficient way to compute the final EPL standings based on the results of all matches played. It has a reasonable time complexity and should be able to handle large amounts of data.
