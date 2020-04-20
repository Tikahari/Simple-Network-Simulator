#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <fstream>
#include <math.h>
#include "lib.h"

using namespace std;

#define debug 0
#define dimension 2

bool point::is_nigh(point &other){
    if(debug)
        printf("is nigh\n");
    return true;
}

void point::print() const{
    cout << "{" << x << "," << y << "}"; 
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

void str_to_node(int arr[], std::string line){
    std::string word = "";
    int count = 0;
    for(int i = 0; i < line.length() && count < 2; i++){
        if(isdigit(line[i])){
            word += line[i];
        }
        else{
            arr[count] = atoi(word.c_str());
            word = "";
            count++;
        }
    }
    if(debug){
        std::cout<<arr[0]<<'\t'<<arr[1]<<'\n';
    }
}

void get_nodes(set<point> &points, string filename){
    if(debug)
        std::cout<<"get nodes from "<< filename <<'\n';
    std::ifstream in(filename);
    std::string line;
    while(!in.eof()){
        std::getline(in, line);
        int arr[dimension];
        str_to_node(arr, line);
        line = "";
        // if(debug)
            // printf("in file, %f %f %f\n", x, y, z);
        points.insert({arr[0], arr[1]});
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
    std::cout<<"print adj list\n";
    for(auto l : list){
        l.first.print();
        for(auto p : l.second){
            cout << "\t&";
            p.print();
        }
        cout << endl;
    }
}

void printlist2(map<point,vector<point>> &list){
    printf("printlist2\n");
    for(std::map<point,vector<point>>::iterator it = list.begin(); it!= list.end(); it++){
        std::cout<<"first: ";
        it->first.print();
        if(list.find(it->first) == list.end()){
            printf("\ncould not find item in list\n");
        }
        for(std::map<point,vector<point>>::iterator it1 = list.begin(); it1 != list.end(); it1++){
            if(it1->first.x == it->first.x && it1->first.y == it->first.y){
                printf("was found\n");
                for(auto i: it->second){
                    std::cout<<" || ";
                    i.print();
                    std::cout<<"\t";
                }
            }
        }
        std::cout<<'\n';
        for(auto i: it->second){
            std::cout<<" & ";
            i.print();
            std::cout<<"\t";
        }
        std::cout<<'\n';
    }
}

void get_adj_list(set<point> &points,map<point,vector<point>>& list){
    int distance;
    for(auto &p1 : points){
        std::vector<point> temp;
        for(auto &p2: points){
            if(debug)
                std::cout<<p1.x<<' '<<p2.x<<' '<<p1.y<<' '<<p2.y<<'\n';
            // improve effeciency
            if(abs(p1.x-p2.x) >= NEIGHBOUR_DISTANCE || abs(p1.y-p2.y) >= NEIGHBOUR_DISTANCE || (p1.x == p2.x && p1.y == p2.y)){
                continue;
            }
            //distance form
            distance = pow((pow(p1.x-p2.x, 2)+pow(p1.y-p2.y, 2)),0.5);
            if(distance < NEIGHBOUR_DISTANCE){
                temp.push_back({p2});
            }
        }
        list[p1] = temp;
        if(debug) std::cout<<" list size "<<list.size()<<'\n';
    }
}
