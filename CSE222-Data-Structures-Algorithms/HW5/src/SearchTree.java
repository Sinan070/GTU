public interface SearchTree<E> {

     void add(E data);
     boolean contain(E data);
     E find(E target);
     E delete(E target);
     boolean remove(E target);



}
