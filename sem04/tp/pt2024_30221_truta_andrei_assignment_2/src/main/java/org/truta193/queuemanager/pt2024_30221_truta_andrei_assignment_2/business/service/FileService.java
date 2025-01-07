package org.truta193.queuemanager.pt2024_30221_truta_andrei_assignment_2.business.service;

import java.io.FileWriter;
import java.io.IOException;

public class FileService {
    public void Save(String filePath, String content) throws IOException {
        try(FileWriter fw = new FileWriter(filePath, true)) {
            fw.append(content);
        } catch (IOException e) {
            throw new IOException();
        }
    }
}
