package City.Entities.Concrete;

import java.util.*;

// A class that implements the interface List.
// Extending the AbstractList class.
public class LDLinkedList<E> extends AbstractList<E> implements List<E> , Iterable<E> {

    // This is creating a new instance of the class LDLinkedList.
    private Node<E> head = null;
    private int size = 0;
    private static LDLinkedList removed = new LDLinkedList();

    // This is the constructor of the class. It is creating a new instance of the class.
    public LDLinkedList() {

    }

    /**
     * Add a new element to the beginning of the list
     *
     * @param element The element to be added to the list.
     */
    private void addFirst(E element){
        head =  new Node<E>(element,head);
        ++size;
    }


    /**
     * Add an element after a given node
     *
     * @param element The element to be added.
     * @param node The node after which the new node is to be inserted.
     */
    private void addAfter(E element, Node<E> node){
        node.next = new Node<E>(element,node.next);
        ++size;
    }

    /**
     * Remove the node after the given node and return the data of the removed node
     *
     * @param node The node to be removed.
     * @return The data of the removed node.
     */
    private E removeAfter(Node<E> node) {
        Node<E> temp = node.next;
        if (temp != null) {
            node.next = temp.next;
            size--;
            addNodetoRemoved(temp);
            return temp.data;
        }
        throw new NoSuchElementException("The List is Empty");
    }

    /**
     * Add the node to the end of the removed list
     *
     * @param node The node to be removed.
     */
    private void addNodetoRemoved(Node<E> node){
        if(removed.head == null){
            removed.head = node;
        }
        else{
            removed.getNode(removed.size-1).next = node;
        }
        ++removed.size;
    }

    /**
     * Remove the first element of the list and return it
     *
     * @return The data of the first node in the list.
     */
    private E removeFirst(){
        Node<E> temp = head;
        if (head != null){
            head = head.next;
        }
        if (temp != null) {
            --size;
            addNodetoRemoved(temp);
            return temp.data;
        }
        throw new NoSuchElementException("The List is Empty");
    }

    /**
     * Given a node, return the node at the given index
     *
     * @param index The index of the node to be returned.
     * @return The node at the given index.
     */
    private Node<E> getNode(int index){
        Node<E> iter = head;
        for(int i = 0;  i< index && iter != null ; ++i){
            iter = iter.next;
        }

        return  iter;
    }


    /**
     * Given an element, remove it from the linked list
     *
     * @param element the element to be removed.
     * @return The removed element.
     */
    public E removee(E element){

        if(head.data.equals(element)){

            return  removeFirst();
        }
        else{
            return removeAfter(getNode(indexOf(element) - 1));
        }
    }



    /**
     * Given an index, set the element at that index to the given element
     *
     * @param index The index of the element to be set.
     * @param element The element to be inserted into the list.
     * @return The element that was set.
     */
    public E set(int index, E element){

        if(index>= size){
            throw new IndexOutOfBoundsException("Invalid Index");
        }
        Node<E> edited = getNode(index);
        edited.data = element;
        return edited.data;
    }

    /**
     * Given an index, return the data at that index
     *
     * @param index The index of the element to retrieve.
     * @return The data of the node at the given index.
     */
    @Override
    public E get(int index) {
        if(index >= size){

            throw new IndexOutOfBoundsException("Invalid Index");
        }
        Node<E> get = getNode(index);

        return  get.data;
    }


    /**
     * If the element is in the removed list, then remove it from the removed list and link it to the end of the list
     *
     * @param element The element to be removed.
     * @return The boolean value of the method.
     */
    private boolean link(E element){
        Node<E> temp;
        int index = removed.indexOf(element);


        if(index == -1) return  false;

        else if(index == 0){
            temp = removed.head;
            removed.head = removed.head.next;
            getNode(size-1).next = temp;
            temp.next = null;
            --removed.size;
            ++size;
            return true;
        }
        else{
            temp = removed.getNode(index-1);
            Node<E> finded = temp.next;
            temp.next = temp.next.next;
            --removed.size;
            getNode(size-1).next= finded;
            finded.next =null;
            ++size;
            return true;
        }
    }

    /**
     * If the list is empty, add the element to the head of the list. Otherwise, add the element to the end of the list
     *
     * @param element The element to be added to the list.
     * @return Nothing
     */
    @Override
    public  boolean add(E element){

        if(head == null){
            if(!link(element)){
                addFirst(element);
            }
        }
        else {
             if(!link(element)) {
                 Node<E> last = getNode(size - 1);
                 addAfter(element, last);
            }
        }
        return  true;
    }



    /**
     * Given an element, return the index of that element in the list
     *
     * @param element The element to search for.
     * @return The index of the element in the list.
     */
    public int indexOf(Object element){
        Node<E> iter  =head;
        for(int i = 0 ; i < size ; ++i){
            if(iter.data.equals(element)){
                return  i;
            }
                iter  = iter.next;
        }
        return  -1;
    }


    /**
     * Returns the number of elements in the list
     *
     * @return The size of the linked list.
     */
    public int size(){
        return  size;
    }


    /**
     * A node is a class that has a data field and a next field
     */
    static class Node<E>{
        Node next;
        E data;
        Node(E element){
            data =element;
            next =null;
        }
        Node(E element, Node inserted){
            data = element;
            next = inserted;
        }

        private E get(){
            return data;
        }

    }


   // Creating a new class that implements the interface Iterator.
    private class LdIterator<E> implements Iterator<E>{
        private Node<E> iter;
        public LdIterator(){
            iter = (Node<E>) head;
        }
        /**
         * Remove the element at the given index from the list
         */
        @Override
        public void remove(){
            int index = indexOf(iter);
            LDLinkedList.Node<E> temp = (LDLinkedList.Node<E>) getNode(index-1);
            temp.next = iter.next;
            iter.next = null;
        }
        /**
         * This function checks if the next element in the iterator is null or not
         *
         * @return The next element in the iteration.
         */
        @Override
        public boolean hasNext() {

            if(iter.next == null){

                return false;
            }
            else{

;                return  true;
            }

        }

        /**
         * The next method returns the next element in the list
         *
         * @return The data of the next element in the list.
         */
        @Override
        public E next() {
            if(!hasNext()){
                throw new  NullPointerException("List is empty");
            }
            else{
                iter = iter.next;
                return  iter.data;
            }
        }

       /**
        * This function returns a string representation of the list
        *
        * @return The string representation of the list.
        */
       public String toString() {
           return iter.get().toString();
       }
    }

    /**
     * Returns an iterator over the elements in this list in proper sequence
     *
     * @return An iterator.
     */
    @Override
    public Iterator<E> iterator(){
        return new LdIterator<E>();
    }


}
