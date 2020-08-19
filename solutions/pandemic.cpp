#include "pandelib.h"
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

int n, k, lim, m;
vector<int> seq[5];

int person;
vector<int> meet[maxn][5];

assignment_t assignments[5][maxn];
bool results[maxn], vis[maxn];

bool bad[maxn];

void gen(int day, vector<int> has) {
    if(day == 5) {
        if(person < n) {
            // meet[person][i] is the set of volunteers that person meets in day i
            for(int i = 1; i <= 4; i++) {
                meet[person][i] = seq[i];
                for(auto x : seq[i]) assignments[i][x].push_back(person);
            }
            person++;
        }
        return ;
    }
    
    // choose 0
    seq[day].clear();
    gen(day + 1, has);

    // choose 1
    for(auto x : has) {
        seq[day].clear(); seq[day].push_back(x);
        vector<int> nxt;
        for(auto t : has) if(t != x) nxt.push_back(t);
        gen(day + 1, nxt);
    }
    
    // choose 2 if L >= 2
    if(lim >= 2) {
        for(auto x : has) {
            for(auto y : has) {
                if(x >= y) continue;
                seq[day].clear(); seq[day].push_back(x); seq[day].push_back(y);
                vector<int> nxt;
                for(auto t : has) if(t != x && t != y) nxt.push_back(t);
                gen(day + 1, nxt);
            }
        }
    }
}

int main() {
    pandemic_init(n, k, lim);

    lim = min(lim, 2);

    if(lim == 1) m = 19;
    else m = 8;

    vector<int> vec;
    for(int i = 0; i < m; i++) vec.push_back(i);
    gen(1, vec);

    for(int day = 1; day <= 4; day++) pandemic_assign(assignments[day], results);
    for(int day = 5; day <= 30; day++) pandemic_assign(assignments[0], results);

    for(int day = 31; day <= 34; day++) {
        pandemic_assign(assignments[0], results);
        vector<int> infected;
        for(int i = 0; i < m; i++) {
            if(results[i] && !vis[i]) {
                vis[i] = 1;
                infected.push_back(i);
            }
        }

        for(int x = 0; x < n; x++) {
            if(meet[x][day - 30] != infected) bad[x] = 1;
        }
    }

    int ans = -1;
    for(int x = 0; x < n; x++) if(!bad[x]) ans = x;

    pandemic_answer(ans);
}