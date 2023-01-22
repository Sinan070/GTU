package City.Entities.Concrete;

import City.Entities.Abstract.Building;


/**
 * Street class keeps buildings
 */
public class Street {
    Building[] buildings;
    private int _buildingCapacity;
    private int _buildingNumber;
    private int _lenght;
    private int _rightSideNum=0;
    private  int _lefSideNum=0;

    private char[][] silhouette;

    /**
     * Lenght of the Street
     * @param lenght of the Street
     */
    public Street(int lenght){
        buildings = new Building[1];
        _buildingCapacity = 1;
        _buildingNumber =0;
        _lenght = lenght;
    }

    /**
     * Find max Heighted building
     * @return height of max heighted building
     */
    private int findMaxHeight(){
        int maxIndex =0;
        for(int i = 0 ; i<_buildingNumber; ++i){
            if(buildings[i].getHeight()>= buildings[maxIndex].getHeight()){
                maxIndex = i;
            }
        }
        return  buildings[maxIndex].getHeight();
    }

    /**
     * Create Skyline Silhoutte
     */
    private void createSilhoutte(){
        int maxHeight = findMaxHeight();
        sortBuildingPosition();
        silhouette = new char[maxHeight][_lenght];
        fillSilhoutte();
    }

    /**
     * Fill Skyline Silhoutte with '#' charechter
     */
    private void fillSilhoutte(){
        int max = findMaxHeight();

        for(int i = 0 ; i<max; ++i){
            for(int j = 0 ; j<_lenght ; ++j ){
                silhouette[i][j] = '.';
            }
        }
       for(int i = 0 ; i <_buildingNumber; ++i){
           int startHeight = max - buildings[i].getHeight();
           int endHeight = max;
           int endPosition = buildings[i].getLenght()+ buildings[i].getPosition();
           int startPosition = buildings[i].getPosition();

         for(int j = startHeight ; j< endHeight ; ++j){
           for(int k = startPosition ; k< endPosition ;++k  ){
               silhouette[j][k] = '#';
           }
         }
       }
    }


    /**
     * Enlarge the Building array dynamically
     */
    private void enlargeBuilding(){
        Building[] tempBuildings = new Building[_buildingCapacity*2];
        System.arraycopy(buildings, 0, tempBuildings,
                0, _buildingNumber);
        buildings = tempBuildings;
        _buildingCapacity *=2;
    }

    /** Setter for lenght of street
     *
     * @param lenght of street
     */
    public void setLenght(int lenght){
        _lenght = lenght;
    }

    /**
     * Add building to the Street
     * @param building to be added
     */
    public void addBuilding(Building building) {
        if(checkPosition(building)){
            if(_buildingNumber >= _buildingCapacity){
                enlargeBuilding();
            }
            buildings[_buildingNumber++] = building;
            building.setId(Building._nextId);
            ++Building._nextId;
            System.out.println(building.getClass().getSimpleName()+ " is added");
            if(building.getSide() == "r"){ ++_rightSideNum;}
            else if(building.getSide() == "l"){++_lefSideNum;}
        }
        else System.out.println("There is no enough space to locate the " + building.getClass().getSimpleName());
    }

    /**
     * Delete building from Street
     * @param building to be deleted
     */
    public void deleteBuilding(Building building) {
        for(int i =0 ; i< _buildingNumber; ++i){
            if(buildings[i].equals(building)){
                shiftBuildingsArray(i);
                --_buildingNumber;
                tidyUptheArray();
                System.out.println("Building is deleted");
            }
        }
    }

    /**
     * Shifting Building array
     * @param index began from shifting
     */
    private void shiftBuildingsArray(int index){

        for(int i = index ; i< _buildingNumber ; ++i){
            buildings[i] = buildings[i+1];
        }
    }


    /**
     * Tidy up the array if There are lots of empty memory in array
     */
    private void tidyUptheArray(){
        if(_buildingNumber <= _buildingCapacity/4){
            Building[] temp = new Building[_buildingCapacity/2];
            System.arraycopy(buildings, 0, temp,
                    0, _buildingNumber);
            buildings = temp;
            _buildingCapacity/=2;
        }
    }

    /**
     * Display buildings details
     */
    public void displayBuildings() {
        for (int i = 0; i< _buildingNumber; ++i){
            System.out.println(buildings[i]);
        }
    }

    /**
            * Remaining Lenght of the Street
     * @return Remaining Lenght of the Street
     */
    public int remainigLenght() {
        int remainLenght = _lenght*2;

        for (int i = 0 ; i<_buildingNumber; ++i){
            remainLenght -= buildings[i].getLenght();
        }

        return remainLenght;
    }

    /**
     *Total  number and ratio of lenth of playgrounds in the street.
     *
     */
    public void numberAndRatioOfPlayGround() {

        int totalLenghtPlayGround =0;
        int totalNumber =0;
        for (int i = 0 ; i<_buildingNumber; ++i){
            if(buildings[i] instanceof  PlayGround){
                totalLenghtPlayGround += buildings[i].getLenght();
                ++totalNumber;
            }
        }
        System.out.printf("Total Number : %d -> Ratio Of Playground:  %f \n",totalNumber,((float)totalLenghtPlayGround / (float) (_lenght*2)));

    }

    /**
     * Total lenth occupaided bt Market , hOUSE and Office
     * @return Total lenth occupaided bt Market , hOUSE and Office
     */
    public int totalLenghtOccupaided() {
        int occupiedLenght =0;

        for (int i = 0 ; i<_buildingNumber; ++i) {
            if (!(buildings[i] instanceof PlayGround)) {
                occupiedLenght += buildings[i].getLenght();
            }
        }
        return occupiedLenght;
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


    /**
     * Sort Buildings by Position
     */
    private void sortBuildingPosition(){
        int minIndex =0;
        for(int i = 0; i< _buildingNumber ; ++i){
            for(int j = i+1 ; j<_buildingNumber ; ++j) {
                if (buildings[minIndex].getPosition() >= buildings[i].getPosition()) {
                    minIndex = i;
                }
            }
            swap(minIndex,i);
        }
    }

    /**
     * Swap two buidling object in array
     * @param index1 of the building array to be swapped
     * @param index2 of the building array to be swapped
     */
    private void swap(int index1 , int index2){
        Building temp = buildings[index1];
        buildings[index1] = buildings[index2];
        buildings[index2] = temp;
    }

    /**
     *  Check position if the building is fit to be located on street
     * @param building to be located
     * @return status
     */
    private Boolean checkPosition(Building building){

        if((_rightSideNum == 0 ||_lefSideNum ==0) && building.getPosition()+building.getLenght() > _lenght){

            return  false;
        }

        for(int i = 0 ; i < _buildingNumber; ++i){
            if(building.getSide().equals(buildings[i].getSide())) {
                if(((buildings[i].getPosition()+buildings[i].getLenght())> building.getPosition()
                && building.getPosition()>= buildings[i].getPosition()) || building.getPosition()+building.getLenght() > _lenght)
                {
                    return  false;
                }
            }
        }
        return true;
    }

    /**
     * Getter for building Number
     * @return building Number
     */
    public  int getBuildingNumber(){
        return _buildingNumber;
    }

}
