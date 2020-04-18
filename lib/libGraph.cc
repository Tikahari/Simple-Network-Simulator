#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <fstream>
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<set>
#include<unordered_set>
#include<fstream>
#include "libGraph.h"
using namespace std;

#define debug 0

bool point::is_nigh(point &other){
    if(debug)
        printf("is nigh\n");
    return true;
}

void point::print() const{
    cout << "{" << x << "," << y << "}" << endl; 
}

bool point::operator<(const point &p) const{
    if (p.x < x)
        return true;
    else if (p.x == x and p.y < y)
        return true;
    else if (p.y == y and p.x == x)
        return true;
    else
        return false;
}

bool point::operator==(const point &other) const{
    return (x == other.x && y == other.y);
}

bool line::is_blocked(point from , point to){
    //check if from and to are on opposite side of (first,second)
    if(is_left(first,second,from) ^ is_left(first,second,to)){
    //check if first and second are on opposite side of (from,to)
        if(is_left(from,to,first) ^ is_left(from,to,second)){
            return true;
        }
    }
    return false;
}

bool line::is_left(point l1, point l2, point p){
    return ((l2.x - l1.x)*(p.y - l1.y) - (l2.y - l1.y)*(p.x - l1.x)) > 0;
}

bool line::operator<(const line &p) const{
    if(p.first<first)return true;
    if(p.first==first  and p.second < second)return true;
    else return false;
}

void get_nodes(set<point> &points,point &src, point &dest ,string filename){
    ifstream in(filename);
    vector<point> vec;
    while(!in.eof()){
        long x = 0 , y = 0 ;
        in >> x >> y;
        vec.push_back({x,y});
    }
    src = vec[0];
    dest = vec.back();
    for(auto v:vec){
        points.insert(v);
    }
}

void get_obstacles(vector<line> &obstacles, string obstaclesfile){
    ifstream in(obstaclesfile);
    vector<line> vec;
    while(!in.eof()){
        long x1 = 0 , y1 = 0 , x2 =0 , y2=0;
        in >> x1 >> y1 >> x2 >> y2;
        vec.push_back({{x1,y1},{x2,y2}});
    }
    for(auto v:vec){
        obstacles.push_back(v);
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
    // Adjust this - how far to consider as a neighbor
    int NEIGHBOUR_DISTANCE = 5;

    for(auto &p :points){
        vector<point> nigh;
        list.insert({p,nigh});
    }
    for(auto &p : points){
        vector<point> nigs;
        for(int i=1;i<=NEIGHBOUR_DISTANCE+1;i++){
            nigs.push_back({p.x - i, p.y});
            nigs.push_back({p.x + i, p.y});
        }
        for(int i=1;i<=NEIGHBOUR_DISTANCE;i++){
            nigs.push_back({p.x, p.y - i});
            nigs.push_back({p.x, p.y + i});
        }
        for(auto &n :nigs){
            if(points.find(n) != points.end()){
                list[p].push_back(n);
            }
        }
    }
}

// helper to check if path is blocked by any obstacle
bool if_blocked(vector<line> &obs,point &from , point &to){
    for (line &o : obs){
        if (o.is_blocked(from, to) == true){
            return true;
        }
    }
    return false;
}

int bfs(point &src, point &dest, map<point,vector<point>> &list,vector<line> obstacles){
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
                if(if_blocked(obstacles,top,nig))
                    continue;
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

