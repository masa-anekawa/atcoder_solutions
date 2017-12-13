#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 105;
const int MMAX = 105;
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
  int to,cap,rev;
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


int N,M,K,A,B,C,D,E;
char dat[NMAX][MMAX] = {};
std::vector<edge> G[NMAX + MMAX];
p S, T;
const int S_id = 201;
const int T_id = 202;

std::vector<p> L;
bool used[NMAX + MMAX] = {};

ll ans = 0;

inline void add_edge(int i, int j){
  G[i].push_back(edge{j, 1, (int)G[j].size()});
  G[j].push_back(edge{i, 1, (int)G[i].size()-1});
}

int dfs(int v, int t, int c){
  debug("dfs(%d, %d, %d)\n", v, t, c);
  if(v == t) return c;
  used[v] = true;
  for(auto&& e : G[v]) {
    if (!used[e.to] && e.cap > 0)
    {
      int d = dfs(e.to, t, min(c, e.cap));
      if(!d) continue;
      e.cap -= d;
      G[e.to][e.rev].cap += d;
      return d;
    }
  }
  return 0;
}

int max_flow(int s, int t){
  int flow = 0;
  while(1) {
    Fill(used, false);
    int f = dfs(s, t, INF);
    if(!f) return flow;
    flow += f;
    debug("flow += 1\n");
  }
}

void solve(){
  // main algorithm
  if (S.first == T.first || S.second == T.second)
  {
    ans = -1LL;
    return;
  }

  // for (int i = 0; i < L.size(); ++i)
  // {
  //   if (L[i].first == S.first || L[i].second == S.second)
  //     add_edge(i, S_id);
  //   if (L[i].first == T.first || L[i].second == T.second)
  //     add_edge(i, T_id);
  //   for (int j = i + 1; j < L.size(); ++j)
  //     if (L[i].first == L[j].first || L[i].second == L[j].second)
  //       add_edge(i, j);
  // }

  G[S_id].push_back(edge{S.first, INF, (int)G[S.first].size()});
  G[S.first].push_back(edge{S_id, 0, (int)G[S_id].size() - 1});
  G[S_id].push_back(edge{S.second + N, INF, (int)G[S.second + N].size()});
  G[S.second + N].push_back(edge{S_id, 0, (int)G[S_id].size() - 1});

  G[T_id].push_back(edge{T.first, 0, (int)G[T.first].size()});
  G[T.first].push_back(edge{T_id, INF, (int)G[T_id].size() - 1});
  G[T_id].push_back(edge{T.second + N, 0, (int)G[T.second + N].size()});
  G[T.second + N].push_back(edge{T_id, INF, (int)G[T_id].size() - 1});

  for(auto&& p : L) {
    G[p.first].push_back(edge{p.second + N, 1, (int)G[p.second + N].size()});
    G[p.second + N].push_back(edge{p.first, 1, (int)G[p.first].size() - 1});
  }

  ans = max_flow(S_id, T_id);
}
void debug(){
  // output debug information
  cout << "G:\n";
  for(int i = 1; i <= N + M; ++i)
    for(auto&& e : G[i]) {
      debug("%d -> %d : %d, rev: %d\n", i, e.to, e.cap, e.rev);
    }
  cout << "S:\n";
  for(auto&& e : G[S_id]) {
    debug("%d -> %d : %d, rev: %d\n", S_id, e.to, e.cap, e.rev);
  }
  cout << "T:\n";
  for(auto&& e : G[T_id]) {
    debug("%d -> %d : %d, rev: %d\n", T_id, e.to, e.cap, e.rev);
  }
}
void answer(){
  // output answer
  printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%d%d", &N,&M);
  for (int i = 1; i <= N; ++i)
  {
    for (int j = 1; j <= M ; ++j)
    {
      scanf(" %c", &dat[i][j]);
      switch(dat[i][j]){
        case 'S':
        S = p(i, j);
        break;
        case 'T':
        T = p(i, j);
        break;
        case 'o':
        L.push_back(p(i, j));
        break;
        case '.':
        break;
        default:
        cerr << "input error\n";
        exit(1);
        break;
      }
    }
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}