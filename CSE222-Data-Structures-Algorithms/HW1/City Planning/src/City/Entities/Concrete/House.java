package City.Entities.Concrete;


import City.Entities.Abstract.Building;

import java.util.Objects;

/**
 * Sub class of Building.
 * Adding to Building abstract class, it has rooms and color field.
 */
public class House extends Building {

    private int _rooms;
    private String _color;

    /**
     *
     * @param owner of the House
     * @param color of the House
     * @param rooms of the number Rooms
     * @param side of the side of street
     * @param lenght of the length of House
     * @param position of the House
     * @param height of the House
     */
    public  House(String owner,String color, int rooms,String side,Integer lenght,Integer position,Integer height){
       super(owner,lenght,position,height,side);
       this.setRooms(rooms);
       this.setColor(color);
    }

    /**
     * Getter for room number of house
     * @return room number of house
     */
    public  int getRooms(){
        return  _rooms;
    }

    /**
     * Setter room number of house
     * @param rooms numbe of House
     */
    public  void  setRooms(int rooms){
        _rooms = rooms;
    }

    /**
     * Getter for color of the House
     * @return color of the House
     */
    public  String getColor(){
        return  _color;
    }

    /**
     * Setter for color of house
     * @param color of the house
     */
    public  void setColor(String color){
        _color = color;
    }

    /**
     * Overriden method for toString method
     * @return details of house
     */
    @Override public String toString(){
        return "House >> " + "Owner : " +getOwner()+ " -> Position : "+ getPosition() + " -> Id : " + getId() +" -> Side : " + getSide();
    }

    /**
     * overridnen equalse method
     * @param o building to be compared
     * @return status
     */
    @Override public boolean equals(Object o){
        if(!(o instanceof  House)){
            return  false;
        }
        House obj = (House) o;
        return obj.getId() == this.getId();
    }

    /**
     * Overriden hasCode method
     * @return hasCode of object
     */
    @Override
    public int hashCode() {
        return Objects.hash(_rooms, _color);
    }
}
