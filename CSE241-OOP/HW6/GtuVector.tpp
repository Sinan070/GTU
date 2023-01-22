/* Default Constructor*/
template<typename T>
GtuVector<T>::GtuVector(int size) : ContainerRepository<T>(){};

/* Access the element using operator[], it returns reference*/
template<typename T>
T& GtuVector<T>::operator[](int index){
    int counter =0;
    
    this->iter = this->root;
    
    while(counter!= index){
        
        this->iter = this->iter->next;
        
        ++counter;
    }
    
return this->iter->_data;

}

/* Insert element with value to desired position pointed by iterator*/
template<typename T>
void GtuVector<T>::insert(const GtuIterator<T> & _iter,const T& value){

    this->iter = this->root;
    while (this->iter != _iter)
    {
        this->iter = this->iter->next;
    }

    this->iter->_data = value;
    this->iter = this->root;

}

/* Push Back operations, add element to end of vector*/
template<typename T>
void GtuVector<T>::push_back(const T& value){ add(value);};

/* PopBack operation, erase element in end of vector*/
template<typename T>
void GtuVector<T>::pop_back(){
    
    this->erase(this->end());
    
}

/* virtual add function implementation using linked list*/
template<typename T>
void GtuVector<T>::add(T value){
    this->iter = this->root;
if(this->root==nullptr){
        
        this->root = this->createNode(value);
        this->iter = this->root;
        this->iter->next = nullptr;
}
else{
    while(this->iter->next != nullptr){
        this->iter = this->iter->next;
    }
    
    this->iter->next = this->createNode(value);
    this->iter = this->iter->next;
    this->iter->next = nullptr;
    
}
    this->iter = this->root;
    ++this->Size;
    
}