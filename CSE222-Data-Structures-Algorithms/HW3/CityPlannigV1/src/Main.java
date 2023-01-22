/**
 * Concrete Entities of City Planning Software
 */
import City.Entities.Abstract.Building;
import City.Entities.Concrete.*;

import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;

/**
 * Main class
 */
public class Main {
    static Menu menu = new Menu();

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int chooseOperation;
        while (true){
            try {

                System.out.println("\nWelcome The City Planning Software");
                System.out.println("1-> Start Program Menu");
                System.out.println("2-> Start Driver Code");
                System.out.println("0-> Close the program");
                System.out.println("Enter the operation: ");
                chooseOperation = Integer.parseInt(scanner.nextLine());
                if(chooseOperation == 1){
                    menu.Start();
                }
                else if(chooseOperation == 2){

                    System.out.println("Lenght of the Street is 40");
                    StreetV1 streetV1 = new StreetV1(40);
                    User user = new User(streetV1);

                    System.out.println("Create 2 House");

                    House house1 = new House("H1","Red",3,"r",5,0,5);
                    House house2 = new House("H2","Yellow",2,"r",6,5,4);

                    user.addBuilding(house1);
                    user.addBuilding(house2);

                    ArrayList<Building> buildings = new ArrayList<>();
                    buildings.add(house1);
                    buildings.add(house2);

                    user.displayBuildings();


                    Market market1 = new Market("M1", LocalTime.of(8,30),LocalTime.of(19,0),"r",4,12,5);
                    Market market2 = new Market("M2", LocalTime.of(8,0),LocalTime.of(20,0),"l",3,17,5);
                    System.out.println("Create 2 Market");
                    buildings.add(market1);
                    buildings.add(market2);
                    user.addBuilding(market1);
                    user.addBuilding(market2);

                    user.displayBuildings();
                    Office office1 = new Office("Of1", "Software","r",4,12,8);
                    Office office2 = new Office("Of2", "Sport","l",8,10,8);
                    System.out.println("Create 2 Office");
                    buildings.add(office1);
                    buildings.add(office2);

                    user.addBuilding(office1);
                    user.addBuilding(office2);

                    user.displayBuildings();
                    PlayGround pg1 =new PlayGround(3,21,"l");
                    PlayGround pg2 =new PlayGround(3,21,"r");
                    System.out.println("Create 2 PlayGround");
                    user.addBuilding(pg1);
                    user.addBuilding(pg2);

                    buildings.add(pg1);
                    buildings.add(pg2);

                    System.out.println("Display Using Iterator");
                    Iterator<Building> iterator = buildings.iterator();
                    while (iterator.hasNext()){
                        System.out.println(iterator);
                        iterator.next();
                    }

                    System.out.println("Display the Total Remaining Length of Lands on the Street");
                    System.out.println(user.remainigLenght());

                    System.out.println("Display The Number and Ratio of Length of PLAYGROUNDS In the Street");
                    user.numberAndRatioOfPlayGround();

                    System.out.println("Display the Total Length of Street Occupied by the Markets, Houses or Offices");
                    System.out.println(user.totalLenghtOccupaided());

                    System.out.println("Remove The 1 Building from Each Type of Building");


                    user.deleteBuilding(0);
                    user.deleteBuilding(2);
                    user.deleteBuilding(4);
                    user.deleteBuilding(10);

                    user.displayBuildings();

                    user.addBuilding(new House("H1","Red",3,"r",5,0,5));
                    user.addBuilding(new House("H4","Red",3,"r",4,30,5));
                    user.addBuilding(new House("H1","Red",3,"l",4,35,5));
                    user.addBuilding(new Market("M1", LocalTime.of(8,30),LocalTime.of(19,0),"r",4,12,5));


                    System.out.println("Display");
                    user.displayBuildings();



                    System.out.println("Display the Total Remaining Length of Lands on the Street");
                    System.out.println(user.remainigLenght());

                    System.out.println("Display The Number and Ratio of Length of PLAYGROUNDS In the Street");
                    user.numberAndRatioOfPlayGround();

                    System.out.println("Display the Total Length of Street Occupied by the Markets, Houses or Offices");
                    System.out.println(user.totalLenghtOccupaided());

                    System.out.println("Displaying Skyline Silhouette");
                    user.displaySkylineSilhouette();
                }
                else if(chooseOperation == 0){
                    System.out.println("Program is Terminated");
                    break;
                }
                else{
                    System.out.println("There is no such an operation");
                }
            }
            catch (NullPointerException e){
                e.getStackTrace();
            }
            catch (NumberFormatException e){

                e.getStackTrace();

            }



        }
    }

}
