import Q1.BSTHashTable;
import Q1.HybridHashTable;
import Q1.KWHashMap;
import Q2.MergeSort;
import Q2.New_Sort;
import Q2.QuickSort;

import java.util.Arrays;
import java.util.Random;


public class Main {
    @SuppressWarnings("unchecked")
    private static  void fillDataSet(int row,int col, Integer[][] array){
        Random rd = new Random(); // creating Random object
        for(int i = 0 ; i< row ; ++i){
            for(int j = 0 ; j< col ; ++j){
                array[i][j] = Math.abs(rd.nextInt());
            }
        }
    }
    private static void fillDataSet(Integer[] array , int size){
        Random rd = new Random(); // creating Random object
        for(int i = 0 ; i< size ; ++i){
            array[i] = Math.abs(rd.nextInt());
        }
    }
    private  static void fillHashTable(int [] dataSet, KWHashMap hashMap){
        for(int i = 0 ; i< dataSet.length ; ++i){

                hashMap.put(dataSet[i],dataSet[i]);
        }
        hashMap.put(18,18);
    }

    private static long getTime(KWHashMap hashMap,int key){

            long start = System.nanoTime();
            // some time passes
            hashMap.get(key);
            long end = System.nanoTime();
            return end - start;


    }
    private static long putTime(KWHashMap hashMap,int key, int value){


            long start = System.nanoTime();
            // some time passes
            hashMap.put(key,value);
            long end = System.nanoTime();
            return end - start;


    }
    private static long removeTime(KWHashMap hashMap, int key){


            long start = System.nanoTime();
            // some time passes
            hashMap.remove(key);
            long end = System.nanoTime();
            return  end - start;




    }

    private static long elapsedTimeMergeSort(Integer [] array){
        long start = System.nanoTime();
        // some time passes
        MergeSort.sort(array);
        long end = System.nanoTime();
        return  end - start;


    }
    private static long elapsedTimeQuickSort(Integer [] array){
        long start = System.nanoTime();
        // some time passes
        QuickSort.sort(array);
        long end = System.nanoTime();
        return  end - start;


    }

