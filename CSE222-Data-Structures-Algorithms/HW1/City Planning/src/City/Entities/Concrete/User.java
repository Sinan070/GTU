package City.Entities.Concrete;

import City.Entities.Abstract.Building;
import City.Entities.Abstract.UserAuthority;

/**
 * User class to do operations
 */
public  class User implements UserAuthority {


    private final Street _street;

    /**
     * User Constructor for operations
     * @param street created
     */
    public User(final Street street){
        this._street = street;

    }


    @Override
    public void addBuilding(Building building) {
        _street.addBuilding(building);
    }

    @Override
    public void deleteBuilding(int Id) {
         for (int i = 0 ; i< _street.getBuildingNumber(); ++i){
             if(_street.buildings[i].getId() == Id){
                 _street.deleteBuilding(_street.buildings[i]);
             }
         }
    }


    @Override
    public void displayBuildings() {
        _street.displayBuildings();
    }

    @Override
    public int remainigLenght() {
        return _street.remainigLenght();
    }

    @Override
    public void numberAndRatioOfPlayGround() {
         _street.numberAndRatioOfPlayGround();
    }

    @Override
    public int totalLenghtOccupaided() {
        return _street.totalLenghtOccupaided();
    }

    @Override
    public void displaySkylineSilhouette() {
        _street.displaySkylineSilhouette();
    }

}
