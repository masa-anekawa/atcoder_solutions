#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 1005;
const int MMAX = 2005;
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


ll N,M,K,A[MMAX],B[MMAX],C[MMAX],D,E;
ll d[NMAX] = {};

string S;
vec v;

ll ans = 0;

void solve(){
  // main algorithm
  Fill(d,INFLL);
  d[1] = 0;
  for (int i = 0; ; ++i)
  {
    bool update = false;
    for (int j = 0; j < M; ++j)
    {
      if (d[A[j]] != INFLL && d[B[j]] > d[A[j]] + C[j])
      {
        update = true;
        d[B[j]] = d[A[j]] + C[j];
        if (i >= N-1 && B[j] == N)
        {
          cout << "inf\n";
          return;
        }else if(i >= 2 * N){
          update = false;
          break;
        }
      }
    }
    if (!update)
    {
      cout << -d[N] << endl;
      return;
    }
  }
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  // printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%lld%lld", &N,&M);
  for (int i = 0; i < M; ++i)
  {
    scanf("%lld%lld%lld", &A[i],&B[i],&C[i]);
    C[i] *= -1;
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}