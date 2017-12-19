#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 8005;
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


ll X,Y;
vec moves[2] = {};
bool dp[2][NMAX] = {};
string S;
vec v;

bool ans = {};

bool check(vec &moves, ll target){
  unordered_map<ll, bool> mp;
  mp[0] = true;
  for (ll m = 0; m < moves.size(); ++m)
  {
    unordered_map<ll, bool> next;
    for(auto&& p : mp) {
      next[p.first + moves[m]] = next[p.first - moves[m]] = true;
    }
    mp = next;
  }
  #ifdef DEBUG
  debug("mp dump:\n");
  for(auto&& p : mp) {
    cout << p.first << " ";
  }
  cout << endl;
  #endif
  return mp[target];
}
void solve(){
  // main algorithm
  ll dir = 0;
  ll cnt = 0;
  bool turned = false;
  for(auto&& ch : S) {
    if (ch == 'F')
    {
      ++cnt;
    }else{
      if(cnt) {
        if(!turned) X -= cnt;
        else moves[dir].push_back(cnt);
      }
      cnt = 0;
      dir = !dir;
      turned = true;
    }
  }
  if(cnt) {
    if(!turned) X -= cnt;
    else moves[dir].push_back(cnt);
  }
  ans = check(moves[0], X) && check(moves[1], Y);
}
void debug(){
  // output debug information
  debug("target: (%lld, %lld)\n", X, Y);
  cout << "X moves:\n";
  for(auto&& i : moves[0]) {
    cout << i << " ";
  }
  cout << endl;
  cout << "Y moves:\n";
  for(auto&& i : moves[1]) {
    cout << i << " ";
  }
  cout << endl;
}
void answer(){
  // output answer
  cout << (ans ? "Yes\n" : "No\n");
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> S >> X >> Y;
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}