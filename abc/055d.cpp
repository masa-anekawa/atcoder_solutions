#define SORT(v) sort(v.begin(), v.end())
#include "iostream"
#include "map"
#include "vector"
#include <stack>
#include "cstdlib"
#include <algorithm>
#include <cstdarg>
#include "cstdio"
// #include "ane.cpp"

#define INF (int)1e9
#define LLINF (long long)1e18
#define NMAX 200
#define MMAX 200
#define MOD 100000
using namespace std;

// コメントアウトするとdb_printf()を実行しない
#define DEBUG
// デバッグ用printf
void db_printf(const char* format, ...){
  #ifndef DEBUG
  return;
  #endif
  va_list arg;
  va_start(arg, format);
  vprintf(format, arg);  // コンソールに出力
  va_end(arg);
}
// n次元配列の初期化。第２引数の型のサイズごとに初期化していく。
template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
  std::fill( (T*)array, (T*)(array+N), val );
}
typedef pair<int, int> p;
typedef long long ll;

ll N,M,K,A,B,C,D,E;
int dp[NMAX][MMAX] = {};

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

string T, ans[] = {"SS","SW","WS","WW"};

void solve(){
  // 解答アルゴリズム
  for (int k = 0; k < 4; ++k)
  {
      for (int i = 1; i <= N; ++i)
      {
          string sub = ans[k].substr(i-1, 2);
          if (T[i-1] == 'o')
          {
              if(sub == "SS"){
                  ans[k] += 'S';
              }
              else if (sub == "SW"){
                  ans[k] += 'W';
              }
              else if(sub ==  "WS"){
                  ans[k] += 'W';
              }
              else if(sub == "WW"){
                  ans[k] += 'S';
              }
              else {
                  cerr << "error\n";
              }
          }
          else
          {
              if(sub == "SS"){
                  ans[k] += 'W';
              }
              else if (sub == "SW"){
                  ans[k] += 'S';
              }
              else if(sub ==  "WS"){
                  ans[k] += 'S';
              }
              else if(sub == "WW"){
                  ans[k] += 'W';
              }
              else {
                  cerr << "error\n";
              }
          }
      }
      if (ans[k][0] == ans[k][N] && ans[k][1] == ans[k][N+1])
      {
          cout << ans[k].substr(1, N) << endl;
          return;
      }
  }
  cout << "-1\n";
}
void debug(){
  // デバッグ用出力
  cout << "debug /*\n";

  for (int k = 0; k < 4; ++k)
  {
      cout << "ans[" << k << "]: " << ans[k] << endl;
  }

  cout << "*/ debug\n";
}
void answer(){
  // 解答出力
  // cout << ans << endl;
}
int main(int argc, char const *argv[])
{
  // 入力の読み込み，番兵法
  ios::sync_with_stdio(false);

  Fill(dp, -1);

  cin >> N >> T;
  solve();
  #ifdef DEBUG
  // debug();
  #endif
  answer();

  return 0;
}