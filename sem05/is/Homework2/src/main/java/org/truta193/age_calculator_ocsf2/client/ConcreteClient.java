package org.truta193.age_calculator_ocsf2.client;

import org.truta193.age_calculator_ocsf2.ui.UiStateManager;

import java.util.function.Consumer;

public class ConcreteClient extends AbstractClient {
    private Consumer<String> messageCallback;
    private Runnable disconnectCallback;

    public ConcreteClient(String host, int port) {
        super(host, port);
    }

    public void setMessageCallback(Consumer<String> callback) {
        this.messageCallback = callback;
    }

    public void setDisconnectCallback(Runnable callback) {
        this.disconnectCallback = callback;
    }

    @Override
    protected void handleMessageFromServer(Object msg) {
        messageCallback.accept("[INFO] Response: " + (String) msg);
    }

    @Override
    protected void connectionClosed() {
        if (disconnectCallback != null) {
            disconnectCallback.run();
        }
    }

    @Override
    protected void connectionException(Exception exception) {
        if (disconnectCallback != null) {
            disconnectCallback.run();
        }
    }

    @Override
    protected void connectionEstablished() {
        messageCallback.accept("[INFO] Connection established");
    }
}
