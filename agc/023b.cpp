#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 305;
const int MMAX = 305;
const int KMAX = 1005;
const int MOD  = 1e9 + 7;
using namespace std;

// comment to disable debug functions
// #define DEBUG

// frequently used macros

#if __cplusplus >= 201103L
#define ALL(v) begin(v),end(v)
#define SORT(v) sort(begin(v), end(v))
#define FIND(v,x) find(begin(v), end(v), (x))
#else
#define ALL(v) (v).begin(),(v).end()
#define SORT(v) sort(v.begin(), v.end())
#define FIND(v,x) find(v.begin(), v.end(), (x))
#endif

#define fi first
#define se second

#define MEMNEXT(from, to) do{ memmove((to), (from), sizeof(from)); \
memset((from), 0, sizeof(from)); } while(0)
#ifdef DEBUG
#define DUMP(x) do{ std::cerr << (#x) << ": " << x << std::endl; }while(0)
#else
#define DUMP(x) do{}while(0)
#endif

// frequent used aliases
typedef long long ll;
typedef pair<int, int> p;
typedef pair<ll, int> lp;
typedef pair<ll, ll> llp;
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

// binary search
ll BSearch(ll ok, ll ng, bool (*f)(ll)){
  ll mid;
  while(abs(ok - ng) > 1LL) {
    mid =  (ok + ng) / 2LL;
    if(f(mid)) {
      debug("BSearch: f(%d) == true\n", mid);
      ok = mid;
    }
    else
    {
      debug("BSearch: f(%d) == false\n", mid);
      ng = mid;
    }
  }
  return ok;
}

ll NUM_TEST_CASE = 1;

ll N,M,K,A,B,C,D,E;
char dat[2 * NMAX][2 * MMAX] = {};

string S;
vec v;

ll ans = {};

bool check(int a, int b){
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      if (dat[a + i][b + j] != dat[a + j][b + i])
      {
        debug("(%d, %d) false(a: %d, b: %d)\n", i, j, a, b);
        return false;
      }
    }
  }
  return true;
}

void solve(){
  // main algorithm
  if(check(0, 0)) ans += N;
  for (int a = 1; a < N; ++a)
  {
    if(check(0, a)) ans += N - a;
    if(check(a, 0)) ans += N - a;
  }
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << ans << endl;
}
void init(){
  // initialize for each test case
  // Fill(dp, -1);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // cin >> NUM_TEST_CASE;

  for (int test_case = 0; test_case < NUM_TEST_CASE; ++test_case)
  {
    init();

    cin >> N;
    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < N; ++j)
      {
        scanf(" %c", &dat[i][j]);
        dat[i + N][j] = dat[i][j + N] = dat[i + N][j + N] = dat[i][j];
      }
    }
    solve();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}