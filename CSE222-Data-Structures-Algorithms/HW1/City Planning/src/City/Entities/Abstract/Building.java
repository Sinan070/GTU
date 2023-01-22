/**
 * Abstarct Entites of City Plannig Software
 */
package City.Entities.Abstract;

/**
 * Abstract Building Class, super class of House,Market,Office and PlayGround
 */
public abstract class Building{
    private String _owner;
    private int _position;
    private int _lenght;
    private int _height;
    private String _side;
    private int _id;
    public static int _nextId =0; /**Next id to be given to building

    /**
     *
     * @param owner of the Building
     * @param lenght of the Building
     * @param position of the Building
     * @param height of the Building
     * @param side of the Street
     */
    public Building(String owner, int lenght, int position, int height, String side){
        this.setHeight(height);
        this.setLenght(lenght);
        this.setPosition(position);
        this.setSide(side);
        this.setOwner(owner);
    }

    /**
     * Get the owner
     * @return owner
     */
    public String getOwner(){
        return  _owner;
    }

    /**
     * Set the owner
     * @param owner of the Building
     */
    public void setOwner(String owner){
        _owner = owner;
    }

    /**
     * Get position of the Building
     * @return position of the Building
     */
    public int getPosition(){
        return _position;
    }

    /**
     * Set the position of the Building
     * @param position of the Building
     */
    public void setPosition(int position){
        _position = position;
    }

    /**
     * Get lenght of the Building
     * @return length of the Building
     */
    public int getLenght(){
        return  _lenght;
    }

    /**
     * Set lenght of the Building
     * @param lenght of the Building
     */
    public void setLenght(int lenght){
        _lenght = lenght;
    }

    /**
     * Get height of the Building
     * @return height of the Bulding
     */
    public int getHeight(){
        return  _height;
    }

    /**
     * Set height of the Building
     * @param height of the Building
     */
    public void setHeight(int height){
        _height = height;
    }

    /**
     * Get side of the Street
     * @return side of the Street
     */
    public  String getSide(){
        return  _side;
    }

    /**
     * Set side of the Street
     * @param side of the Street
     */
    public  void setSide(String side){
        _side = side;
    }

    /**
     * Get id of the Building
     * @return id of thre Building
     */
    public int getId(){
        return  _id;
    }

    /**
     * Set id of the bulding
     * @param id of the Building
     */
    public  void setId(int id){
        this._id = id;
    }
}
