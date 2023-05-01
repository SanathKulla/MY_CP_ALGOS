int n,m;
//2d matrix of size n*m;
vector<vector<int>> v(n,vector<int> (m,0)),pre(n,vector<int> (m,0));
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        cin>>v[i][j];
    }
}
for(int i=0;i<m;i++){
    if(i==0)pre[0][0]=v[0][0];
    else pre[0][i]=pre[0][i-1]+v[0][i];
}
for(int i=0;i<n;i++){
    if(i==0)pre[0][0]=v[0][0];
    else pre[i][0]=pre[i-1][0]+v[i][0];
}
for(int i=1;i<n;i++){
    for(int j=1;j<m;j++){
        pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+v[i][j];
    }
}
   int x1,y1,x2,y2;
   // area of rectangle b/w (x1,y1) and (x2,y2);

   int sum=pre[x2][y2]-((x1==0)?0:pre[x1-1][y2])-((y1==0)?0:pre[x2][y1-1])+((x1==0 || y1==0)?0:pre[x1-1][y1-1]);
    
