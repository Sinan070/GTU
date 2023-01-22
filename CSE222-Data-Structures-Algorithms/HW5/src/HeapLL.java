import java.io.Serializable;


public class HeapLL<E extends  Comparable<E>>extends  BT<E>{
    // These are the variables that are used in the class.
    private Node<E> root;
    private Node<E> tail;
    private boolean addReturn;
    private int size = 0;
    private int count = 0;
    private boolean getReturn;
    private E value;

    // This is the default constructor of the class.
    public HeapLL(){
        root = null;
    }
    // This is a constructor that takes a node as a parameter.
    public HeapLL(Node<E> root1){
        root = root1;
    }

    /**
     * The add() function is a wrapper for the offer() function
     *
     * @param data The data to be added to the queue.
     * @return The method returns a boolean value.
     */
    public boolean add(E data){
        return offer(data);

    }


    /**
     * The function takes in a data of type E and adds it to the heap
     *
     * @param data The data that is being added to the heap.
     * @throws  if the data to be added is null
     * @return The method returns a boolean value.
     */
    public boolean offer(E data) throws  NullPointerException{
        addReturn= false;
        // This is a check to make sure that the data being added to the heap is not null.
        if(data == null){
            throw  new NullPointerException();
        }
        ++size;
        // Calculating the height of the tree.
        int height = height(root);
        // This is the case when the heap is empty.
        if(root == null){
            root = new Node<>(data,null);
            tail = root;
        }
        else{
            // Adding the new node to the heap.
            for(int i  = 1 ; i<= height; ++i){
                root = add(root,i,data,root);
            }
        }

        // Making sure that the heap property is maintained.
        upHeapfiy(tail);
        return  true;
    }

    /**
     * The Node class is a generic class that implements the Serializable interface. It has four fields: data, left, right,
     * and parent. The data field is of type E, which is a generic type. The left, right, and parent fields are of type
     * Node<E>. The Node class has two constructors: a default constructor and a constructor that takes two parameters. The
     * default constructor initializes the data, left, right, and parent fields to null. The constructor that takes two
     * parameters initializes the data field to the value of the first parameter and the parent field to the value of the
     * second parameter. The left and right fields are initialized to null
     */
    protected  static class Node<E> implements Serializable {

        protected E data;
        protected Node<E> left;
        protected Node<E> right;
        protected Node<E> parent;
        public Node(){};
        public Node(E data, Node<E> p){
            this.data = data;
            left = null;
            right = null;
            parent = p;

        }
    }

    /**
     * If the data is null, throw a NullPointerException. If the localRoot is null, return a new node with the data. If the
     * level is greater than 0, recursively call the add function on the left and right subtrees
     *
     * @param localRoot The root of the local subtree
     * @param level The level of the tree where the data is to be inserted.
     * @param data the data to be added to the tree
     * @param p the parent of the node we are adding
     * @throws NullPointerException if the data to be adde is null
     * @throws ClassCastException if the data to be added not match the generic type
     * @return The localRoot is being returned.
     */
    private Node<E> add(Node<E> localRoot, int level, E data,Node<E> p) throws ClassCastException,NullPointerException{

        if(data == null){
            throw new NullPointerException();
        }

        if (localRoot == null) {
            addReturn = true;

            return tail= new Node<>(data,p);
        }

        if (level > 0) {
            if(!addReturn ){
                localRoot.left =add(localRoot.left, level - 1,data,localRoot);

            }
            if(!addReturn ) {
                localRoot.right = add(localRoot.right, level - 1, data,localRoot);
            }
        }
        return localRoot;
    }

    /**
     * If the parent of the localRoot is greater than the localRoot, swap the parent and the localRoot and call the
     * function again on the parent
     *
     * @param localRoot The node that we are currently looking at.
     */
    private void upHeapfiy(Node<E> localRoot){
        if(localRoot.parent == null)
        {
            return;
        }
        if(localRoot.parent.data.compareTo(localRoot.data) >0 )
        {
            E temp = localRoot.data;
            localRoot.data = localRoot.parent.data;
            localRoot.parent.data = temp;
            upHeapfiy(localRoot.parent);
        }
    }

    /**
     * The height of a tree is the number of edges on the longest path from the root to a leaf
     *
     * @param localRoot The root of the subtree we're currently looking at.
     * @return The height of the tree.
     */
    private int height(Node<E> localRoot){
        return (int)Math.ceil(Math.log(size +
                1) / Math.log(2))  ;
    }

    /**
     * It traverses the tree in pre-order fashion.
     *
     * @return A string representation of the tree.
     */
    public String preOrderTraverse(){
        StringBuilder builder = new StringBuilder();
        preOrderTraverse(root,builder);
        builder.append("\n");
        return builder.toString();
    }

    /**
     * > If the current node is not null, then print the current node, then traverse the left subtree, then traverse the
     * right subtree
     *
     * @param localRoot The root of the subtree we're currently traversing.
     * @param builder This is the StringBuilder object that will be used to build the string.
     */

    private void   preOrderTraverse(Node<E> localRoot,StringBuilder builder){
        if(localRoot != null) {
            builder.append(localRoot.data+"->");
            preOrderTraverse(localRoot.left,builder);
            preOrderTraverse(localRoot.right,builder);
        }

    }


