#ifndef LIB_Score_H
#define LIB_Score_H
using namespace std;

bool if_blocked(vector<line> &obs,point &from , point &to);
int bfs(point &src, point &dest, map<point,vector<point>> &list,vector<line> obstacles);
int get_Coverage(std::string filename);
int get_Hops(double* hops, map<point,vector<point>> &list,vector<line> obstacles);

#endif