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
queue<int> q;

/* prototypes */

int stringToInt(string s);
int dateToInt(string s);
bool srt(Team t1, Team t2);
void BFS_date(int s, int choice, vector<Team> &team);
void BFS_round(int s, int choice, vector<Team> &team);

/* main function */

int main(){

    fstream data;
    string s, round, date, homeTeam, awayTeam, homeGoals, awayGoals, result; 
    data.open("epl_results.csv", ios::in);
    getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');
    getline(data, s, ',');getline(data, s, ',');getline(data, s, '\n');
    while(getline(data, round, ',')){
        getline(data, date, ',');getline(data, homeTeam, ',');getline(data, awayTeam, ',');
        getline(data, homeGoals, ',');getline(data, awayGoals, ',');getline(data, result, '\n');
        if(stoint.find(homeTeam) == stoint.end()){
            nteam++;
            stoint[homeTeam] = counter++;
            inttos[counter] = homeTeam;
        }
        if(stoint.find(awayTeam) == stoint.end()){
            nteam++;
            stoint[awayTeam] = counter++;
            inttos[counter] = awayTeam;
        }
    }
    data.close();

    adj = vector<vector<pair<int, Match>>>(nteam);
    vis = vector<int>(nteam, 0);

    data.open("epl_results.csv", ios::in);
    getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');getline(data, s, ',');
    getline(data, s, ',');getline(data, s, ',');getline(data, s, '\n');
    while(getline(data, round, ',')){
        getline(data, date, ',');getline(data, homeTeam, ',');getline(data, awayTeam, ',');
        getline(data, homeGoals, ',');getline(data, awayGoals, ',');getline(data, result, '\n');
        if(awayGoals == "-" ) continue; 
        Match m (stringToInt(round), dateToInt(date), stringToInt(homeGoals), stringToInt(awayGoals), result);
        adj[stoint[homeTeam]].push_back({stoint[awayTeam],m});
    }
    data.close();

    while(true){
        vector<Team> teams;
        for(int i = 0; i <= nteam; ++i) vis[i] = 0;
        for(auto el : inttos){
            teams.push_back(Team(el.second));
        }
        int trio, choice; 
        cout << nl <<  "1 - Search by round " << nl << nl << "2 - search by date " << nl << nl << "3 - End The Program " << nl << nl ; 
        cout << "Enter Your Choice : ";
        cin >> trio ; 
        if(trio == 1){
            cout << "Enter the round number : ";
            cin >> choice; 
            for(int i = 1; i <= nteam; ++i){
                if(!vis[i]){
                    BFS_round(i, choice, teams);
                }
            }
        }
        else if(trio == 2){
            cout << "Enter the date in the form 'dd/mm/year' : " ;
            string da;
            cin >> da;
            choice = dateToInt(da);
            for(int i = 1; i <= nteam; ++i){
                if(!vis[i]){
                    BFS_date(i, choice, teams);
                }
            }
        }
        else {
            break;
        }

        sort(teams.begin(), teams.end(), srt);

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
                "G Diff" << ',' << "G Diff" << '\n';

        for(auto el : teams){
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

int stringToInt(string s){
    int res = 0;
    for(auto el: s)
    {
        res = (res * 10) + (el - '0');
    } 
    return res;
}

int dateToInt(string s){
    int year, month, day;
    std::sscanf(s.c_str(), "%d/%d/%d", &day, &month, &year) ;
    return 10000 * year + 100 * month + day;
}

bool srt(Team t1, Team t2){
    if(t1.points != t2.points)return t1.points > t2.points;
    else if(t1.goalsFor - t1.goalsAgainst != t2.goalsFor - t2.goalsAgainst) return t1.goalsFor - t1.goalsAgainst > t2.goalsFor - t2.goalsAgainst;
    else return t1.goalsFor > t2.goalsFor;
}

void BFS_round(int s, int choice, vector<Team> &teams){
    q.push(s);
    vis[s] = 1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v : adj[u]){
            if(match.round <= choice){
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

void BFS_date(int s, int choice, vector<Team> &teams){
    q.push(s);
    vis[s] = 1;
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