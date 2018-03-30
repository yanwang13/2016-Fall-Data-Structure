#include <iostream>
#include <iomanip>
using namespace std;

class MatrixTerm{
	friend class SparseMatrix;
	
	private:
		int row, col;
		float value;
};
class SparseMatrix{
	private:
		int rows,cols,terms,capacity;
		//rows and cols are the size of the matrix
		//terms is the total numnber of nonzero entries
		//capacity is the size of smArray
		
		MatrixTerm *smArray;
		int *rowStart;
	
	public:
		SparseMatrix(int rows, int cols);
		SparseMatrix(const SparseMatrix &a); //copy constructor
		~SparseMatrix();
		float get(int row, int col);
		void set(int row, int col, float value);
		void list_sparse();
		void list_full();
		SparseMatrix Add(SparseMatrix b);
		void operator=(const SparseMatrix &); 
		int Search(int row, int col, const SparseMatrix &a);
};

SparseMatrix::SparseMatrix(int rows, int cols):rows(rows),cols(cols){
	terms = 0;
	capacity = 1;
	rowStart = new int[rows];
	smArray = new MatrixTerm[capacity];

	for(int i=0;i<rows;i++)
		rowStart[i]=0;
}

SparseMatrix::SparseMatrix(const SparseMatrix &a){
	rows = a.rows;
	cols = a.cols;
	terms = a.terms;
	capacity = a.capacity;
	
	rowStart = new int[rows];
	smArray = new MatrixTerm[capacity];
	
	for(int i=0;i<rows;++i){
		rowStart[i] = a.rowStart[i];
	}
	
	for(int i=0;i<terms;++i){
		smArray[i] = a.smArray[i];
	}
}

SparseMatrix::~SparseMatrix(){
	delete [] smArray;
	delete [] rowStart;
}

float SparseMatrix::get(int row, int col){
	if(row>(rows-1)||col>(cols-1)){
		std::cout<<"you can only get the term that is in the matrix.";
		return -2;
	}
	
	int k=Search(row, col, *this);
	if(k==-1)
		return 0;

	return smArray[k].value;
}

void SparseMatrix::set(int row, int col, float value){
	if(row>(rows-1)||col>(cols-1)){
		std::cout<<"you can only set the term that is in the matrix.\n";
		return;
	}

	int k = Search(row, col, *this);
	
	//when the term already exits
	if(k!=-1){
		if(value==0){
			--terms;
			
			//delete that term
			for(int i=k;i<terms;++i){
				smArray[i] = smArray[i+1];
			}

			//modify rowStart
			for(int i=row+1;i<=this->rows;++i){
				--rowStart[i];
			}
			return;
		}

		else
			smArray[k].value = value;
		return;	
	}
	
	//adding new term
	else{
		++terms;
		
		//if capacity is not enough
		if(terms>capacity){
			capacity*= 2;
			
			MatrixTerm *tmp = new MatrixTerm[capacity];
			
			for(int i=0;i<terms-1;++i){
				tmp[i] = smArray[i];
			}

			delete [] smArray;
			smArray = tmp;
		}
		
		//finding where to put the new term
		int index=rowStart[row]; //index represent where to put the new term
		while(index<rowStart[row+1] && index<terms){
			if(col>smArray[index].col && col<smArray[index+1].col)
				break;
			++index;
		}
		if(index==terms)
			--index;

		//shift the element after index a position back
		for(int i=terms-1;i>index;--i){
			smArray[i] = smArray[i-1];
		}
		
		smArray[index].row = row;
		smArray[index].col = col;
		smArray[index].value = value;
		
		//modify rowStart
		for(int i=row+1;i<rows;++i){
			++rowStart[i];
		}
		return;
	}

		


}

void SparseMatrix::list_sparse(){
	for(int i=0;i<terms;i++){
		std::cout<<"<"<<smArray[i].row<<","<<smArray[i].col<<","<<smArray[i].value<<"> ";
	}
	cout<<"\n";
	return;
}

void SparseMatrix::list_full(){
	int k=0;
	//if(i, j) is in the smArray print its value
	for(int i=0;i<rows;++i){
		for(int j=0;j<cols;++j){
			if(smArray[k].row==i && smArray[k].col==j){
				cout<<setw(4)<<smArray[k].value;
				++k;
			}
			else
				cout<<setw(4)<<"0";
		}
		std::cout<<"\n";
	}
}

SparseMatrix SparseMatrix::Add(SparseMatrix b){
	if(b.rows==this->rows &&  b.cols==this->cols){
		SparseMatrix result(rows, cols);
		
		result.capacity = capacity + b.capacity;
		MatrixTerm *tmp = new MatrixTerm[result.capacity];
		int index_a=0, index_b=0, flag=0;
		for(int i=0;i<rows;++i){
			for(int j=0;j<cols;++j){
				
				//put in a's element
				if(smArray[index_a].row == i && smArray[index_a].col==j){
					tmp[result.terms++] = smArray[index_a++];
					flag = 1;
				}
				
				//if b also has this element 
				if(b.smArray[index_b].row == i && b.smArray[index_b].col==j){
					if(flag)
						tmp[result.terms-1].value += b.smArray[index_b++].value; 
					else
						tmp[result.terms++] = b.smArray[index_b++];
						
				}
				flag =0;
			}
		}
		
		delete [] result.smArray;
		result.smArray = tmp;
		
		//calculate the rowStart
		for(int i=0;i<terms;++i){
			int cur_row = result.smArray[i].row;
			for(int j= cur_row+1;j<rows;++j){
				++result.rowStart[j];
			}
		}		
		return result;
	}
	else{
		std::cout<<"size mismatch.\n";
		SparseMatrix a(0,0);
		return a;
	}
}

void SparseMatrix::operator=(const SparseMatrix &a){
	this->rows = a.rows;
	this->cols = a.cols;
	this->terms = a.terms;
	this->capacity = a.capacity;

	delete [] rowStart;
	delete [] smArray;

	rowStart =  new int[rows];
	smArray = new MatrixTerm[capacity];

	for(int i=0;i<rows;++i){
		rowStart[i] = a.rowStart[i];
	} 

	for(int i=0;i<terms;++i){
		smArray[i] = a.smArray[i];
	}
}

int SparseMatrix::Search(int row, int col, const SparseMatrix &a){
	int left= a.rowStart[row];
	int right = row==rows-1? terms+1 : a.rowStart[row+1]; //prevent out of rowStart
	while(left<right){
		int mid = (left+right)/2;

		if(col<a.smArray[mid].col)
			right = mid -1;
		else if(col>a.smArray[mid].col)
			left = mid + 1;
		else return mid;
	}
	return -1;
}
 

