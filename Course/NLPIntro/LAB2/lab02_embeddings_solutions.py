import torch
from torch.autograd import Variable
import numpy as np
import torch.nn.functional as F
from tqdm import tqdm
import nltk

# nltk.download('punkt')
# nltk.download('wordnet')
with open("train.txt", "r") as f:
    big_corpus = f.read()

print(len(big_corpus))

#%%

from nltk import word_tokenize

print("Tokenizing...")
tokenized = word_tokenize(big_corpus.lower())
vocabulary = set(tokenized)

vocabulary_size = len(vocabulary)
print(vocabulary_size)

print("Preparing word2idx and idx2word...")
word2idx = {w: idx for (idx, w) in enumerate(vocabulary)}
idx2word = {idx: w for (idx, w) in enumerate(vocabulary)}

def look_up_table(word_idx):
    x = torch.zeros(vocabulary_size).float()
    x[word_idx] = 1.0
    return x

#%%

window_size = 2
idx_pairs = []
context_dict = {i : set() for i in range(vocabulary_size)}

tokenized_corpus_raw = big_corpus.lower().split(".")
tokenized_corpus = []
for one in tokenized_corpus_raw:
    tokenized_corpus.append(word_tokenize(one))

print("Preparing context dict...")
for sentence in tqdm(tokenized_corpus):

  # Ignore words that's not in the index table
  indices = [word2idx[word] for word in sentence if word in word2idx]
  for center_word_pos in range(len(indices)):
      for w in range(-window_size, window_size + 1):
          context_word_pos = center_word_pos + w
          if context_word_pos < 0 or context_word_pos >= len(indices) or center_word_pos == context_word_pos:
              continue
              
          context_word_idx = indices[context_word_pos]
          idx_pairs.append((indices[center_word_pos], context_word_idx))
          context_dict[indices[center_word_pos]].add(context_word_idx)

# Calculating the non_context_dict
noncontext_dict = {i : [] for i in range(vocabulary_size)}
for one in tqdm(noncontext_dict.keys()):
    noncontext_dict[one] = list(set(i for i in range(vocabulary_size)) - context_dict[one])

idx_pairs = np.array(idx_pairs) # it will be useful to have this as numpy array

print(idx_pairs)
print(len(idx_pairs))

#%%

# Hyperparameters for Negative Sample:
embedding_dims = 5
num_epochs = 100
learning_rate = 0.001
negative_sample_count = 5

# The two weight matrices:
W1 = torch.randn(embedding_dims, vocabulary_size, requires_grad=True)
W2 = torch.randn(embedding_dims, vocabulary_size, requires_grad=True)

for epoch in range(num_epochs):
    print("EPOCH{} Started.".format(epoch))
    epoch_loss = 0
    for data, target in tqdm(idx_pairs):
        x_var = Variable(look_up_table(data)).float()

        y_pos = Variable(torch.from_numpy(np.array([target])).long())
        y_pos_var = Variable(look_up_table(target)).float()

        non_context_words = noncontext_dict[data]

        neg_indices = []
        for i in range(negative_sample_count):
            neg_indices.append(non_context_words[np.random.randint(len(non_context_words))])

        neg_sample = Variable(torch.from_numpy(np.array(neg_indices)).long())

        # Now for test only
        neg_sample =  Variable(torch.from_numpy(np.array([non_context_words[np.random.randint(len(non_context_words))]])).long())
        y_neg_var = Variable(look_up_table(neg_sample)).float()
        
        #TO DO: use the look up table
         
        x_emb = torch.matmul(W1, x_var) 
        y_pos_emb = torch.matmul(W2, y_pos_var)
        y_neg_emb = torch.matmul(W2, y_neg_var)
        
        # get positive sample score
        pos_loss = F.logsigmoid(torch.matmul(x_emb, y_pos_emb))
        
        # get negsample score
        neg_loss = F.logsigmoid(-1 * torch.matmul(x_emb, y_neg_emb))
        
        # TO DO: compute loss
        loss = -(pos_loss + neg_loss)
        epoch_loss += loss.item()
        
        # propagate the error
        loss.backward()
        
        # gradient descent
        W1.data -= learning_rate * W1.grad.data
        W2.data -= learning_rate * W2.grad.data

        # zero out gradient accumulation
        W1.grad.data.zero_()
        W2.grad.data.zero_()
        
    if epoch % 10 == 0:    
        print(f'Loss at epoch {epoch}: {epoch_loss/len(idx_pairs)}')