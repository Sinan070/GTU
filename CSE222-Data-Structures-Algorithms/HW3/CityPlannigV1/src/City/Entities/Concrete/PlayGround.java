package City.Entities.Concrete;

import City.Entities.Abstract.Building;

/**
 * Sub class of Building.
 *  * Default value of height is 1.
 */

public class PlayGround extends Building {
    /**
     *
     * @param lenght of PlayGround
     * @param position of PlayGround
     * @param side of Street
     */
    public PlayGround(Integer lenght, Integer position,  String side) {

        super("Childirens",lenght, position,2,side);
    }


    /**
     * Overriden toString method
     * @return details of PlayGround
     */
    @Override public String toString(){
        return "PlayGround >> " + "Lenght : " +getLenght()+ " -> Position : "+ getPosition() +" -> Id : " + getId()+" -> Side : " + getSide();
    }

    /** Overriden equals method
     * @param o building to be compared
     * @return status
     */
    @Override public boolean equals(Object o){
        if(!(o instanceof  PlayGround)){
            return  false;
        }
        PlayGround obj = (PlayGround) o;
        if(obj.getHeight() == this.getHeight()
        &&
        obj.getPosition() == this.getPosition()
        &&
        obj.getSide().equals(this.getSide())
        &&
        obj.getLenght() == this.getLenght()
        &&
        obj.getOwner().equals(this.getOwner())){
            return true;
        }
        return false;

    }

    /**
     * Overriden hasCode method
     * @return hasCode of object
     */
    @Override
    public int hashCode() {
        return super.hashCode();
    }
}
