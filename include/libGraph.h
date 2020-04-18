
using namespace std;
#ifndef LIB_Graph_H
#define LIB_Graph_H

class point{
public:
    long x, y;
    bool is_nigh(point &other);
    // Just for debugging ;
    void print() const;
    bool operator<(const point &p) const;
    bool operator==(const point &other) const;
    point(long x,long y):x(x),y(y){}
};

class line{
    public:
    point first,second;
    line(point f,point s):first(f),second(s){}
    bool is_blocked(point from , point to){
        //check if from and to are on opposite side of (first,second)
        if(is_left(first,second,from) ^ is_left(first,second,to)){
        //check if first and second are on opposite side of (from,to)
            if(is_left(from,to,first) ^ is_left(from,to,second)){
                return true;
            }
        }
        return false;
    }
    // checks if p is left of (l1,l2)
    bool is_left(point l1, point l2, point p){
        return ((l2.x - l1.x)*(p.y - l1.y) - (l2.y - l1.y)*(p.x - l1.x)) > 0;
    }
    bool operator<(const line &p) const{
        if(p.first<first)return true;
        if(p.first==first  and p.second < second)return true;
        else return false;
    }	    
};


void get_nodes(set<point> &points,point &src, point &dest ,string filename);

void get_obstacles(vector<line> &obstacles, string obstaclesfile);

void get_adj_list(set<point> &points,map<point,vector<point>>& list);

int bfs(point &src, point &dest, map<point,vector<point>> &list,vector<line> obstacles);

void printlist(map<point,vector<point>> &list);

#endif