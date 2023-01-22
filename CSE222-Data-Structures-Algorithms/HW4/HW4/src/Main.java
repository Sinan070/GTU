import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class Main {
    private static void fillArray(int[] array) {
        for (int i = 0; i < array.length; ++i) {
            array[i] = i;
        }
    }

    private  static void printList(ArrayList<ArrayList<Integer>> list){
        for (ArrayList<Integer> elements : list) {
            for (int element : elements) {
                System.out.print(element + " ");
            }
            System.out.println();
        }
    }

    private static void fillArraySameNumber(int[] array){
        Random random = new Random();
        for(int i = 0 ; i < array.length ; ++i){
            array[i] = 1;
        }
    }

    public static void main(String[] argv) {

        long start;
        long end;


        try {

            System.out.println("1.PROBLEM");
            StringBuilder mainBuilder = new StringBuilder();
            StringBuilder subBuilder = new StringBuilder();

            mainBuilder.append("kabcdabcmabcdabceabc");
            subBuilder.append("abc");

            Q1 q1 = new Q1();
            int result1a = q1.findIndexedSubString(mainBuilder.toString(), subBuilder.toString(), 2);
            System.out.println("Main String : " + mainBuilder + "  Sub String : " + subBuilder + "Index : " + 2);
            System.out.println("RESULT 1.A  " + result1a + "\n");

            mainBuilder.replace(0, mainBuilder.length(), "DATACSE222CSE222CSEDATACSE222DATA");
            subBuilder.replace(0, subBuilder.length(), "CSE");
            int result1b = q1.findIndexedSubString(mainBuilder.toString(), subBuilder.toString(), 3);
            System.out.println("Main String : " + mainBuilder + "  Sub String : " + subBuilder + "  Index : " + 3);
            System.out.println("RESULT 1.B  " + result1b + "\n");

            int result1c = q1.findIndexedSubString(mainBuilder.toString(), subBuilder.toString(), 7);
            System.out.println("Main String : " + mainBuilder + "  Sub String : " + subBuilder + "  Index : " + 7);
            System.out.println("RESULT 1.C  " + result1c + "\n");


            int result1d = q1.findIndexedSubString(mainBuilder.toString(), "cse", 3);
            System.out.println("Main String : " + mainBuilder + "  Sub String : " + "cse" + "  Index : " + 3);
            System.out.println("RESULT 1.D  " + result1d + "\n");


            System.out.println("\n2.PROBLEM");

            Q2 q2 = new Q2();
            int[] array = new int[100];
            int[] array1 = new int[1000];
            int[] array2 = new int[10000];
            System.out.println("Fill arrays 100 , 1000, 10000 sorted numbers started with 1");
            fillArray(array);
            fillArray(array1);
            fillArray(array2);
            System.out.println("Find number of numbers between 45 - 99 in arrays");
            start = System.nanoTime();
            int result2a = q2.findValueBetweenTwo(array, 45, 99);
            end = System.nanoTime();
            System.out.printf("Result : %d Elapsed Time :%d\n", result2a, (end - start));

            start = System.nanoTime();
            int result2b = q2.findValueBetweenTwo(array1, 45, 99);
            end = System.nanoTime();
            System.out.printf("Result : %d Elapsed Time :%d\n", result2b, (end - start));

            start = System.nanoTime();
            int result2c = q2.findValueBetweenTwo(array2, 45, 99);
            end = System.nanoTime();
            System.out.printf("Result : %d Elapsed Time :%d\n", result2c, (end - start));


            System.out.println("\n3.PROBLEM");

            Q3 q3 = new Q3();
            ArrayList<ArrayList<Integer>> result3;
            int[] array4 = new int[30];
            int[] array5 = new int[60];
            int[] array6 = new int[120];

            Arrays.fill(array5,1);
            Arrays.fill(array6,1);
            Arrays.fill(array4,1);

            start = System.nanoTime();
            result3 = q3.findSum(array4, 10);
            end = System.nanoTime();
            System.out.println("Result of 30 size array filled with 1 (Find the value 10)");
            printList(result3);
            System.out.println("Elapsed time is "+ (end- start));

            start = System.nanoTime();
            result3 = q3.findSum(array5, 10);
            end = System.nanoTime();
            System.out.println();
            System.out.println("Result of 60 size array filled with 1(Find the 10)");
            printList(result3);
            System.out.println("Elapsed time is "+ (end- start));
            System.out.println();

            start = System.nanoTime();
            result3= q3.findSum(array6, 10);
            end = System.nanoTime();
            System.out.println();
            System.out.println("Result of 120 size array filled with 1 (Find the 10)");
            printList(result3);
            System.out.println("Elapsed time is "+ (end- start));



        }catch(NullPointerException e){
            e.getMessage();
        }catch (RuntimeException e){
            e.getMessage();
        }
        catch (StackOverflowError e){
            System.out.println("CRASH");
        }

    }
}
