import numpy as np
import pandas as pd
import re
import string
import nltk
from nltk import word_tokenize

nltk.download('stopwords')

### Load data from csv -------------------------------
print("Loading data from csv...")

train_data = pd.read_csv("train.csv")  # Data set used to train.
test_data = pd.read_csv("dev.csv")  # Data set used to set.

train_data = train_data[train_data.label!=0]
test_data = test_data[test_data.label!=0]

# Add a new column called 'edited' as the edited headline.

train_data["edited"] = train_data.apply(
    lambda x: re.sub(r"<.+/>", x["edit"], x["original"]), axis=1
)
test_data["edited"] = test_data.apply(
    lambda x: re.sub(r"<.+/>", x["edit"], x["original"]), axis=1
)

train_data["original"] = train_data["original"].str.replace(r"<(.+)/>", "\g<1>")
test_data["original"] = test_data["original"].str.replace(r"<(.+)/>", "\g<1>")

# Remove stop words
from nltk.corpus import stopwords

stop_words = set(stopwords.words("english"))
punctuations = string.punctuation

# Split the train data into train set and test set

### Pre-processing -----------------------------------

print("Loading word2vec model...")
# Using word2vec trained by Google (We don't need to train embedding model ourself)
# https://code.google.com/archive/p/word2vec/
import gensim.downloader as downloader

# Download the *pretrained* word2vec model.
# This size of the model is 1662.8MB so it might take a while.
word2vec = downloader.load("word2vec-google-news-300")


def tokenize(text):
    tokens = word_tokenize(text.lower())
    # Punctuation Removal
    tokens = [one for one in tokens if one not in stop_words]
    # Stop words removal
    tokens = [one for one in tokens if one not in punctuations]
    return tokens


def convert2vector(headlines):
    """
    Convert a list of headlines to a list of vectors.
    """
    corpus = [tokenize(one) for one in headlines]

    vectors = []

    for tokenized_headline in corpus:
        # Only consider words that's in the word2vec model.
        tokenized_headline = [one for one in tokenized_headline if one in word2vec.vocab]
        # The vector for each headline is the mean value of all vectors for words.
        vector = np.mean(word2vec[tokenized_headline], axis=0)
        vectors.append(vector)

    return np.array(vectors)


print("Tokenizing words...")

x_train_original = convert2vector(train_data["original"])
x_train_edited = convert2vector(train_data["edited"])

# Combine original headlines with edited headlines
# [[...Original, ...Edited], [...Original, ...Edited], [...Original, ...Edited], ...]
x_train = np.array([
    np.concatenate((x_train_original[i], x_train_edited[i]), axis=None) for i in range(len(x_train_original))
])
# x_train_all = x_train_all.reshape(x_train_all.shape[0], 600, 1)

y_train = train_data["meanGrade"]
y_train = y_train.to_numpy().reshape(y_train.shape[0], 1)

x_test_original = convert2vector(test_data["original"])
x_test_edited = convert2vector(test_data["edited"])

# Combine original headlines with edited headlines
# [[...Original, ...Edited], [...Original, ...Edited], [...Original, ...Edited], ...]
x_test = np.array([
    np.concatenate((x_test_original[i], x_test_edited[i]), axis=None) for i in range(len(x_test_original))
])
# x_train_all = x_train_all.reshape(x_train_all.shape[0], 600, 1)

y_test = test_data["meanGrade"]
y_test = y_test.to_numpy().reshape(y_test.shape[0], 1)

# Prepare for CNN
x_train = x_train.reshape((x_train.shape[0], x_train.shape[1], 1))
x_test = x_test.reshape((x_test.shape[0], x_test.shape[1], 1))

### Train the model ---------------------------------------

import tensorflow as tf
from tensorflow import keras

# Split the training set into train set and test set
# TRAIN_RATIO = 0.90 # Let 90% of the data used for training
#
# x_train, x_test = tf.split(x_train_all, [int(x_train_all.shape[0] * TRAIN_RATIO), x_train_all.shape[0] - int(x_train_all.shape[0] * TRAIN_RATIO)])
# y_train, y_test = tf.split(y_train_all, [int(x_train_all.shape[0] * TRAIN_RATIO), x_train_all.shape[0] - int(x_train_all.shape[0] * TRAIN_RATIO)])

# Parameters
LEARNING_RATE = 0.001
TRAINING_EPOCHS = 15
BATCH_SIZE = 100

# Building a FFNN network, Linear Regression

model = keras.Sequential([
    keras.layers.Conv1D(10, 20, activation='relu', input_shape=x_train.shape[1:]),
    keras.layers.Reshape(target_shape=[10 * 581]),
    keras.layers.Dense(64, activation='softmax'),
    keras.layers.Dropout(0.2),
    keras.layers.Dense(1)  # Output layer
])

optimizer = tf.keras.optimizers.RMSprop(learning_rate=LEARNING_RATE)

# Using mean square error as loss function
model.compile(loss=keras.losses.mean_squared_error, optimizer=optimizer, metrics=['mse'])

model.summary()

history = model.fit(x_train, y_train, batch_size=BATCH_SIZE, epochs=TRAINING_EPOCHS)

#######

model.evaluate(x_test, y_test, verbose=2)


# Testing the rmse of predicting result
def rmse(pred, traget):
    return np.sqrt(np.mean((pred - traget) ** 2))


def roundToOneDecimal(value):
    value = value.reshape(value.shape[0])
    roundedValue = np.array([round(one, 1) for one in value])
    return roundedValue.reshape([value.shape[0], 1])


y_pred = model.predict(x_test)
# y_pred = roundToOneDecimal(y_pred)

print("RMSE: {}".format(rmse(y_pred, y_test)))

### Predict the final result -------------------------

# test.csv doesn't have labels. This file will be used for grading.

grading_data = pd.read_csv("test.csv")

grading_data["edited"] = grading_data.apply(
    lambda x: re.sub(r"<.+/>", x["edit"], x["original"]), axis=1
)

grading_data["original"] = train_data["original"].str.replace(r"<(.+)/>", "\g<1>")

x_grading_original = convert2vector(grading_data["original"])
x_grading_edited = convert2vector(grading_data["edited"])

x_grading = np.array([
    np.concatenate((x_grading_original[i], x_grading_edited[i]), axis=None) for i in range(len(x_grading_original))
])

x_grading = x_grading.reshape((x_grading.shape[0], x_grading.shape[1], 1))

y_grading = model.predict(x_grading)

# y_grading = roundToOneDecimal(y_grading)
y_grading = y_grading.reshape([x_grading.shape[0]])

result = pd.DataFrame({"id": grading_data["id"], "pred": y_grading})
result.to_csv("task-1-output.csv", index=False)

# Grading...
test_full_data = pd.read_csv("data/semeval-2020-task-7-dataset(full)/subtask-1/test.csv")
test_truth = test_full_data["meanGrade"]
print("RMSE to be submitted: {}".format(rmse(y_grading, test_truth)))
