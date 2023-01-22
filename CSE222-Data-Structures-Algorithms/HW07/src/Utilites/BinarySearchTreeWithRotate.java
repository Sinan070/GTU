package Utilites;

public class BinarySearchTreeWithRotate<E extends Comparable<E>> extends  BinarySearchTree<E>{
    public BinarySearchTreeWithRotate(E data) {
        super(data);
    }
    public BinarySearchTreeWithRotate() {
        super();
    }

    /**
     * "Rotate right" means that the left child of the root becomes the new root, and the old root becomes the right child
     * of the new root
     *
     * @param root the root of the tree
     * @return The root of the tree.
     */
    public Node<E> rotateRight(Node<E> root){
        Node<E> temp =root.left;
        root.left = temp.right;
        temp.right = root;
        return temp;
    }
    /**
     * Rotate the right child of the root to the left, and return the new root.
     *
     * @param root the root of the tree
     * @return The root of the tree.
     */
    public  Node<E> rotateLeft(Node<E> root){
        Node<E> temp = root.right;
        root.right = temp.left;
        temp.left = root;
        return temp;
    }
}
