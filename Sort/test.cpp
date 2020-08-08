#include <stddef.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

typedef int Rank;

template <typename T> struct ListNode {
	T data;
	ListNode<T>* pred;
	ListNode<T>* succ;

	ListNode() {} // @suppress("Class members should be properly initialized")
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL)
		: data(e), pred(p), succ(s) {}
	ListNode<T>* insertAsPred(T const& e){
	      ListNode<T>* x = new ListNode ( e, pred, this );
	      pred->succ = x; pred = x;
	      return x;
	 };
	ListNode<T>* insertAsSucc(T const& e){
		ListNode<T>* x = new ListNode(e,this,succ);
		succ->pred = x; succ = x;
	};
};

template <typename T> class List{

private:
	int _size;//规模
	ListNode<int>* header;
	ListNode<int>* trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNode<int>*, int);
	void merge(ListNode<int>*&, int, List<T>&, ListNode<int>*, int);
	void mergeSort(ListNode<int>*&, int);
	void selectionSort(ListNode<int>*, int);
	void insertionSort(ListNode<int>*, int);

public:
    List(){init();}
    List(List<T> const& L);
    List(ListNode<int>* p,int n);
    List(List<T> const& L,Rank r,int n);

    ~List();
    Rank size() const{return _size;}
    bool empty() const{return _size == 0;}
    bool valid(ListNode<int>* p){
    	return p&&(trailer!=p)&&(header!=p);
    }
    T& operator[] (Rank r) const;
    ListNode<int>* first() const{return header->succ;}
    ListNode<int>* last() const{return trailer->pred;}
    ListNode<int>* find(T const& e){return find(e,_size,trailer);}
    ListNode<int>* find(T const& e,int n,ListNode<int>* p) const;
    ListNode<int>* search(T const& e){return search(e,_size,trailer);}
    ListNode<int>* search(T const& e,int n,ListNode<int>* p) const;
    ListNode<int>* selectMax(ListNode<int>* p, int n);
    ListNode<int>* selectMax() {return selectMax(header->succ, _size);}
    ListNode<int>* insertAsFirst(T const& e);
    ListNode<int>* insertAsLast(T const& e);
    ListNode<int>* insertA(ListNode<int>* p,T const& e);
    ListNode<int>* insertB(ListNode<int>* p,T const& e);
	void sort() {sort(first(), _size);}
	void sort(ListNode<int>* p, int n);
    int deduplicate();
    int uniquify();
    T remove(ListNode<int>* p);

    void traverse(void (*visit) (T&));
    template <typename VST> void traverse(VST&);
};

template <typename T> void List<T>::init(){
	header = new ListNode<int>;
	trailer = new ListNode<int>;
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;//记录规模
}

template <typename T> int List<T>::clear(){//清空列表
	int oldSize = _size;
	while(0 < _size){
		remove(header->succ);
	}
	return oldSize;
}

template <typename T> void List<T>::copyNodes(ListNode<int>* p,int n){
	init();
	while(n--){
		insertAsLast( p->data );
	}
	p = p->succ;
}

template <typename T> void List<T>::merge(ListNode<int>* & p, int n, List<T>& L, ListNode<int>* q, int m){
   ListNode<int>* pp = p->pred;
   while(0 < m){
	   if ( (0 < n)&&(p->data <= q->data)){
		   if(q == (p = p->succ))break;n--;}
	   else{
		   insertB(p, L.remove((q = q->succ)->pred));m--;}
	   p = pp->succ;
   }
}

template <typename T> void List<T>::mergeSort(ListNode<int>* &p, int n){
    if(n < 2) return;
    int m = n>>1;
    ListNode<int>* q = p;
    for(int i = 0;i < m;i++){
    	q = q->succ;
    }
    mergeSort(p,m);mergeSort(q,n-m);
    merge(p,m,*this,q,n-m);
}

template <typename T> void List<T>::selectionSort(ListNode<int>* p, int n){//?
    ListNode<int>* head = p->pred;
    ListNode<int>* tail = p;
    for(int i = 0;i<n;i++) tail = tail->succ;
    while(1 < n){
    	ListNode<int>* max = selectMax(head->succ,n);
    	insertB(tail,remove(max));
    	tail = tail->pred;
    	n--;
    }
}

