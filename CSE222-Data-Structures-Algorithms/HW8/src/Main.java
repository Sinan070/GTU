import Utilities.BreadthFirstSearch;
import MyGraph.MyGraph;
import Utilities.Dijkstra;
import MyGraph.Vertex;

import java.util.*;

public class Main {
    public  static void main(String[] argv){
        try {
            //CREATING THE GRAPH

            MyGraph myGraph = new MyGraph( false);

        /*myGraph.addVertex(myGraph.newVertex("v0",3.0));
        myGraph.addVertex(myGraph.newVertex("v1",2.0));
        myGraph.addVertex(myGraph.newVertex("v2",1.0));
        myGraph.addVertex(myGraph.newVertex("v3",0.0));
        myGraph.addVertex(myGraph.newVertex("v4",1.0));
        myGraph.addVertex(myGraph.newVertex("v5",2.0));
        myGraph.addVertex(myGraph.newVertex("v6",2.0));
        myGraph.addVertex(myGraph.newVertex("v7",3.0));
        myGraph.addVertex(myGraph.newVertex("v8",1.0));
        myGraph.addVertex(myGraph.newVertex("v9",2.0));

        myGraph.addEdge(0,1,5);
        myGraph.addEdge(0,3,6);
        myGraph.addEdge(1,2,7);
        myGraph.addEdge(1,4,2);
        myGraph.addEdge(1,7,5);
        myGraph.addEdge(1,6,1);
        myGraph.addEdge(2,3,8);
        myGraph.addEdge(2,1,9);
        myGraph.addEdge(2,9,10);
        myGraph.addEdge(2,8,11);
        myGraph.addEdge(3,0,5);
        myGraph.addEdge(3,2,6);
        myGraph.addEdge(4,1,7);
        myGraph.addEdge(4,6,8);

        myGraph.addEdge(4,7,1);
        myGraph.addEdge(4,5,1);
        myGraph.addEdge(5,4,1);

        myGraph.addEdge(6,1,1);
        myGraph.addEdge(6,4,1);
        myGraph.addEdge(6,7,1);

        myGraph.addEdge(7,1,1);
        myGraph.addEdge(7,6,1);
        myGraph.addEdge(7,4,1);

        myGraph.addEdge(8,2,1);
        myGraph.addEdge(9,2,1);*/

/*
        myGraph.addVertex(myGraph.newVertex("1",5.0));
        myGraph.addVertex(myGraph.newVertex("2",6.0));
        myGraph.addVertex(myGraph.newVertex("3",7.0));
        myGraph.addVertex(myGraph.newVertex("4",8.0));
        myGraph.addVertex(myGraph.newVertex("5",8.0));
        myGraph.addVertex(myGraph.newVertex("6",5.0));



        myGraph.addEdge(0,1,2);
        myGraph.addEdge(0,2,4);

        myGraph.addEdge(1,3,7);
        myGraph.addEdge(1,2,1);


        myGraph.addEdge(2,4,3);


        myGraph.addEdge(3,5,1);

        myGraph.addEdge(4,3,2);
        myGraph.addEdge(4,5,5);
*/



/*
        myGraph.addVertex(myGraph.newVertex("A",5.0));
        myGraph.addVertex(myGraph.newVertex("B",5.0));
        myGraph.addVertex(myGraph.newVertex("C",6.0));
        myGraph.addVertex(myGraph.newVertex("D",7.0));
        myGraph.addVertex(myGraph.newVertex("E",8.0));
        myGraph.addVertex(myGraph.newVertex("F",9.0));
        myGraph.addVertex(myGraph.newVertex("H",9.0));


        myGraph.addEdge(0,1,5);
        myGraph.addEdge(0,4,1);
        myGraph.addEdge(0,2,6);

        myGraph.addEdge(1,5,1);

        myGraph.addEdge(2,3,4);
        myGraph.addEdge(2,1,1);

        myGraph.addEdge(3,6,5);

        myGraph.addEdge(4,2,2);

        myGraph.addEdge(5,3,3);

        myGraph.addEdge(5,6,2);

*/
        /*
        myGraph.addVertex(myGraph.newVertex("A",2.0));
        myGraph.addVertex(myGraph.newVertex("B",3.0));
        myGraph.addVertex(myGraph.newVertex("C",1.0));
        myGraph.addVertex(myGraph.newVertex("D",6.0));

        myGraph.addEdge(0,1,4);
        myGraph.addEdge(1,2,9);
        myGraph.addEdge(0,3,6);
        myGraph.addEdge(3,2,5);
*/

            // CREATING VERTICES
            Vertex boston = myGraph.newVertex("Boston",6); // 0
            Vertex istanbul = myGraph.newVertex("Istanbul",5);
            Vertex madrid = myGraph.newVertex("Madrid",4);  //2
            Vertex beijing = myGraph.newVertex("Beijing",4);
            Vertex rio = myGraph.newVertex("Rio",3); //4
            Vertex cairo = myGraph.newVertex("Cairo",7);
            Vertex hanoi = myGraph.newVertex("hanoi",7); //6
            Vertex capetown = myGraph.newVertex("Capetown",5);
            Vertex tripoli = myGraph.newVertex("Tripoli",5);  //8
            Vertex beirut = myGraph.newVertex("Beirut",6);
            Vertex moscow = myGraph.newVertex("Moscow",2);  // 10
  /*      Vertex beijing = myGraph.newVertex("Beijing",1);
        Vertex sydney = myGraph.newVertex("Sydney",6); // 12
        Vertex buenosAires = myGraph.newVertex("Buenos aires",4);
        Vertex rio = myGraph.newVertex("Rio",5); // 14
        Vertex ottawa = myGraph.newVertex("Ottawa",5);
        Vertex  boston = myGraph.newVertex("Boston",4); // 16
        Vertex tashkent = myGraph.newVertex("Tashkent",5);
*/

            //CREATING EDGES
            myGraph.addVertex(boston);
            myGraph.addProperties(0,"Continent","North America");

            myGraph.addVertex(istanbul);
            myGraph.addProperties(1,"Continent","Europe");

            myGraph.addVertex(madrid);
            myGraph.addProperties(2,"Continent","Europe");

            myGraph.addVertex(beijing);
            myGraph.addProperties(3,"Continent","Asia");

            myGraph.addVertex(rio);
            myGraph.addProperties(4,"Continent","South America");

            myGraph.addVertex(cairo);
            myGraph.addProperties(5,"Continent","Africa");

            myGraph.addVertex(hanoi);
            myGraph.addProperties(6,"Continent","Asia");

            myGraph.addVertex(capetown);
            myGraph.addProperties(7,"Continent","Africa");

            myGraph.addVertex(tripoli);
            myGraph.addProperties(8,"Continent","Africa");

            myGraph.addVertex(beirut);
            myGraph.addProperties(9,"Continent","Asia");

            myGraph.addVertex(moscow);
            myGraph.addProperties(10,"Continent","Europe");


            System.out.print("\nVERTICES \n");
            myGraph.printGraph();
  /*      myGraph.addVertex(beijing);
        myGraph.addProperties(11,"Continent","Asia");

        myGraph.addVertex(sydney);
        myGraph.addProperties(12,"Continent","Oceania");

        myGraph.addVertex(buenosAires);
        myGraph.addProperties(13,"Continent","South America");

        myGraph.addVertex(rio);
        myGraph.addProperties(14,"Continent","South America");

        myGraph.addVertex(ottawa);
        myGraph.addProperties(15,"Continent","North America");

        myGraph.addVertex(boston);
        myGraph.addProperties(16,"Continent","North America");

        myGraph.addVertex(tashkent);
        myGraph.addProperties(17,"Continent","Asia");
*/

            // boston
            myGraph.addEdge(0,1,20); // ist
            myGraph.addEdge(0,3,30);  // beijing
            myGraph.addEdge(0,4,15); // rio



            // Istanbul
            myGraph.addEdge(1,0,25); // boston
            myGraph.addEdge(1,8,30); // tripoli
            myGraph.addEdge(1,10,25); // moskow
            myGraph.addEdge(1,5,20); //cairo
            myGraph.addEdge(1,3,20);  // beijing


            // Madrid
            myGraph.addEdge(2,1,25); // ist
            myGraph.addEdge(2,4,20); // rio
            myGraph.addEdge(2,10,22); // moskow

            // Beijing
            myGraph.addEdge(3,9,22); // beirut
            myGraph.addEdge(3,10,22); // moskow
            myGraph.addEdge(3,0,23); // boston
            myGraph.addEdge(3,4,24); //rio
            myGraph.addEdge(3,6,25); //honoi
            myGraph.addEdge(3,1,26); //ist

            // Rio
            myGraph.addEdge(4,0,25); //boston
            myGraph.addEdge(4,7,25); // capetown
            myGraph.addEdge(4,2,25); // madrid


            // Kahire
            myGraph.addEdge(5,1,24); // ist
            myGraph.addEdge(5,8,28); // tripoli
            myGraph.addEdge(5,9,29); // beirut

            // Honoi
            myGraph.addEdge(6,3,26); // beijing

            // Capetown
            myGraph.addEdge(7,9,27); // beiurt
            myGraph.addEdge(7,4,28); // rio

            //Tripoli
            myGraph.addEdge(8,1,29); // ist

            // Beirut
            myGraph.addEdge(9,5,24); // cairo
            myGraph.addEdge(9,1,24); // ist


            //Moskow
            myGraph.addEdge(10,0,26); // boston
            myGraph.addEdge(10,3,27); // bejing
            myGraph.addEdge(10,8,29); // tripol,
            myGraph.addEdge(10,5,25); // cairo
            myGraph.addEdge(10,1,24); // ist


            System.out.print("\n\nVERTICES AND EDGES\n");
            myGraph.printGraph();
/*

        myGraph.addEdge(0,1,5);
        myGraph.addEdge(0,3,6);
        myGraph.addEdge(1,2,7);
        myGraph.addEdge(1,4,2);
        myGraph.addEdge(1,7,5);
        myGraph.addEdge(1,6,1);
        myGraph.addEdge(2,3,8);
        myGraph.addEdge(2,1,9);
        myGraph.addEdge(2,9,10);
        myGraph.addEdge(2,8,11);
        myGraph.addEdge(3,0,5);
        myGraph.addEdge(3,2,6);
        myGraph.addEdge(4,1,7);
        myGraph.addEdge(4,6,8);

        myGraph.addEdge(4,7,1);
        myGraph.addEdge(4,5,1);
        myGraph.addEdge(5,4,1);

        myGraph.addEdge(6,1,1);
        myGraph.addEdge(6,4,1);
        myGraph.addEdge(6,7,1);

        myGraph.addEdge(7,1,1);
        myGraph.addEdge(7,6,1);
        myGraph.addEdge(7,4,1);

        myGraph.addEdge(8,2,1);
        myGraph.addEdge(9,2,1);*/


            MyGraph temp = myGraph.filterVertices("Continent","Asia");


            System.out.print("\n\nMATRIX EXPRESSION\n");

            double [][] matrix = myGraph.exportMatrix();
            for (double [] array: matrix) {
                for (double element: array) {
                    System.out.print(element+" ");
                }
                System.out.println();
            }


            System.out.print("\n\nDIJKSTRA (DISTANCE FROM BOSTON TO OTHER CITIES)\n");
            HashMap<Integer,Double> distance = Dijkstra.dijkstra(myGraph,0);

            Set entrySet = distance.entrySet();
            // Obtaining an iterator for the entry set
            Iterator it = entrySet.iterator();

            // Iterate through HashMap entries(Key-Value pairs)
            while(it.hasNext()){
                Map.Entry me = (Map.Entry)it.next();
                System.out.println("City ID: "+me.getKey() +
                        " & " +
                        " Distance: "+me.getValue());
            }

            System.out.print("\n\nREMOVE EDGE FROM GRAPH\n");
            System.out.print("BEIJING - ISTANBUL EDGE IS REMOVED\n");
            myGraph.removeEdge(3,1);

            System.out.print("MADRID - MOSKOW EDGE IS REMOVED\n");
            myGraph.removeEdge(2,10);

            System.out.print("Remove Non-Existed Edge  ");

            System.out.print(myGraph.removeEdge(11,10));


            System.out.print("\n\nNEW GRAPH\n");
            myGraph.printGraph();

            System.out.print("\nREMOVE VERTEX FROM GRAPH\n");

            System.out.print("CAIRO IS REMOVED FORM GRAPH\n");

            myGraph.removeVertex(5);

            System.out.print("Remove Non-Existed Vertex   :  ");
            if(myGraph.removeVertex(20) == null){
                System.out.print("Vertex is not found\n");
            }
            System.out.print("\nNEW GRAPH\n");
            myGraph.printGraph();



            System.out.println("\nFILTER THE GRAPH ACCORDING TO CONTINENT OF CITY. SEARCH ASIAN CITIES");
            MyGraph asiaGraph = myGraph.filterVertices("Continent","Asia");
            asiaGraph.printGraph();

            System.out.println("\nFILTER THE EUROPE CITIES");
            MyGraph europaGraph = myGraph.filterVertices("Continent","Europe");
            europaGraph.printGraph();


            System.out.println("\nFILTER THE AFRICA CITIES");
            MyGraph africaGraph = myGraph.filterVertices("Continent","Africa");
            africaGraph.printGraph();





            System.out.print("\n\nDIJKSTRA (DISTANCE FROM BOSTON TO OTHER CITIES)\n");
            distance = Dijkstra.dijkstra(myGraph,0);

            entrySet = distance.entrySet();
            // Obtaining an iterator for the entry set
            it = entrySet.iterator();

            // Iterate through HashMap entries(Key-Value pairs)
            while(it.hasNext()){
                Map.Entry me = (Map.Entry)it.next();
                System.out.println("City ID: "+me.getKey() +
                        " & " +
                        " Distance: "+me.getValue());
            }

        System.out.println("\n\nBREADTH FIRST SEARCH ALGORITHM");
        HashMap<Integer,Integer> parent = BreadthFirstSearch.breadFirstSearch(myGraph,0,distance);


        System.out.println("\n\nDISTANCE FROM THE BOSTON TO OTHER USING BREADTH SEARCH");

        Set entrySet1 = distance.entrySet();

            Iterator iter = entrySet1.iterator();

            while(iter.hasNext()){
                Map.Entry me = (Map.Entry)iter.next();
                System.out.println("Source Id: "+me.getKey() +
                        " & " +
                        " Distance : "+me.getValue());
            }

            System.out.println();
            System.out.println("\nPARENT OF EACH CITIESA");


         entrySet1 = parent.entrySet();

         iter = entrySet1.iterator();

        while(iter.hasNext()){
            Map.Entry me = (Map.Entry)iter.next();
            System.out.println("Source Id : "+me.getKey() +
                    " & " +
                    " Parent Id : "+me.getValue());
        }


        }
        catch (NullPointerException e){
            e.getStackTrace();

        }
        catch (NoSuchElementException e){
            System.out.print(e.getMessage());
        }



    }



}
