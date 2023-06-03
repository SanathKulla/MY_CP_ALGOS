vector<ll> edges[200010];  // graph
vector<ll> component(200010); // the vertex belongs to which connected component ?
vector<ll> component_size(200010,1); // size of a connected component
vector<ll> nedges(200010); // no of edges in a connected component


void relabel(ll v, ll target){
    if(component[v] == target) return;

    component[v] = target;

    for(ll &neighbour: edges[v]){
        relabel(neighbour, target);
    }
}

void merge(ll u,ll v){
    int cu=component[u], cv=component[v];

    edges[u].push_back(v);
    edges[v].push_back(u);

    ++nedges[cu];

    if(cu == cv)return;

    if(component_size[cu] > component_size[cv]){
         swap(u, v);
         swap(cu, cv);
    }

    relabel(u, cv);

    component_size[cv] += component_size[cu];
    nedges[cv] += nedges[cu];

}

void build_dsu(ll n,ll m){

  for(ll i=0; i<n; i++){
          component[i] = i;
  }

  for(ll i=0; i<m; i++){
          ll u,v;
          cin>>u>>v;
          --u;--v;
          merge(u,v);
  }
}
