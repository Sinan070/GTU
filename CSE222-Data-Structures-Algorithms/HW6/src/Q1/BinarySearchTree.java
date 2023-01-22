package Q1;

import java.util.Iterator;
import java.util.LinkedList;

/**
 * This class implements a binary search tree that stores objects of type E, where E is a class that implements the
 * Comparable interface
 */
public class BinarySearchTree<E extends Comparable> implements Iterable<E>{

    // A private variable that is used to store the root of the tree.
    private Node<E> root;

    // This is a constructor. The first one is the default constructor.
    public BinarySearchTree(){
        root = null;
    }

    // A constructor that takes an object as a parameter.
    public BinarySearchTree(Object obj){
        this.root = (Node<E>) obj;
    }


    /**
     * A node is a class that contains a data element and two pointers to other nodes
     */
    private static class Node<E>{
        E data;
        Node<E> left;
        Node<E> right;
        Node(){
            data = null;
            left = null;
            right = null;
        }
        // A constructor that takes an object of type E as a parameter.
        Node(E data){
            this.data = data;
            this.left = null;
            this.right = null;
        }


    }


    /**
     * If the root is null, then the root is set to a new node with the data. Otherwise, the root is set to the result of
     * the recursive call to insert with the data and the root
     *
     * @param data The data to be inserted into the tree.
     * @throws ClassCastException
     * @throws NullPointerException
     */
    public  void insert(E data) throws ClassCastException,NullPointerException{
        if(root == null){
            root = new Node<>(data);
        }
        else root = insert(data, root);
    }

    /**
     * If the data is less than the localRoot, then insert it into the left subtree, otherwise insert it into the right
     * subtree
     *
     * @param data the data to be inserted
     * @param localRoot the root of the subtree we're currently looking at
     * @return The localRoot is being returned.
     */
    private Node<E> insert(E data, Node<E> localRoot) throws NullPointerException ,ClassCastException{
        if(localRoot == null){
            return new Node<>(data);
        }
        if(data.compareTo(localRoot.data)<0){
            localRoot.left = insert(data,localRoot.left);}
        else{
            localRoot.right = insert(data,localRoot.right);
        }
        return localRoot;
    }

    /**
     * If the data is not in the tree, do nothing. Otherwise, if the data is in the tree, delete it
     *
     * @param data The data to be deleted from the tree.
     */
    public void delete(E data) throws  ClassCastException, NullPointerException{
        delete(data,root);
    }
    /**
     * If the data is found, replace it with the smallest value in the right subtree, and then delete that value from the
     * right subtree
     *
     * @param data the data to be deleted
     * @param localRoot The root of the subtree we're currently searching
     * @return The node that is being deleted.
     */
    private Node<E> delete(E data, Node<E> localRoot){
        if(localRoot == null){
            return  null;
        }
        if( localRoot.data.equals(data)) {
            if (localRoot.right == null && localRoot.left == null) {
                return null;
            }

            if (localRoot.right != null) {
                localRoot.data = min(localRoot.right);
                localRoot.right = delete(data, localRoot.right);

            } else {
                localRoot.data = max(localRoot.left);
                localRoot.left = delete(data, localRoot.left);
            }
            return localRoot;
        }
        if(localRoot.data.compareTo(data) < 0)
        {
            localRoot.right=delete(data,localRoot.right);
            return localRoot;
        }
        localRoot.left=delete(data,localRoot.left);
        return localRoot;
    }


    /**
     * If the right child of the current node is not null, then the current node becomes the right child of the current
     * node, and the loop repeats. If the right child of the current node is null, then the current node is the maximum
     * value in the tree.
     *
     * @param localRoot The root of the current subtree.
     * @return The maximum value in the tree.
     */
    private E max(Node<E> localRoot){
        while (localRoot.right != null){
            localRoot= localRoot.right;
        }
        return  localRoot.data;
    }


    /**
     * If the left child of the current node is not null, then the minimum value is the minimum value of the left child.
     * Otherwise, the minimum value is the current node.
     *
     * @param localRoot The root of the subtree we're currently looking at.
     * @return The smallest value in the tree.
     */
    private E min(Node<E> localRoot){
        while (localRoot.left != null){
            localRoot = localRoot.left;
        }
        return localRoot.data;
    }

    /**
     * It finds the target in the tree.
     *
     * @param target the element we are looking for
     * @return The node that contains the target value.
     */
    public E find(E target){
        return find(root,target);
    }

    /**
     * If the target is less than the current node, search the left subtree. If the target is greater than the current
     * node, search the right subtree. If the target is equal to the current node, return the current node
     *
     * @param localRoot The root of the current subtree.
     * @param target the data we are looking for
     * @return The data field of the node that contains the target.
     */
    private E find(Node<E> localRoot, E target){
        if (localRoot == null)
            return null;

        // Compare the target with the data field at the root.
        int compResult = target.compareTo(localRoot.data);
        if (compResult == 0)
            return localRoot.data;
        else if (compResult < 0)
            return find(localRoot.left, target);
        else
            return find(localRoot.right, target);
    }


   /**
    * Itr is a private class that implements the Iterator interface. It has a LinkedList and an Iterator. It has a
    * constructor that takes a root node and converts it to a LinkedList. It has a convertToLinkedList method that takes a
    * root node and converts it to a LinkedList
    */
   private class Itr<E> implements Iterator<E>{
        private LinkedList<E> list;
        private Iterator<E> iter;


        // Creating a new LinkedList and converting the tree to a LinkedList.
        public  Itr(){
            Node<E> iterNode = (Node<E>)root;
            list = new LinkedList<E>();
            convertToLinkedList(iterNode);
            this.iter = list.iterator();
        }

       /**
         * "Convert the tree rooted at localRoot to a linked list by traversing the tree in order and adding each node's
         * data to the linked list."
         * The function is called on the root of the tree, so it converts the entire tree to a linked list
         *
         * @param localRoot The root of the tree that we are currently traversing.
         */
         private void convertToLinkedList(Node<E> localRoot){
           if(localRoot == null)	return;
           convertToLinkedList(localRoot.left);
           this.list.offer(localRoot.data);
           convertToLinkedList(localRoot.right);
       }

       /**
        *
        *
        * @return The next element in the iteration.
        */
       @Override
       public boolean hasNext() {
           return iter.hasNext();
       }

       /**
        *
        *
        * @return The next element in the list.
        */
       @Override
       public E next() {
           return iter.next();
       }
   }

   /**
    * The iterator() method returns an object of type Itr, which is an inner class of ArrayList
    *
    * @return An iterator of type E.
    */
   public Iterator<E> iterator(){
        return  new Itr<>();
   }


    /**
     * It traverses the tree in pre-order.
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
     * If the current node is not null, append the current node's data to the string builder, then recursively call the
     * function on the left and right children of the current node
     *
     * @param localRoot The root of the subtree we're currently traversing.
     * @param builder a StringBuilder object that will be used to build the string.
     */
    private void   preOrderTraverse(Node<E> localRoot,StringBuilder builder){
        if(localRoot != null) {
            builder.append(localRoot.data.toString());
            preOrderTraverse(localRoot.left,builder);
            preOrderTraverse(localRoot.right,builder);
        }

    }

    /**
     * The toString() function returns a string representation of the tree
     *
     * @return The preOrderTraverse method is being returned.
     */
    @Override
    public String toString(){

        return preOrderTraverse();
    }




}
