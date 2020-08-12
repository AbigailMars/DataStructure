typedef int Rank;
#define DEFAULT_CAPACITY 3  //默认的初始容量


template<typename T>class Vector{
protected:
    Rank size;
    int capacity;
    T* elem;
    void copyFrom(T const* A,Rank lo,Rank hi);
    void expand();//空间不足时扩容
    void shrink();//装填因子过小时压缩
    bool bubble(Rank lo,Rank hi);
    bool bubbleSort(Rank lo,Rank hi);
    Rank max(Rank lo,Rank hi);
    void selectionSort(Rank lo,Rank hi);
    void merge(Rank lo,Rank mi,Rank hi);
    void mergeSort(Rank lo,Rank hi);
    void heapSort(Rank lo,Rank hi);
    Rank partition(Rank lo,Rank hi);
    void quickSort(Rank lo,Rank hi);
    void shellSort(Rank lo,Rank hi);
public:
    //构造函数
    Vector(int c =DEFAULT_CAPACITY,int s = 0,T v = 0){
        elem = new T[capacity=c];
        size = s;
        for(size = 0;size < s;elem[size++] = v);//s<=c
    }
    Vector(T const*A,Rank n){
        copyFrom(A,0,n);
    }
    Vector(T const*A,Rank lo,Rank hi){
        copyFrom(A, lo, hi);
    }
    Vector(Vector<T> const&v){
        copyFrom(v.elem, 0, v.size);
    }
    Vector(Vector<T> const&v,Rank lo,Rank hi){
        copyFrom(v.elem, lo, hi);
    }
    //析构函数
    ~Vector(){
        delete []elem;
    }
    
    //只读访问接口
    Rank length() const{
        return size;
    }
    bool empty(){
        return !size;
    }
    Rank find(T& e)const{
        return find(e,0,size);
    }
    Rank find(T& e,Rank lo,Rank hi)const;
    Rank search(T const& e)const{
        return(0>=size)?-1:search(e,0,size);
    }
    Rank search(T const&e,Rank lo,Rank hi)const;
    
   //可写访问接口
    T& operator[](Rank r);
    const T& operator[](Rank r) const;
    Vector<T> &operator=(Vector<T> const&);
    
    T remove(Rank r);
    int remove(Rank lo,Rank hi);
    Rank insert(Rank r,T const&e);
    Rank insert(T const&e){
        return insert(size,e);
    }
    void sort(Rank lo,Rank hi);
    void sort(){
        sort(0,size);
    }
    void permute();
    void unsort(Rank lo,Rank hi);
    void unsort(){
        unsort(0,size);
    }
    int disordered() const;
    int deduplicate();
    int uniquify;
    
    //遍历
    void traverse(void(*)(T&));
    template<typename VST>void traverse(VST&);
};//Vector

template<typename T>
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi){
    elem = new T[capacity = 2*(hi-lo)];
    size = 0;
    while(lo<hi){
        elem[size++] = A[lo++];
    }
}

template<typename T>
void Vector<T>::expand(){
    if(size < capacity) return;
    if(capacity <DEFAULT_CAPACITY) capacity = DEFAULT_CAPACITY;
    T* oldElem = elem;
    elem = new T(capacity <<=1);
    for(int i =0;i<size;i++){
        elem[i] = oldElem[i];
    }
    delete []oldElem;
}

template<typename T>
void Vector<T>::shrink(){
    if (capacity < DEFAULT_CAPACITY <<1) return;
    if(size<<2 >capacity) return;
    T* oldElem = elem;
    elem = new T(capacity >>=1);
    for(int i =0;i<size;i++){
        elem[i] = oldElem[i];
    }
    delete []oldElem;
}

template<typename T>
bool Vector<T>::bubble(Rank lo,Rank hi){
    int flag = true;
    for(int i = lo; lo<hi;i++){
        if(elem[i] > elem[i+1]){
            flag = false;
            T tmp = elem[i];
            elem[i] = elem[i+1];
            elem[i+1] = elem[i];
        }
    }
    return flag;
    }

