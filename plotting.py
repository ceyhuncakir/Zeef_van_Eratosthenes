import csv
import pandas as pd
import matplotlib.pyplot as plt

def mpionly(n: int):

    mpionly = pd.read_csv("spreadsheet/mpionly.csv", delimiter=";")
    mpionly.columns = [column.replace(' ', '') for column in mpionly.columns]

    mpionly_data = mpionly.loc[mpionly['Amountofnumbers'] == n, ['NumberOfprocesses', 'Time']]

    plt.plot(mpionly_data['NumberOfprocesses'], mpionly_data['Time'], label="mpi only")
    plt.xlabel("Number of processes")
    plt.ylabel("Time (s)")
    plt.title("n = " + str(n))
    plt.legend()

    plt.savefig("plot_images/mpionly/plot_" + str(n) + ".png")


mpionly(1000000000)
