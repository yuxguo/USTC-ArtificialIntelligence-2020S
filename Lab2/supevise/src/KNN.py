import numpy as np


def l1(a, b):
    '''
    :param a: [1, m]
    :param b: [n, m]
    :return: [n, 1]
    '''
    return np.sum(np.fabs(a - b), axis=1)


def l2(a, b):
    return np.sum(np.sqrt(a - b), axis=1)


def dis_match(a, b):
    return np.sum((a != b), axis=1)


class KNN(object):
    '''
    解决二分类问题，标签 [0, 1]
    '''

    def __init__(self, distance_function=dis_match, threshold=0.5, K=20):
        if distance_function == 'l1':
            self.d_f = l1
        elif distance_function == 'l2':
            self.d_f = l2
        else:
            self.d_f = dis_match
        self.K = K
        self.threshold = threshold
        self.train_x = None
        self.train_y = None
        self.test_x = None

    def fit(self, train_x, train_y):
        self.train_x = train_x.copy()
        self.train_y = train_y.copy()

    def predict(self, test_x):
        '''
        :param test_x: [n_1, m]
        :return: [n_1, 1]
        '''
        assert self.train_x is not None, 'Not init train_x'
        assert self.train_y is not None, 'Not init train_y'
        assert self.train_x.shape[0] == self.train_y.shape[0]
        self.test_x = test_x.copy()
        result = []
        for t_x in test_x:
            top_k_idx = np.argpartition(self.d_f(t_x, self.train_x), self.K)[:self.K]
            top_k_y = self.train_y[top_k_idx]
            predict_y = [1] if np.sum(top_k_y) / self.K > self.threshold else [0]
            result.append(predict_y)

        return np.array(result)

