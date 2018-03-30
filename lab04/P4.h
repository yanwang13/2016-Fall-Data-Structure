#include<deque>
#include<list>
using namespace std;

class MyGraphVertex{
	int degree;
	list<int> edge;
	
	friend class MyGraph;
};

class MyGraph{
	private:
		int vertex_num;
		int edge_num;
		MyGraphVertex* adj_list;
	public:
		MyGraph(int, int*);
		int OneStroke();
};

MyGraph::MyGraph(int num,int* x){
	
	vertex_num = num;
	edge_num = 0;
	adj_list = new MyGraphVertex[num];
	for(int i=0;i<num;++i){
		adj_list[i].degree = 0;
		for(int j=0;j<num;++j){
			if(x[num*i+j]!=0) {
					adj_list[i].degree++;
					adj_list[i].edge.push_back(j);
			}
		}
		edge_num += adj_list[i].degree;
	}
	edge_num = edge_num/2;
}

int MyGraph::OneStroke(){
	int odd_vertex = 0;
	for(int i=0;i<vertex_num;++i){
		if(adj_list[i].degree%2!=0) ++odd_vertex;
	}
	
	//only if there is zero or two vertex with odd edges can do
	if(odd_vertex!=0 && odd_vertex!=2) 
		return 0;
	
	int start=0;
	if(odd_vertex==2){
		while(adj_list[start].degree%2==0)
			++start;
	}
	deque<int> ans;
	while(1){
		int cur = start;
		ans.push_back(cur);
		while(!ans.empty()){
			
			//find the next edge
			int next = 0;
			list<int>::iterator it;
			for(it=adj_list[cur].edge.begin();it!=adj_list[cur].edge.end();++it){
				if(*it!=-1){
					next =  *it;
					*it = -1;
					for(list<int>::iterator k=adj_list[next].edge.begin();k!=adj_list[next].edge.end();++k){
						if(*k == cur){
							*k = -1;
							break;
						}
					}
					break;
				}
			}

			//wrong way
			if(it==adj_list[cur].edge.end() && ans.size()!=edge_num){
				if(ans.size())ans.pop_back();
				else break;
				int pre = ans.back();
				
				list<int>::iterator k;
				for(k = adj_list[cur].edge.begin();k!=adj_list[cur].edge.end();++k)
					if(*k == -1)break;
				*k = pre;
				
				adj_list[pre].edge.remove(-1);
				adj_list[pre].edge.push_back(cur);
				
				cur = pre;
				continue;
			}	
				
			ans.push_back(next);
			cur = next;
			if(ans.size()==edge_num+1){
				for(deque<int>::iterator it = ans.begin();it!=ans.end();++it)
					cout<< *it <<" ";
				cout << endl;
				return 1;
			}
		}
		++start;
		if(start==vertex_num) return 0;
	}
	
}