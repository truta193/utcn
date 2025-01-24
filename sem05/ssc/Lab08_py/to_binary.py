import pandas as pd
import os

input_file_path = "04-12-22_temperature_measurements.csv"

def convert_to_binary_and_save(data, output_dir="binary_files"):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for column in data.columns[1:]:
        binary_file_path = os.path.join(output_dir, f"{column}.bin")
        with open(binary_file_path, "w") as file:
            for value in data[column]:
                binary_representation = bin(value)[2:]
                file.write(binary_representation + "\n")

        print(f"Binary data for {column} saved to {binary_file_path}")

data = pd.read_csv(input_file_path)

data.iloc[:, 1:] = data.iloc[:, 1:].apply(pd.to_numeric, downcast='integer')

convert_to_binary_and_save(data)