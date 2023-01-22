package City.Entities.Abstract;

/**
 * Interface for User Authority
 */
public interface UserAuthority {
    /**
     * Add Building
     * @param building to be added
     */


    void addBuilding(Building building);

    /**
     * Delete Building from Street
     * @param Id of the building to be deleted
     */
    void deleteBuilding(int Id);

    /**
     *  Display all buildings details
     */
    void displayBuildings();

    /**
     * Remaining Lenght of the Street
     * @return Remaining Lenght of the Street
     */
    int remainigLenght();

    /**
     *Total  number and ratio of lenth of playgrounds in the street.
     *
     */
    void numberAndRatioOfPlayGround();

    /**
     * Total lenth occupaided bt Market , hOUSE and Office
     * @return Total lenth occupaided bt Market , hOUSE and Office
     */
    int totalLenghtOccupaided();

    /**
     * Display Skyline Silhoutte of Street
     */
    void displaySkylineSilhouette();
}
