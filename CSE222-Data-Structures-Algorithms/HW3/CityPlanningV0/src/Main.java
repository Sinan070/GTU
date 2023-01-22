/**
 * Concrete Entities of City Planning SoftwareS
 */
import City.Entities.Concrete.*;

import java.time.LocalTime;
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
                    StreetV0 streetV0 = new StreetV0(40);
                    User user = new User(streetV0);

                    System.out.println("Create 2 House");
                    user.addBuilding(new House("H1","Red",3,"r",5,0,5));
                    user.addBuilding(new House("H2","Yellow",2,"r",6,5,4));
                    user.displayBuildings();

                    System.out.println("Create 2 Market");
                    user.addBuilding(new Market("M1", LocalTime.of(8,30),LocalTime.of(19,0),"r",4,12,5));
                    user.addBuilding(new Market("M2", LocalTime.of(8,0),LocalTime.of(20,0),"l",3,17,5));

                    user.displayBuildings();

                    System.out.println("Create 2 Office");
                    user.addBuilding(new Office("Of1", "Software","r",4,12,8));
                    user.addBuilding(new Office("Of2", "Sport","l",8,10,8));

                    user.displayBuildings();

                    System.out.println("Create 2 PlayGround");
                    user.addBuilding(new PlayGround(3,21,"l"));
                    user.addBuilding(new PlayGround(3,21,"r"));

                    user.displayBuildings();

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
