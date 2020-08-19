#include "colorblind.h"
#include<bits/stdc++.h>
using namespace std;

char get_flip(char x, bool flip) {
	if(!flip) return x;
	return x == 'R' ? 'B' : 'R';
}

string investivate_colors(int n) {
	if(n == 1) return "RB";

	int cost = use_device(0, 1);

	string answer = "";

	{
		int x = use_device(0, 2) - cost;
		int y = use_device(1, 2) - cost;

		if(x == 0 && y == 0) answer = "RRR";
		if(x == -2 && y == -2) answer = "RRB";
		if(x == 0 && y == 2) answer = "RBR";
		if(x == 2 && y == 0) answer = "RBB";
	}

	vector<int> sum(2 * n);
	for(int i = 0; i < 3; i++) {
		sum[i] = (i ? sum[i - 1] : 0) + (answer[i] == 'R' ? 1 : -1);
	}

	for(int i = 3; i < 2 * n; i++) {
		bool flip = (answer[i-2] == 'B');
		int pref = !flip ? sum[i-3] : -sum[i-3];

		if(get_flip(answer[i-1], flip) == 'R') {
			if(pref >= 0) answer += get_flip((use_device(i - 1, i) - cost == 0 ? 'R' : 'B'), flip);
			else answer += get_flip((use_device(i - 2, i) - cost == 0 ? 'R' : 'B'), flip);
		}
		else {
			if(pref >= 0) answer += get_flip((use_device(i - 1, i) - cost == 2 ? 'R' : 'B'), flip);
			else answer += get_flip((use_device(i - 2, i) - cost == 0 ? 'R' : 'B'), flip);
		}

		sum[i] = sum[i-1] + (answer[i] == 'R' ? 1 : -1);
	}

	return answer;
}