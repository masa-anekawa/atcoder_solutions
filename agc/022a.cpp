#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
  string S;
  cin >> S;
  string S_orig(S);
  bool used[26];
  if (S.size() < 26)
  {
    for(auto ch :S){
      used[ch - 'a'] = true;
    }
    int i = 0;
    while(used[i]) ++i;
    cout << S + (char)('a' + i) << endl;
    return 0;
  }
  if(next_permutation(begin(S), end(S))) {
    for(int i = 0; i < S.size(); ++i){
      if (S[i] == S_orig[i])
      {
        cout << S[i];
      }else if(S[i] > S_orig[i]){
        cout << S[i] << endl;
        break;
      }else{
        cerr << "error: S < S_orig\n";
        exit(1);
      }
    }
  }
  else {
    cout << "-1\n";
  }
  return 0;
}