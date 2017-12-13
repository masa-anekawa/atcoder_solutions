#include <bits/stdc++.h>

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 5005;
const int KMAX = 5005;
const int MOD  = 1e9 + 7;
using namespace std;

// comment to disable debug functions
// #define DEBUG


// frequently used macros
#define SORT(v) sort(begin(v), end(v))
#define FIND(v,x) find(begin(v), end(v), (x))
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
typedef pair<ll, int> lp;
typedef pair<ll, ll> llp;
typedef vector<int> vec;
typedef vector<vec> mat;

// frequently used constants
static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

// freawuently used structs
struct edge{
  int to,cost;
};

// printf for debug
void debug(const char* format, ...){
  #ifndef DEBUG
  return;
  #else
  va_list arg;
  va_start(arg, format);
  vprintf(format, arg);
  va_end(arg);
  #endif
}

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

// fill of multi dimensions
template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
  std::fill( (T*)array, (T*)(array+N), val );
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


int N,M,K,A[NMAX],B,D,E;
bool dp[NMAX][KMAX] = {};

string S;
vec v;

ll ans = 0;

bool C(int x){
  debug("x == %d, A[x] == %d\n", x, A[x]);
  Fill(dp, false);
  dp[0][0] = true;
  for (int i = 1; i <= N; ++i)
  {
  for (int j = 0; j < K; ++j)
  {
    if (!dp[i-1][j]) continue;

    dp[i][j] = true;
    if(i != x) dp[i][min(j + A[i], K)] = true;

    if (j >= K - A[x]
    || (i != x && j + A[i] >= K - A[x] && j + A[i] < K))
      return true;
  }
  DUMPV(dp[i], K);
  }
  return false;
}

void solve(){
  // main algorithm
  sort(A+1, A+1+N);
  DUMPV(A, N+1);
  ans = BSearch(0, N + 1, C) - 1LL;
}
void debug(){
  // output debug information
}
void answer(){
  // output answer
  printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%lld%lld", &N,&K);
  for (int i = 1; i <= N; ++i)
  {
      scanf("%lld", &A[i]);
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}