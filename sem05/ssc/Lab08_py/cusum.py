import pandas as pd
import matplotlib.pyplot as plt

def cusum_anomaly_detection(x, threshold, drift):
    g_pos = 0
    g_neg = 0
    anomalies = []

    for t in range(1, len(x)):
        s_t = x[t] - x[t - 1]
        g_pos = max(g_pos + s_t - drift, 0)
        g_neg = max(g_neg - s_t - drift, 0)

        if g_pos > threshold or g_neg > threshold:
            anomalies.append(t)
            g_pos = 0
            g_neg = 0

    return anomalies

def plot_series_with_anomalies(series, anomalies, title):
    plt.figure(figsize=(10, 6))
    plt.plot(series, label='Temperature', color='blue')
    plt.scatter(anomalies, series[anomalies], color='red', label='Anomalies', zorder=5)
    plt.title(title)
    plt.xlabel('Time Index')
    plt.ylabel('Temperature (scaled)')
    plt.legend()
    plt.grid()
    plt.show()

file_path = "04-12-22_temperature_measurements.csv"
data = pd.read_csv(file_path)

data.iloc[:, 1:] = data.iloc[:, 1:].apply(pd.to_numeric)

threshold = 200  # Corresponds to 2°C
drift = 50       # Corresponds to 0.5°C

for column in data.columns[1:]:
    series = data[column]
    anomalies = cusum_anomaly_detection(series.values, threshold, drift)
    plot_series_with_anomalies(series, anomalies, title=f'CUSUM Anomalies in {column}')
