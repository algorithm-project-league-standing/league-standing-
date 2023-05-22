#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

#define nl "\n"
#define match v.second

/* classes */
class Match
{
    public:
        int homeGoals;
        int awayGoals;
        int round;
        int  date;
        string result;

        Match(int r, int d, int hg, int ag, string rs){
            round = r;
            date = d;
            homeGoals = hg;
            awayGoals = ag;
            result = rs;
        }
};

class Team
{
    public:
        string teamName;
        int  matchPlayed;
        int wins;
        int drawns;
        int loses;
        int goalsFor;
        int goalsAgainst;
        int goalsDiff;
        int points;

        Team(string s){
            teamName = s;
            matchPlayed = 0;
            wins = 0;
            drawns = 0;
            loses = 0;
            goalsFor = 0;
            goalsAgainst = 0;
            goalsDiff = 0;
            points = 0;    
        }
};

/* global variables */

int counter, nteam, cnt;
map<string, int> stoint;
map<int, string> inttos;
vector<vector<pair<int, Match>>> adj;
vector<int> vis;


/* prototypes */

int stringToInt(string s);
int dateToInt(string s);
bool srt(Team t1, Team t2);

/* main function */

// V (vertices) is the number of teams
// E (Edges) is the number of played matches  

int main(){

    // O (E lg V)
    fstream data;
    string s, round, date, homeTeam, awayTeam, homeGoals, awayGoals, result; 
    data.open("epl_results.csv", ios::in);
    getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');
    getline(data, s, ',');getline(data, s, ',');getline(data, s, '\n');    // -> O(1)
    while(getline(data, round, ',')){                               // -> O(E)
        getline(data, date, ',');getline(data, homeTeam, ',');getline(data, awayTeam, ',');
        getline(data, homeGoals, ',');getline(data, awayGoals, ',');getline(data, result, '\n');
        if(stoint.find(homeTeam) == stoint.end()){
            nteam++;  // -> O(1)
            stoint[homeTeam] = counter++;  // -> O(1)
            inttos[counter] = homeTeam;    // -> O(1)
        }
        if(stoint.find(awayTeam) == stoint.end()){                  // -> O(lg V)
            nteam++; // -> O(1)
            stoint[awayTeam] = counter++; // -> O(1)
            inttos[counter] = awayTeam; // -> O(1)
        }
    }
    data.close();

    // O(E)
    adj = vector<vector<pair<int, Match>>>(nteam);     // -> O(V)
    vis = vector<int>(nteam, 0);                       // -> O(V)

    data.open("epl_results.csv", ios::in);
    getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');
    getline(data, s, ',');getline(data, s, ',');getline(data, s, '\n');    // O(1)
    while(getline(data, round, ',')){  // O(E)
        getline(data, date, ',');getline(data, homeTeam, ',');getline(data, awayTeam, ',');
        getline(data, homeGoals, ',');getline(data, awayGoals, ',');getline(data, result, '\n'); // O(1)
        if(awayGoals == "-" ) continue; // O(1)
        Match m (stringToInt(round), dateToInt(date), stringToInt(homeGoals), stringToInt(awayGoals), result); // O(1)
        adj[stoint[homeTeam]].push_back({stoint[awayTeam],m}); // O(1)
    }
    data.close();

    queue<int> q;
    while(true){
        vector<Team> teams;
        for(int i = 0; i <= nteam; ++i) vis[i] = 0;
        for(auto el : inttos){          // O(V)
            teams.push_back(Team(el.second));  // O(1)
        }
        int trio, choice; 
        cout << nl <<  "1 - Search by round " << nl << nl << "2 - search by date " << nl << nl << "3 - End The Program " << nl << nl ; 
        cout << "Enter Your Choice : ";
        cin >> trio ; 
        if(trio == 1){
            cout << "Enter the round number : ";
            cin >> choice; 
            
            // O(V+E)
            for(int i = 1; i <= nteam; ++i){
                if(!vis[i]){ // O(1)
                    q.push(i);
                    vis[i] = 1;
                    while(!q.empty()){   // O(V)
                        int u = q.front(); // O(1)
                        q.pop(); // O(1)
                        for(auto v : adj[u]){ // O(E)
                            // # define v.second match 
                            if(match.round <= choice){ // O(1)
                                teams[u].goalsFor += match.homeGoals;
                                teams[v.first].goalsAgainst += match.homeGoals;
                                teams[u].goalsAgainst += match.awayGoals;
                                teams[v.first].goalsFor += match.awayGoals;
                                teams[u].matchPlayed++;
                                teams[v.first].matchPlayed++;
                                if(match.result == "H"){
                                    teams[u].wins++;
                                    teams[u].points +=3;
                                    teams[v.first].loses ++;
                                }
                                else if(match.result == "A"){
                                    teams[v.first].wins++;
                                    teams[v.first].points +=3;
                                    teams[u].loses ++;
                                }
                                else{
                                    teams[u].drawns++;
                                    teams[v.first].drawns++;
                                    teams[u].points++;
                                    teams[v.first].points++;
                                }
                            }
                            if(!vis[v.first]){ // O(1)
                                q.push(v.first); 
                                vis[v.first] = 1;
                            }
                        }
                    }
                }
            }
        }
        else if(trio == 2){
            cout << "Enter the date in the form 'dd/mm/year' : " ;
            string da;
            cin >> da;
            choice = dateToInt(da);
            // O(V+E)
            for(int i = 1; i <= nteam; ++i){
                if(!vis[i]){
                    q.push(i);
                    vis[i] = 1;
                    while(!q.empty()){
                        int u = q.front();
                        q.pop();
                        for(auto v : adj[u]){
                            if(match.date <= choice){
                                teams[u].goalsFor += match.homeGoals;
                                teams[v.first].goalsAgainst += match.homeGoals;
                                teams[u].goalsAgainst += match.awayGoals;
                                teams[v.first].goalsFor += match.awayGoals;
                                teams[u].matchPlayed++;
                                teams[v.first].matchPlayed++;
                                if(match.result == "H"){
                                    teams[u].wins++;
                                    teams[u].points +=3;
                                    teams[v.first].loses ++;
                                }
                                else if(match.result == "A"){
                                    teams[v.first].wins++;
                                    teams[v.first].points +=3;
                                    teams[u].loses ++;
                                }
                                else{
                                    teams[u].drawns++;
                                    teams[v.first].drawns++;
                                    teams[u].points++;
                                    teams[v.first].points++;
                                }
                            }
                            if(!vis[v.first]){
                                q.push(v.first);
                                vis[v.first] = 1;
                            }
                        }
                    }
                }
            }
        }
        else {
            break;
        }

        sort(teams.begin(), teams.end(), srt);  // O(V lg V)

        ofstream out("league standing.csv");
        cout << nl << nl;
        cnt = 1;
        cout<< left << setw(13)  << "#" 
            << left << setw(23) << "Team"
            << left << setw(13)  << "M Played" 
            << left << setw(13)  << "Wins" 
            << left << setw(13)  << "Drawns" 
            << left << setw(13)  << "Loses" 
            << left << setw(13)  << "G For" 
            << left << setw(13)  << "G Against" 
            << left << setw(13)  << "G Diff"  
            << left << setw(13)  << "Points" 
            << nl << nl;
        cout << "======================================================================================================================================" << nl << nl;
    
        out << "#" << ','<< "Team" << ',' << "M Played" << ',' << "Wins" << ',' <<
                "Drawns" << ',' << "Loses" << ',' << "G For" << ',' << "G Against" << ',' <<
                "G Diff" << ',' << "G Diff" << '\n';  // O(1)

        for(auto el : teams){   // O(V)
            cout<< left << setw(13) << cnt 
                << left << setw(23) << el.teamName 
                << left << setw(13) << el.matchPlayed 
                << left << setw(13) << el.wins 
                << left << setw(13) << el.drawns 
                << left << setw(13) << el.loses 
                << left << setw(13) << el.goalsFor 
                << left << setw(13) << el.goalsAgainst 
                << left << setw(13) << el.goalsFor - el.goalsAgainst 
                << left << setw(13) << el.points 
                << nl << nl;

            out << cnt << ','<< el.teamName << ',' << el.matchPlayed << ',' << el.wins << ',' <<
                el.drawns << ',' << el.loses << ',' << el.goalsFor << ',' << el.goalsAgainst << ',' <<
                el.goalsFor - el.goalsAgainst << ',' << el.points << '\n';

            cnt++;
        }
        cout << "======================================================================================================================================" << nl << nl;
    }

    return 0;
}


/* Fuctions */

// O(1)
int stringToInt(string s){
    int res = 0;
    for(auto el: s)
    {
        res = (res * 10) + (el - '0');
    } 
    return res;
}

// O(1)
int dateToInt(string s){
    int year, month, day;
    std::sscanf(s.c_str(), "%d/%d/%d", &day, &month, &year) ;
    return 10000 * year + 100 * month + day;
}

// O(1)
bool srt(Team t1, Team t2){
    if(t1.points != t2.points)return t1.points > t2.points;
    else if(t1.goalsFor != t2.goalsFor) return t1.goalsFor - t1.goalsAgainst > t2.goalsFor - t2.goalsAgainst;
    else return t1.goalsFor < t2.goalsFor;
}
