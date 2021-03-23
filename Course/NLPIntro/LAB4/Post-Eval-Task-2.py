import numpy as np
import tensorflow as tf

import numpy as np
import pandas as pd
import re
import string
import nltk
from nltk import word_tokenize

nltk.download('stopwords')

### Load data from csv -------------------------------
print("Loading data from csv...")

train_data = pd.read_csv("train.csv") # Data set used to train.
test_data = pd.read_csv("dev.csv") # Data set used to set.

# Add a new column called 'edited' as the edited headline.

def add_edited(dataset):
    dataset["edited1"] = dataset.apply(
        lambda x: re.sub(r"<.+/>", x["edit1"], x["original1"]), axis=1
    )
    dataset["edited2"] = dataset.apply(
        lambda x: re.sub(r"<.+/>", x["edit2"], x["original2"]), axis=1
    )
    dataset["original1"] = dataset["original1"].str.replace(r"<(.+)/>", "\g<1>")
    dataset["original2"] = dataset["original2"].str.replace(r"<(.+)/>", "\g<1>")

add_edited(train_data)
add_edited(test_data)


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
word2vec.add('.', np.zeros(300))  # For padding

# The average sequence length = 7.530647052553033 (Tokenized)
SEQUENCE_LENGTH = 10

def tokenize(text):
    tokens = word_tokenize(text.lower())
    # Punctuation Removal
    tokens = [one for one in tokens if one not in stop_words]
    # Stop words removal
    tokens = [one for one in tokens if one not in punctuations]
    return tokens

maxl = 0
l = []

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
        tokenized_headline = tokenized_headline[:SEQUENCE_LENGTH]
        while len(tokenized_headline) != SEQUENCE_LENGTH:
            tokenized_headline.append(".")  # Padding
        # global maxl
        # maxl = max(len(tokenized_headline), maxl)
        # l.append(len(tokenized_headline))
        vector = word2vec[tokenized_headline]
        vectors.append(vector)

    return np.array(vectors)

print("Tokenizing words...")

def get_processed_input(dataset):
    original = convert2vector(dataset["original1"])
    edited1 = convert2vector(dataset["edited1"])
    edited2 = convert2vector((dataset["edited2"]))
    input_vector = np.array([
        np.concatenate((edited1[i], edited2[i]), axis=0) for i in range(len(dataset))
    ])
    return input_vector

from tensorflow import keras

def get_processed_output(dataset):
    output = dataset["label"]
    output = output.to_numpy().reshape(output.shape[0], 1)
    return keras.utils.to_categorical(output)

x_train = get_processed_input(train_data)
x_test = get_processed_input(test_data)

y_train = get_processed_output(train_data)
y_test = get_processed_output(test_data)


#
# x_train_original = convert2vector(train_data["original1"])
# x_train_edited = convert2vector(train_data["edited"])
#
# # Combine original headlines with edited headlines
# # [[...Original, ...Edited], [...Original, ...Edited], [...Original, ...Edited], ...]
# x_train = np.array([
#     np.concatenate((x_train_original[i], x_train_edited[i]), axis=None) for i in range(len(x_train_original))
# ])
# # x_train_all = x_train_all.reshape(x_train_all.shape[0], 600, 1)
#
# y_train = train_data["meanGrade"]
# y_train = y_train.to_numpy().reshape(y_train.shape[0], 1)
#
# x_test_original = convert2vector(test_data["original"])
# x_test_edited = convert2vector(test_data["edited"])
#
# # Combine original headlines with edited headlines
# # [[...Original, ...Edited], [...Original, ...Edited], [...Original, ...Edited], ...]
# x_test = np.array([
#     np.concatenate((x_test_original[i], x_test_edited[i]), axis=None) for i in range(len(x_test_original))
# ])
# # x_train_all = x_train_all.reshape(x_train_all.shape[0], 600, 1)
#
# y_test = test_data["meanGrade"]
# y_test = y_test.to_numpy().reshape(y_test.shape[0], 1)
#
# # Prepare for CNN
# x_train = x_train.reshape((x_train.shape[0], x_train.shape[1], 1))
# x_test = x_test.reshape((x_test.shape[0], x_test.shape[1], 1))

### Train the model ---------------------------------------

import tensorflow as tf
from tensorflow import keras

# Split the training set into train set and test set
# TRAIN_RATIO = 0.90 # Let 90% of the data used for training
#
# x_train, x_test = tf.split(x_train_all, [int(x_train_all.shape[0] * TRAIN_RATIO), x_train_all.shape[0] - int(x_train_all.shape[0] * TRAIN_RATIO)])
# y_train, y_test = tf.split(y_train_all, [int(x_train_all.shape[0] * TRAIN_RATIO), x_train_all.shape[0] - int(x_train_all.shape[0] * TRAIN_RATIO)])

# Parameters
LEARNING_RATE = 0.0008
TRAINING_EPOCHS = 15
BATCH_SIZE = 64

# Building a FFNN network, Linear Regression

model = keras.Sequential([
    keras.layers.Bidirectional(keras.layers.LSTM(64), input_shape=(2 * SEQUENCE_LENGTH, 300)),
    keras.layers.Dense(64, activation='relu'),
    keras.layers.Dropout(0.15),
    keras.layers.Dense(3, activation="softmax")  # Output layer
])

optimizer = tf.keras.optimizers.Adam(learning_rate=LEARNING_RATE)

# Using mean square error as loss function
model.compile(loss=keras.losses.CategoricalCrossentropy(from_logits=True), optimizer=optimizer, metrics=['accuracy'])

model.summary()

history = model.fit(x_train, y_train, batch_size=BATCH_SIZE, epochs=TRAINING_EPOCHS)



#######

model.evaluate(x_test, y_test, verbose=2)

# Testing the rmse of predicting result

#
# def roundToOneDecimal(value):
#     value = value.reshape(value.shape[0])
#     roundedValue = np.array([round(one, 1) for one in value])
#     return roundedValue.reshape([value.shape[0], 1])
#
# y_pred = model.predict(x_test)
# # y_pred = roundToOneDecimal(y_pred)
#
# print("RMSE: {}".format(rmse(y_pred, y_test)))


### Predict the final result -------------------------

# test.csv doesn't have labels. This file will be used for grading.

grading_data = pd.read_csv("test.csv")
add_edited(grading_data)

x_grading = get_processed_input(grading_data)
y_grading = model.predict(x_grading)

y_grading = np.argmax(y_grading, axis=1)


result = pd.DataFrame({"id": grading_data["id"], "pred": y_grading})
result.to_csv("task-2-output.csv", index=False)

# # Grading...
# test_full_data = pd.read_csv("data/semeval-2020-task-7-dataset(full)/subtask-1/test.csv")
# test_truth = test_full_data["meanGrade"]
# print("RMSE to be submitted: {}".format(rmse(y_grading, test_truth)))