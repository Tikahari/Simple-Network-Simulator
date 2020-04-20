#ifndef LIB_Graph_H
#define LIB_Graph_H
using namespace std;

class point{
public:
    int x, y;
    bool is_nigh(point &other);
    // Just for debugging ;
    void print() const;
    bool operator<(const point &p) const;
    bool operator==(const point &other) const;
    point(int x,int y):x(x),y(y){}
};
class line{
public:
    point first,second;
    line(point f,point s):first(f),second(s){}
    bool is_blocked(point from , point to);
    // checks if p is left of (l1,l2)
    bool is_left(point l1, point l2, point p);
    bool operator<(const line &p) const;	    
};
void str_to_node(int arr[], std::string line);
void get_nodes(set<point> &points, string filename);
void get_obstacles(vector<line> &obstacles, string obstaclesfile);
void get_adj_list(set<point> &points,map<point,vector<point>>& list);
int bfs(point &src, point &dest, map<point,vector<point>> &list,vector<line> obstacles);
void printlist(map<point,vector<point>> &list);

#endif