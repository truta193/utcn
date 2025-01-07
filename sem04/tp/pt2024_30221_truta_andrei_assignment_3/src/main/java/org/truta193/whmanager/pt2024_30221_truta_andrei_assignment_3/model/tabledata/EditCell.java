package org.truta193.whmanager.pt2024_30221_truta_andrei_assignment_3.model.tabledata;

import javafx.event.Event;
import javafx.scene.control.ContentDisplay;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableColumn.CellEditEvent;
import javafx.scene.control.TablePosition;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.util.StringConverter;

/**
 * A custom TableCell implementation for editing content within a TableView.
 * This TableCell supports editing text-based content using a TextField.
 *
 * @param <S> The type of the TableView generic type.
 * @param <T> The type of the content within the TableCell.
 */
public class EditCell<S, T> extends TableCell<S, T> {

    private final TextField textField = new TextField(); // Text field for editing
    private final StringConverter<T> converter; // Converter for converting text to user type

    /**
     * Constructs an EditCell with the specified converter.
     *
     * @param converter The converter for converting text to the user type and vice versa.
     */
    public EditCell(StringConverter<T> converter) {
        this.converter = converter;

        // Listen for changes in item property to update cell text
        itemProperty().addListener((obx, oldItem, newItem) -> {
            if (newItem == null) {
                setText(null);
            } else {
                setText(converter.toString(newItem));
            }
        });

        // Set the graphic to the text field and display content as text only
        setGraphic(textField);
        setContentDisplay(ContentDisplay.TEXT_ONLY);

        // Commit edit on enter key press or focus lost
        textField.setOnAction(evt -> {
            commitEdit(this.converter.fromString(textField.getText()));
        });
        textField.focusedProperty().addListener((obs, wasFocused, isNowFocused) -> {
            if (!isNowFocused) {
                commitEdit(this.converter.fromString(textField.getText()));
            }
        });

        // Handle key events for navigation and editing
        textField.addEventFilter(KeyEvent.KEY_PRESSED, event -> {
            if (event.getCode() == KeyCode.ESCAPE) {
                textField.setText(converter.toString(getItem()));
                cancelEdit();
                event.consume();
            } else if (event.getCode() == KeyCode.UP) {
                getTableView().getSelectionModel().selectAboveCell();
            } else if (event.getCode() == KeyCode.DOWN) {
                getTableView().getSelectionModel().selectBelowCell();
            }
        });
    }

    /**
     * Static method to create a default EditCell for String values.
     *
     * @param <S> The type of the TableView generic type (typically the model class).
     * @return A new EditCell configured to edit String values.
     */
    public static <S> EditCell<S, String> createStringEditCell() {
        return new EditCell<>(IDENTITY_CONVERTER);
    }

    /**
     * Sets the text of the text field and displays the graphic for editing.
     */
    @Override
    public void startEdit() {
        super.startEdit();
        textField.setText(converter.toString(getItem()));
        setContentDisplay(ContentDisplay.GRAPHIC_ONLY);
        textField.requestFocus();
    }

    /**
     * Reverts to text display without committing any changes.
     */
    @Override
    public void cancelEdit() {
        super.cancelEdit();
        setContentDisplay(ContentDisplay.TEXT_ONLY);
    }

    /**
     * Commits the edit and updates the property value if possible.
     * Reverts to text display after committing.
     *
     * @param item The new item value after editing.
     */
    @Override
    public void commitEdit(T item) {
        if (!isEditing() && !item.equals(getItem())) {
            TableView<S> table = getTableView();
            if (table != null) {
                TableColumn<S, T> column = getTableColumn();
                CellEditEvent<S, T> event = new CellEditEvent<>(table,
                        new TablePosition<>(table, getIndex(), column),
                        TableColumn.editCommitEvent(), item);
                Event.fireEvent(column, event);
            }
        }

        super.commitEdit(item);
        setContentDisplay(ContentDisplay.TEXT_ONLY);
        getTableView().refresh();
    }

    /**
     * A StringConverter that simply returns the input string as is.
     */
    private static final StringConverter<String> IDENTITY_CONVERTER = new StringConverter<>() {
        @Override
        public String toString(String object) {
            return object;
        }

        @Override
        public String fromString(String string) {
            return string;
        }
    };
}