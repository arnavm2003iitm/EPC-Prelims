#include <bits/stdc++.h>

using namespace std;

const int MX = 42;

char s[MX];
int cnt[10];

int main() {
	int T;
	ignore = scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		ignore = scanf("%s", s);
		
		int n = strlen(s);
		fill(cnt, cnt + 10, 0);
		for (int i = 0; i < n; i++) {
			cnt[s[i] - '0']++;
		}
		
		long long ans;
		if (n % 2 == 1) {
			long long x = 0, y = 0;
			for (int i = 0; i < (n + 1) / 2; i++) {
				int j = (i == 0 ? 1 : 0);
				while (cnt[j] == 0) j++;
				
				x = 10 * x + j;
				cnt[j]--;
			}
			
			for (int d = 9; d >= 0; d--) {
				for (int i = 0; i < cnt[d]; i++) {
					y = 10 * y + d;
				}
			}
			
			ans = x - y;
		}
		else {
			ans = 1LL << 60;
			
			auto solveOne = [&ans](int start) {
				for (int a = start; a < 10; a++)
					for (int b = start; b < a; b++) {
						if (cnt[a] == 0) continue;
						if (cnt[b] == 0) continue;
						
						vector<int> ccnt(cnt, cnt + 10);
						
						ccnt[a]--;
						ccnt[b]--;
						
						int m = accumulate(ccnt.begin(), ccnt.end(), 0);
						
						long long x = a, y = b;
						for (int i = 0; i < m; i += 2) {
							int dx = 0;
							while (ccnt[dx] == 0) dx++;
							
							int dy = 9;
							while (ccnt[dy] == 0) dy--;
							
							ccnt[dx]--;
							ccnt[dy]--;
							
							x = 10 * x + dx;
							y = 10 * y + dy;
						}
						
						ans = min(ans, x - y);
					}
			};
			
			function<void(int, int, bool)> brute = [&solveOne, &brute](int d, int start, bool need) {
				if (d == 10) {
					if (need == false) solveOne(start);
					return;
				}
				
				int cc = cnt[d];
				
				for (int x = cc; x >= 0; x -= 2) {
					cnt[d] = x;
					
					brute(d + 1, start, need);
					
					start = 0;
					need = false;
				}
				
				cnt[d] = cc;
			};
			
			bool ok = true;
			for (int d = 0; d < 10; d++)
				if (cnt[d] % 2 == 1)
					ok = false;
			
			if (ok) {
				ans = 0;
			}
			else {
				int cc = cnt[0];
				
				for (int x = cc; x >= 0; x -= 2) {
					cnt[0] = x;
					
					brute(1, 1, x < cc);
				}
			}
		}
		
		printf("Case #%d: %lld\n", t, ans);
	}
	
	return 0;
}
