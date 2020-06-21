import numpy as np
import random


class KMeans(object):
    def __init__(self, K=3, threshold=0.01):
        self.K = K
        self.threshold = threshold
        self.train_x = None

    def fit(self, train_x):
        self.train_x = np.mat(train_x.copy())
        m, n = np.shape(self.train_x)
        center = []
        # 随机选取中心点
        for i in random.sample(range(m), self.K):
            center.append(list(np.squeeze(np.array(self.train_x[i, :]))))
        center = np.mat(center)
        error = 10000000
        label = None
        while error > self.threshold:
            center_old = center.copy()
            label = []
            for i in range(m):
                min_label = -1
                min_distance = 10000000
                for j in range(self.K):
                    dis_i_j = distance(self.train_x[i], center[j])
                    if dis_i_j < min_distance:
                        min_distance = dis_i_j
                        min_label = j
                label.append(min_label)
            label = np.array(label)
            center = np.array([np.mean(self.train_x[label == i, :], axis=0) for i in range(self.K)])
            center = np.mat(np.squeeze(center))
            error = np.sum(np.linalg.norm(center-center_old, ord=2, axis=1))
        return center, np.expand_dims(label, 1)


def distance(x, y):
    return np.linalg.norm(x-y, ord=2)
