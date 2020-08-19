#include<bits/stdc++.h>
using namespace std;

const int maxn = 1.5e3 + 5;
const int inf = 2e9;

int n,m;
int a[maxn][maxn];
int d1[maxn][maxn], d2[maxn][maxn], d3[maxn][maxn], d4[maxn][maxn];

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]);

	// upper left
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(i == 1 && j == 1) d1[i][j] = 0;
			else d1[i][j] = inf;
			if(i > 1) d1[i][j] = min(d1[i][j], d1[i-1][j] + a[i-1][j]);
			if(j > 1) d1[i][j] = min(d1[i][j], d1[i][j-1] + a[i][j-1]);
		}
	}
	
	// upper right
	for(int i=1;i<=n;i++) {
		for(int j=m;j>=1;j--) {
			if(i == 1 && j == m) d2[i][j] = 0;
			else d2[i][j] = inf;
			if(i > 1) d2[i][j] = min(d2[i][j], d2[i-1][j] + a[i-1][j]);
			if(j < m) d2[i][j] = min(d2[i][j], d2[i][j+1] + a[i][j+1]);
		}
	}

	// lower left
	for(int i=n;i>=1;i--) {
		for(int j=1;j<=m;j++) {
			if(i == n && j == 1) d3[i][j] = 0;
			else d3[i][j] = inf;
			if(i < n) d3[i][j] = min(d3[i][j], d3[i+1][j] + a[i+1][j]);
			if(j > 1) d3[i][j] = min(d3[i][j], d3[i][j-1] + a[i][j-1]);
		}
	}

	// lower right
	for(int i=n;i>=1;i--) {
		for(int j=m;j>=1;j--) {
			if(i == n && j == m) d4[i][j] = 0;
			else d4[i][j] = inf;
			if(i < n) d4[i][j] = min(d4[i][j], d4[i+1][j] + a[i+1][j]);
			if(j < m) d4[i][j] = min(d4[i][j], d4[i][j+1] + a[i][j+1]);
		}
	}

	int ans = inf;

	// horizontal
	for(int x=1;x<=n;x++) {
		int best = inf;
		for(int y=1,sum=0;y<=m;y++) {
			best = min(best, d1[x][y] + d3[x][y] - sum);
			sum += a[x][y];
			ans = min(ans, best + d2[x][y] + d4[x][y] + sum);
		}
	}

	// vertical
	for(int y=1;y<=m;y++) {
		int best = inf;
		for(int x=1,sum=0;x<=n;x++) {
			best = min(best, d1[x][y] + d2[x][y] - sum);
			sum += a[x][y];
			ans = min(ans, best + d3[x][y] + d4[x][y] + sum);
		}
	}

	printf("%d",ans);
}