
/* Default Constructor for Gtu Set*/
template<typename T>
GtuSet<T>::GtuSet() : ContainerRepository<T>(){this->iter = this->root;}
        
/* Add elements to Set in an ascending order*/        

template<typename T>
void GtuSet<T>::add(T value){
        this->iter = this->root;
    if(this->root == nullptr){
        this->root = this->createNode(value);
        this->iter = this->root;
        this->iter->next = nullptr;
        ++this->Size;
    }
    else if(checkEntity(value) != true){
        ++this->Size;
        if(this->root->_data > value){
            std::shared_ptr<Node<T>> temp = this->createNode(value);
            temp->next = this->root;
            this->root = temp;
            
            
        }
        else {
            
            while (this->iter->next != nullptr && this->iter->next->_data < value)
            {   
                this->iter = this->iter->next;
                        
            }
            
            std::shared_ptr<Node<T>> temp = this->createNode(value);
            temp->next = this->iter->next;
            this->iter->next = temp;
            
        
        }
        this->iter = this->root;
    }
    
}
    

/* Public insert function add element in an ascending order*/
template<typename T>
void GtuSet<T>::insert(T value){
    add(value);
    
}

template<typename T>
GtuSet<T> GtuSet<T>::intersectSet(const GtuSet<T> & other){
    return other;
}

template<typename T>
GtuSet<T> GtuSet<T>::unionSet(const GtuSet<T> & other){
    return other;
}

/* Check if the element to be added is in the set already or not*/
template<typename T>
bool GtuSet<T>::checkEntity(T &value){
    this->iter =this->root;
    while(this->iter != nullptr){
        if(this->iter->_data == value) return true;
        this->iter = this->iter->next; 
    }
    this->iter = this->root;
    return false;
}
