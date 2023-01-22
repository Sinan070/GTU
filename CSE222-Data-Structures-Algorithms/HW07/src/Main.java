import Utilites.*;

import java.io.PrintStream;
import java.util.Arrays;
import java.util.Random;


public class Main {

    public static void main(String[] argv) {
        try {
            BinarySearchTree<Integer> bst = new BinarySearchTree<>();
            bst.add(5);
            bst.add(15);
            bst.add(10);
            bst.add(23);
            bst.add(20);
            bst.add(28);
            bst.add(25);
            bst.add(40);
            bst.add(30);
            Integer[] array = new Integer[]{23, 10, 9, 8, 15, 20, 78, 36, 45};
            BinarySearchTree<Integer> bst2 = BinarySearchTree.arrayToBstLikeBinaryTree(array, bst);
            System.out.print("QUESTION 1\n\n");
            System.out.print("First Binary Tree \n");
            System.out.print(bst + "\n");
            System.out.print("\nDesired Array\n");
            for (int element :
                    array) {
                System.out.print(element + "->>");
            }
            System.out.println();
            System.out.print("\nSecond Binary Tree with All the Elements are at same Level as First Binary Tree\n");
            System.out.print(bst2 + "\n");


            AVLTree<Integer> avlTree = new AVLTree<>();
            avlTree.convertBstToAvl(bst);
        /*HeapSort<Integer> heapSort = new HeapSort<>(array);
        for (int element:
             array) {
            System.out.print(element+" ");
        }*/
            System.out.print("QUESTION 2\n\n");

            System.out.print("Converting First Binary Tree to Balanced Avl Tree\n");
            System.out.print("Balanced Tree \n");
            System.out.print(bst);
            System.out.print("Is the Tree Balanced : ");
            System.out.print(bst.isBalanced(bst.root) + "\n\n\n");

            System.out.print("QUESTION 3\n\n");
            System.out.print("Skip list Test Result\n");
            CustomSkipList<Integer> skipList = new CustomSkipList<>();
            int[] testArray;
            testArray = createRandomArray(31);
            System.out.print("Skip list with all level. Size of the SkipList is 31. Level is incresed with 10's multiplies\n");
            fillSkipList(skipList, testArray);

            System.out.print(skipList);
        }catch (NullPointerException e){
            e.getMessage();
        }
        catch (IndexOutOfBoundsException e){
            e.getMessage();

        }
        catch (ClassCastException e){
            e.getMessage();
        }
    }
    private static void fillSkipList(CustomSkipList<Integer> skipList, int[] array){
        for (int element:
             array) {
            skipList.add(element);
        }
    }

    private static int[] createRandomArray(int size){
        int[]array = new int[size];
        Random random = new Random();
        for(int i = 0 ; i < size; ++i){
            array[i] = random.nextInt(100);
        }
        return array;
    }


}
