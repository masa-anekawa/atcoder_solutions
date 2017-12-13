#define SORT(v) sort(v.begin(), v.end())
#include "iostream"
#include "map"
#include "vector"
#include <stack>
#include "cstdlib"
#include <algorithm>
#include <cstdarg>
#include <cstdio>
// #include "ane.cpp"

#define INF (int)1e9
#define NMAX 55
#define MMAX 55
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
typedef pair<int, int> P;

int N,M,dp[NMAX][MMAX] = {};
int S[NMAX][NMAX]={}, T[MMAX][MMAX] = {};

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int ans = 0;
bool check(int i, int j){
  // if(i + M > N || j + M > N) return false;
  for (int k = 0; k < M; ++k)
  {
      for (int l = 0; l < M; ++l)
      {
          if ( i+k > N-1 || j+l > N-1 || S[i+k][j+l] != T[k][l])
          {
              return false;
          }
      }
  }
  return true;
}
void solve(){
  // 解答アルゴリズム
  for (int i = 0; i < N; ++i)
  {
      for (int j = 0; j < N; ++j)
      {
          if(check(i, j)){
              cout << "Yes" << endl;
              return;
          }
      }
  }
  cout << "No" << endl;
}
void debug(){
  // デバッグ用出力
  for (int i = 0; i < N; ++i)
  {
      for (int j = 0; j < N; ++j)
      {
          cout << S[i][j];
      }
      cout << endl;
  }
  for (int i = 0; i < M; ++i)
  {
      for (int j = 0; j < M; ++j)
      {
          cout << T[i][j];
      }
      cout << endl;
  }
}
void answer(){
  // 解答出力
  cout << ans << endl;
}
int main(int argc, char const *argv[])
{
  // 入力の読み込み，番兵法
  ios::sync_with_stdio(false);

  Fill(dp, -1);

  cin >> N >> M;
  for (int i = 0; i < N; ++i)
  {
      for (int j = 0; j < N; ++j)
      {
          char ch;
          scanf(" %c", &ch);
          S[i][j] = (ch == '#');
      }
  }
  for (int i = 0; i < M; ++i)
  {
      for (int j = 0; j < M; ++j)
      {
          char ch;
          scanf(" %c", &ch);
          T[i][j] = (ch == '#');
      }
  }
  solve();
  #ifdef DEBUG
  // debug();
  #endif
  // answer();

  return 0;
}