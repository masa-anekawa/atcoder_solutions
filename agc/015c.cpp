#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 2005;
const int MMAX = 2005;
const int QMAX = 200005;
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


ll N,M,K,E,Q;
int A[QMAX],B[QMAX],C[QMAX],D[QMAX];
int dat[NMAX][MMAX] = {};
int blues[NMAX][MMAX] = {};
int v_connects[NMAX][MMAX] = {};
int h_connects[NMAX][MMAX] = {};

string S;
vec v;

ll ans[QMAX] = {};

void solve(){
  // main algorithm
  // fill sum tables
  for (int i = 1; i <= N; ++i)
  {
    for (int j = 1; j <= M; ++j)
    {
      blues[i][j] = blues[i][j-1] + blues[i-1][j] - blues[i-1][j-1]
        + dat[i][j];
      v_connects[i][j] = v_connects[i-1][j]
        + v_connects[i][j-1] - v_connects[i-1][j-1]
        + (dat[i-1][j] && dat[i-1][j] == dat[i][j]);
      h_connects[i][j] = h_connects[i-1][j]
        + h_connects[i][j-1] - h_connects[i-1][j-1]
        + (dat[i][j-1] && dat[i][j-1] == dat[i][j]);
    }
  }

  // query
  for (int i = 0; i < Q; ++i)
  {
    int a = A[i], b = B[i], c = C[i], d = D[i];
    int blue,vc,hc;
    blue = blues[c][d]
      - blues[c][b-1] - blues[a-1][d] + blues[a-1][b-1];
    if(c - a < 1) vc = 0;
    else vc = v_connects[c][d]
      - v_connects[c][b-1] - v_connects[a][d] + v_connects[a][b-1];
    if(d - b < 1) hc = 0;
    else hc = h_connects[c][d]
      - h_connects[c][b] - h_connects[a-1][d] + h_connects[a-1][b];
    DUMP(blue);
    DUMP(vc);
    DUMP(hc);
    ans[i] = blue - vc - hc;
  }
}
void debug(){
  // output debug information
  cout << "dat:\n";
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      cout << dat[i+1][j+1] << " ";
    }
    cout << endl;
  }
  cout << "blues:\n";
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      cout << blues[i+1][j+1] << " ";
    }
    cout << endl;
  }
  cout << "v_connects:\n";
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      cout << v_connects[i+1][j+1] << " ";
    }
    cout << endl;
  }
  cout << "h_connects:\n";
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      cout << h_connects[i+1][j+1] << " ";
    }
    cout << endl;
  }
}
void answer(){
  // output answer
  for(int i=0; i < Q; ++i) printf("%lld\n", ans[i]);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%lld%lld%lld", &N,&M,&Q);
  for (int i = 0; i < N ; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      char ch;
      scanf(" %c", &ch);
      dat[i+1][j+1] = ch - '0';
    }
  }
  for (int i = 0; i < Q; ++i)
  {
    scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}