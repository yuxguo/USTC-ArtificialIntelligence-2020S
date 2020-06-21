import numpy as np


def ent(p):
    ent_d = 0
    for p_k in p:
        ent_d += 0 if p_k == 0 else p_k * np.log2(p_k)
    return -ent_d


def check_equ(a):
    flag = True
    for line in a:
        if list(line) != list(a[0, :]):
            flag = False
            break
    return flag


class ID3(object):
    def __init__(self):
        self.train_x = None
        self.train_y = None
        self.tree = {}
        self.test_x = None
        pass

    def fit(self, train_x, train_y):
        self.train_x = train_x.copy()
        self.train_y = train_y.copy()
        m, n = self.train_x.shape
        self.tree = self.tree_generate(np.array([True] * m), list(range(n)))
        pass

    def query(self, rows, col, col_v):
        result = []
        for i in range(len(self.train_x)):
            if rows[i] and self.train_x[i, col] == col_v:
                result.append(True)
            else:
                result.append(False)
        return np.array(result)

    def select_attr(self, a_idx, d_idx):
        D = len(d_idx)
        cnt_p = np.bincount(np.squeeze(self.train_y[d_idx, :]))
        p = cnt_p / D
        ent_d = ent(p)
        gain = []
        for a in a_idx:
            gain_tmp = 0
            for v in range(np.max(self.train_x[:, a]) + 1):
                v_y = self.train_y[self.query(d_idx, a, v), :]
                D_v = len(v_y)
                if D_v == 0:
                    continue
                cnt_p_v = np.bincount(np.squeeze(v_y, 1))
                p_v = cnt_p_v / D_v
                ent_d_v = ent(p_v)
                gain_tmp += D_v / D * ent_d_v
            gain.append(ent_d - gain_tmp)

        gain = np.array(gain)
        return a_idx[np.argmax(gain)]

    def tree_generate(self, d_idx, a_idx):
        if np.max(self.train_y[d_idx, :]) == np.min(self.train_y[d_idx, :]):
            return int(self.train_y[d_idx][0][0])

        if len(a_idx) == 0 or check_equ(self.train_x[d_idx, :][:,  a_idx]):
            return int(np.argmax(np.bincount(np.squeeze(self.train_y[d_idx, :], 1))))

        node = {}
        select_attr = self.select_attr(a_idx, d_idx)
        left_attrs = [a for a in a_idx if a != select_attr]
        for v in range(np.max(self.train_x[:, select_attr]) + 1):
            if len(self.train_y[self.query(d_idx, select_attr, v), :]) == 0:
                node[str(select_attr) + '-' + str(v)] = int(np.argmax(np.bincount(np.squeeze(self.train_y[d_idx, :], 1))))
            else:
                child = self.tree_generate(self.query(d_idx, select_attr, v), left_attrs)
                node[str(select_attr) + '-' + str(v)] = child
        return node

    def predict(self, test_x):
        self.test_x = test_x.copy()
        result = []
        for line in self.test_x:
            n = self.tree
            while not isinstance(n, int):
                attr = int(list(n.keys())[0].split('-')[0])
                val = line[attr]
                n = n[str(attr) + '-' + str(val)]
            result.append([n])
        return np.array(result)

