#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 5e18;
const int NMAX = 55;
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


ll N,M,K,A[NMAX],B[NMAX],C,D,E;
int dp[NMAX] = {};

string S;
vec v;
int sum[NMAX][NMAX] = {};
ll ans = {};

int count_inside(ll x1, ll x2, ll y1, ll y2){
  int ret = 0;
  for (int k = 0; k < N; ++k)
  {
   if(A[k] >= x1 && A[k] <= x2 && B[k] >= y1 && B[k] <= y2)
    ret++;
}
return ret;
}
inline ll calc_area(ll x1, ll x2, ll y1, ll y2){
  return (x2 - x1)*(y2 - y1);
}
void solve(){
  // main algorithm
  ans = INFLL;
  for (int i = 0; i < N; ++i)
  {
    for (int j = i ; j < N; ++j)
    {
      for (int k = j; k < N; ++k)
      {
        for (int l = k; l < N ; ++l)
        {
          ll x1 = min(min(A[i], A[j]), min(A[k], A[l])),
          x2 = max(max(A[i], A[j]), max(A[k], A[l])),
          y1 = min(min(B[i], B[j]), min(B[k], B[l])),
          y2 = max(max(B[i], B[j]), max(B[k], B[l]));
          debug("count_inside(%d, %d, %d, %d) = %d\n", i, j, k, l, count_inside(x1, x2, y1, y2));
          if(count_inside(x1, x2, y1, y2) >= K){
            ll area = calc_area(x1, x2, y1, y2);
            debug("area(%d, %d, %d, %d) = %lld\n", i, j, k, l, area);
            if(area < ans) ans = area;
          }
        }
      }
    }
  }
}
void solve2(){
  // calc sum 2dim
  map<ll, int> ord_x, ord_y;
  for (int i = 0; i < N; ++i)
  {
    ord_x.insert(lp{A[i], 0});
    ord_y.insert(lp{B[i], 0});
  }
  int order = 0;
  for(auto&& p : ord_x) {
    p.second = order;
    ++order;
  }
  order = 0;
  for(auto&& p : ord_y) {
    p.second = order;
    ++order;
  }
  for (int i = 0; i < N; ++i)
  {
    sum[ord_x[A[i]] + 1][ord_y[B[i]] + 1]++; // 番兵法
  }

  #ifdef DEBUG
  debug("DEPLOYMENT:\n");
  for (int y = N; y > 0; --y)
  {
    for (int x = 1; x <= N; ++x)
    {
      printf("%c", sum[x][y] ? '*' : '.');
    }
    printf("\n");
  }
  #endif

  for (int i = 1; i <= N; ++i)
  {
    for (int j = 1; j <= N; ++j)
    {
      sum[i][j] += sum[i][j-1];
    }
  }
  for (int j = 1; j <= N; ++j)
  {
    for (int i = 1; i <= N; ++i)
    {
      sum[i][j] += sum[i-1][j];
    }
  }


  #ifdef DEBUG
  debug("SUM 2D:\n");
  for (int y = N; y > 0; --y)
  {
    for (int x = 1; x <= N; ++x)
    {
      printf("%d ", sum[x][y]);
    }
    printf("\n");
  }
  #endif

  // search
  ans = INFLL;
  for (int x1 = 0; x1 < N ; ++x1)
  {
    for (int x2 = x1; x2 < N; ++x2)
    {
      for (int y1 = 0; y1 < N ; ++y1)
      {
        for (int y2 = y1; y2 < N; ++y2)
        {
          ll xx1 = min(A[x1], A[x2]),
          xx2 = max(A[x1], A[x2]),
          yy1 = min(B[y1], B[y2]),
          yy2 = max(B[y1], B[y2]);
          int cnt = sum[ord_x[xx2] + 1][ord_y[yy2] + 1]
          - sum[ord_x[xx1]][ord_y[yy2] + 1]
          - sum[ord_x[xx2] + 1][ord_y[yy1]]
          + sum[ord_x[xx1]][ord_y[yy1]];
          // DUMP(sum[ord_x[xx2] + 1][ord_y[yy2] + 1]);
          // DUMP(sum[ord_x[xx1]][ord_y[yy2] + 1]);
          // DUMP(sum[ord_x[xx2] + 1][ord_y[yy1]]);
          // DUMP(sum[ord_x[xx1]][ord_y[yy1]]);
          if(cnt >= K){
            debug("cnt(%d, %d, %d, %d) = %d\n",
              ord_x[A[x1]], ord_x[A[x2]], ord_y[B[y1]], ord_y[B[y2]], cnt);
            ll area = calc_area(xx1, xx2, yy1, yy2);
            debug("area(%d, %d, %d, %d) = %lld\n", xx1, xx2, yy1, yy2, area);
            if(area < ans) ans = area;
          }
        }
      }
    }
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
  cin >> N >> K;
  for (int i = 0; i < N; ++i)
  {
    scanf("%lld%lld", &A[i],&B[i]);
  }
  solve2();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}