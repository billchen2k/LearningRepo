
#%%
import sklearn
from sklearn import model_selection
import random
import pandas as pd
import pickle
import numpy as np
import matplotlib.pyplot as plt
# housing = pd.read_csv("./housing.csv")

import moxing as mox
mox.file.shift('os', 'mox')
with mox.file.File("s3://billc//ML//housing//data//housing.csv", "r") as f:
    input_data = pd.read_csv(f)

housing = input_data
# 处理海岸数据
housing.ocean_proximity = housing.ocean_proximity.replace(['NEAR BAY', '<1H OCEAN', 'INLAND', 'NEAR OCEAN', 'ISLAND'],
                                                          ['2','4','5','3','1'])

# 划分数据集
train, test = model_selection.train_test_split(housing, test_size=0.2, random_state=random.randint(0, 100))
train.describe()
test.describe()
train_x = train.drop('median_house_value', axis=1)
train_y = train.median_house_value
test_x = test.drop('median_house_value', axis=1)
test_y = train.median_house_value
housing.head()

#%%
# 使用平均值填补空缺数据
train_x = train_x.fillna(train_x['total_bedrooms'].mean())
test_x = test_x.fillna(train_x['total_bedrooms'].mean())

#%%
# 训练
from sklearn.linear_model import LinearRegression
model = LinearRegression()
model.fit(train_x, train_y)
score = model.score(train_x, train_y)
print("Finished. Accuracy: {}".format(score))

with open('model', 'wb+') as f:
    pickle.dump(model, f)