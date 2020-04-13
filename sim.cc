#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<set>
#include<fstream>

using namespace std;

class point{
public:
    long x, y, z;
    point(long x,long y,long z):x(x),y(y),z(z){}
    bool is_nigh(point &other){
        return true;
    }
    // Just for debugging ;
    void print() const{
        cout << "{" << x << "," << y << "," << z << "}" << endl; 
    }
    bool operator<(const point &p) const{
        if (p.x < x)
            return true;
        else if (p.x == x and p.y < y)
            return true;
        else if (p.y == y and p.x == x and p.z < z)
            return true;
        else
            return false;
    }
    bool operator==(const point &other) const{
        return (x == other.x && y == other.y && z == other.z);
    }
};

void get_nodes(set<point> &points,point &src, point &dest ,string filename){
    ifstream in(filename);
    vector<point> vec;
    while(!in.eof()){
        long x = 0 , y = 0 , z = 0;
        in >> x >> y >> z;
        vec.push_back({x,y,z});
    }
    src = vec[0];
    dest = vec.back();
    for(auto v:vec){
        points.insert(v);
    }
}

// Just for debugging ; 
void printlist(map<point,vector<point>> &list){
    for(auto l : list){
        l.first.print();
        for(auto p : l.second){
            cout << "\t => ";
            p.print();
        }
        cout << endl;
    }
}
void get_adj_list(set<point> &points,map<point,vector<point>>& list){
    for(auto &p :points){
        vector<point> nigh;
        list.insert({p,nigh});
    }
    
    for(auto &p : points){
        vector<point> nigs;
        nigs.push_back({p.x-1,p.y,p.z});
        nigs.push_back({p.x+1,p.y,p.z});
        nigs.push_back({p.x,p.y-1,p.z});
        nigs.push_back({p.x,p.y+1,p.z});
        nigs.push_back({p.x,p.y,p.z-1});
        nigs.push_back({p.x,p.y,p.z+1});
        for(auto &n :nigs){
            if(points.find(n) != points.end()){
                list[p].push_back(n);
            }
        }
    }
}

int bfs(point &src, point &dest, map<point,vector<point>> &list){
    queue<point> q1,q2;
    q1.push(src);
    set<point> visited;
    visited.insert(src);
    int res = 0;
    while(!q1.empty()){
        while(!q1.empty()){
            point top = q1.front();q1.pop();
            if(top==dest)return res;
            for(auto nig : list.at(top)){
                if(visited.find(nig)==visited.end()){
                    q2.push(nig);
                    visited.insert(nig);
                }
            }
        }
        res++;
        swap(q1,q2);
    }
    return -1;
}

int main(){
    set<point> pnts;
    point src({-1, -1, -1});
    point dest({-1, -1, -1});
    get_nodes(pnts, src, dest, "nodes.txt");
    map<point, vector<point>> list;
    get_adj_list(pnts, list);
    // printlist(list);
    int res = bfs(src, dest, list);
    cout << "min hops " << res << endl;
}