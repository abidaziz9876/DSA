#include<bits/stdc++.h>
using namespace std;

/*
what I learn form this particular problem is, we can combine (union) two edges and then we can
also detach two nodes by creating a temporary rank (or size) and parent array if something breaks
then we can store the state
*/

class DSU{
    public:
    vector<int> parent,size;
    DSU(int n){
        parent.resize(n);
        size.resize(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
            size[i]=0;
        }
    }
    int findParent(int node){
        if(parent[node]==node){
            return node;
        }
        return parent[node]=findParent(parent[node]);
    }

    void unionBySize(int u,int v){
        int ulp_u=findParent(u);
        int ulp_v=findParent(v);

        if(ulp_u==ulp_v){
            return;
        }

        if(size[ulp_u]<=size[ulp_v]){
            parent[ulp_v]=ulp_u;
            size[ulp_u]+=size[ulp_v];
        }
        else{
            parent[ulp_u]=ulp_v;
            size[ulp_v]+=size[ulp_u];
        }
    }
    bool connected(int u,int v){
        int par_v=findParent(v);
        int par_u=findParent(u);
        if(par_u==par_v){
            return true;
        }
        return false;
    }
};

class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        DSU ds(n);
        int m=requests.size();
        vector<bool> ans(m);
        for(int i=0;i<m;i++){
            int u=requests[i][0];
            int v=requests[i][1];
            bool possible=true;
            vector<int> temp_size=ds.size;
            vector<int> temp_parent=ds.parent;
            ds.unionBySize(u,v);
            for(auto& res: restrictions){
                if(ds.connected(res[0],res[1])){
                    possible=false;
                    break;
                }
            }
            if(possible){
                ans[i]=true;
            }
            else{
                ds.parent=temp_parent;          //this two steps is very important to undo things
                ds.size=temp_size;
            }
        }
        return ans;
    }
};