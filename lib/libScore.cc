#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include "lib.h"

#define debug 1

class Coverage{
public:
    Coverage(std::vector<point> bounds);
    std::vector<point> bounds;
    std::vector<line> lines;
    void get_lines();
    int getArea();
};

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
    if(debug)
        printf("begin bfs\n");
    queue<point> q1;
    q1.push(src);
    set<point> visited;
    visited.insert(src);
    int res = 0;
    while(!q1.empty()){
        point top = q1.front();
        q1.pop();
        printf("pop\n");
        if(top==dest)return res;
        printf("no return\n");
        for(auto nig : list[top]){
            printf("vector in map\n");
            if(if_blocked(obstacles,top,nig))
                continue;
            if(visited.find(nig)==visited.end()){
                q1.push(nig);
                visited.insert(nig);
            }   
        }
        res++;
    }
    return -1;
}

int get_gridVal(std::string filename){
    std::ifstream in(filename);
    std::string line;
    // get max possible coverage
    getline(in, line);
    return atoi(line.c_str());
}

int get_Coverage(std::string filename){
    std::cout<<"get coverage " << filename << '\n';
    int total_area = pow(get_gridVal(filename), 2);
    std::cout<< "total area "<<total_area<<'\n';
    return 0;
}

int get_Hops(double* hops, map<point,vector<point>> &list,vector<line> obstacles){
    if(debug) printf("get hops\n");
    point src({1999, 1446});
    point dest({1447, 1086});
    int num = bfs(src, dest, list, obstacles);
    printf("output of bfs is %d\n", num);
    return 0;
}