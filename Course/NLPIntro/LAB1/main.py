from typing import Any

import torch, torchvision
from torch.nn.modules.module import T_co

model = torchvision.models.resnet18(pretrained=True)
data = torch.rand(1,3,64,64)
labels = torch.rand(1, 1000)

prediction = model(data)

loss = (prediction - labels).sum()
loss.backward()

optim = torch.optim.SGD(model.parameters(), lr=1e-2, momentum=0.9)
optim.step() #gradient descent

def test() -> int:
    """
    This is a help document.
    :return: An integer
    """
    return 3