package City.Entities.Concrete;

import City.Entities.Abstract.Building;
import City.Entities.Abstract.StreetVersion;

import java.util.Collections;
import java.util.LinkedList;

public class StreetV2 extends StreetVersion {

    private LinkedList<Building> _buildings;


    public StreetV2(int lenght){
        super(lenght);
        _buildings = new LinkedList<>();

    }

    /**
     * Find max Heighted building
     * @return height of max heighted building
     */
    protected int findMaxHeight(){
        int maxIndex =0;
        for(int i = 0 ; i<_buildingNumber; ++i){
            if(_buildings.get(i).getHeight()>= _buildings.get(maxIndex).getHeight()){
                maxIndex = i;
            }
        }
        return _buildings.get(maxIndex).getHeight();
    }



    /**
     * Fill Skyline Silhoutte with '#' charechter
     */
    protected void fillSilhoutte(){
        int max = findMaxHeight();

        for(int i = 0 ; i<max; ++i){
            for(int j = 0 ; j<_lenght ; ++j ){
                silhouette[i][j] = '.';
            }
        }
        for(int i = 0 ; i <_buildingNumber; ++i){
            int startHeight = max - _buildings.get(i).getHeight();
            int endHeight = max;
            int endPosition = _buildings.get(i).getLenght()+ _buildings.get(i).getPosition();
            int startPosition = _buildings.get(i).getPosition();

            for(int j = startHeight ; j< endHeight ; ++j){
                for(int k = startPosition ; k< endPosition ;++k  ){
                    silhouette[j][k] = '#';
                }
            }
        }
    }



    /**
     * Add building to the Street
     * @param building to be added
     */
    public void addBuilding(Building building) {
        if(checkPosition(building)){
            _buildings.add(building);
            building.setId(Building._nextId);
            ++Building._nextId;
            System.out.println(building.getClass().getSimpleName()+ " is added");
            ++_buildingNumber;
            if(building.getSide() == "r"){ ++_rightSideNum;}
            else if(building.getSide() == "l"){++_lefSideNum;}
        }
        else System.out.println("There is no enough space to locate the " + building.getClass().getSimpleName());
    }

    @Override
    public void deleteBuilding(int Id) {
         Building building = findBuilding(Id);
         _buildings.remove(building);
         --_buildingNumber;
    }





    /**
     * Display buildings details
     */
    public void displayBuildings() {
        for (int i = 0; i< _buildingNumber; ++i){
            System.out.println(_buildings.get(i));
        }
    }

    /**
     * Remaining Lenght of the Street
     * @return Remaining Lenght of the Street
     */
    public int remainigLenght() {
        int remainLenght = _lenght*2;

        for (int i = 0 ; i<_buildingNumber; ++i){
            remainLenght -= _buildings.get(i).getLenght();
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
            if(_buildings.get(i) instanceof  PlayGround){
                totalLenghtPlayGround += _buildings.get(i).getLenght();
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
            if (!(_buildings.get(i) instanceof PlayGround)) {
                occupiedLenght += _buildings.get(i).getLenght();
            }
        }
        return occupiedLenght;
    }




    /**
     * Sort Buildings by Position
     */
    protected void sortBuildingPosition(){
        Collections.sort(_buildings);
    }


    /**
     *  Check position if the building is fit to be located on street
     * @param building to be located
     * @return status
     */
    protected boolean checkPosition(Building building){

        if((_rightSideNum == 0 ||_lefSideNum ==0) && building.getPosition()+building.getLenght() > _lenght){

            return  false;
        }

        for(int i = 0 ; i < _buildingNumber; ++i){
            if(building.getSide().equals(_buildings.get(i).getSide())) {
                if(((_buildings.get(i).getPosition()+ _buildings.get(i).getLenght())> building.getPosition()
                        && building.getPosition()>= _buildings.get(i).getPosition()) || building.getPosition()+building.getLenght() > _lenght)
                {
                    return  false;
                }
            }
        }
        return true;
    }

    @Override
    protected Building findBuilding(int Id) {
        for (int i = 0; i< getBuildingNumber(); ++i){
            if(_buildings.get(i).getId() == Id){
                return _buildings.get(i);
            }
        }
        throw new NullPointerException("Building is not found");
    }


}
