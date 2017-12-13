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


int N,M,K,A[3 * NMAX]={};
std::vector<p> sorted;
priority_queue<int, vector<int>, greater<int> > lft;
map<int, int> rit;
ll dp_left[NMAX] = {}, dp_right[NMAX] = {};

ll ans = 0;

void solve(){
  // main algorithm
  sort(sorted.begin(), sorted.begin() + N);
  for(int i = 0; i < N; ++i) lft.push(sorted[i].first);
  sort(sorted.begin() + N, sorted.begin() + 3 * N);
  for(int i = N; i < 2 * N; ++i) rit[sorted[i].first]++;
  int pos = 2 * N;

  ll lft_sum = accumulate(sorted.begin(), sorted.begin() + N, 0,
    [](ll l, p r){return l + r.first;});
  ll rit_sum = accumulate(sorted.begin() + N, sorted.begin() + 2 * N, 0,
    [](ll l, p r){return l + r.first;});
  ans = lft_sum - rit_sum;
  for (int i = N; i < 2 * N; ++i)
  {
    debug("i = %d\n", i);
    if(A[i] > lft.top()) {
      lft_sum = lft_sum + A[i] - lft.top();
      lft.pop();
      lft.push(A[i]);
    }
    if(rit.count(A[i])) {
      while(i >= sorted[pos].second) pos++;
      rit_sum = rit_sum + sorted[pos].first - A[i];
      rit[A[i]]--;
      rit[sorted[pos].first]++;
    }
    ans = max(ans, lft_sum - rit_sum);
    DUMP(ans);
  }
}

void solve2(){
  // calc left for each k = N..2N
  priority_queue<int, vector<int>, greater<int> > que;
  ll left_sum = 0;
  for (int i = 1; i <= N; ++i){
    que.push(A[i]);
    left_sum += A[i];
  }
  dp_left[0] = left_sum;
  for (int k = N + 1; k <= 2*N; ++k)
  {
    left_sum += A[k];
    que.push(A[k]);
    left_sum -= que.top();
    que.pop();
    dp_left[k - N] = left_sum;
  }
  // cal right
  priority_queue<int> que2;
  ll right_sum = 0;
  for (int i = 3 * N; i >= 2 * N + 1; --i){
    que2.push(A[i]);
    right_sum += A[i];
  }
  dp_right[N] = right_sum;
  for (int k = 2 * N - 1; k >= N; --k)
  {
    right_sum += A[k + 1];
    que2.push(A[k + 1]);
    right_sum -= que2.top();
    que2.pop();
    dp_right[k - N] = right_sum;
  }
  // get max
  ans = -INFLL;
  for (int i = 0; i <= N; ++i)
  {
    ans = max(ans, dp_left[i] - dp_right[i]);
  }
}

void debug(){
  // output debug information
  cout << "dp_left:\n";
  for (int i = 0; i <= N; ++i)
  {
    cout << i << " " << dp_left[i] << "\n";
  }
  cout << endl;
  cout << "dp_right:\n";
  for (int i = 0; i <= N; ++i)
  {
    cout << i << " " << dp_right[i] << "\n";
  }
  cout << endl;
}
void answer(){
  // output answer
  printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%d", &N);
  for (int i = 1; i <= 3*N; ++i)
  {
    scanf("%d", &A[i]);
    sorted.push_back(p(A[i], i));
    // debug("A[%d] = %d\n", i, A[i]);
  }
  solve2();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}