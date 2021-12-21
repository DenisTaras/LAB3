#ifndef GRAF_HPP
#define GRAF_HPP
#include <vector>
#include "Sequence.hpp"
#include <queue>
#include <limits>
#include <tuple>
#include <set>
#include <algorithm>

struct Vert
{
    int vertex;
    int weight;
};
struct Edge
{
    int q1;
    int q2;
    int weight;
    bool operator == (const Edge& x){
        return (x.q1 == this->q1) && (x.q2 == this->q2) && (x.weight == this->weight);
    }
};

class graf
{
private:
    std::vector<std::vector<Vert>> data;
public:
    graf(){};
    graf(int n) : data(n){};
    void Set_Vertex(Edge q){
        Vert v;
        v.vertex = q.q2;
        v.weight = q.weight;
        data[q.q1].push_back(v);
        v.vertex = q.q1;
        v.weight = q.weight;
        data[q.q2].push_back(v);
    };
    void Set(std::vector<Vert> neww ){
        data.push_back(neww);
        for(int i = 0; i < neww.size() ; i++ ){
            Vert q;
            q.vertex = neww.size() - 1;
            q.weight = neww[i].weight;
            data[neww[i].vertex].push_back(q);
        }
    };
    int Get_size(){
        return data.size();
    }
    int weight_path(std::vector<int> path){
        int w = 0;
        for(int i = 0; i < path.size() - 1; i++ ){
            for(int j = 0; j < data[path[i]].size(); j++){
                if(data[path[i]][j].vertex == path[i+1]){
                    w+= data[path[i]][j].weight;
                }
            }
        }
        return w;
    };

    void print_graf(){
        for(int i = 0; i< data.size(); i++){
            std::cout<< i << ": ";
            for(int j = 0; j < data[i].size(); j++){
                std::cout << data[i][j].vertex << " ("<< data[i][j].weight << "), ";
            }
            std::cout << std::endl;
        }
    };
    std::vector<int> Dijkstra(int n, int m){
        std::vector<int> distance(data.size(), std::numeric_limits<int>::max());
        std::vector<int> path(data.size() , -1);
        std::vector<bool> visit(data.size(), false);
        distance[n] = 0;
        path[n] = n;
        while (std::count(visit.begin(), visit.end(), false) > 0)
        {
            int v = -1;
            for(int i = 0; i < visit.size(); i++){
                if(visit[i]){
                    continue;
                }
                if(v == -1 || v > -1 && distance[i] < distance[v]){
                    v = i;
                }
            }
            for(int i = 0; i < data[v].size(); i++ ){
                if(visit[data[v][i].vertex]){
                    continue;
                }
                if(distance[data[v][i].vertex] > distance[v] + data[v][i].weight){
                    distance[data[v][i].vertex] = distance[v] + data[v][i].weight;
                    path[data[v][i].vertex] = v;
                }
            }
            visit[v] = true;
        }

        std::vector<int> dpath;
        int p = m;
        while(p != n){
            dpath.push_back(p);
            if(path[p] != -1){
            p = path[p];
            }else{
                return std::vector<int> ();
            }
        }
        dpath.push_back(n);
        std::reverse(dpath.begin(), dpath.end());
        return dpath;
    }
    
    struct less_nocase 
{
    bool operator( )( const Edge& x, const Edge& y ) const
    {
        return x.weight < y.weight;
    }
};


    std::vector<Edge> Kruskal(){
        std::set < Edge, less_nocase > edges;
        std::vector<Edge> res;
        for(int i = 0; i < data.size(); i++ ){
            for(int j = 0; j < data[i].size(); j++){
                Edge q;
                q.q1 = std::min(i, data[i][j].vertex);
                q.q2 = std::max(i, data[i][j].vertex);
                q.weight = data[i][j].weight;
                edges.insert(q);
            }
        }
        std::vector<bool> visit(data.size(), false);
        for(auto i : edges){
            if( visit[i.q1] && visit[i.q2] ){
                continue;
            }
            else{
                visit[i.q1] = true;
                visit[i.q2] = true;
                res.push_back(i);
            }
        }
        return res;
    }
};
#endif
