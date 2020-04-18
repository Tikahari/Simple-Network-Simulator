
using namespace std;
#ifndef LIB_Graph_H
#define LIB_Graph_H

class point{
public:
    long x, y, z;
    bool is_nigh(point &other);
    // Just for debugging ;
    void print() const;
    bool operator<(const point &p) const;
    bool operator==(const point &other) const;
    point(long x,long y,long z);
};

void get_nodes(set<point> &points,point &src, point &dest ,string filename);

void get_adj_list(set<point> &points,map<point,vector<point>>& list);

int bfs(point &src, point &dest, map<point,vector<point>> &list);

void printlist(map<point,vector<point>> &list);

#endif