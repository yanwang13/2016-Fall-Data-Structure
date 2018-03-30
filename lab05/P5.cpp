#include<fstream>
#include<iomanip>
#include "P5.h"

//hash function
int hashfunc(const string &K){
	unsigned long hash = 5381;
	for(int i=0;i<=K.size();++i)
		hash = ((hash<<5)+hash) + K[i];
	return hash % 1024;
}

int main(){
	
	string file_name;
	fstream file;
	
	cout << "Please enter the text file:\n";
	cin >> file_name;

	file.open(file_name, ios::in);
	
	if(!file){//chack if the input file_name is can be opened
		cout << "file could not be open"<<endl;
		exit(1);
	}
	
	char ch;
	MyHash<string,int> hash(&hashfunc, 1024);
	
	while(1){
		string input;
		while(file.get(ch)){
			if(ch>='a' && ch <='z')
				input.push_back(ch);
			else if(ch>='A' && ch<='Z')//transform upper case to lower case
				input.push_back(ch+32);
			else
				break;
		}
		
		if(input.size()){ //ignore if there is no character in the input
			int *find = hash.get_element(input);
			
			if(find==nullptr)
					hash.insert(input, 1);
			else
				++(*find);
		}
		
		if(file.eof())//finish putting record in the hash table if ecounter end of file
			break;
	}
	
	
	vector<std::pair<string, int>> output;
	hash.get_item(output);
	
	for(vector<std::pair<string,int>>::iterator it = output.begin() ; it != output.end(); ++it){

		cout << left<<setw(20)<<it->first<<right<<setw(4)<<it->second <<endl;//make the output looks better
	}
	
	return 0;
}
