# %%

# Imports

import torch
import torch.nn as nn
import pandas as pd
import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
from torch.utils.data import Dataset, random_split
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB
import torch.optim as optim
import codecs
import tqdm

# %%

# Setting random seed and device
SEED = 1

torch.manual_seed(SEED)
torch.cuda.manual_seed(SEED)
torch.backends.cudnn.deterministic = True

use_cuda = torch.cuda.is_available()
device = torch.device("cuda:0" if use_cuda else "cpu")

# %%

# Load data
train_df = pd.read_csv('data/task-2/train.csv')
test_df = pd.read_csv('data/task-2/dev.csv')

# %%

# Number of epochs
epochs = 20

# Proportion of training data for train compared to dev
train_proportion = 0.8


# %% md

#### Approach 1: Using pre-trained word representations (GLOVE)


# %%

# We define our training loop
def train(train_iter, dev_iter, model, number_epoch):
    """
    Training loop for the model, which calls on eval to evaluate after each epoch
    """

    print("Training model.")

    for epoch in range(1, number_epoch + 1):

        model.train()

        epoch_loss = 0
        epoch_correct = 0
        no_observations = 0  # Observations used for training so far

        for batch in train_iter:
            feature, target = batch
            feature, target = feature.to(device), target.to(device)

            # for RNN:
            model.batch_size = target.shape[0]
            no_observations = no_observations + target.shape[0]
            model.hidden = model.init_hidden()

            predictions = model(feature).squeeze(1)
            optimizer.zero_grad()
            loss = loss_fn(predictions, target)

            correct, __ = model_performance(np.argmax(predictions.detach().cpu().numpy(), axis=1),
                                            target.detach().cpu().numpy())

            loss.backward()
            optimizer.step()

            epoch_loss += loss.item() * target.shape[0]
            epoch_correct += correct

        valid_loss, valid_acc, __, __ = eval(dev_iter, model)

        epoch_loss, epoch_acc = epoch_loss / no_observations, epoch_correct / no_observations
        print(f'| Epoch: {epoch:02} | Train Loss: {epoch_loss:.2f} | Train Accuracy: {epoch_acc:.2f} | \
        Val. Loss: {valid_loss:.2f} | Val. Accuracy: {valid_acc:.2f} |')


# %%

# We evaluate performance on our dev set
def eval(data_iter, model):
    """
    Evaluating model performance on the dev set
    """
    model.eval()
    epoch_loss = 0
    epoch_correct = 0
    pred_all = []
    trg_all = []
    no_observations = 0

    with torch.no_grad():
        for batch in data_iter:
            feature, target = batch

            feature, target = feature.to(device), target.to(device)

            # for RNN:
            model.batch_size = target.shape[0]
            no_observations = no_observations + target.shape[0]
            model.hidden = model.init_hidden()

            predictions = model(feature).squeeze(1)
            loss = loss_fn(predictions, target)

            # We get the mse
            pred, trg = predictions.detach().cpu().numpy(), target.detach().cpu().numpy()
            correct, __ = model_performance(np.argmax(pred, axis=1), trg)

            epoch_loss += loss.item() * target.shape[0]
            epoch_correct += correct
            pred_all.extend(pred)
            trg_all.extend(trg)

    return epoch_loss / no_observations, epoch_correct / no_observations, np.array(pred_all), np.array(trg_all)


# %%

# How we print the model performance
def model_performance(output, target, print_output=False):
    """
    Returns accuracy per batch, i.e. if you get 8/10 right, this returns 0.8, NOT 8
    """
    correct_answers = (output == target)
    correct = sum(correct_answers)
    acc = np.true_divide(correct, len(output))

    if print_output:
        print(f'| Acc: {acc:.2f} ')

    return correct, acc


# %%

# To create our vocab
def create_vocab(data):
    """
    Creating a corpus of all the tokens used
    """
    tokenized_corpus = []  # Let us put the tokenized corpus in a list

    for sentence in data:

        tokenized_sentence = []

        for token in sentence.split(' '):  # simplest split is

            tokenized_sentence.append(token)

        tokenized_corpus.append(tokenized_sentence)

    # Create single list of all vocabulary
    vocabulary = []  # Let us put all the tokens (mostly words) appearing in the vocabulary in a list

    for sentence in tokenized_corpus:

        for token in sentence:

            if token not in vocabulary:

                if True:
                    vocabulary.append(token)

    return vocabulary, tokenized_corpus


