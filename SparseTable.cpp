const int maxn = 1e5+10;
const int maxlog = 20;
vector<int> arr(maxn);
class SparseTable{
public:

    vector<int> lg;
    vector<vector<int>> dp;
    int n;
    SparseTable(int n){
    this->n=n;
    lg.resize(n+1);
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i/2] + 1;
    dp.resize(n);
    for(int i=0;i<n;i++){
        dp[i].resize(lg[n]+1);
    }

  }

  void buildmin(){
    int k=lg[n];
    for(int i=0;i<n;i++)dp[i][0]=arr[i];
    for(int j=1;j<=k;j++){
        for(int i=0;i+(1<<j)<=n;i++){
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
    }
  }


  void buildmax(){
    int k=lg[n];
    for(int i=0;i<n;i++)dp[i][0]=arr[i];
    for(int j=1;j<=k;j++){
        for(int i=0;i+(1<<j)<=n;i++){
            dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
    }
  }
  
  void buildsum(){
    int k=lg[n];
    for(int i=0;i<n;i++)dp[i][0]=arr[i];
    for(int j=1;j<=k;j++){
        for(int i=0;i+(1<<j)<=n;i++){
            dp[i][j]=(dp[i][j-1]+dp[i+(1<<(j-1))][j-1]);
        }
    }
  }


  int querymin(int l,int r){
    int k=r-l+1;
    k=lg[k];
    return min(dp[l][k],dp[r-(1<<k)+1][k]);
  }

  int querymax(int l,int r){
    int k=r-l+1;
    k=lg[k];
    return max(dp[l][k],dp[r-(1<<k)+1][k]);
  }

  long long querysum(int l,int r){
  long long sum = 0;
   for (int i = 20; i >= 0; i--) {
    if ((1 << i) <= r - l + 1) {
        sum += dp[l][i];
        l += 1 << i;
    }
  }
   return sum;
  }

};
