package City.Entities.Abstract;

import City.Entities.Concrete.PlayGround;

import java.util.NoSuchElementException;

public abstract class   StreetVersion {
    protected int _buildingCapacity;
    protected int _buildingNumber;
    protected int _lenght;
    protected int _rightSideNum=0;
    protected   int _lefSideNum=0;

    protected char[][] silhouette;

    public StreetVersion(int lenght){
        _buildingNumber =0;
        _lenght = lenght;
    }

    public void set_buildingCapacity(int capacity){
        _buildingCapacity = capacity;
    }
    abstract public   void addBuilding(Building building);

    abstract protected int findMaxHeight();

    /**
     * Delete Building from Street
     * @param Id of the building to be deleted
     */
    abstract public void deleteBuilding(int Id) throws NoSuchElementException;

    /**
     * Create Skyline Silhoutte
     */
    protected void createSilhoutte(){
        int maxHeight = findMaxHeight();
        sortBuildingPosition();
        silhouette = new char[maxHeight][_lenght];
        fillSilhoutte();

    }

    abstract protected void fillSilhoutte();

    /** Setter for lenght of street
     *
     * @param lenght of street
     */
    public void setLenght(int lenght){
        _lenght = lenght;
    }

    /**
     * Display Skyline Silhoutte of Street
     */
    public void displaySkylineSilhouette() {

        createSilhoutte();

        int max = findMaxHeight();
        for (int i = 0; i< max; ++i){
            for (int j = 0 ; j<_lenght ; ++j) {
                if (silhouette[i][j] == '#'){
                    if((i == 0 || j == 0 || i == max-1 || j == _lenght-1)){
                        System.out.print("*");
                    }
                    else if ((silhouette[i + 1][j] == '#'
                            && silhouette[i - 1][j] == '#'
                            && silhouette[i][j + 1] == '#'
                            && silhouette[i][j - 1] == '#')
                            && (silhouette[i-1][j+1] == '#' && silhouette[i-1][j-1] == '#' )) {

                        System.out.print(" ");
                    }
                    else{
                        System.out.print("*");

                    }

                }
                else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }
        for(int i = 0; i<= _lenght +7 ;++i){
            System.out.print("*");
        }
        System.out.println();
        for(int i = 0 ; i<= _lenght ;++i){

            if(i%5 ==0){
                System.out.print(i);
            }
            else{
                System.out.print('-');
            }
        }
    }

    abstract protected void sortBuildingPosition();
    abstract  protected  boolean checkPosition(Building building);
    abstract protected  Building findBuilding(int Id);
    /**
     * Getter for building Number
     * @return building Number
     */
    public  int getBuildingNumber(){
        return _buildingNumber;
    }


    /**
     *  Display all buildings details
     */
    abstract public void displayBuildings();

    /**
     * Remaining Lenght of the Street
     * @return Remaining Lenght of the Street
     */
    abstract public int remainigLenght();

    /**
     *Total  number and ratio of lenth of playgrounds in the street.
     *
     */
    abstract public void numberAndRatioOfPlayGround();

    /**
     * Total lenth occupaided bt Market , hOUSE and Office
     * @return Total lenth occupaided bt Market , hOUSE and Office
     */
    abstract public  int totalLenghtOccupaided();

    /**
     * Display Skyline Silhoutte of Street
     */

}