template<typename T>
bool Vector<T>::bubbleSort(Rank lo,Rank hi){
    while(!bubble(lo,hi--));
}

template<typename T>
Rank Vector<T>::max(Rank lo,Rank hi){ // O(n),有优化方法，见FindMax
    int max = lo;
    for(int i=lo;i<=hi;i++){
        if(elem[max] < elem[i]){
            max = i;
        }
    }
    return max;
}

template<typename T>
void  Vector<T>::selectionSort(Rank lo,Rank hi){
    for(int i=0;i<=hi;i++){
        Rank rank = max(lo,hi);
        int tmp = elem[hi];
        elem[hi] = elem[rank];
        tmp = elem[hi];
        --hi;
    }
}

template<typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi){//new 和delete数组操作 占用大量CPU时间
    int i =lo,j=mi+1;
    T* aux = new T[hi-lo+1];
    for(int k=lo;k<=hi;k++){
        aux[k] = elem[k];
    }
    for(int k=lo;k<=hi;k++){
        if(i > mi) elem[k++] = aux[j++];
        else if(j>hi) elem[k++] = aux[i++];
        else if(elem[i]>elem[j]) elem[k++] = aux[j++];
        else elem[k++] = aux[i++];
    }
}

template<typename T>
void Vector<T>::mergeSort(Rank lo,Rank hi){
    int mi = (lo+hi)>>1;
    mergeSort(lo,mi);
    mergeSort(mi+1,hi);
    merge(lo,mi,hi);
}

template<typename T>
void heapSort(Rank lo,Rank hi){//堆排序
    
}

template<typename T>
Rank Vector<T>::partition(Rank lo,Rank hi){
    int pivot = elem[lo];
    while(lo<hi){
        while(lo<hi&&pivot<=elem[hi]) --hi;
        elem[lo] = elem[hi];
        while(lo<hi&&pivot>=elem[lo]) --lo;
        elem[hi] = elem[lo];
    }
    elem[lo] = pivot;
    return lo;
}

template<typename T>
void Vector<T>::quickSort(Rank lo,Rank hi){
    int pivotPos = partition(lo, hi);
    quickSort(lo,pivotPos-1);
    quickSort(pivotPos+1,hi);
}

template<typename T>
void Vector<T>::shellSort(Rank lo,Rank hi){
    int length = hi-lo+1;
    for (int dk=length/2;dk>=1;dk=dk/2){
        for(int i=dk+1;i<length;i++){
            for(int j=i;elem[j]<elem[j-dk];j=j-dk){
                int tmp = elem[j];
                elem[j] = elem[j-dk];
                elem[j-dk] = tmp;
            }
        }
    }
}

template<typename T>
Rank Vector<T>::find(T& e,Rank lo,Rank hi)const{
    Rank rank = -1;//若无，，则返回初始值-1
    for(int i=lo;i<=hi;i++){
        if(e == elem[i]){
            rank = i;
        }
    }
    return rank;
}

template<typename T>
Rank Vector<T>::search(T const& e,Rank lo,Rank hi)const{
   return (rand() % 2)?
    binSearch1(e,lo,hi):binSearch2(e,lo,hi);
}

template<typename T>
static Rank binSearch1(T const& e,Rank lo,Rank hi){//1.左右分支不平衡 2.重复元素随机 3.查找失败不能返回失败位置
    while(lo<hi){//成功查找能提前停止
        Rank mi = (lo+hi)>>1;
        if(e == elem[mi]) {
           return mi;
        }else if(e < elem[mi]){
            hi = mi;
        }else{
            lo = mi+1;
        }
        return lo;
    }
    return -1;
}


template<typename T>
static Rank binSearch2(T const& e,Rank lo,Rank hi){//解决了左右分支以及重复元素选择后置位的
   while(lo<hi){//成功查找不能提前停止
       Rank mi = (lo+hi)>>1;
       if(e < elem[mi]){
           hi = mi;
       }else{
         lo = mi+1;
       }
   }
   return --lo;
}
    
