#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 200005;
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
  std::fill( reinterpret_cast<T*>(array),
             reinterpret_cast<T*>(array+N),
             val );
}

// binary search
ll BSearch(ll ok, ll ng, bool (*f)(ll)){
  ll mid;
  while(abs(ok - ng) > 1LL) {
    mid =  (ok + ng) / 2LL;
    if(f(mid)) {
      debug("BSearch: f(%d) == true\n", mid);
      ok = mid;
    }
    else
    {
      debug("BSearch: f(%d) == false\n", mid);
      ng = mid;
    }
  }
  return ok;
}


// Segment Tree for Range Minimum Query
  // **********************************************************
  // *** important: all functions' variable,                ***
  // *** such as "index", "l", "r", etc., must be 0-origin. ***
  // **********************************************************
  // ********************************************
  // *** important: N_MAX must be power of 2. ***
  // ********************************************
template<typename T>
class SegmentTree{
  private:
  ll n_;
  const T INF_VAL = numeric_limits<T>::max();
  vector<T> dat_sum_, dat_xor_; // 0 origin, A[i] = dat[i + n_]

  T _querySum(ll l, ll r, ll l_dat, ll r_dat, ll i_dat){
    if(r_dat <= l_dat) return 0;

    // debug("_querySum(%lld, %lld, %lld, %lld, %lld) called\n", l, r, l_dat, r_dat, i_dat);

    if (r <= l_dat || r_dat <= l)
      return 0;

    else if(l <= l_dat && r_dat <= r)
      return dat_sum_[i_dat];

    else
      return _querySum(l ,r, l_dat, (l_dat + r_dat) / 2, i_dat * 2)
           + _querySum(l, r, (l_dat + r_dat) / 2, r_dat, i_dat * 2 + 1);
  }

  T _queryXor(ll l, ll r, ll l_dat, ll r_dat, ll i_dat){
    if(r_dat <= l_dat) return 0;

    // debug("_queryXor(%lld, %lld, %lld, %lld, %lld) called\n", l, r, l_dat, r_dat, i_dat);

    if (r <= l_dat || r_dat <= l)
      return 0;

    else if(l <= l_dat && r_dat <= r)
      return dat_xor_[i_dat];

    else
      return _queryXor(l ,r, l_dat, (l_dat + r_dat) / 2, i_dat * 2)
           ^ _queryXor(l, r, (l_dat + r_dat) / 2, r_dat, i_dat * 2 + 1);
  }

  public:
  void init(ll n){
      n_ = 1; while(n_ < n) n_ *= 2;
      dat_sum_ = vector<T>(2 * n_, 0);
      dat_xor_ = vector<T>(2 * n_, 0);
  }
  void set(int index, T val){
      int i_dat = index + n_;
      dat_sum_[i_dat] = val;
      dat_xor_[i_dat] = val;
      for (i_dat /= 2; i_dat > 0; i_dat /= 2)
      {
          dat_sum_[i_dat] = dat_sum_[i_dat * 2] + dat_sum_[i_dat * 2 + 1];
          dat_xor_[i_dat] = dat_xor_[i_dat * 2] ^ dat_xor_[i_dat * 2 + 1];
      }
  }
  bool query(ll l, ll r){
      debug("query(%d, %d):\n", l, r);
      auto sum_ = _querySum(l, r, 0, n_, 1);
      auto xor_ = _queryXor(l, r, 0, n_, 1);
      DUMP(sum_);
      DUMP(xor_);
      return sum_ == xor_;
  }
  void dump(){
      cout << "\n*** SegTree dump begin ***\n";
      cout << "n_ = " << n_ << ", INF_VAL = " << INF_VAL << endl;
      cout << "\ndat_sum:\n";
      for (int i = 1; i < n_ * 2; i *= 2)
      {
          for (int j = i; j < i * 2; ++j)
          {
              if(dat_sum_[j] == INF_VAL) cout << "INF ";
              else cout << dat_sum_[j] << " ";
          }
          cout << endl;
      }
      cout << "\ndat_xor:\n";
      for (int i = 1; i < n_ * 2; i *= 2)
      {
          for (int j = i; j < i * 2; ++j)
          {
              if(dat_xor_[j] == INF_VAL) cout << "INF ";
              else cout << dat_xor_[j] << " ";
          }
          cout << endl;
      }
      cout << "*** SegTree dump end ***\n\n";
  }
};
ll NUM_TEST_CASE = 1;

ll N,M,K,A[NMAX],B,C,D,E;
int dp[NMAX] = {};

SegmentTree<ll> st;

ll ans = {};

void solve(){
  // main algorithm
  st.init(N);
  for (int i = 0; i < N; ++i)
  {
    st.set(i, A[i]);
  }
  // st.dump();
  for (int i = 0; i < N; ++i)
  {
    for (int j = i; j < N; ++j)
    {
      if(st.query(i, j + 1)){
        ++ans;
      }
    }
  }
}
void solve2(){
  unordered_map<int, int> bits = {{0, 1}};
  for (int i = 0; i < N; ++i)
  {
    unordered_map<int, int> nex;
    debug("i: %d(=> %lld):\n", i, A[i]);
    for(auto ite = bits.begin(); ite != bits.end(); ++ite) {
      debug("ite => {%d, %d}\n", ite->first, ite->second);
      if((ite->first & A[i]) == 0) {
        ans += ite->second;
        nex[ite->first ^ A[i]] = ite->second;
      }
    }
    nex[0]++;
    bits = nex;
  }
}
void debug(){
  // output debug information
  // st.dump();
}
void answer(){
  // output answer
  cout << ans << endl;
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

    cin >> N;
    for (int i = 0; i < N ; ++i)
    {
      scanf("%lld", &A[i]);
    }
    solve2();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}