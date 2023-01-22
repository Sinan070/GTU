import City.Entities.Concrete.*;

import java.time.DateTimeException;
import java.time.LocalTime;
import java.time.format.DateTimeParseException;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * User Menu
 */
public class Menu {

    private  Street street;
    private Scanner scanner = scanner = new Scanner(System.in);
    private User user;

    /**
     * Method to start User Menu
     */
    public void Start() {
        while(true) {
            if (user == null) {
                System.out.println("Please Enter the Lenght of the Street");
                int length = Integer.parseInt(scanner.nextLine());
                if(length<=0){
                    System.out.println("Please enter positive value");

                }
                else {
                    user = new User(new Street(length));
                    break;
                }
            }
        }
        while (true) {
            try {

                System.out.println("1-Editing Mode");
                System.out.println("2-Display only Mode");
                System.out.println("0-Back to the Main Menu");

                int mode = Integer.parseInt(scanner.nextLine());
                if(mode == 1){
                       editMode();
                }
                else if(mode == 2){
                    if(user == null){
                        System.out.println("There is No User");
                        break;
                    }
                    displayMode();
                }
                else if(mode == 0){
                    return;
                }
                else{
                    System.out.println("Mode choice is Invalid");
                }


            }catch (NumberFormatException e) {
                e.getStackTrace();
                System.out.println("Invalid Input");
            }catch(NullPointerException e) {
                e.getStackTrace();
            }catch(ArrayIndexOutOfBoundsException  e) {
                e.getStackTrace();
            }
            catch (DateTimeParseException e){
                e.getStackTrace();
                System.out.println("Date Must be HH:MM format");
            }
        }
    }

    /**
     * Getting user choice for building properties
     * @param length of building
     * @param position of building
     * @param height of building
     */
    private  void getBuildingPropertiesFromUser(AtomicInteger length, AtomicInteger position, AtomicInteger height){

        System.out.print("Please Enter the Position of the Building : ");
        var position1 = Integer.parseInt(scanner.nextLine());
        System.out.print("Please Enter the Lenght of the Building : ");
        var length1 = Integer.parseInt(scanner.nextLine());
        System.out.print("Please Enter the Height of the Building : ");
        var height1 = Integer.parseInt(scanner.nextLine());


        length.set(length1);
        position.set(position1);
        height.set(height1);
    }

    /**
     *Overloaded method to get user choice for building properties
     * @param length of playGround
     * @param position of PlayGround
     */
    private  void getBuildingPropertiesFromUser(AtomicInteger length,AtomicInteger position){

        System.out.print("Please Enter the Position of the Building : ");
        var position1 = Integer.parseInt(scanner.nextLine());
        System.out.print("Please Enter the Lenght of the Building : ");
        var length1 = Integer.parseInt(scanner.nextLine());


        length.set(length1);
        position.set(position1);
    }

