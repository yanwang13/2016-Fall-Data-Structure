#include<string>
#include<vector>
#include<list>
#include<iostream>
using namespace std;

template<class K,class E>
class MyHash{
	public:
		MyHash(int(*hf)(const K&), int nb);
		~MyHash();
		E* get_element(const K&);
		void insert(const K&, const E&);
		void get_item(vector<pair<K,E>>&) const;
	
	private:
		int (*hf) (const K&);
		int bucket;
		list<std::pair<K,E>>* slot;//array of linked list
};

template<class K,class E>
MyHash<K,E>::MyHash(int(*hf)(const K&), int nb):hf(hf){
	bucket = nb;
	slot = new list<std::pair<K,E>> [nb];
}

template<class K,class E>
MyHash<K,E>::~MyHash()
{
    delete []slot;
}

template<class K,class E>
E* MyHash<K,E>::get_element(const K& input){
	int pos = hf(input);//whcih bucket should the input be
		for(list<pair<string,int>>::iterator it= slot[pos].begin(); it != slot[pos].end(); ++it){
		if(it->first==input)
			return &(it->second);
	}
	return nullptr;//return null pointer if the input isn't in the bucket yet
}



template<class K,class E>
void MyHash<K,E>::insert(const K& input, const E& num){
	int pos = hf(input);//whcih bucket should the input be
	slot[pos].push_back(pair<K,E>(input, num));
}

template<class K,class E>
void MyHash<K,E>::get_item(vector<pair<K,E>>& out) const{
	for(int i=0;i<bucket;++i){
		for(list<pair<string,int>>::iterator it= slot[i].begin(); it != slot[i].end(); ++it){
			out.push_back(make_pair(it->first, it->second));//copy the record from the buckets in the vector one by one
		}
	}
}
