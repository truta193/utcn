import csv

file_path = "04-12-22_temperature_measurements.csv"

def check_conversion_needed(data):
    for row in data[1:]:
        for value in row[1:]:
            try:
                if float(value) != int(float(value)):
                    return True
            except ValueError:
                continue
    return False


def preprocess_data(file_path):
    with open(file_path, mode='r') as file:
        reader = csv.reader(file)
        data = list(reader)

    if not check_conversion_needed(data):
        print("No conversion needed. All values are already integers.")
        return

    processed_data = [data[0]]
    for row in data[1:]:
        processed_row = [row[0]]
        for value in row[1:]:
            try:
                processed_row.append(str(round(float(value) * 100)))
            except ValueError:
                processed_row.append(value)
        processed_data.append(processed_row)

    with open(file_path, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(processed_data)

    print("Conversion completed. The file has been updated.")

preprocess_data(file_path)