    /**
     * Editing mode
     * @throws NumberFormatException
     */
    private void editMode() throws NumberFormatException, DateTimeParseException {
        while (true) {
            System.out.println("1-Add Building on a Land in Street");
            System.out.println("2-Delete Building on a Land in Steet");
            System.out.println("0-Back to  Select Mode");
            int operation = Integer.parseInt(scanner.nextLine());
            switch (operation) {
                case 1:

                        String owner;
                        AtomicInteger lengthBuilding = new AtomicInteger();
                        AtomicInteger position = new AtomicInteger();
                        AtomicInteger height = new AtomicInteger();
                        String side = new String();

                        System.out.println("1-Add House");
                        System.out.println("2-Add Market");
                        System.out.println("3-Add Office");
                        System.out.println("4-Add Playground");
                        System.out.println("Press another key to Edit Menu");
                        int typeOfbuilding = Integer.parseInt(scanner.nextLine());
                        switch (typeOfbuilding) {
                            case 1:
                                String color;
                                int room;
                                System.out.println("Adding the House");
                                System.out.print("Please Enter the Owner of House :  ");
                                owner = scanner.nextLine();
                                System.out.print("Please Enter the Color of House : ");
                                color = scanner.nextLine();
                                System.out.print("Please Enter the Number of Rooms : ");
                                room = Integer.parseInt(scanner.nextLine());
                                getBuildingPropertiesFromUser(lengthBuilding, position, height);
                                System.out.print("Please Enter the Side of the Street (right to r, left to l) : ");
                                side = scanner.nextLine();
                                user.addBuilding(new House(owner, color, room, side, lengthBuilding.get(), position.get(), height.get()));

                                break;
                            case 2:
                                LocalTime closeTime;
                                LocalTime openTime;
                                System.out.println("Adding the Market");
                                System.out.print("Please Enter the Owner of Market :  ");
                                owner = scanner.nextLine();
                                System.out.print("Please Enter the Opening Time of Market (ex: 07:06) : ");
                                openTime = LocalTime.parse(scanner.nextLine());
                                System.out.print("Please Enter the Closing Time  of Market (ex: 09:12) : ");
                                closeTime = LocalTime.parse(scanner.nextLine());
                                getBuildingPropertiesFromUser(lengthBuilding, position, height);
                                System.out.print("Please Enter the Side of the Street (right to r, left to l) : ");
                                side = (scanner.nextLine());
                                user.addBuilding(new Market(owner, openTime, closeTime, side, lengthBuilding.get(), position.get(), height.get()));
                                break;
                            case 3:
                                String jobType;
                                System.out.println("Adding the Office");
                                System.out.print("Please Enter the Owner of Office :  ");
                                owner = scanner.nextLine();
                                System.out.print("Please Enter the Job Type of Office : ");
                                jobType = (scanner.nextLine());
                                getBuildingPropertiesFromUser(lengthBuilding, position, height);
                                System.out.print("Please Enter the Side of the Street (right to r, left to l) : ");
                                side = (scanner.nextLine());
                                user.addBuilding(new Office(owner, jobType, side, lengthBuilding.get(), position.get(), height.get()));
                                break;
                            case 4:
                                System.out.println("Adding the PlayGround");
                                getBuildingPropertiesFromUser(lengthBuilding, position);
                                System.out.print("Please Enter the Side of the Street (right to r, left to l) : ");
                                side =scanner.nextLine();
                                user.addBuilding(new PlayGround(lengthBuilding.get(), position.get(), side));
                                break;
                            default:
                                return;
                        }

                    break;
                case 2:
                    System.out.println("Please Enter the Id of the Building");
                    int Id = Integer.parseInt(scanner.nextLine());
                    user.deleteBuilding(Id);
                    break;
                case 0:
                    return;
                default:
                    System.out.println("Invalid Operation");
            }
        }
    }

    /**
     * Display mode
     */
    private  void displayMode(){
        while (true) {
            System.out.println("Displaying Mode");
            System.out.println("1-display the total remaining length of lands on the street.");
            System.out.println("2-display the list of buildings on the street.");
            System.out.println("3-display the number and ratio of lenth of playgrounds in the street.");
            System.out.println("4-Display the total length of street occupied by the markets, houses or offices.");
            System.out.println("5-display the skyline silhouette of the street.");
            System.out.println("0- Back to the Mode ");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice){
                case 1:
                    System.out.println("Displaying Remaining Length");
                    System.out.println(user.remainigLenght());
                    System.out.println();
                    break;
                case 2:
                    System.out.println("Displaying Buildings");
                    user.displayBuildings();
                    System.out.println();

                    break;
                case 3:
                    System.out.println("Displaying the number and ratio of Playground");
                    user.numberAndRatioOfPlayGround();
                    System.out.println();

                    break;
                case 4:
                    System.out.println("Displaying the Occupied Length");
                    System.out.println(user.totalLenghtOccupaided());
                    System.out.println();

                    break;
                case 5:
                    System.out.println("Displaying Skyline Silhoutte");
                    user.displaySkylineSilhouette();
                    System.out.println();
                    break;
                case 0:
                    System.out.println();
                    return;
            }
        }
    }

}