template <typename T>
T& Vector<T>::operator[](Rank r){
    return elem[r];
}
template <typename T>
const T& Vector<T>::operator[](Rank r) const{
    return elem[r];
}
template <typename T>
Vector<T> & Vector<T>::operator=(Vector<T> const& v){
    if(elem) delete[]elem;
    copyFrom(v.elem, 0, v.size);
    return *this;
}

template <typename T>
static bool lt( T* a,T* b){return lt(*a, *b);}
template <typename T>
static bool lt( T& a,T& b){return a<b;}
template <typename T>
static bool eq( T* a,T* b){return eq(*a, *b);}
template <typename T>
static bool lt( T& a,T& b){return a==b;}




template <typename T>
T Vector<T>::remove(Rank r){
    T e = elem[r];
    remove(r,r+1);
    return e;
}

template <typename T>
int Vector<T>::remove(Rank lo,Rank hi){ //[lo,hi)
    if(lo == hi) return 0; //处于效率考虑，单独处理退化情况
       for(int i=hi;i<size;++i){
           elem[lo++] = elem[i++];
       }
      size = lo;
      shrink();
      return hi-lo;
}

template <typename T>
Rank Vector<T>::insert(Rank r,T const&e){
    expand();//若有必要，扩容
    for(int i=size;i>r;--i){
        elem[i] = elem[i-1];
    }
    elem[r] = e;
    ++size;
    return r;
}

template <typename T>
void Vector<T>::sort(Rank lo,Rank hi){
    switch(rand()%7){
        case 1:bubbleSort(lo,hi);
            break;
        case 2:selectionSort(lo,hi);
            break;
        case 3:mergeSort(lo,hi);
            break;
        case 4:heapSort(lo,hi);
            break;
        case 5:quickSort(lo,hi);
            break;
        case 6:shellSort(lo,hi);
            break;
            
    }
}

template <typename T>
void Vector<T>::permute(){
    for(int i=size;i>0;--i){
        T tmp = elem[i-1];
        int random = rand()%sie;
        elem[i-1] = elem(random);
        elem[random] = tmp;
    }
}

template <typename T>
void Vector<T>::unsort(Rank lo,Rank hi){
    T *V = elem + lo; //[lo,hi)
    for( Rank i = hi-1o;i>0;--i){ //[0,i)
        T tmp = elem[i -1];
        int random = rand()%i;
        elem[i-1] = elem[ranom];
        elem[random] = tmp;
    }
    
}

template <typename T>
int Vector<T>::disordered() const{//有序性甄别
    int count = 0;
    for(int i=1;i<size;i++){
        if(elem[i-1] > elem[i])
            count++;
        }
    return count;
}

template <typename T>
int Vector<T>::deduTplicate(){
    //无序向量低效版
    int oldSize = size;
    Rank i = 1;
    while(i < size){
      (find(elem[i],0,size) < 0)?
        i++ : remove(i);
    }
    return oldSize - size;d
}

template <typename T>
int Vector<T>::uniquify(){
    //低效版
//    int oldSize = size;
//    int i = 1;
//    while(i<size){
//        elem[i-1] == elem[i]? remove(i);
//        i++;
//    }
//    return oldSize - size;
    //高效版
    int i = 0;
    int j = 0;
    while(++j < size){
        if (elem[i] != elem[j]){
            elem[++i] = elem[j];
        }
    }
    size = ++i;
    shrink();
    return j-i;
}
 
 //遍历
template <typename T>
void Vector<T>::traverse(void(*)(T& e)){
    for(int i=0;i<size;++i){
        visit(elem[i]);//遍历向量
    }
}

/**
支持对向量元素的关联修改：
          1.各元素独立修改
          2.根据某个（些）元素的数值相应的修改另一元素
          3.前一形式也可，但要繁琐很多
 */
template<typename VST> void traverse(VST& visit){
    for(int i=0;i<size;++i){
        visit(elem[i]);
    }
}
