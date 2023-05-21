#include <D:\Documents\C++\asd\stdc++.h>
using namespace std;
#define ll long long
#define nl "\n"
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
const long long MOD = 1e9 + 7, OO = 1e13;
const double PI = acos(-1);
const long long N = 1e6 + 5, M = 1e5 + 5;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};


#define match v.second

class Match
{
    public:
    int homeGoals, awayGoals,  round, date;
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
    int  matchPlayed, wins, drawns, loses, goalsFor, goalsAgainst, goalsDiff, points;
        Team(string s){
            teamName = s;
            matchPlayed = 0, wins = 0, drawns = 0, loses = 0, goalsFor = 0, goalsAgainst = 0, goalsDiff = 0, points = 0;    
        }
};

int counter, nteam;
map<string, int> stoint;
map<int, string> inttos;
vector<vector<pair<int, Match>>> adj;
vector<int> vis;

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
    else if(t1.goalsFor != t2.goalsFor) return t1.goalsFor > t2.goalsFor;
    else return t1.goalsDiff > t2.goalsDiff;
}

int main()
{
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

    queue<int> q;
    while(true){
        vector<Team> teams;
        for(int i = 0; i <= nteam; ++i) vis[i] = 0;
        for(auto el : inttos){
            teams.push_back(Team(el.second));
        }
        int pole, choice; 
        cout << nl <<  "1 - Search by round " << nl << nl << "2 - search by date " << nl << nl ; 
        cout << "Enter Your Choice : ";
        cin >> pole ; 
        if(pole == 1){
            cout << "Enter the round number : ";
            cin >> choice; 
            q.push(1);
            vis[1] = 1;
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
        else{
            cout << "Enter the date in the form 'dd/mm/year' : " ;
            string da;
            cin >> da;
            choice = dateToInt(da);
            q.push(1);
            vis[1] = 1;
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
        sort(teams.begin(), teams.end(), srt);
        cout << nl << nl;;
        ll cnt = 1;
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
            cnt++;
        }
        cout << "======================================================================================================================================" << nl << nl;
        teams.clear();
        // q.clear();
    }

    return 0;
}
