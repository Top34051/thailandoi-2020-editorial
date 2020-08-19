#include<bits/stdc++.h>
using namespace std;

const int maxn = 350 + 5;
const int inf = 1e9;

int n, m;
int a[maxn], sum[maxn];
int dp[205][maxn][maxn];

int f(int k, int l, int r) {
	if(l > r) return 0;
	if(k == 0) return inf;
	if(l == r) return 0;
	if(dp[k][l][r] == -1) {
		dp[k][l][r] = inf;
		int bound = (r - l + 1) / k;
		for(int y=1;y<=bound;y++) {
			for(int x=y;x+y<=r-l+1;x++) {
				int left_cost = (sum[l+x-1] - sum[l-1]) * (x-1);
				int right_cost = (sum[r] - sum[r-y]) * (y-1);
				int cost = left_cost + right_cost + x * y * 2;

				dp[k][l][r] = min(dp[k][l][r], f(k-1,l+x,r-y) + cost);
			}
		}
	}
	return dp[k][l][r];
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);

	sort(&a[1], &a[n+1]);
	for(int i=1;i<=n;i++) sum[i] = sum[i-1]+a[i];

	memset(dp,-1,sizeof(dp));
	printf("%d", f(m,1,n));
}