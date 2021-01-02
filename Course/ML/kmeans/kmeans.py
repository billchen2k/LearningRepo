import numpy as np
import matplotlib.pyplot as plt
from logger import logger

# PARAMETERS
K_MIN = 2
K_MAX = 5
# Stop condition
MAX_EPOCHS = 100

data = np.empty((0, 2), float)

cores = np.empty((0, 2), float)

def load_data():
    global data
    logger.info("Loading data from data.txt...")
    with open("data.txt", "r") as f:
        lines = f.readlines()
        for oneLine in lines:
            (x, y) = oneLine.replace("\n", "").split(" ")
            data = np.append(data, np.array([[x, y]]), axis=0)

def init_core(k=2):
    row_rand_array = np.arange(data.shape[0])
    np.random.shuffle(row_rand_array)
    return data[row_rand_array[0:k]]


def fit(epochs=100):
    pass

def evaluate():
    pass

def plot():
    plt.scatter(data[:, 0], data[:, 1])
    plt.show()

def kmeans():
    pass

def main():
    load_data()

if __name__ == '__main__':
    logger.info("This is a simple program demonstrating K-Means algorithm.")
    main()
    pass