package DayOfYearSet;

import DayOfYearSet.DayOfYearSet.*;

import java.util.ArrayList;

/**
 * Main program to drive DayOfYearSet code.
 */
public class ProgramMain {

    public static void main(String[] arg){

        var set1 = new DayOfYearSet();

        set1.add(new DayofYear(1,1));
        set1.add(new DayofYear(5,10));
        set1.add(new DayofYear(7,7));
        set1.add(new DayofYear(1,12));
        set1.add(new DayofYear(4,4));
        set1.add(new DayofYear(10,5));

        set1.add(new DayofYear(1,25));
        set1.add(new DayofYear(5,5));

        System.out.println("\nSET1");
        System.out.println(set1);
        System.out.println("Number of Element in SET1");
        System.out.println(set1.size());

        set1.remove(new DayofYear(1,25));
        set1.remove(new DayofYear(5,5));

        System.out.println("\nREMOVE (1,25) and (5,5) from SET1");
        System.out.println("\nSET1");
        System.out.println(set1);
        System.out.println("Number of Element in SET1");
        System.out.println(set1.size());





        ArrayList<DayofYear> arrayListSet= new ArrayList<>();

        arrayListSet.add(new DayofYear(7,12));
        arrayListSet.add(new DayofYear(16,12));
        arrayListSet.add(new DayofYear(16,12));
        arrayListSet.add(new DayofYear(23,4));
        arrayListSet.add(new DayofYear(29,10));
        arrayListSet.add(new DayofYear(19,5));
        arrayListSet.add(new DayofYear(30,8));




        DayOfYearSet set2 = new DayOfYearSet(arrayListSet);
        set2.add(new DayofYear(4,4));
        set2.add(new DayofYear(10,5));

        System.out.println("\nSET2");
        System.out.println("SET 2 is created from ArrayList");
        System.out.println(set2);
        System.out.println("Number of Element in SET2");
        System.out.println(set2.size());


        DayOfYearSet set3 = set1.difference(set2);

        System.out.println("\nSET3");
        System.out.println("SET3 is diffrence set of SET1 and SET2");
        System.out.println(set3);
        System.out.println("Number of Element in SET3");
        System.out.println(set3.size());


        DayOfYearSet set4 = set2.difference(set1);
        System.out.println("\nSET4 is diffrence set of SET2 and SET1");
        System.out.println("SET4");

        System.out.println(set4);
        System.out.println("Number of Element in SET4");
        System.out.println(set4.size());

        DayOfYearSet set5 = set1.intersect(set2);
        System.out.println("\nSET5");
        System.out.println("\nSET5 is intersect set of SET1 and SET2");
        System.out.println(set5);
        System.out.println("Number of Element in SET5");
        System.out.println(set5.size());

        DayOfYearSet set6 = set1.union(set2);
        System.out.println("\nSET6");
        System.out.println("\nSET6 is union set of SET1 and SET2");
        System.out.println(set6);
        System.out.println("Number of Element in SET6");
        System.out.println(set6.size());



        DayOfYearSet set7 = set1.complement();
        System.out.println("\nSET7");
        System.out.println("\nSET7 is complement set of SET1");
        System.out.println(set7);
        System.out.println("Number of Element in SET7");
        System.out.println(set7.size());


        var set8 = set2.complement();
        System.out.println("\nSET8");
        System.out.println("\nSET8 is complement set of SET2");
        System.out.println(set8);
        System.out.println("Number of Element in SET8");
        System.out.println(set8.size());


        System.out.println("\nDe Morgan Rules for SET1 and SET2");
        if(set1.union(set2).complement().equals(set1.complement().intersect(set2.complement()))){
            System.out.println("THE MORGAN RULES FOR SET1 and SET2 is TRUE");
        }

        if(set2.union(set3).complement().equals(set2.complement().intersect(set3.complement()))){
            System.out.println("THE MORGAN RULES FOR SET2 and SET3 is TRUE");
        }

        if(set3.union(set4).complement().equals(set3.complement().intersect(set4.complement()))){
            System.out.println("THE MORGAN RULES FOR SET3 and SET4 is TRUE");
        }
        if(set4.union(set5).complement().equals(set4.complement().intersect(set5.complement()))){
            System.out.println("THE MORGAN RULES FOR SET4 and SET5 is TRUE");
        }
        if(set6.union(set7).complement().equals(set6.complement().intersect(set7.complement()))){
            System.out.println("THE MORGAN RULES FOR SET6 and SET7 is TRUE");
        }

        System.gc();

        System.out.printf("\n\nTOTAL NUMBER OF DAY OF YEAR SET ALIVE = ");
        System.out.printf("%d \n", DayOfYearSet.totalSet());

        set1 = null;
        System.gc();
        System.out.println("SET1 IS REMOVED USING GARBAGE COLLECTOR");


        System.out.println("TOTAL NUMBER OF DAY OF YEAR SET ALIVE = "+ DayOfYearSet.totalSet());




    }



}
