#ifndef LIB_Score_H
#define LIB_Score_H
using namespace std;

class Coverage{
public:
    Coverage(std::vector<point> bounds);
    std::vector<point> bounds;
    std::vector<line> lines;
    void get_lines();
    int getArea();
};
bool in(int* indices, int count);
point* get_points(map<point, vector<point>> &list, int* indices);
bool if_blocked(vector<line> &obs,point &from , point &to);
std::vector<point> find(map<point,vector<point>> &list, point p);
bool find(set<point> visited, point p);
int bfs(point &src, point &dest, map<point,vector<point>> &list,vector<line> obstacles);
int get_Coverage(std::string filename);
float get_Hops(float* hops, map<point,vector<point>> &list,vector<line> obstacles, std::string filename);

#endif