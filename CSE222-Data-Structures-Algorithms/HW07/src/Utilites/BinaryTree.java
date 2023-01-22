package Utilites;

import java.awt.image.BufferedImage;
import java.io.Serializable;
import java.util.Objects;

public class BinaryTree<E extends Comparable<E>>  {
    // A public variable that is used to store the root of the tree.
    public Node<E> root;


    // A constructor that takes no parameters and sets the root to null.
    public BinaryTree(){
        this.root = null;
    }
    // A constructor that takes a data as a parameter and creates a new node with that data.
    public  BinaryTree(E data){
        this.root = new Node<>(data);
    }
    // A constructor that takes a node as a parameter.
    protected BinaryTree(Node<E> root){
        this.root = root;
    }

    /**
     * > If the node is not null, then increment the level, traverse the left subtree, print the node, traverse the right
     * subtree, and decrement the level
     *
     * @param node The node to start the traversal from.
     * @param sb StringBuilder object to store the output
     * @param level This is the level of the node in the tree.
     */
    private void inOrderTraverse(Node<E> node, StringBuilder sb,int level){
            if(node != null) {
                ++level;
                inOrderTraverse(node.left, sb,level);
                sb.append("Level : "+level+"  Value : "+node);
                sb.append("\n");
                inOrderTraverse(node.right, sb,level);
            }
            -- level;
    }


    /**
     * A generic class that implements the Serializable interface.
     */
    public  static class Node<E> implements Serializable {
        protected  E data;
        public   Node<E> left;
        public  Node<E> right;
        // A constructor for the Node class.
        public  Node(E data){
            this.data = data;
            this.left = null;
            this.right = null;
        }
        /**
         * The toString() function returns a string representation of the object
         *
         * @return The data in the node.
         */
        public  String toString(){
            return data.toString();
        }
    }

    /**
     * It prints the tree in order.
     *
     * @return The string representation of the tree.
     */
    @Override
    public  String toString(){
        StringBuilder builder = new StringBuilder();
        inOrderTraverse(root,builder,0);
        builder.append("\n");
        return builder.toString();
    }
}
