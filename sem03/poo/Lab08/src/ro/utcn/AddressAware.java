package ro.utcn;

public interface AddressAware {

  String getAddress();

  void setAddress(String address);

  default void printId() {
    System.out.println(getAddress());
  }
}
