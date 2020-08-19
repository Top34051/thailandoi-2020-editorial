#include "castle.h"
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

int n, m, q, know;
vector<int> U, V;
vector<int> way[maxn], children[maxn];

vector<int> special;
bool is_special[maxn], destroyed[maxn];

int head[maxn], depth[maxn];
int new_color, color[maxn];

int findhead(int x) {
	if(x == head[x]) return x;
	return head[x] = findhead(head[x]);
}

void dfs(int u, int last) {
	depth[u] = depth[last] + 1;
	for(auto v : way[u]) {
		if(v == last) continue;
		dfs(v, u);
		children[u].push_back(v);
	}
}

void coloring(int u) {
  	for(auto v : children[u]) {
  		if(color[u] == color[v]) coloring(v); 
  	}
	color[u] = new_color;
}

void cut(int id) {
	destroyed[id] = true;
	if(is_special[id]) return ;
	int u = U[id], v = V[id];
	new_color += 1;
	if(depth[u] > depth[v]) coloring(u);
	else coloring(v);
}

bool can_reach(int x, int y) {
	// build dsu
	for(auto i : special) {
		if(destroyed[i]) continue;
		int u = color[U[i]], v = color[V[i]];
		head[findhead(u)] = findhead(v);
	}
	bool answer = findhead(x) == findhead(y);
	// reset dsu
	for(auto i : special) {
		int u = color[U[i]], v = color[V[i]];
		head[u] = u; head[v] = v;
	}
	return answer;
}

int main() {
	castle_init(n, m, q, know);
	castle_read_map(U, V);
	for(int i = 0; i < n; i++) head[i] = i;
	for(int i = 0; i < m; i++) {
		int u = U[i], v = V[i];
		// special edge
		if(findhead(u) == findhead(v)) {
			special.push_back(i);
			is_special[i] = true;
		}
		// normal edge
		else {
			head[findhead(u)] = findhead(v);
			way[u].push_back(v); way[v].push_back(u);
		}
	}

	dfs(0, -1);

	for(int i = 0; i < n; i++) head[i] = i;
	while(q--) {
		int type, x, y;
		castle_read_event(type, x, y);
		
		if(type == 1) cut(x);
		else {
			int u = color[x], v = color[y];
			castle_answer(can_reach(u, v));
		}
	}
	return 0;
}