using namespace GTU;
    
    /* ELEMENTS ARE STRORED AS LINKED LIST*/



    /* Default Constructor for Containers*/
    template<typename T>            
    ContainerRepository<T>::ContainerRepository(){ 
        root = nullptr;
        iter = root;
        Size =0;
        maxSize =1000;
    }

    /* Copy Constructor for Containers*/
    template<typename T>
    ContainerRepository<T>::ContainerRepository(const ContainerRepository<T>& other) : Size(other.Size), maxSize(other.maxSize){ 

        if(other.root != nullptr){

            std::shared_ptr<Node<T>> iterator;
            iterator = other.root;                
            
            this->root = createNode(iterator->_data);
            
            this->iter = this->root;
            

            iterator = iterator->next;                    

            while(iterator!=nullptr){
                
                this->iter->next = createNode(iterator->_data);
                iterator = iterator->next;
                this->iter = this->iter->next;
                
            }
        }
        this->iter = this->root;

    }

    /* Move constructor for Containers*/ 
    template<typename T>
    ContainerRepository<T>::ContainerRepository(ContainerRepository&& other){;
        root = other.root;
        this->Size = other.Size;

    
        other.root.reset();
        other.root = nullptr;
        this->iter = this->root;
    }
    /* Assigment Operator for Containers*/
    template<typename T>
    ContainerRepository<T>& ContainerRepository<T>::operator=(const ContainerRepository<T>& other){
        
        if(&other != this){
            *this = ContainerRepository<T>(other);
            this->iter = this->root;
            this->Size = other.Size;

        }
        return *this;
    }
    
    /* Move Assigment Operator for Containers*/
    template<typename T>
    ContainerRepository<T>& ContainerRepository<T>::operator=(ContainerRepository<T>&& other){
        
        this->clear();
        this->Size = other.Size;
        this->root = other.root;
        other.root = nullptr;
        return *this;
    }

    /* Check if the container is empty or not*/
    template<typename T>
    bool ContainerRepository<T>::empty() const{
        bool status = false;
        if(root == nullptr){
            status = true;
        }
        return status;
    }

    /* Get Containers Element Number*/
    template<typename T>
    int ContainerRepository<T>::size() const{
        return this->Size;

    }

    /* Erase desired position element using iterator from Container*/
    template<typename T>
    void ContainerRepository<T>::erase(const GtuIterator<T>& a){
        
        this->iter = this->root;
        
        if(this->root->next == nullptr) root.reset();
        else if(this->root == a.iter &&  root->next != nullptr){
            
            this->root = root->next;
            this->iter.reset();
            this->iter = nullptr;
            
        }

        else{
            
            while(this->iter->next!=a.iter)    {this->iter = this->iter->next;}
            
                if(iter->next->next != nullptr) {this->iter->next = this->iter->next->next;
                    std::shared_ptr<Node<T>> temp = this->iter->next;
                    std::cerr << temp << " "<< iter->next->_data;
                    temp.reset();
                    temp = nullptr;
                ;}        
                else{
                    iter->next.reset();
                }
        }
        --this->Size;
        this->iter = this->root;
    }

    /* Clear the Container fully*/
    template<typename T>
    void ContainerRepository<T>::clear(){
        

        this->iter = root;
        while(this->iter!=nullptr){
            this->iter = this->iter->next;
            
            root.reset();
            
            root = nullptr;
            root = this->iter;
        }
        this->Size =0;
        
    }
    
    /* Return iterator that point the beginnig of the Container*/
    template<typename T>
    GtuIterator<T> ContainerRepository<T>::begin(){return GtuIterator<T>(root);}
    
    /* Return iterator that point the end of the Container*/
    template<typename T>
    GtuIterator<T> ContainerRepository<T>::end(){
        this->iter = this->root;
        while(this->iter->next != nullptr){
            this->iter = this->iter->next;
        }

        return GtuIterator<T>(this->iter);

    }

    /* Return const iterator that point the beginnig of the Container*/
    template<typename T>
    const GtuIterator<T> ContainerRepository<T>::cbegin() {}
    
    
    /* Return const iterator that point the end of the Container*/
    template<typename T>
    const GtuIterator<T> ContainerRepository<T>::cend(){}


    /* Create New Node to store The element*/
    template<typename T>
    std::shared_ptr<Node<T>> ContainerRepository<T>::createNode(T  value){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp->_data = value;
        
        return temp;
    }

    /* Print the elements in Container*/
    template<typename T>
    void ContainerRepository<T>::print(){
        
        this->iter = this->root;

        while(this->iter != nullptr){
            std::cout<<this->iter->_data<<" ";
            this->iter = this->iter->next;
        }
        this->iter = root;
    }

    /* Destructor */
    template<typename T>
    ContainerRepository<T>::~ContainerRepository<T>(){}

    /* Set the Container size, If the Container Size negative then throw exception*/
    template<typename T>
    void ContainerRepository<T>::setSize(int maxSize){
        if(maxSize>0){
            this->maxSize = maxSize;
        }
        else  throw "Unproper Value";
    }