    /**
     * We remove the last node of the heap and replace the root with it. Then we downheapify the root
     */
    public boolean remove( Object obj){
        if(root == null){
           return false;
        }
        int index = indexOf((E) obj);

        if(index == -1) {return  false;};
        Node<E> deleted = getNode(index);

        deleted.data = tail.data;

        //System.out.print(tail.parent.left.data);
        if(tail.parent.right == tail)
        {

            tail = tail.parent.left;
            tail.right = null;

        }
        else if(tail.parent.left == tail){
            tail = tail.parent;
            tail.left = null;

        }

        downHeapify(deleted);
        --size;
        return true;
    }

    /**
     * If the local root has a left child, and the left child has a right child, and the left child's right child is
     * smaller than the left child, swap the left child's right child with the left child
     *
     * @param localRoot The root of the subtree we're currently looking at.
     */
    private void downHeapify(Node<E> localRoot){
        Node<E> min;

        if(localRoot.left != null && localRoot.right != null){
            min = localRoot.left.data.compareTo(localRoot.right.data) < 0 ?  localRoot.left : localRoot.right;
        }
        else if(localRoot.right == null && localRoot.left != null){
            min = localRoot.left;
        }
        else if(localRoot.right != null && localRoot.left == null){
            min = localRoot.right;
        }
        else {
            return;
        }

        if(localRoot.data.compareTo(min.data) > 0){

            E temp = localRoot.data;
            localRoot.data = min.data;
            min.data = temp;
            downHeapify(min);
        }
    }

    /**
     * It returns the index of the first occurrence of the data in the list.
     *
     * @param data The data to be searched for.
     * @return The index of the data in the list.
     */
    private int indexOf(final E data){

        for (int i = 0 ; i < size ;++i){
            if(data.compareTo(getNode(i).data) == 0){
                return i;
            }
        }
        return -1;
    }

    /**
     * If the index of the data is greater than or equal to 0, then return true, otherwise return false.
     *
     * @param data The data to search for.
     * @return The index of the data.
     */
    public boolean contains(E data){
        return indexOf(data) >= 0;
    }

    /**
     * If the data is in the heap, swap it with its parent
     *
     * @param data The data to be inserted into the heap.
     * @return The method is returning a boolean value.
     */
    public boolean incPriority(final E data, final E newDATA ){
        int index = indexOf(data);
        if(index != -1){
            Node<E> node = getNode(index);
            node.data = newDATA;
            if(node.parent == null){
                downHeapify(root);
            }
            else if(node.parent.data.compareTo(newDATA)>0 ){

                upHeapfiy(node);
            }
            else if(node.parent.data.compareTo(newDATA)<0){

                downHeapify(node);
            }

            return true;
            }
        return  false;
    }



    /**
     * It removes the first element in the list and returns it.
     *
     * @return The data of the root node.
     */
    public E pool(){
        if(root == null) return  null;
        E retVal = root.data;
        remove(root.data);
        return retVal;
    }

    /**
     * If the root is null, return null, otherwise return the data of the root
     *
     * @return The data of the root node.
     */
    public E peek(){
        if(root == null) return null;
        else return root.data;
    }

    /**
     * It merges two heaps.
     *
     * @param heap1 The heap to be merged with the current heap.
     * @return A new heap that is the result of merging the two heaps.
     */
    public HeapLL<E> merge(final HeapLL<E> heap1){

        HeapLL<E> result = new HeapLL<>();
        for(int i = 0 ; i< this.size; ++i){
            result.add(this.getData(i));
        }
        for(int i = 0 ; i< heap1.size; ++i){
            result.add(heap1.getData(i));
        }
        return  result;
    }
    /**
     * Get the data of the node at the given index.
     *
     * @param index the index of the node you want to get
     * @return The data of the node at the given index.
     */
    private E getData(final int index){
        return getNode(index).data;
    }

    /**
     * The function takes in an index and returns the node at that index
     * Search the node level order.
     * @param index the index of the node you want to get
     * @return The node at the given index.
     */
    protected Node<E>  getNode(int index){
        count = 0;
        getReturn = false;
        if(index > size-1){
            return null;
        }
        int h =  (int)(Math.ceil(Math.log(index+2) / Math.log(2)));
        int i;
            int preCount = (int) Math.pow(2.0,h-1) -1;
            count = preCount;
        return getNode(this.root, h, index ,null);

    }

    /**
     * It returns the node at the given index.
     *
     * @param localRoot The root of the subtree we're currently looking at.
     * @param level The level of the tree we are currently at.
     * @param index the index of the node you want to get
     * @param retNode The node that is returned.
     * @return The node at the given index.
     */
    private Node<E> getNode(Node<E> localRoot,int level ,int index,Node<E> retNode) {

        if (localRoot == null) {
            return null;
        }
        if (level == 1){
            if(count == index){
                getReturn = true;
                return   localRoot;
            }
            ++count;
        }
        else if (level > 1) {
            if(!getReturn) {
                  retNode =getNode(localRoot.left, level - 1, index, retNode);
            }
            if(!getReturn){
                   retNode =getNode(localRoot.right, level - 1,index,retNode);
            }
        }
    return  retNode;
    }

    /**
     * The toString() function returns a string representation of the tree
     *
     * @return The preOrderTraverse method is being returned.
     */
    public String toString(){
        return preOrderTraverse();
    }


    /**
     * Return the size of the list.
     *
     * @return The size of the list.
     */
    public int size(){
        return this.size;
    }
}
