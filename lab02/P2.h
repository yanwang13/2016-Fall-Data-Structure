#include<iostream>
#include<iomanip>
#include <cstdlib>
using namespace std;

class node{
	public:
		friend class SparseMatrix;
		int row, col, value;
		node *right, *down;
};

class SparseMatrix{
	private:
		node* head;

	public:
		friend class node;
		SparseMatrix(int rows, int cols);
		SparseMatrix(const SparseMatrix &b);
		~SparseMatrix();
		float get(int row, int col)const;
		void set(int row, int col, float value);
		SparseMatrix Add(const SparseMatrix &b);
		SparseMatrix Multiply(const SparseMatrix &b);
		void Transpose();
		void operator=(const SparseMatrix& b);
		friend std::ostream& operator<<(std::ostream& os, const SparseMatrix& m);
};

SparseMatrix::SparseMatrix(int rows, int cols){

	head = new node;

	head->row = rows;
	head->col = cols;
	head->right = nullptr;
	head->down = nullptr;
	//create header nodes
	node *rowhead = head;
	for(int i=0;i<rows;++i){
		rowhead->down = new node;
		rowhead->down->right = nullptr;
		rowhead->down->down = nullptr;
		rowhead = rowhead->down;	
	}

	node *colhead = head;
	for(int i=0;i<cols;++i){
		colhead->right = new node;
		colhead->right->down = nullptr;
		colhead->right->right = nullptr;
		colhead = colhead->right;
	}
}

SparseMatrix::SparseMatrix(const SparseMatrix &b){
	head = new node;
	head->row = b.head->row;
	head->col = b.head->col;
	head->right = nullptr;
	head->down = nullptr;
	
	//initial matrix
	//create header nodes
	node *rowhead = head;
	for(int i=0;i<b.head->row;++i){
		rowhead->down = new node;
		rowhead->down->right = nullptr;
		rowhead->down->down = nullptr;
		rowhead = rowhead->down;
	}

	node *colhead = head;
	for(int i=0;i<b.head->col;++i){
		colhead->right = new node;
		colhead->right->down = nullptr;
		colhead->right->right = nullptr;
		colhead = colhead->right;
	}
	//copy b's nodes by row
	rowhead = b.head->down;
	node *cur;
	while(rowhead!=nullptr){
		for(cur=rowhead;cur->right!=nullptr;cur=cur->right){
			if(cur->right!=nullptr)
				set(cur->right->row, cur->right->col, cur->right->value);
		}
		rowhead = rowhead->down;
	}
}

SparseMatrix::~SparseMatrix(){
	node *next = head->down;
	node * currow = head->right;
	while(currow!=nullptr){ //erase by row;
		while(currow->right!=nullptr){
			node *cur = currow;
			currow = currow->right;
			delete cur;
		}
		delete currow;
		currow = next;
		if(currow==nullptr)
			break;
		next = next ->down;
	}

	delete head;
}

float SparseMatrix::get(int row, int col)const{

	if(row>(head->row-1)||col>(head->col-1)||row<0||col<0){
		cout<<"you can only get the term that is in the matrix.";
		return -2;
	}

	else{
		//find the right row
		node *findrow = head->down;
		for(int i=0;i<row;++i){
			findrow = findrow -> down;
		}


		for(node *tar= findrow;tar->right!=nullptr;tar= tar->right){
			if(tar->right->col == col)
				return tar->right->value;
		}

		return 0;
	}

}

