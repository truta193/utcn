package ro.utcn.service;
import java.util.UUID;

public interface StorageService {

  void save(Object object);

  Object load(String uuid);
}
