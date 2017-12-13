#define SORT(v) sort(v.begin(), v.end())
#include "iostream"
#include "map"
#include "vector"
#include <stack>
#include "cstdlib"
#include <algorithm>
#include <cstdarg>
// #include "ane.cpp"

#define INF (int)1e9
#define NMAX 10
#define MMAX 30
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
int G[NMAX][NMAX]={};
std::vector<int> vec;

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int ans = 0;

void solve(){
  // 解答アルゴリズム

  do
  {
      bool err = false;
      // for (int i = 0; i < N; ++i)
      // {
      //     cout << vec[i] << " ";
      // }
      // cout << endl;
      for (int i = 0; i < N-1; ++i)
      {
          if (!G[vec[i]][vec[i+1]])
          {
              err = true;
              break;
          }
      }
      if(!err)ans++;
  } while (next_permutation(vec.begin()+1, vec.end()));
}
void debug(){
  // デバッグ用出力
  cout << "G:\n";
  for (int i = 0; i < N; ++i)
  {
      for (int j = 0; j < N; ++j)
      {
          cout << G[i+1][j+1];
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
  for (int i = 0; i < M; ++i)
  {
      int a,b;
      cin >> a >> b;
      G[a][b] = 1;
      G[b][a] = 1;
  }
  for (int i = 1; i <= N; ++i)
  {
      vec.push_back(i);
  }
  solve();
  #ifdef DEBUG
  // debug();
  #endif
  answer();

  return 0;
}