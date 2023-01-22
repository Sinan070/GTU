public class Main {

     public  static void main(String[] argv){
/*          BSTArray<Integer> bstArray = new BSTArray<>();
          bstArray.add(15);
          bstArray.add(25);
          bstArray.add(35);
          bstArray.add(16);
          bstArray.add(12);
         // bstArray.inOrderPrint();
*/
          try {


               System.out.println("NODE BASED HEAP");
               HeapLL<Integer> heapLL = new HeapLL<>();

               System.out.println("Adding to heap 15");
               heapLL.add(15);

               System.out.println("Adding to heap 25");
               heapLL.add(25);

               System.out.println("Adding to heap 35");
               heapLL.add(35);

               System.out.println("Adding to heap 16");
               heapLL.add(16);

               System.out.println("Adding to heap 12");
               heapLL.add(12);

               System.out.println("Adding to heap 10");
               heapLL.add(10);

               System.out.println("\nPreorder Traversal");
               System.out.print(heapLL);


               System.out.println("\nPoll the First Data in Heap");
               System.out.println(heapLL.pool() + " was polled");


               System.out.println("\nPeek the First Data in Heap");
               System.out.println(heapLL.peek() + " was peeked");

               System.out.println("\nPreorder Traversal");
               System.out.print(heapLL);


               System.out.println("\nRemove 16 from Heap");
               if(heapLL.remove(16)){
                    System.out.println("16 is removed");
               }
               else System.out.println("There is such an value");


               System.out.println("\nRemove 30 from Heap");
               if(heapLL.remove(30)){
                    System.out.println("30 is removed");
               }
               else System.out.println("There is such an value");

               System.out.println("\nPreorder Traversal");
               System.out.print(heapLL);

               System.out.println("\nContain Method with parameter 80");
               System.out.println(heapLL.contains(80));

               System.out.println("\nContain Method with parameter 12");
               System.out.println(heapLL.contains(12));

               System.out.println("\nIncresing Priority of 12 to 100. If the value exist then return true");
               System.out.println(heapLL.incPriority(12,100));

               System.out.println("\nIncresing Priority of 35 to 50. If the value exist  then return true");
               System.out.println(heapLL.incPriority(35,50));

               System.out.print("\nSize of the Heap ->>>  ");
               System.out.println(heapLL.size());


               System.out.println("\nCreating Another Heap");

               HeapLL<Integer> heapLL1 = new HeapLL<>();

               System.out.println("Adding to heap 18");
               heapLL1.add(18);

               System.out.println("Adding to heap 27");
               heapLL1.add(27);

               System.out.println("Adding to heap 39");
               heapLL1.add(39);

               System.out.println("Adding to heap 14");
               heapLL1.add(14);

               System.out.println("Adding to heap 17");
               heapLL1.add(17);

               System.out.println("Adding to heap 100");
               heapLL1.add(100);

               System.out.println("\nPreorder Traversal");
               System.out.print(heapLL1);


               System.out.println("\nMerging 2 Heap");
               HeapLL<Integer> result = heapLL.merge(heapLL1);

               System.out.println("\nNew Heap preOrder Traversal");
               System.out.print(result);

          }
          catch (NullPointerException e){
               e.getStackTrace();
          }
          catch (ClassCastException e){
               e.getStackTrace();
          }
     }
}