# %%

# Used for collating our observations into minibatches:
def collate_fn_padd(batch):
    '''
    We add padding to our minibatches and create tensors for our model
    '''

    batch_labels = [l for f, l in batch]
    batch_features = [f for f, l in batch]

    batch_features_len = [len(f) for f, l in batch]

    seq_tensor = torch.zeros((len(batch), max(batch_features_len))).long()

    for idx, (seq, seqlen) in enumerate(zip(batch_features, batch_features_len)):
        seq_tensor[idx, :seqlen] = torch.LongTensor(seq)

    batch_labels = torch.LongTensor(batch_labels)

    return seq_tensor, batch_labels


# We create a Dataset so we can create minibatches
class Task2Dataset(Dataset):

    def __init__(self, train_data, labels):
        self.x_train = train_data
        self.y_train = labels

    def __len__(self):
        return len(self.y_train)

    def __getitem__(self, item):
        return self.x_train[item], self.y_train[item]


# %%


class BiLSTM_classification(nn.Module):

    def __init__(self, embedding_dim, hidden_dim, vocab_size, batch_size, device):
        super(BiLSTM_classification, self).__init__()
        self.hidden_dim = hidden_dim
        self.embedding_dim = embedding_dim
        self.device = device
        self.batch_size = batch_size
        self.embedding = nn.Embedding(vocab_size, embedding_dim, padding_idx=0)

        # The LSTM takes word embeddings as inputs, and outputs hidden states
        # with dimensionality hidden_dim.
        self.lstm = nn.LSTM(embedding_dim, hidden_dim, bidirectional=True)

        # The linear layer that maps from hidden state space to tag space
        self.hidden2label = nn.Linear(hidden_dim * 2, 3)
        self.hidden = self.init_hidden()

    def init_hidden(self):
        # Before we've done anything, we dont have any hidden state.
        # Refer to the Pytorch documentation to see exactly why they have this dimensionality.
        # The axes semantics are (num_layers * num_directions, minibatch_size, hidden_dim)
        return torch.zeros(2, self.batch_size, self.hidden_dim).to(self.device), \
               torch.zeros(2, self.batch_size, self.hidden_dim).to(self.device)

    def forward(self, sentence):
        embedded = self.embedding(sentence)
        embedded = embedded.permute(1, 0, 2)

        lstm_out, self.hidden = self.lstm(
            embedded.view(len(embedded), self.batch_size, self.embedding_dim), self.hidden)

        out = self.hidden2label(lstm_out[-1])
        return out


# %%

## Approach 1 code, using functions defined above:

# We set our training data and test data
training_data = train_df['original1']
test_data = test_df['original1']

##### Preproceccing the data
train_df['original1']

# Creating word vectors
training_vocab, training_tokenized_corpus = create_vocab(training_data)
test_vocab, test_tokenized_corpus = create_vocab(test_data)

# Creating joint vocab from test and train:
joint_vocab, joint_tokenized_corpus = create_vocab(pd.concat([training_data, test_data]))

print("Vocab created.")

# We create representations for our tokens
wvecs = []  # word vectors
word2idx = []  # word2index
idx2word = []

# This is a large file, it will take a while to load in the memory!
with codecs.open('glove.6B.100d.txt', 'r', 'utf-8') as f:
    # Change
    index = 0
    for line in f.readlines():
        # Ignore the first line - first line typically contains vocab, dimensionality
        if len(line.strip().split()) > 3:
            word = line.strip().split()[0]
            if word in joint_vocab:
                (word, vec) = (word, list(map(float, line.strip().split()[1:])))
                wvecs.append(vec)
                word2idx.append((word, index))
                idx2word.append((index, word))
                index += 1

wvecs = np.array(wvecs)
word2idx = dict(word2idx)
idx2word = dict(idx2word)

vectorized_seqs = [[word2idx[tok] for tok in seq if tok in word2idx] for seq in training_tokenized_corpus]

INPUT_DIM = len(word2idx)
EMBEDDING_DIM = 100
BATCH_SIZE = 32

model = BiLSTM_classification(EMBEDDING_DIM, 50, INPUT_DIM, BATCH_SIZE, device)
print("Model initialised.")

