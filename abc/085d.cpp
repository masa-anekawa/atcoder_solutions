#include <iostream>
#include <algorithm>

#define NMAX 100005

using namespace std;
using ll =  long long;


int N,H,A[NMAX],B[NMAX];

bool check(int x){
  int i = 0;
  ll sum = 0;
  for(; x > 0 && i < N && A[0] <= B[i]; --x){
      sum += B[i++];
  }
  sum += (ll)x * A[0];
  return sum >= H;
}

int main(){
  cin >> N >> H;
  for(int i = 0; i < N; ++i){
    scanf("%d %d", &A[i], &B[i]);
  }
  sort(A, A + N, greater<int>());
  sort(B, B + N, greater<int>());
  // solve
  int low = 0, hi = H;
  while(hi - low > 1){
    int mid = low + (hi - low) / 2;
    if(check(mid)){
      hi = mid;
    }
    else {
      low = mid;
    }
  }
  // answer
  cout << hi << endl;

  return 0;
}