#include<iostream>
#include<string>
#include<deque>
using namespace std;

class node{
	int data;
	node *down, *right;
	
	public:
		friend class GeneralTree;
	    node(const int data);
		~node();
};

node::node(const int data):data(data){
	down = nullptr;
	right = nullptr;
}
node::~node(){
	delete down;
	delete right;
}

class GeneralTree{
	node* root;
	
	public:
		GeneralTree(const std::string &str);
		~GeneralTree();
		void preorder_rec();
		void preorder_rec(node* cur);
		void preorder_nonrec();
		void postorder_rec();
		void postorder_rec(node* cur);
		void postorder_nonrec();
		void levelorder();
};

GeneralTree::GeneralTree(const std::string &str){
	deque<node*> ss;
	int tmp = 0;
	node* cur;
	
	int i=0;
	while(str[i]!=' ') //store the first num
		tmp = tmp*10 + (str[i++]-'0');
	root = new node(tmp);
	cur = root;
	++i; //skip the space
	
	tmp = 0;
	for(;i<=str.size();++i){
		if(str[i]=='(') {
			ss.push_back(cur);
			i += 2; //skip the space
			while(str[i]!=' ')tmp = tmp*10 + (str[i++]-'0');
			cur->down = new node(tmp);
			cur = cur->down;
			tmp = 0;
		}
		else if(str[i]==' '){
			cur->right = new node(tmp);
			cur = cur->right;
			tmp = 0;
		} 
		else if(str[i]==')'){
			cur = ss.back();
			ss.pop_back();
			++i; //skip the space
		}
		else tmp = tmp*10 + (str[i] - '0');
	}
}

GeneralTree::~GeneralTree(){
	delete root;
}

void GeneralTree::preorder_rec(){
	preorder_rec(root);
	cout<<endl;
}
void GeneralTree::preorder_rec(node* cur){
	if(cur){
		cout << cur->data << " ";
		preorder_rec(cur->down);
		preorder_rec(cur->right);
	}
}

void GeneralTree::preorder_nonrec(){
	deque<node*> ss;
	node* cur = root;
	while(1){
		while(cur){
			cout << cur->data <<" ";
			if(cur->right) ss.push_back(cur->right);//store the siblings
			cur = cur->down;
		}
		
		if(!ss.empty()){
			cur = ss.back();
			ss.pop_back();
		}
		else break;
	}
	cout << endl;
}

void GeneralTree::postorder_rec(){
	postorder_rec(root);
	cout<<endl;
}
void GeneralTree::postorder_rec(node* cur){
	if(cur){
		postorder_rec(cur->down);
		cout<< cur->data <<" "; //print the data when it don't have child
		postorder_rec(cur->right);
	}
}
void GeneralTree::postorder_nonrec(){//go as down as it can then go right
	deque<node*> ss;
	node* cur = root;
	while(1){
		while(cur){
			ss.push_back(cur);
			cur = cur->down;
		}
		
		if(!ss.empty()){
			cur = ss.back();
			ss.pop_back();
			cout << cur->data <<" ";
			cur = cur->right;
		}
		else break;
	}
	cout << endl;
}
void GeneralTree::levelorder(){
	deque<node*> q;
	node* cur = root;
	while(cur){
		cout<< cur->data <<" ";
		if(cur->down)
			q.push_back(cur->down);//store te child
		if(cur->right){
			cur = cur->right;//print the siblings
			continue;
		}
		cur =  q.front();
		q.pop_front();
	}
	cout<<endl;
}
