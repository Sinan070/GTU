import com.sun.source.tree.BinaryTree;

import java.io.Serializable;

/**
 * The class BT is a class that represents a binary tree
 */
public class BT<E extends Comparable<E>> implements Serializable{

    // A field of the class.
    protected  Node root;


    // A constructor.
    public  BT(){
        root = null;
    }


    // A constructor that takes a node as a parameter and sets the root of the tree to that node.
    public BT(Node<E> root){
        this.root = root;
    }



    // A constructor that takes a data, a right tree and a left tree as parameters and sets the root of the tree to the
    // data and the left and right subtrees to the left and right trees respectively.
    public BT(E data, BT<E> rightTree, BT<E> leftTree){
        root  =   new Node<E>(data);
        if(leftTree != null){
            root.left = leftTree.root;
        }
        else root.left = null;

        if(rightTree != null){
            root.right = rightTree.root;
        }
        else root.right = null;
    }


  // Returning the left and right subtree of the tree.
      public BT<E> getLeftSubtree(){

        if(root != null && root.left != null){
            return  new BT(root.left);
        }
        else return null;
    }

    public BT<E> getRightSubtree(){
        if(root != null && root.right != null){
            return  new BT(root.right);
        }
        else return null;
    }

    // Return the data of root
    public E getData(){
        return (E)root.data;
    }

    /**
     * If the left and right children of the root are both null, then the root is a leaf.
     *
     * @return The method isLeaf() returns true if the root of the tree is a leaf, and false otherwise.
     */
    public boolean isLeaf(){
        return (root.left == null) && (root.right == null);
    }



    /**
     * It prints the tree in preorder traversal.
     *
     * @param node the node to be traversed
     * @param depth the depth of the current node
     * @param sb StringBuilder object that will be used to build the string representation of the tree.
     */
    private void preOrderTraverse(Node<E> node , int depth , StringBuilder sb){
        for(int i = 0 ; i<depth ; ++i){
            if(node == null){
                sb.append("null\n");
            }
            else {
                preOrderTraverse(node.left, depth+1, sb);
                sb.append(node);
                sb.append("\n");
                preOrderTraverse(node.right, depth+1, sb);
            }
        }
    }


    /**
     * A node in a binary tree is a data object that contains a data element and two references to other nodes
     */
    protected  static class Node<E> implements Serializable {


        protected E data;
        protected  Node<E> left;
        protected  Node<E> right;

        public Node(E data){
            this.data = data;
            left = null;
            right = null;
        }
    }

    /**
     * It prints the tree in preorder traversal.
     *
     * @return A string representation of the tree.
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }

}
