

/* Default Gtu Array Constructor*/
template<typename T,int size>
GtuArray<T,size>::GtuArray() : ContainerRepository<T>(){
                
    this->setSize(size);
    
    int counter =0;

    this->root = this->createNode();
    this->iter = this->root;
    ++counter;
    this->Size = size;
    
    while(counter != size && size !=0){
        this->iter->next = this->createNode();
        
        this->iter = this->iter->next;
        
        ++counter;
    }
    this->iter = this->root;
            
};

/* Iterotor point to reverse of begin*/
template<typename T,int size>
GtuIterator<T> GtuArray<T,size>::rbegin(){
    return this->end();
}

/* Iterotor point to reverse of end*/
template<typename T,int size>
GtuIterator<T> GtuArray<T,size>::rend(){ return this->root;}

/* Access Gtu Array element using operator[], it returns reference*/
template<typename T,int size>
T& GtuArray<T,size>::operator[](int index){
    int counter =0;
        
        this->iter = this->root;
        while(counter!= index){
            
            this->iter = this->iter->next;
            ++counter;
        }
    
    return this->iter->_data;
}


/* Fill the Gtu Array fully with desired element*/
template<typename T,int size>
void GtuArray<T,size>::fill(T data){
    this->iter = this->root;
    while(this->iter != nullptr){
        this->iter->_data = data;
        this->iter = this->iter->next;
    }
    this->iter = this->root;

}

/* Get the elemet at the end of the Array*/
template<typename T,int size>
T & GtuArray<T,size>::back(){
    
    return this->end().iter->_data;


}

/* Get the elemet at the beginnig of the Array*/
template<typename T,int size>
T & GtuArray<T,size>::front(){
    
    return this->begin().iter->_data;
}