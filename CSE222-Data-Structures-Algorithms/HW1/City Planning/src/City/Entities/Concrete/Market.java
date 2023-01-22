package City.Entities.Concrete;


import City.Entities.Abstract.Building;

import java.time.LocalTime;
import java.util.Objects;

/**
 * Sub class of Building.
 *  * Adding to Building abstract class, it has open and closing time field.
 */
public class  Market extends Building {
    private LocalTime _open;
    private LocalTime _close;

    /**
     *
     * @param owner of the Market
     * @param open time of the Market
     * @param close time of the Markket
     * @param side of the Street
     * @param lenght of the Market
     * @param position of the Market
     * @param height of the Market
     */
    public  Market(String owner, LocalTime open , LocalTime close,String side,Integer lenght,Integer position,Integer height){
        super(owner,lenght,position,height,side);
        setOpenTime(open);
        setCloseTime(close);
    }

    /**
     * Getter for opening time of Market
     * @return opening time of Market
     */
    public  LocalTime getOpenTime(){
        return  _open;
    }

    /**
     * Setter for Opening time of Market
     * @param time of opening time
     */
    public void setOpenTime(LocalTime time){
        _open = time;
    }

    /**
     * getter for closing time of Market
     * @return closing time of Market
     */
    public  LocalTime getCloseTime(){
        return _close;

    }

    /**
     * Setter for closing time of Market
     * @param time of closing Time of market
     */
    public  void setCloseTime(LocalTime time){
        _close = time;
    }


    /**
     * Overriden toString method
     * @return details of Market
     */
    @Override public String toString(){
        return "Market >> " + "Opening Time : " +getOpenTime()+ " -> Close Time : " + getCloseTime() +" -> Position : "+ getPosition() + " -> Id : " + getId()+" -> Side : " + getSide();
    }

    /**
     * Overriden equals method
     * @param o building to be compared
     * @return status
     */
   @Override public boolean equals(Object o){
        if(!(o instanceof  Market)){
            return  false;
        }
        Market obj = (Market) o;
        return obj.getId() == this.getId();
    }

    /**
     * Overriden hasCode method
     * @return hasCode of object
     */
    @Override
    public int hashCode() {
        return Objects.hash(_open, _close);
    }
}
