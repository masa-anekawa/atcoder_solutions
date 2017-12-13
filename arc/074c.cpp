#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 302;
const int MMAX = 302;
const int KMAX = 1005;
const int MOD  = 1e9 + 7;
using namespace std;

// comment to disable debug functions
// #define DEBUG

// frequently used macros

#define PLUSMOD(a,b) do{(a) = ((a) + (b)) % MOD;}while(0)

#if __cplusplus >= 201103L
#define ALL(v) begin(v),end(v)
#define SORT(v) sort(begin(v), end(v))
#define FIND(v,x) find(begin(v), end(v), (x))
#else
#define ALL(v) (v).begin(),(v).end()
#define SORT(v) sort(v.begin(), v.end())
#define FIND(v,x) find(v.begin(), v.end(), (x))
#endif

#define MEMNEXT(from, to) do{ memmove((to), (from), sizeof(from)); \
memset((from), 0, sizeof(from)); } while(0)
#ifdef DEBUG
#define DUMP(x) do{ std::cerr << "(DUMP) " << (#x) << ": " << x << std::endl; }while(0)
#else
#define DUMP(x) do{}while(0)
#endif

// frequent used aliases
typedef long long ll;
typedef pair<int, int> p;
typedef pair<ll, int> pl;
typedef pair<ll, ll> pll;
typedef vector<int> vec;
typedef vector<ll> vecll;
typedef vector<vec> mat;
typedef vector<vecll> matll;

// frequently used constants
static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

// frequently used structs
struct edge{
  int to,cost;
};

// printf for debug
#ifndef DEBUG
void debug(const char* format, ...){}
#else
void debug(const char* format, ...){
  va_list arg;
  va_start(arg, format);
  vprintf(format, arg);
  va_end(arg);
}
#endif

// dump vector
#ifdef DEBUG
#define DUMPV(v, c) do{       \
  printf("%s: ", #v);         \
  for (int i = 0; i < (c); ++i) \
  {                           \
  cout << (v)[i] << " ";      \
  }                           \
  cout << endl;               \
} while(0)
#else
#define DUMPV(v,c)
#endif

// std::fill of multi dimensions
template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
  std::fill( (T*)array, (T*)(array+N), val );
}

template<typename A>
A MODEQ(A x, A y, int mod = MOD){
  return x = (x + y) % mod;
}

// binary search
ll BSearch(ll _begin, ll _end, bool (*f)(int)){
  ll mid;
  while(_end - _begin > 1LL) {
  mid = (_begin + _end) / 2LL;
  if(f(mid)) {
    debug("BSearch: f(%d) == true\n", mid);
    _end = mid;
  }
  else
  {
    debug("BSearch: f(%d) == false\n", mid);
    _begin = mid;
  }
  }
  return _end;
}





int N,M,K,L[MMAX], R[MMAX],X[MMAX],D,E;
int dp[NMAX][NMAX][NMAX] = {};
map<int, vector<p> > mp;

ll ans = 0LL;

inline bool check(int i, int j, int k){
  int arr[] = {i, j, k}; sort(arr, arr + 3);
  int mx = arr[2], md = arr[1], mn = arr[0];
  if(!mp.count(mx)) return true;
  for (auto&& p : mp[mx])
  {
    int l = p.first;
    switch(p.second){
      case 1:
      if(md >= l) return false;
      break;
      case 2:
      if(mn >= l || md < l) return false;
      break;
      case 3:
      if(mn < l) return false;
      break;
    }
  }
  return true;
}
void solve(){
  dp[0][0][0] = 1;
  for (int k = 0; k <= N; ++k)
    for (int i = 0; i <= k; ++i)
      for (int j = i; j <= k; ++j)
        if (dp[k][i][j])
        {
          if(!check(i,j,k)) dp[k][i][j] = 0;
          PLUSMOD(dp[k+1][i][j], dp[k][i][j]);
          PLUSMOD(dp[k+1][j][k], dp[k][i][j]);
          PLUSMOD(dp[k+1][i][k], dp[k][i][j]);
        }
}
void debug(){
  // output debug information
  cout << "dp;\n";
  for (int i = 0; i < N+1; ++i)
  {
    cout << "i = " << i << "\n";
    for (int j = 0; j < N+1; ++j)
    {
      for (int k = 0; k < N+1; ++k)
      {
        cout << dp[i][j][k] << " ";
      }
      cout << endl;
    }
  }
}
void answer(){
  // output answer
  for (int i = 0; i < N + 1; ++i)
    for (int j = i; j < N + 1; ++j)
      PLUSMOD(ans, dp[N][i][j]);

  cout << ans << endl;
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%d%d", &N,&M);
  for (int i = 0; i < M; ++i)
  {
    scanf("%d%d%d", &L[i], &R[i], &X[i]);
    mp[R[i]].push_back(p(L[i], X[i]));
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}