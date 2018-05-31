#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 105;
const int MMAX = 100005;
const int KMAX = 1005;
const int MOD  = 1e9 + 7;
using namespace std;

// comment to disable debug functions
#define DEBUG

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
ll BSearch(ll _begin, ll _end, bool (*f)(ll)){
  ll mid;
  while(_end - _begin > 1LL) {
  mid = _begin + (_end - _begin) / 2LL;
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

ll NUM_TEST_CASE = 1;

ll N,M,K,A,B,C,D,E;
int dp[NMAX] = {};
ll W,H;
string S;
vec v;
bool isWhiteBigger = false;
char ans[NMAX][NMAX] = {};

void draw(bool isWhite, int num, int col_offset){
  int jj;
  for (int i = 0; i < num; ++i)
  {
    jj = col_offset + (i % 2 ? 1 : 2);
    ans[i + 1][jj] = (isWhite ? '.' : '#');
  }
}
void solve(){
  // main algorithm
  int col_A = (A - 1 + 97) / 98;
  int col_B = (B - 1 + 97) / 98;
  W = 3 * (col_A + col_B) + 2;
  H = 100;
  if (W > 100)
  {
    cerr << "fail!" << endl;
    exit(1);
  }
  int W_A = 3 * col_B + 1;
  for (int i = 0; i < 100; ++i)
  {
    for (int j = 0; j < W; ++j)
    {
      ans[i][j] = (j < W_A ? '.' : '#');
    }
  }
  for(int i = 0; i < col_B; ++i) draw(false, min<int>(98, B-1 - 98*i), 3 * i);
  for(int i = 0; i < col_A; ++i) draw(true,  min<int>(98, A-1 - 98*i), 3 * i + W_A);
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << H << " " << W << endl;
  for (int i = 0; i < H; ++i)
  {
    for (int j = 0; j < W; ++j)
    {
      printf("%c", ans[i][j]);
    }
    printf("\n");
  }
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

    cin >> A >> B;
    solve();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}