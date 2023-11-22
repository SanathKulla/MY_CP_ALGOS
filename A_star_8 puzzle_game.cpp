#include<bits/stdc++.h>
using namespace std;



int main(){

   vector<vector<int>> start(3,vector<int> (3)) , goal(3,vector<int> (3));
   for(int i=0; i<3; i++){
           for(int j = 0 ; j< 3; j++){
                cin>>start[i][j];
           }
   }
   for(int i=0; i<3; i++){
           for(int j = 0 ; j< 3; j++){
                cin>>goal[i][j];
           }
   }
   map<vector<vector<int>> , int> open , closed , g  , f ;
   map<vector<vector<int>> , vector<vector<int>>>   par;
   priority_queue< pair<int,vector<vector<int>>> , vector<pair<int,vector<vector<int>>>> , greater<pair<int,vector<vector<int>>>> > pq;
   
   auto GoalTest = [&](vector<vector<int>> &current){
       return current == goal;
   };

   auto MoveGen = [&](vector<vector<int>> &current){
        vector<vector<vector<int>>> res;
        for(int i = 0 ; i<3;i++){
            for(int j = 0;j<3;j++){
                if(current[i][j] == 0){
                    vector<vector<int>> v = current;
                    if(i){
                        swap(v[i][j] , v[i-1][j]);
                        res.push_back(v);
                        swap(v[i][j] , v[i-1][j]);                        
                    }
                    if(j){
                        swap(v[i][j] , v[i][j-1]);
                        res.push_back(v); 
                        swap(v[i][j] , v[i][j-1]);                        
                    }
                    if(i+1 < 3){
                        swap(v[i][j] , v[i+1][j]);
                        res.push_back(v);
                        swap(v[i][j] , v[i+1][j]);                        
                    }
                    if(j+1 < 3){
                        swap(v[i][j] , v[i][j+1]);
                        res.push_back(v);
                        swap(v[i][j] , v[i][j+1]);                        
                    }
                }
            }
        }
        return res;
   }; 

   auto huristic = [&](vector<vector<int>> &v){
       int res = 0;
       for(int i = 0; i<3;i++){
        for(int  j = 0;j<3;j++){
            res += v[i][j] != goal[i][j];
        }
       }
       return res;
   };
   function< void (vector<vector<int>> ) > propogate_improvement = [&](vector<vector<int>> v){
       auto neighbours = MoveGen(v);
       for(auto it:neighbours){
           if(g[it] > g[v] + 1){
               g[it] = g[v] + 1;
               f[it] = g[it] + huristic(it);
               if(closed.find(it)!= closed.end()){
                 propogate_improvement(it);
               }else{
                  pq.push({f[it] , it});
               }
           }
       }
   };
   auto print = [&](vector<vector<int>> v){
        for(int i=0; i<3; i++){
                for(int j = 0;j<3;j++){
                    cout<<v[i][j]<<" ";
                }
                cout<<endl;
        }
        cout<<"g = "<<g[v]<<' '<<"f= "<<f[v]<<endl;
        cout<<endl;
        return true;
   };  
   auto RecostructPath = [&](vector<vector<int>> &cur){
       vector<vector<vector<int>>> res;
       while(cur != start){
            res.push_back(cur);
            cur = par[cur];
       }
       res.push_back(start);
       reverse(res.begin() , res.end());
       for(auto it:res){
        print(it);
       }
       cout<<"goal found"<<endl;
       return true;
   };

   g[start] = 0;
   f[start] = huristic(start);
   open[start] = true;
   par[start] = start;
   pq.push({huristic(start) , start});
   while(pq.size()){
      auto [f_value , node] = pq.top();
      if(GoalTest(node)){
        RecostructPath(node);
        return 0;
      }
      pq.pop();
      if(f[node] < f_value)continue;
      closed[node] = true;
      auto neighbours = MoveGen(node);
      for(auto it:neighbours){
        if(open.find(it) == open.end() and closed.find(it) == closed.end()){
            par[it] = node;
            g[it] = g[node] + 1;
            f[it] = g[it] + huristic(it);
            open[it] = true;
            pq.push({f[it] , it});
        }else if(open.find(it) != open.end() and closed.find(it) == closed.end()){
            if(g[it] > g[node] + 1){
                par[it] = node;
                g[it] = g[node] + 1;
                f[it] = g[it] + huristic(it);
                pq.push({f[it] , it});
            }
        }else{
            if(g[it] > g[node] + 1){
                par[it] = node;
                g[it] = g[node] + 1;
                f[it] = g[it] + huristic(it);
                propogate_improvement(it);
            }
        }
      }

   }
   

  
   cout<<"failure"<<endl;

    return 0;
}
