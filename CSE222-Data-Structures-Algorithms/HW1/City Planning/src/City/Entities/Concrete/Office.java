package City.Entities.Concrete;


import City.Entities.Abstract.Building;

import java.util.Objects;

/**
 * Sub class of Building.
 *  * Adding to Building abstract class, it has jobType field.
 */
public class Office extends Building {
    private  String _job_type;
    /**
     *
     * @param owner of the Office
     * @param job_type of the Office
     * @param side of the Street
     * @param lenght of the Office
     * @param position of the Office
     * @param height of the Office
     */
    public  Office(String owner, String job_type,String side,Integer lenght,Integer position,Integer height){
        super(owner,lenght,position,height,side);
        this.setJob_type(job_type);
    }

    /** Setter for Job type of Office
     *
     * @param job_type of Office
     */
    public void setJob_type(String job_type){
        _job_type = job_type;
    }

    /**
     * Getter for job type of Office
     * @return job type of Office
     */
    public  String getJob_type(){
        return  _job_type;
    }

    /**
     * Overriden toString method
     * @return details of Office
     */
    @Override public String toString(){
        return "Office >> " + "JobType : " +getJob_type()+ " -> Position : "+ getPosition() + " -> Id : " + getId()+" -> Side : " + getSide();
    }

    /** Overriden equals method
     * @param o building to be compared
     * @return status
     */
    @Override public boolean equals(Object o){
        if(!(o instanceof  Office)){
            return  false;
        }
        Office obj = (Office) o;
        return obj.getId() == this.getId();
    }

    /**
     * Overriden hasCode method
     * @return hasCode of object
     */
    @Override
    public int hashCode() {
        return Objects.hash(_job_type);
    }
}