    private static void test(){

        long[] btsGetTime = new long[3];
        long[] btsPutTime = new long[3];
        long[] btsRemoveTime = new long[3];

        long[] hybrdGetTime = new long[3];
        long[] hybrdPutTime = new long[3];
        long[] hybrdRemoveTime = new long[3];

        long[] mergeSort = new long[3];
        long[] quickSort = new long[3];


        Integer[][] data100 = new Integer[100][100];
        Integer[][] data1000 = new Integer[100][1000];
        Integer[][] data10000 = new Integer[100][10000];

        BSTHashTable<Integer,Integer> bstHashTable100 = new BSTHashTable<>();
        BSTHashTable<Integer,Integer> bstHashTable1000 = new BSTHashTable<>();
        BSTHashTable<Integer,Integer> bstHashTable10000 = new BSTHashTable<>();

        HybridHashTable<Integer,Integer> hybridHashTable100 = new HybridHashTable<>();
        HybridHashTable<Integer,Integer> hybridHashTable1000 = new HybridHashTable<>();
        HybridHashTable<Integer,Integer> hybridHashTable10000 = new HybridHashTable<>();

        fillDataSet(100,100,data100);
        fillDataSet(100,1000,data1000);
        fillDataSet(100,10000,data10000);
try{
        for(int i  = 0 ; i < 100  ; ++i){
            //fillHashTable(data100[i],bstHashTable100);
            //btsGetTime[0] += getTime(bstHashTable100,10);
            //btsPutTime[0] += putTime(bstHashTable100,18,18);
            //btsRemoveTime[0] += removeTime(bstHashTable100,18);
            // bstHashTable100 = new BSTHashTable<>();

            //fillHashTable(data100[i],hybridHashTable100);
            //hybrdGetTime[0]+= getTime(hybridHashTable100,18);
            //hybrdPutTime[0]+= putTime(hybridHashTable100,18,18);
            //hybrdRemoveTime[0]+= removeTime(hybridHashTable100,18);
            // hybridHashTable100 = new HybridHashTable<>();


            //fillHashTable(data1000[i],bstHashTable1000);
            //btsGetTime[1] += getTime(bstHashTable1000,10);
            //btsPutTime[1] += putTime(bstHashTable1000,18,18);
            //btsRemoveTime[1] += removeTime(bstHashTable1000,18);
            //bstHashTable1000 = new BSTHashTable<>();

            //fillHashTable(data1000[i],hybridHashTable1000);
            //hybrdGetTime[1]+= getTime(hybridHashTable1000,18);
            //hybrdPutTime[1]+= putTime(hybridHashTable1000,18,18);
            //hybrdRemoveTime[1]+= removeTime(hybridHashTable1000,18);
            // hybridHashTable1000 = new HybridHashTable<>();


            //fillHashTable(data10000[i],bstHashTable10000);
            //btsGetTime[2] += getTime(bstHashTable10000,10);
            //btsPutTime[2] += putTime(bstHashTable10000,18,18);
            //btsRemoveTime[2] += removeTime(bstHashTable10000,18);
            // bstHashTable10000 = new BSTHashTable<>();

            //fillHashTable(data10000[i],hybridHashTable10000);
            //hybrdGetTime[2]+= getTime(hybridHashTable10000,18);
            //hybrdPutTime[2]+= putTime(hybridHashTable10000,18,18);
            //hybrdRemoveTime[2]+= removeTime(hybridHashTable10000,18);
            //hybridHashTable10000 = new HybridHashTable<>();

            //mergeSort[0] += elapsedTimeMergeSort(data100[i]);
            //mergeSort[1] += elapsedTimeMergeSort(data1000[i]);
            //mergeSort[2] += elapsedTimeMergeSort(data10000[i]);

            quickSort[0] += elapsedTimeQuickSort(data100[i]);
            quickSort[1] += elapsedTimeQuickSort(data1000[i]);
            quickSort[2] += elapsedTimeQuickSort(data10000[i]);

        }
        //.out.print("MergeSort Result 100 - 1000 -10000 Respectively\n");
        //System.out.print(mergeSort[0]/100.0+" "+mergeSort[1]/100.0+" "+mergeSort[2]/100.0+" \n");

        System.out.print("QuickSort Result 100 - 1000 -10000 Respectively\n");
        System.out.print(quickSort[0]/100.0+" "+quickSort[1]/100.0+" "+quickSort[2]/100.0+" \n");
        /*
        System.out.print("Get Method Average Performance for Binary Search Tree Hash Table size 100\n");
        System.out.print(btsGetTime[0]/100.0+"\n");*/
        /*System.out.print("Get Method Average Performance for Binary Search Tree Hash Table size 1000\n");
        System.out.print(btsGetTime[1]/100.0+"\n");*/
         /*System.out.print("Get Method Average Performance for Binary Search Tree Hash Table size 10000\n");
        System.out.print(btsGetTime[2]/100.0+"\n");
*/
        //System.out.print("Get Method Average Performance for Hybrid Hash Table size 100\n");
        //System.out.print(hybrdGetTime[0]/100.0+"\n");
       /* System.out.print("Get Method Average Performance for Hybrid  Hash Table size 1000\n");
        System.out.print(hybrdGetTime[1]/100.0+"\n");
     *//*
        System.out.print("Get Method Average Performance for Hybrid  Hash Table size 10000\n");
        System.out.print(hybrdGetTime[2]/100.0+"\n");
*/

        /*System.out.print("Put Method Average Performance for Binary Search Tree Hash Table size 100\n");
        System.out.print(btsPutTime[0]/100.0+"\n");*/
       /*System.out.print("Put Method Average Performance for Binary Search Tree Hash Table size 1000\n");
        System.out.print(btsPutTime[1]/100.0+"\n");*/
       /* System.out.print("Put Method Average Performance for Binary Search Tree Hash Table size 10000\n");
        System.out.print(btsPutTime[2]/100.0+"\n");
*//*
        System.out.print("Put Method Average Performance for Hybrid Hash Table size 100\n");
        System.out.print(hybrdPutTime[0]/100.0+"\n");*/
        /*System.out.print("Put Method Average Performance for Hybrid  Hash Table size 1000\n");
        System.out.print(hybrdPutTime[1]/100.0+"\n");*//*
        System.out.print("Put Method Average Performance for Hybrid  Hash Table size 10000\n");
        System.out.print(hybrdPutTime[2]/10.0+"\n");*/

/*
        System.out.print("Remove Method Average Performance for Binary Search Tree Hash Table size 100\n");
        System.out.print(btsRemoveTime[0]/100.0+"\n");*/
        /*System.out.print("Remove Method Average Performance for Binary Search Tree Hash Table size 1000\n");
        System.out.print(btsRemoveTime[1]/100.0+"\n");*/
        //System.out.print("Remove Method Average Performance for Binary Search Tree Hash Table size 10000\n");
        // System.out.print(btsRemoveTime[2]/100.0+"\n");
/*
        System.out.print("Remove Method Average Performance for Hybrid Hash Table size 100\n");
        System.out.print(hybrdRemoveTime[0]/100.0+"\n");
        System.out.print("Remove Method Average Performance for Hybrid  Hash Table size 1000\n");
        System.out.print(hybrdRemoveTime[1]/100.0+"\n");*/
        //System.out.print("Remove Method Average Performance for Hybrid  Hash Table size 10000\n");
        //System.out.print(hybrdRemoveTime[2]/10.0+"\n");




    }catch (ClassCastException e) {
    e.getStackTrace();
}
}


