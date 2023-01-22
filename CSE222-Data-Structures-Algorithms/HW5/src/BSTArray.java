
import java.util.Arrays;
import java.util.PriorityQueue;

public class BSTArray<E extends  Comparable<E>> implements SearchTree<E>{

    private Object[] data;
    private static final Object[] EMPTY_ELEMENTDATA = {};
    private int capacity;
    private int size;

    public BSTArray(){
        capacity = 2;
        size = 0;
        data = new Object[100];
    }

    E getData(int index){
        return (E)data[index];
    }

    private void grow(){
            capacity = capacity*2;
            Arrays.copyOf(data, capacity);

    }
    private void trimToSize(){
        if (size < data.length) {
            data = (size == 0)
                    ? EMPTY_ELEMENTDATA
                    : Arrays.copyOf(data, size);
        }
    }


    @Override
    public void add(E data) {
        int addedFlag =0;

        /*if(size == capacity){
            grow();
        }*/

        if(this.data[0] == null){
            this.data[0]= data;
        }
        else{
            int parent =0;
            while (addedFlag == 0){
                E value = getData(parent);
                if(data.compareTo(value) <0){
                    if(this.data[2*parent +1] == null){
                        this.data[2*parent +1] = data;
                        addedFlag = 1;
                    }
                    else parent = ((2*parent) +1);
                }
                else if(data.compareTo(value) >0){
                    if(this.data[(2*parent) +2] == null){
                        this.data[(2*parent) +2] = data;
                        addedFlag = 1;
                    }
                    else parent = ((2*parent) +2);
                }
            }
        }
                ++size;
    }
    @Override
    public boolean contain(E data) {
        return  false;
    }

    @Override
    public E find(E target) {
        return null;
    }

    @Override
    public E delete(E target) {
        return null;
    }

    @Override
    public boolean remove(E target) {
        return false;
    }

    public void inOrderPrint(){
        inOrderPrint(0);
    }
    private void inOrderPrint(int p){
        if(getData(p) == null){
            return;
        }
        inOrderPrint((2*p)+1);
        System.out.print(getData(p));
        inOrderPrint((2*p)+2);
    }
}
