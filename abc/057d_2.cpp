#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 52;
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


int N,M,K,A,B,C,D,E;
ll V[NMAX];

map<ll, int, greater<ll> > mp;
double ans = 0;
ll ans_c = 0;
ll sum = 0;
int cnt = 0;

ll comb[51][51] = {};

void solve(){
  // main algorithm
  // fill pascal's triangle
  for (int i = 0; i < 51; ++i)
  {
    for (int j = 0; j <= i; ++j)
    {
      if(j == 0 || j == i) comb[i][j] = 1;
      else comb[i][j] = comb[i-1][j-1]  + comb[i-1][j];
    }
  }

  for (auto ite = mp.begin(); ite != mp.end(); ++ite)
  {
    if (A > ite->second)
    {
      A -= ite->second;
      B -= ite->second;
      sum += ite->first * ite->second;
      cnt += ite->second;
      continue;
    }else if(A == ite->second){
      sum += ite->first * ite->second;
      cnt += ite->second;
      ans = (double)sum / cnt;
      ans_c = 1;
      break;;
    }

    // A < ite->second
    if(cnt == 0) {
      ans = ite->first;
      for(int num = A; num <= B && num <= ite->second; num++)
        ans_c += comb[ite->second][num];
    }
    else {
      sum += ite->first * A;
      cnt += A;
      ans = (double)sum / cnt;
      ans_c = comb[ite->second][A];
    }
    break;
  }
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  printf("%.6lf\n", ans);
  cout << ans_c << endl;
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> N >> A >> B;
  for (int i = 0; i < N; ++i)
  {
    scanf("%lld", &V[i]);
    mp[V[i]]++;
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}