    public static void main(String[] args) {

        try{

        //test();

        BSTHashTable<Integer,Integer> bstHashTable = new BSTHashTable<>();
        HybridHashTable<Integer,Integer> hybridHashTable = new HybridHashTable<>();
        Integer[] array = new Integer[]{45,48,55,12,15,66,45,78,78,99,25,16,19};
        System.out.println("Adding Elements to Binary Search Tree Hash Table");
        System.out.print("Adding the (3,9)");
        bstHashTable.put(3,10);
        System.out.println();

        System.out.print("Adding the (12,10)");
        bstHashTable.put(12,10);
        System.out.println();

        System.out.print("Adding the (22,11)");
        bstHashTable.put(22,11);
        System.out.println();

        System.out.print("Adding the (13,12)");
        bstHashTable.put(13,12);
        System.out.println();

        System.out.print("Adding the (25,13)");
        bstHashTable.put(25,13);
        System.out.println();

        System.out.print("Adding the (23,14)");
        bstHashTable.put(23,14);
        System.out.println();

        System.out.print("Adding the (51,15)");
        bstHashTable.put(51,15);
        System.out.println();

        System.out.print("Hash Table\n"+bstHashTable);

        System.out.print("Removing the (25)\nValue is :  ");
        System.out.print(bstHashTable.remove(25));
        System.out.println("\nNew Hash Table\n");
        System.out.print(bstHashTable);

        System.out.print("Removing Non Existed Element (15)\nValue is : ");
        System.out.print(bstHashTable.remove(15));
        System.out.println();
        System.out.print("\nHash Table"+bstHashTable);

        System.out.print("Getting the value of 51 : ");
        System.out.print(bstHashTable.get(51));
        System.out.println();

        System.out.print("Getting the value of non Existing Item 101 :  ");
        System.out.print(bstHashTable.get(101));
        System.out.println();

            System.out.print("\nSize of BST Hash Table :  ");
            System.out.print(bstHashTable.size());

            System.out.print("\nIs empty ?   ");
            System.out.print(bstHashTable.isEmpty());


        System.out.println("\n\nAdding Elements to HYBRID Hash Table");
        System.out.print("Adding the (3,9)");
        hybridHashTable.put(3,10);
        System.out.println();

        System.out.print("Adding the (12,10)");
        hybridHashTable.put(12,10);
        System.out.println();

        System.out.print("Adding the (22,11)");
        hybridHashTable.put(22,11);
        System.out.println();

        System.out.print("Adding the (13,12)");
        hybridHashTable.put(13,12);
        System.out.println();

        System.out.print("Adding the (25,13)");
        hybridHashTable.put(25,13);
        System.out.println();

        System.out.print("Adding the (23,14)");
        hybridHashTable.put(23,14);
        System.out.println();

        System.out.print("Adding the (51,15)");
        hybridHashTable.put(51,15);
        System.out.println();

        System.out.print("Hash Table\n"+hybridHashTable);

        System.out.print("\nRemoving the (25)\nValue is :  ");
        System.out.print(hybridHashTable.remove(25));
        System.out.println("\nNew Hash Table");
        System.out.print(hybridHashTable);

        System.out.print("Removing Non Existed Element (15)\nValue is : ");
        System.out.print(hybridHashTable.remove(15));
        System.out.println();
        System.out.print("\nHash Table"+hybridHashTable);

        System.out.print("Getting the value of 51 : ");
        System.out.print(hybridHashTable.get(51));
        System.out.println();

        System.out.print("Getting the value of non Existing Item 101 :  ");
        System.out.print(hybridHashTable.get(101));
        System.out.println();

        System.out.print("\nSize of Hybrid Hash Table :  ");
        System.out.print(hybridHashTable.size());

        System.out.print("\nIs empty ?   ");
        System.out.print(hybridHashTable.isEmpty());


        Integer[] arrayClone = new Integer[13];
        System.arraycopy(array,0,arrayClone,0,13);

        System.out.print("\n\nSort Using Merge Sort\n");
        System.out.print("Array\n");
            for (int element: array) {
                System.out.print(element+" ");
            }
            MergeSort.sort(arrayClone);
            System.out.print("\nSorted Array\n");

            for (int element: arrayClone) {

                System.out.print(element+" ");

            }

        System.out.print("\nSort Using Quick Sort\n");
            System.out.print("Array\n");
            System.arraycopy(array,0,arrayClone,0,13);

            for (int element: array) {
                System.out.print(element+" ");
            }
            System.out.print("\nSorted Array\n");

            QuickSort.sort(arrayClone);
            for (int element: arrayClone) {
                System.out.print(element+" ");
            }

            System.out.print("\nSort Using New Sort\n");
            System.out.print("Array\n");
            for (int element: array) {
                System.out.print(element+" ");
            }
            System.out.print("\nSorted Array\n");
            New_Sort.sort(array);
            for (int element: arrayClone) {
                System.out.print(element+" ");
            }





    }
        catch (NullPointerException e){
            e.getStackTrace();
        }
        catch (ClassCastException e){
            e.getStackTrace();
        }

    }



}
