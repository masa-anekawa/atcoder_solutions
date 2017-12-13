#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 55;
const int MMAX = 55;
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


ll N,M,K,A,B,C,D,E;
int G[NMAX][NMAX] = {};
p edges[MMAX];
ll ans = {};

bool hasPath(int a, int b){
  bool used[NMAX] = {};
  queue<int> que;
  que.push(a);
  while(!que.empty()){
    int i = que.front();
    que.pop();
    if(used[i]) continue;
    debug("%d ", i);
    used[i] = true;
    for (int j = 1; j <= N; ++j)
    {
      if(G[i][j] == 1 && !used[j]){
        if(j == b) return true;
        else que.push(j);
      }
    }
  }
  return false;
}
void solve(){
  // main algorithm
  for (int i = 0; i < M; ++i)
  {
    int a = edges[i].first, b = edges[i].second;
    G[a][b] = G[b][a] = 0;
    if(!hasPath(a, b)){
      debug("\nPath %d <-> %d is a bridge\n", a, b);
      ans++;
    }else{
      debug("\nPath %d <-> %d is not a bridge\n", a, b);
    }
    G[a][b] = G[b][a] = 1;
  }
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << ans << endl;
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> N >> M;
  for (int i = 0; i < M ; ++i)
  {
    int a,b;
    scanf("%d%d", &a, &b);
    G[a][b] = G[b][a] = 1;
    edges[i] = p{a, b};
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}