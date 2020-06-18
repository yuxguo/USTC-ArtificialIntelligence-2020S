import numpy as np
import random


class SVM(object):
    def __init__(self, kernel='poly', max_iter=40, C=0.5, toler=0.00001):
        self.C = C
        self.kernel_f = get_kernel_function(kernel)
        self.max_iter = max_iter
        self.train_x = None
        self.train_y = None
        self.test_x = None
        self.alphas = None
        self.m = None
        self.n = None
        self.b = 0
        self.toler = toler
        pass

    def fit(self, train_x, train_y):
        self.train_x = np.mat(train_x.copy())
        self.train_y = train_y.copy()
        self.train_y[self.train_y == 0] = -1  # convert label to -1, +1
        self.train_y = np.mat(self.train_y)

        self.m, self.n = np.shape(self.train_x)
        self.alphas = np.mat(np.zeros((self.m, 1)))
        self.b = 0
        self.smo()
        pass

    def predict(self, test_x):
        self.test_x = np.mat(test_x.copy())
        result = []
        for i in range(len(test_x)):
            r = np.sign(self.f_x(self.alphas, self.train_x, self.train_y, self.test_x[i, :], self.b))
            result.append([1] if r == 1 else [0])

        return np.array(result)

    def f_x(self, alphas, x_m, y_m, x, b):
        m, n = np.shape(x_m)
        result = 0
        for i in range(m):
            result += float(alphas[i] * y_m[i] * self.kernel_f(x, x_m[i])) + b
        return result

    def select_j(self, i):
        j = i
        while j == i:
            j = int(random.uniform(0, self.m))
        return j

    def examine(self, i):
        f_X_i = self.f_x(self.alphas, self.train_x, self.train_y, self.train_x[i], self.b)
        E_i = f_X_i - float(self.train_y[i])
        if ((self.train_y[i] * E_i < -self.toler) and (self.alphas[i] < self.C)) or (
                (self.train_y[i] * E_i > self.toler) and (self.alphas[i] > 0)):
            j = self.select_j(i)
            f_X_j = self.f_x(self.alphas, self.train_x, self.train_y, self.train_x[j], self.b)
            E_j = f_X_j - float(self.train_y[j])
            alpha_i_old = self.alphas[i].copy()
            alpha_j_old = self.alphas[j].copy()
            if self.train_y[i] != self.train_y[j]:
                L = max(0, self.alphas[j] - self.alphas[i])
                H = min(self.C, self.C + self.alphas[j] - self.alphas[i])
            else:
                L = max(0, self.alphas[j] + self.alphas[i] - self.C)
                H = min(self.C, self.alphas[j] + self.alphas[i])
            if L == H:
                return 0

            eta = -2.0 * self.kernel_f(self.train_x[i, :], self.train_x[j, :]) + \
                  self.kernel_f(self.train_x[i, :], self.train_x[i, :]) + self.kernel_f(self.train_x[j, :],
                                                                                        self.train_x[j, :])
            if eta <= 0:
                return 0

            self.alphas[j] += self.train_y[j] * (E_i - E_j) / eta

            if self.alphas[j] > H:
                self.alphas[j] = H
            elif self.alphas[j] < L:
                self.alphas[j] = L

            if abs(self.alphas[j] - alpha_j_old) < 0.00001:
                return 0

            self.alphas[i] += self.train_y[j] * self.train_y[i] * (alpha_j_old - self.alphas[j])

            b1 = self.b - E_i - self.train_y[i] * (self.alphas[i] - alpha_i_old) * self.kernel_f(self.train_x[i, :],
                                                                                       self.train_x[i, :]) - \
                 self.train_y[j] * (self.alphas[j] - alpha_j_old) * self.kernel_f(self.train_x[i, :], self.train_x[j, :])

            b2 = self.b - E_j - self.train_y[i] * (self.alphas[i] - alpha_i_old) * self.kernel_f(self.train_x[i, :],
                                                                                       self.train_x[j, :]) - \
                 self.train_y[j] * (self.alphas[j] - alpha_j_old) * self.kernel_f(self.train_x[j, :], self.train_x[j, :])

            if (0 < self.alphas[i]) and (self.C > self.alphas[i]):  # 判断符合条件的b
                self.b = b1
            elif (0 < self.alphas[j]) and (self.C > self.alphas[j]):
                self.b = b2
            else:
                self.b = (b1 + b2) / 2.0
            return 1
        else:
            return 0

    def smo(self):
        iters = 0
        num_changed = 0
        examine_all = True
        while iters < self.max_iter and (num_changed > 0 or examine_all):
            num_changed = 0

            if examine_all:
                for i1 in range(self.m):
                    num_changed += self.examine(i1)
            else:
                for i1 in range(len(self.alphas)):
                    if 0 < self.alphas[i1] < self.C:
                        num_changed += self.examine(i1)
            iters += 1
            print(iters)
            if examine_all:
                examine_all = False
            elif num_changed == 0:
                examine_all = True


def get_kernel_function(kernel):
    sigma = 0.5
    offset = 1
    dim = 3
    kernel_dict = {
        'linear': lambda x, y: x * y.T,
        'poly': lambda x, y: (offset + x * y.T) ** dim,
        'rbf': lambda x, y: np.exp(-np.sqrt(np.linalg.norm(x-y) ** 2 / (2 * sigma ** 2)))
    }
    return kernel_dict[kernel]