void SparseMatrix::set(int row, int col,float value){
	if(row>(head->row-1)||col>(head->col-1)||row<0||col<0){
		std::cout<<"you can only set the term that is in the matrix.\n";
		return;
	}

	else{
		//find the right row
		node *findrow = head->down;
		int i;
		for(i=0;i<row;++i){
			findrow = findrow -> down;
		}
		
		node *tar;
		for(tar= findrow;tar->right!=nullptr;tar= tar->right){
			if(tar->right->col >col)
				break;
			else if(tar->right->col==col){
				//delete a element
				if(value==0){
					node *tmp = tar->right;
					tar->right = tmp->right;
					delete tmp;
					return;
				}

				tar->right->value = value;
				return;
			}
		}
		//find the right col
		node *findcol = head->right;
		for(int j=0;j<col;++j){
			findcol = findcol -> right;
		}
		node *k;
		for(k=findcol;k->down!=nullptr;k=k->down){
			if(k->down->row > row)
				break;
		}
		
		if(value==0)
			return;
		
		node *add;
		add = new node;

		add->row = row;
		add->col = col;
		add->value = value;

		add->right = tar->right==nullptr? nullptr: tar->right;
		tar->right = add;

		add->down = k->down==nullptr? nullptr: k->down;
		k->down = add;
		return;
	}
}

SparseMatrix SparseMatrix::Add(const SparseMatrix &b){
	if(b.head->row!=head->row ||  b.head->col!=head->col){
		cout<<"size mismatch.\n";
		SparseMatrix a(0,0);
		return a;
	}

	else{

		SparseMatrix result(head->row, head->col);
		
		for(int i=0;i<head->row;++i){
			for(int j=0;j<head->col;++j){
				result.set(i,j,get(i,j)+ b.get(i, j));
			}
		}
		return result;
	}
}

SparseMatrix SparseMatrix::Multiply(const SparseMatrix &b){
	if(b.head->row!=head->col){
		cout<<"size mismatch.\n";
		SparseMatrix a(0,0);
		return a;
	}

	else{
		SparseMatrix result(head->row, b.head->col);
		
		int sum;
		for(int i=0;i<result.head->row;++i){
			for(int j=0;j<result.head->col;++j){
				for(int k=0;k<head->col;++k){
					sum += get(i,k) * b.get(k,j);
				}
				result.set(i,j,sum);
				sum = 0;
			}
		}
		return result;
	}
}

void SparseMatrix::Transpose(){
	//create a new matirx
	SparseMatrix tmp(head->col, head->row);

	node *currow = head->down;
	//transpose
	while(currow!=nullptr){
		node *cur = currow->right;
		while(cur!=nullptr){
			tmp.set(cur->col,cur->row, cur->value);
			cur = cur->right;
		}
		currow = currow->down;
	}

	node *trans = tmp.head;
	tmp.head = this->head;
	this->head = trans;
}

std::ostream& operator<<(std::ostream& os, const SparseMatrix& m){
	node *currow = m.head->down;
	for(int i=0;i<m.head->row;++i){
		node *cur=currow-> right;
		for(int j=0;j<m.head->col;++j){
			if(cur!=nullptr && i==cur->row && j==cur->col){
				os << setw(4) << cur->value;
				cur = cur->right;
			}
			else
				os << setw(4) << "0";
		}
		os << "\n";
		currow = currow->down;
	}
	os << endl;
	return os;
}

void SparseMatrix::operator=(const SparseMatrix& b){
	head->row = b.head->row;
	head->col = b.head->col;
	//destroy old matrix
	node *next = head->down;
	node * currow = head->right;
	while(currow!=nullptr){ //erase by row;
		while(currow->right!=nullptr){
			node *cur = currow;
			currow = currow->right;
			delete cur;
		}
		delete currow;
		currow = next;
		if(currow==nullptr)
			break;
		next = next ->down;
	}
	
	//initial new matrix;
	node *rowhead = head;
	for(int i=0;i<b.head->row;++i){
		rowhead->down = new node;
		rowhead->down->right = nullptr;
		rowhead->down->down = nullptr;
		rowhead = rowhead->down;
	}

	node *colhead = head;
	for(int i=0;i<b.head->col;++i){
		colhead->right = new node;
		colhead->right->down = nullptr;
		colhead->right->right = nullptr;
		colhead = colhead->right;
	}
	
	rowhead = b.head->down;
	node *cur;
	while(rowhead!=nullptr){
		for(cur=rowhead;cur->right!=nullptr;cur=cur->right){
			if(cur->right!=nullptr){
				set(cur->right->row, cur->right->col, cur->right->value);
			}
				
		}
		rowhead = rowhead->down;
	}
	
	
}
