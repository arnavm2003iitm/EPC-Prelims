#include <bits/stdc++.h>
using namespace std;

template<typename F, typename S>
ostream& operator <<(ostream& ostream, pair<F, S>& p) {
	cout << p.first << " " << p.second;
	return ostream;
}

template<typename T>
ostream& operator <<(ostream& ostream, vector<T>& v) {
	for(auto& element : v) {
		cout << element << " ";
	}
	return ostream;
}

template<typename T>
ostream& operator <<(ostream& ostream, vector<vector<T>>& v) {
	for(auto& row : v) {
		for(auto& cell : row) {
			cout << cell << " ";
		}
		cout << "\n";
	}
	return ostream;
}

template<typename F, typename S>
istream& operator >>(istream& istream, pair<F, S>& p) {
	cin >> p.first >> p.second;
	return istream;
}

template<typename T>
istream& operator >>(istream& istream, vector<T>& v) {
	for(auto& element : v) {
		cin >> element;
	}
	return istream;
}

using big = long long;
using ludo = long double;
using pii = pair<int, int>;
using pbb = pair<long long, long long>;
#define fe first
#define se second
#define fr(i, s, e) for(int i = s; i < e; i++)
#define revfr(i, s, e) for(int i = s - 1; i >= e; i--)
#define nl "\n"

constexpr int mod = 1000000009;
// const big mod = 998244353;
const big infinity = 1000000000000000000;
const int inf = 1e9 + 5;


// make mod constexpr if not variable mod
// int MOD = mod;
template<int MOD = mod>
struct Mint {
	int value;
	// static const int MOD_value = MOD;

	Mint(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
	Mint(long long a, long long b) : value(0){ *this += a; *this /= b;}

	Mint& operator+=(Mint const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
	Mint& operator-=(Mint const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
	Mint& operator*=(Mint const& b) {value = (long long)value * b.value % MOD;return *this;}

	Mint mexp(Mint a, long long e) {
		Mint res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
		return res;
	}
	
	Mint inverse(Mint a) { return mexp(a, MOD - 2); }

	Mint& operator/=(Mint const& b) { return *this *= inverse(b); }
	friend Mint operator+(Mint a, Mint const b) { return a += b; }
	friend Mint operator-(Mint a, Mint const b) { return a -= b; }
	friend Mint operator-(Mint const a) { return 0 - a; }
	friend Mint operator*(Mint a, Mint const b) { return a *= b; }
	friend Mint operator/(Mint a, Mint const b) { return a /= b; }
	friend std::istream& operator>>(std::istream& istream, Mint& a) {long long v; istream >> v; a = v; return istream;}
	friend std::ostream& operator<<(std::ostream& ostream, Mint const& a) {return ostream << a.value;}
	friend bool operator==(Mint const& a, Mint const& b) {return a.value == b.value;}
	friend bool operator!=(Mint const& a, Mint const& b) {return a.value != b.value;}
};

using mint = Mint<mod>;


void kmp(vector<int>& v, string s, int len) {

	fr(i, 1, len) {

		int j = v[i - 1];

		while(j > 0 && s[i] != s[j]) {

			j = v[j - 1];
		}

		if(s[i] == s[j]) {

			j++;
		}
		
		v[i] = j;
	}
}


void solve() {
	int n;
	cin >> n;

	string s;
	cin >> s;

	string ans = s;
	reverse(ans.begin(), ans.end());

	string aux = ans + "#" + s;
	int L = aux.length();
	vector<int> pi(L, 0);

	kmp(pi, aux, L);

	int ansn = n;
	int lsuf = pi[L - 1];


	vector<mint> fhash(n, 0), rhash(n, 0);
	mint cry = 1;
	mint p = 31;
	fhash[0] = (s[0] - 'a' + 1);

	fr(i, 1, n) {
		cry *= p;
		fhash[i] = fhash[i - 1] + (s[i] - 'a' + 1) * cry;
	}

	cry = 1;
	rhash[n - 1] = (s[n - 1] - 'a' + 1);

	revfr(i, n - 1, 0) {
		cry *= p;
		rhash[i] = rhash[i + 1] + (s[i] - 'a' + 1) * cry;
	}

	auto isPal = [&](int l, int r) {
		mint F = fhash[r];
		if(l > 0) F -= fhash[l - 1];

		mint R = rhash[l];
		if(r < n - 1) R -= rhash[r + 1];

		int offset = n - 1 - r;
		F *= F.mexp(p, offset);

		return (F.value == R.value);
	};

	while(lsuf > 0) {
		if(lsuf == n) {
			lsuf = pi[lsuf - 1];
			continue;
		}

		int rem = n - lsuf;

		if(isPal(0, rem - 1)) {
			ansn = min(ansn, rem);
		}

		lsuf = pi[lsuf - 1];
	}

	ans = "";

	fr(i, 0, ansn) ans += s[i];
	reverse(ans.begin(), ans.end());
	cout << ans << nl;
}


int main() {
	
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	// FAST I/O

	int TC = 1;
	cin >> TC;

	for(int tc = 1; tc <= TC; tc++) {

		cout << "Case #" << tc << ": ";
		solve();
	}

	return 0;
}
