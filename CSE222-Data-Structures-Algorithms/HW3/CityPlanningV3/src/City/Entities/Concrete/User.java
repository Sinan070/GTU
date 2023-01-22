package City.Entities.Concrete;

import City.Entities.Abstract.Building;
import City.Entities.Abstract.StreetVersion;
import City.Entities.Abstract.UserAuthority;

/**
 * User class to do operations
 */
public  class User implements UserAuthority {


    private final StreetVersion _street;

    /**
     * User Constructor for operations
     * @param street created
     */
    public User(final StreetVersion street){
        this._street = street;

    }


    @Override
    public void addBuilding(Building building) {

        _street.addBuilding(building);
    }

    @Override
    public void deleteBuilding(int Id) {

        try {
            _street.deleteBuilding(Id);
        }
        catch (NullPointerException e) {
            System.out.println(e.getMessage());
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
