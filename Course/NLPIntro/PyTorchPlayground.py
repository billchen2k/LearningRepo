import torch
import torch.nn as nn
from torch.autograd import Variable

h = [1, 0, 0, 0]
e = [0, 1, 0, 0]
l = [0, 0, 1, 0]
o = [0, 0, 0, 1]

cell = nn.RNN(input_size=4, hidden_size=2, batch_first=True)

hidden = Variable(torch.randn(1, 1, 2))

inputs = Variable(torch.Tensor([h, e, l, l, o]))

for one in inputs:
    one = one.view(1, 1, -1)
    out, hidden = cell(one, hidden)
    print("input size = {}, output size = {}".format(one.size(), out.size()))

inputs = inputs.view(1, 5, -1)
out, hidden = cell(inputs, hidden)
print("sequence input size = {}, output size = {}".format(inputs.size(), out.size()))