model.to(device)
# We provide the model with our embeddings
model.embedding.weight.data.copy_(torch.from_numpy(wvecs))

feature = vectorized_seqs

# 'feature' is a list of lists, each containing embedding IDs for word tokens
train_and_dev = Task2Dataset(feature, train_df['label'])

train_examples = round(len(train_and_dev) * train_proportion)
dev_examples = len(train_and_dev) - train_examples

train_dataset, dev_dataset = random_split(train_and_dev,
                                          (train_examples,
                                           dev_examples))

train_loader = torch.utils.data.DataLoader(train_dataset, shuffle=True, batch_size=BATCH_SIZE,
                                           collate_fn=collate_fn_padd)
dev_loader = torch.utils.data.DataLoader(dev_dataset, batch_size=BATCH_SIZE, collate_fn=collate_fn_padd)

print("Dataloaders created.")

loss_fn = nn.CrossEntropyLoss()
loss_fn = loss_fn.to(device)

optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# %%
epochs = 10
train(train_loader, dev_loader, model, epochs)

# %%
#
# training_data, dev_data, training_y, dev_y = train_test_split(train_df['edit1'], train_df['label'],
#                                                                         test_size=(1-train_proportion),
#                                                                         random_state=42)
#
#
# test_loader = torch.utils.data.DataLoader(dev_dataset, batch_size=len(dev_dataset.dataset.y_train), collate_fn=collate_fn_padd)
#
# for batch in test_loader:
#     batch_feature, batch_targets = batch
#     batch_feature, batch_targets = batch_feature.to(device), batch_targets.to(device)
#     model.batch_size = batch_targets.shape[0]
#     batch_pred = model(batch_feature)
#     batch_correct = model_performance(torch.tensor(np.argmax(batch_pred.detach().cpu().numpy(), axis=1)),
#                                       batch_targets.detach().cpu(), True)
#
# pred = model(test_features)
training_data, dev_data, training_y, dev_y = train_test_split(train_df['edit1'], train_df['label'],
                                                              test_size=(1 - train_proportion),
                                                              random_state=42)

pred_baseline = torch.zeros(len(dev_y)) + 1  # 1 is most common class
print("\nBaseline performance:")
sse, mse = model_performance(pred_baseline, torch.tensor(dev_y.values), True)

# %%
def score_task_2(truth_loc, prediction_loc):
    truth = pd.read_csv(truth_loc, usecols=['id', 'label'])
    pred = pd.read_csv(prediction_loc, usecols=['id', 'pred'])

    assert (sorted(truth.id) == sorted(pred.id)), "ID mismatch between ground truth and prediction!"

    data = pd.merge(truth, pred)
    data = data[data.label != 0]
    accuracy = np.sum(data.label == data.pred) * 1.0 / len(data)

    print("Accuracy = %.3f" % accuracy)

def predict(data_iter, model):
    """
    Predict and return result
    """
    model.eval()
    epoch_loss = 0
    epoch_correct = 0
    pred_all = []
    trg_all = []
    no_observations = 0

    with torch.no_grad():
        for batch in data_iter:
            feature, target = batch

            feature, target = feature.to(device), target.to(device)

            # for RNN:
            model.batch_size = target.shape[0]
            no_observations = no_observations + target.shape[0]
            model.hidden = model.init_hidden()

            predictions = model(feature).squeeze(1)
            loss = loss_fn(predictions, target)

            # We get the mse
            pred, trg = predictions.detach().cpu().numpy(), target.detach().cpu().numpy()
            correct, __ = model_performance(np.argmax(pred, axis=1), trg)

            epoch_loss += loss.item() * target.shape[0]
            epoch_correct += correct
            pred_all.extend(pred)
            trg_all.extend(trg)
    return pred_all
#
test_vectorized_seqs = [[word2idx[tok] for tok in seq if tok in word2idx] for seq in test_tokenized_corpus]
outtest_dataset = Task2Dataset(test_vectorized_seqs, test_df['label'])
test_dataset, __ = random_split(test_dataset, (len(test_dataset), 0))
test_loader = torch.utils.data.DataLoader(test_dataset, batch_size=BATCH_SIZE, collate_fn=collate_fn_padd)

loss, accu, __, __ = eval(test_loader, model)
print("LOSS: {}, ACCURACY: {}".format(loss, accu))
