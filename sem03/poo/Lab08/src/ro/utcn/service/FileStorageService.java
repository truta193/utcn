package ro.utcn.service;

import ro.utcn.model.Person;

import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.Serializable;
import java.util.UUID;

public class FileStorageService implements StorageService {
    private final String localStoragePath = "/home/andrei/Documents/2023-2024/POO/Lab08";

    @Override
    public void save(Object object) {
        //Cast to person is yicky
        //Could generate a random id on the spot here
        if (!(object instanceof Person)) return;
        UUID uuid = ((Person) object).getUuid();
        try {
            FileOutputStream fileOutputStream = new FileOutputStream(localStoragePath + "/" + uuid);
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(fileOutputStream);

            objectOutputStream.writeObject(object);
            objectOutputStream.flush();
            objectOutputStream.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public Object load(String uuid) {
        try {
            FileInputStream fileInputStream = new FileInputStream(localStoragePath + "/" + uuid);
            ObjectInputStream objectInputStream = new ObjectInputStream(fileInputStream);
            Object obj = objectInputStream.readObject();
            objectInputStream.close();
            return obj;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