template <typename T> void List<T>::insertionSort(ListNode<int>* p, int n){ //valid(p) && rank(p)+n <_size
	for (int r = 0; r < n; r++){
		insertA( search(p->data,r,p), p->data );
		p = p->succ;//转向下一节点
		remove(p->pred);
	}
}

template <typename T> List<T>::List(List<T> const& L) { // @suppress("Class members should be properly initialized")
	copyNodes(L.first(), L._size);
}

template <typename T> List<T>::List(ListNode<int>* p,int n){
	copyNodes(p,n);
}

template <typename T> List<T>::List(List<T> const& L,Rank r,int n){ // @suppress("Class members should be properly initialized")
	copyNodes(L[r],n);
}

template <typename T> List<T>::~List(){
    clear();
    delete header;
    delete trailer;
}

template <typename T> T& List<T>::operator[] (Rank r) const{ //通过Rank直接访问列表节点（虽方便，但是效率极低）
    ListNode<int>* p =first();
    while(0 < r--){
    	p = p->succ;
    }
    return p->data;
}

template <typename T> ListNode<int>* List<T> :: find(T const& e,int n,ListNode<int>* p) const{
	while(0 < n--){
		if (e == ((p = p->pred)->data))
			return p;
	}
	return NULL;  //复杂度O(n）
}

template <typename T> ListNode<int>* List<T> :: search(T const& e,int n,ListNode<int>* p) const{
	while(0 < n--){
		if ((p = p->pred)->data <= e) // ?
		break;
	}
	return p;
}//失败时返回左边界的前驱

template <typename T> ListNode<int>* List<T> :: selectMax(ListNode<int>* p, int n){
	ListNode<int>* max = p;
	for (ListNode<int>* cur =p;1<n;n--){
		if(! ((cur = cur->succ )->data >= max->data) )
			max = cur;
	}
	return max;
}

template <typename T> ListNode<int>* List<T> ::insertAsFirst(T const& e){
	_size++;
	return header->insertAsSucc(e);
}

template <typename T> ListNode<int>* List<T> ::insertAsLast(T const& e){
	_size++;
	return trailer->insertAsPred(e);
}


template <typename T> ListNode<int>* List<T> ::insertA(ListNode<int>* p,T const& e){
	_size++;
	return p->insertAsSucc(e);
}

template <typename T> ListNode<int>* List<T> ::insertB(ListNode<int>* p,T const& e){
	_size++;
	return p->insertAsPred(e);
}


template <typename T> void List<T>:: sort(ListNode<int>* p, int n){
	switch(rand()%3){
	case 1 :insertionSort (p,n);break;
	case 2 :selectionSort (p,n);break;
	default :mergeSort (p,n);break;
	}
}

template<typename T> int List<T>::deduplicate(){
	if(_size < 2) return 0;
	int oldSize = _size; //记录原规模
	ListNode<int>* p = header;
	Rank r = 0;
	while(trailer != (p = p->succ)){//依次直到末节点
		ListNode<int>* q =find(p->data,r,p);//前驱中查找雷同元素
		q? remove(q):r++;	//?
	}
	return oldSize -_size;
}

template <typename T> int List<T>::uniquify(){//成批剔除重复元素，效率极高
	if(_size < 2) return 0;
	int oldSize = _size;
	ListNode<int>* p = first();
	ListNode<int>* q; //q为其后继
	while(trailer != (q = p->succ)){//反复考察紧邻的节点对
		if (p->data != q->data) p=q;//若互异，则转向下一区段
		else remove(q);//若雷同则删除
	}
	return oldSize-_size;
}

template <typename T> T List<T>::remove(ListNode<int>* p){
   T e = p->data;
   p->pred->succ = p->succ;
   p->succ->pred = p->pred;
   delete p;
   _size--;
   return e;
}

template <typename T> void List<T>::traverse(void (*visit) (T&)){
	for(ListNode<int>* p = header->succ;p!=trailer;p=p->succ){
		visit (p->data);
	}
}

template <typename T> template <typename VST> void List<T>::traverse(VST& visit){
	for(ListNode<int>* p = header->succ;p!=trailer;p=p->succ){
		visit (p->data);
	}
}

int main(){

}




