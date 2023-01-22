package Utilites;

import java.lang.reflect.Array;
import java.util.*;

public class BinarySearchTree<E extends Comparable<E>>  extends BinaryTree<E>  implements SearchTree<E> {


    protected  boolean addReturn;
    protected  E deleteReturn;

    public BinarySearchTree(Node newRoot) {
        this.root = newRoot;
    }

    // Calling the constructor of the super class.
    public  BinarySearchTree(E data){
        super(data);
    }
    // A constructor that takes no arguments.
    public  BinarySearchTree(){
        super();
    }
    /**
     * If the data is not in the tree, add it to the tree and return true. Otherwise, return false
     *
     * @param data the data to be added to the tree
     * @return The root of the tree.
     */
    @Override
    public boolean add(E data) {
        root = add( data, root);
        return addReturn;
    }

    /**
     * If the data is not in the tree, add it. Otherwise, do nothing
     *
     * @param data the data to be added to the tree
     * @param root The root of the current subtree
     * @return The root of the tree.
     */
    private Node<E> add(E data,Node<E> root){
        if(root == null){
            addReturn =  true;
            return new Node<E>(data);
        }
        else {
            int comp = data.compareTo(root.data);
            if(comp == 0){
                addReturn= false;
                return root;
            }
            else if(comp < 0){

                root.left = add(data,root.left);
                return root;
            }
            else{

                root.right = add(data,root.right);
                return root;
            }
        }
    }

    /**
     * If the data is found, return true. Otherwise, return false
     *
     * @param data The data to search for.
     * @return The data that was found.
     */
    @Override
    public boolean contains(E data) {
        E result = find(data);
        return result == data;
    }

    /**
     * It finds the data in the tree.
     *
     * @param data the data to be found
     * @return The data that is being searched for.
     */
    @Override
    public E find(E data) {
        return find(data, root);
    }
    /**
     * If the data is less than the root, search the left subtree. If the data is greater than the root, search the right
     * subtree. If the data is equal to the root, return the root
     *
     * @param data the data we are looking for
     * @param root The root of the tree.
     * @return The data that is being searched for.
     */
    private E find(E data,Node<E> root){
        if(root == null ){
            return null;
        }
        int comp = data.compareTo(root.data);
        if(comp == 0 ){
            return root.data;
        }
        else if(comp < 0){
            return  find(data,root.left);
        }
        else return find(data,root.right);

    }

    /**
     * If the data is in the tree, delete it and return the data
     *
     * @param data the data to be deleted
     * @return The data that was deleted.
     */
    @Override
    public E delete(E data) {
        root = delete(data, root);
        return deleteReturn;
    }
    /**
     * If the data is found, delete it and return the root of the modified tree. Otherwise, return the root of the tree
     * that results from recursively calling delete on the left or right subtree
     *
     * @param data the data to be deleted
     * @param root the root of the tree
     * @return The root of the tree.
     */
    private Node<E> delete(E data, Node<E> root){
        if(root == null){
            deleteReturn = null;
            return this.root;
        }
        int comp = data.compareTo(root.data);
        if(comp == 0){
            deleteReturn = root.data;
           if(root.left == null){
               return  root.right;
           }
           else if(root.right == null){
               return root.left;
           }
           else{
               if(root.left.right == null) {
                   root.data = root.left.data;
                   root.left = root.left.left;
               }
               else{
                   root.data = findLargestChild(root.left);
               }
               return root;
           }

        }
        else if(comp < 0){
            root.left = delete(data, root.left);
            return root;
        }
        else {
            root.right = delete(data, root.right);
            return root;
        }

    }
    /**
     * If the right child of the parent has no right child, then it is the inorder predecessor. Otherwise, recursively call
     * the function on the right child
     *
     * @param parent the parent of the node we want to remove
     * @return The data of the inorder predecessor
     */
    private E findLargestChild(Node<E> parent) throws ClassCastException{
        //if the right child has no right child, it is the inorder predecessor
        if(parent.right.right == null){
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            return returnValue;
        } else {
            return findLargestChild(parent.right);
        }
    }

    /**
     * If the data is found, delete it and return true. Otherwise, return false
     *
     * @param data the data to be removed
     * @return The data that was deleted.
     */
    @Override
    public boolean remove(E data) throws ClassCastException{
        delete(data);
        return deleteReturn == data;
    }



    /**
     * The above function converts a binary tree to a binary search tree.
     *
     * @param arr The array to be converted to a binary search tree.
     * @param tree The tree to be converted to a binary search tree.
     * @return A binary search tree.
     */
    public static BinarySearchTree arrayToBstLikeBinaryTree(Comparable[] arr,BinaryTree tree) throws ClassCastException{
        BinarySearchTree binarySearchTree = new BinarySearchTree();
        Comparable[] temp = new Comparable[arr.length];
        int[] index = new int[]{0};
        System.arraycopy(arr,0, temp,0,arr.length);
        Arrays.sort(temp);
        binarySearchTree.root =createBinarySearchTree(tree.root);
        fillBinarySearchTree(temp,binarySearchTree.root,index);
        return binarySearchTree;
    }
    /**
     * It creates a copy of the binary tree.
     *
     * @param btRoot The root of the binary tree to be copied.
     * @return A new binary search tree with the same structure as the original.
     */
    private static Node createBinarySearchTree(Node btRoot){
        if(btRoot != null) {
            Node newNode = new Node(0);
            newNode.left = createBinarySearchTree(btRoot.left);
            newNode.right = createBinarySearchTree(btRoot.right);
            return newNode;
        }
        return null;

    }
    /**
     * The function takes in a BST, an array of Comparable objects, and an array of one element. The function then fills
     * the BST with the elements of the array in order
     *
     * @param arr The array of Comparable objects that we want to fill the tree with.
     * @param root The root of the tree
     * @param i This is an array of size 1. We are using this array to pass the value of i by reference.
     */
    private static void fillBinarySearchTree(Comparable[] arr,Node root, int[] i){
        if(root != null){
            fillBinarySearchTree(arr,root.left,i);
            root.data = arr[i[0]++];
            fillBinarySearchTree(arr,root.right,i);
        }
    }

    /**
     * If the difference between the heights of the left and right subtrees is greater than 1, then the tree is unbalanced
     *
     * @param node the node to check
     * @return The height of the tree.
     */
    public boolean  isBalanced(Node node)
    {
        int l;
        int r;

        if (node == null)
            return true;

        l = height(node.left);
        r = height(node.right);

        if (Math.abs(l - r) <= 1 && isBalanced(node.left) && isBalanced(node.right))
            return true;

        return false;
    }


    /**
     * The height of a node is 1 + the maximum of the heights of its children.
     *
     * @param node The node whose height is to be calculated.
     * @return The height of the tree.
     */
    int height(Node node)
    {
        if (node == null)
            return 0;
        return 1 + Math.max(height(node.left), height(node.right));
    }

    /**
     * The toString() method returns a string representation of the object
     *
     * @return The toString method is being called on the super class.
     */
    @Override
    public String toString(){
        return super.toString();
    }
}
