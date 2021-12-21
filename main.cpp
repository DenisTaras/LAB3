#include "graf.hpp"

int main(){
    int n;
    std::cout<<"Enter vertex num:"<<"\n";
    std::cin>> n;
    graf G(n);
    graf O(n);
    std::cout<<"Enter edge num:"<<"\n";
    std::cin>> n;
    for(int i = 0; i < n; i++){
        Edge q;
        std::cout<<"Enter vertex 1:"<<"\n";
        std::cin>> q.q1;
        while ( q.q1 < 0 && q.q1 > G.Get_size()){
            std::cout<<"Enter vertex 1:"<<"\n";
            std::cin>> q.q1;
        }
        std::cout<<"Enter vertex 2:"<<"\n";
        std::cin>> q.q2;
        while ( q.q2<0 && q.q2 > G.Get_size()){
        std::cout<<"Enter vertex 2:"<<"\n";
        std::cin>> q.q2;
        }

        std::cout<<"Enter weight:"<<"\n";
        std::cin>> q.weight;
        while (q.weight < 0){
            std::cout<<"Enter weight:"<<"\n";
            std::cin>> q.weight;
        }
        
        G.Set_Vertex(q);
    }
    std::cout<<"------------------"<<"\n";
    
    G.print_graf();

    std::cout<<"------------------"<<"\n";

    std::vector<Edge> ostov = G.Kruskal();
    for(int i = 0; i < ostov.size(); i++){
        O.Set_Vertex(ostov[i]);
    }
    std::cout<<"Minimum spanning graph:"<<"\n";
    O.print_graf();
    std::cout<<"------------------"<<"\n";
    std::cout<<"Enter visits num:"<<"\n";
    std::cin>> n;
    std::vector<int> path;
    for(int i = 0; i < n; i++){
        int s;
        std::cout<<"Enter vertex "<< i << ":"<< "\n";
        std::cin>> s;
        path.push_back(s);
    }
    std::vector<std::vector<int>> P(n);
    std::vector<int> res;
    int weight;
        for(int i = 0; i < path.size() - 1; i++){
            P[i] = G.Dijkstra(path[i], path[i+1]);
            if(P[i].size() == 0){
                std::cerr << "Path not found" << std::endl;
            }
        }
        
        for (int i = 0; i < P.size(); i++)
        {
            for(int j = 0; j < P[i].size(); j++){
                res.push_back(P[i][j]);
            }
        }
        if(res.size() > 0)
            weight = G.weight_path(res); 

    for(int i = 0; i< res.size(); i++){
        std::cout<< res[i] << " ";
    }
    std::cout<<"weight: ";
    std::cout<<weight;



    return 0;
} 