#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 100005;
const int MMAX = 100005;
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

struct node
{
  int next[2];
  node(){
    next[0] = next[1] = -1;
  }
};
ll N,M,K,L;
node G[NMAX];
node *root = &G[0];

string S[NMAX];
map<ll, bool> mp;
vector<ll> ranks; // ranks of each tree of the forest
bool ans = {}; // true ans means Alice losing
vec lens; // vector of lengths of S
int lensSum[NMAX] = {};

void dfs(int nodeID, node &nd, int depth){
  assert((ll)nd.next[0] * nd.next[1] != 0);
  assert(nd.next[0] < NMAX);
  assert(nd.next[1] < NMAX);
  debug("dfs(%d, (%d, %d), %d) called\n",
    nodeID, nd.next[0], nd.next[1], depth);

  if((ll)nd.next[0] * nd.next[1] < 0){
    ranks.push_back(L - depth);
  }
  if(nd.next[0] > 0) dfs(nd.next[0], G[nd.next[0]], depth + 1);
  if(nd.next[1] > 0) dfs(nd.next[1], G[nd.next[1]], depth + 1);
}
ll calcGrundy(ll rank){
  assert(rank > 0);
  return rank & -rank;
  // for (int i = 0; ; ++i)
  //   if((1 << i) & rank) return 1LL << i;
}
void solve(){
  // main algorithm
  // make_tree
  debug("lens: ");
  for (int i = 0; i < N; ++i)
  {
    lensSum[i+1] = lensSum[i] + lens[i];
    debug("%d ", lensSum[i+1]);
  }
  debug("\n");
  int sumLength = lensSum[N];
  int nodeID = 1;
  for (int s_i = 0; s_i < N; ++s_i)
  {
    node *nd = root;
    for (; nodeID <= lensSum[s_i + 1]; ++nodeID)
    {
      int i = nodeID - 1 - lensSum[s_i];
      int &next = nd->next[(int)(S[s_i][i] - '0')];
      if(next == -1){
        next = nodeID;
      }
      nd = &G[next];
    }
  }
  assert(nodeID == lensSum[N] + 1);
  // calc forest_leaves
  dfs(0, *root, 0);
  // calc nim

  debug("ranks:\n");
  for(auto&& d : ranks) {
    debug("%d ", d);
  }
  debug("\n");

  ll grundy = 0LL;
  for(auto&& d : ranks) {
    grundy ^= calcGrundy(d);
  }
  ans = grundy == 0LL;
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << (ans ? "Bob" : "Alice") << endl;
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> N >> L;
  for (int i = 0; i < N; ++i)
  {
    cin >> S[i];
    lens.push_back(S[i].size());
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}