package ro.utcn;

public class ObjectSorter {

  public Comparable[] sort(Comparable[] objects, boolean ascending) {
    Comparable[] ret = new Comparable[objects.length];
    for (int i = 0; i < objects.length; i++) {
      ret[i] = objects[i];
    }
    for (int i = 0; i < ret.length - 1; i++) {
      for (int j = i + 1; j < ret.length; j++) {
        if (ascending) {
          if (ret[i].compareTo(ret[j]) > 0) {
            Comparable aux = ret[i];
            ret[i] = ret[j];
            ret[j] = aux;
          }
        } else {
          if (ret[i].compareTo(ret[j]) < 0) {
            Comparable aux = ret[i];
            ret[i] = ret[j];
            ret[j] = aux;
          }
        }
      }
    }
    return ret;
  }
}
