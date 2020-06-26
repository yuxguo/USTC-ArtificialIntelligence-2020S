import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from PCA import PCA
from KMeans import KMeans


def data_loader(dataset_dir, normalization=True, rnd=False, select_col=None, dst_col='Class'):
    data = pd.read_csv(dataset_dir)

    data[dst_col] = np.array(data[dst_col]) - np.min(np.array(data[dst_col]))
    if select_col is not None:
        data_x = data[data.columns.difference([dst_col])][select_col].copy()
    else:
        data_x = data[data.columns.difference([dst_col])].copy()

    data_y = data[dst_col].copy()
    idx = np.arange(len(data))
    if rnd:
        np.random.shuffle(idx)

    train_x = np.array(data_x).copy()[idx]
    train_y = np.array(data_y).copy()[idx]

    if normalization:
        for i in range(train_x.shape[1]):
            train_x[:, i] = (train_x[:, i] - np.mean(train_x[:, i])) / np.std(train_x[:, i])

    return train_x.reshape(len(train_x), -1), train_y.reshape(len(train_y), -1), np.array(data)


def evaluate(train_x, train_y, predict_y, k=3):
    assert train_y.shape == predict_y.shape
    a, b, c, d = 0, 0, 0, 0
    for i in range(len(train_y)):
        for j in range(i+1, len(train_y)):
            if i == j:
                continue
            if train_y[i][0] == train_y[j][0] and predict_y[i][0] == predict_y[j][0]:
                a += 1
            elif train_y[i][0] == train_y[j][0] and predict_y[i][0] != predict_y[j][0]:
                b += 1
            elif train_y[i][0] != train_y[j][0] and predict_y[i][0] == predict_y[j][0]:
                c += 1
            elif train_y[i][0] != train_y[j][0] and predict_y[i][0] != predict_y[j][0]:
                d += 1
    s = []
    for i in range(len(train_y)):
        dis = [[] for _ in range(k)]
        class_i = predict_y[i][0]
        for j in range(len(train_y)):
            if i == j:
                continue
            dis[predict_y[j][0]].append(np.linalg.norm(train_x[i, :] - train_x[j, :], ord=2))
        a_i = np.mean(dis[class_i])
        b_i = min([np.mean(dis[j]) for j in range(k) if j != class_i])
        s.append((b_i - a_i) / max(a_i, b_i))

    return {
        'S': np.mean(np.array(s)),
        'RI': (a + d) / (a + b + c + d)
    }


def save_to_csv(data, label):
    classes = np.max(label)
    for c in range(classes+1):
        save_list = []
        for i in range(len(data)):
            if c == label[i][0]:
                save_list.append(data[i])
        pd_data = pd.DataFrame(np.array(save_list))
        pd_data.to_csv('../output/class-%d.csv' % c, index=False)


def visualization(center, data, label, k):
    colors = ['lightgreen', 'orange', 'lightblue', 'yellow', 'black']
    if k == 2:
        for i in range(len(data)):
            plt.scatter(data[i, 0], data[i, 1], c=colors[label[i][0]])

        for i in range(len(center)):
            plt.scatter(center[i, 0], center[i, 1], c='red', marker='*')
        plt.show()
    elif k == 3:
        fig = plt.figure()
        ax = Axes3D(fig)
        for i in range(len(data)):
            ax.scatter(data[i, 0], data[i, 1], data[i, 2], c=colors[label[i][0]])
        for i in range(len(center)):
            ax.scatter(center[i, 0], center[i, 1], center[i, 2], c='red', marker='*')
        plt.show()
    pass


def main():
    dim = 2
    num_class = 3
    dataset_dir = '../input/wine.csv'
    train_x, train_y, raw_data = data_loader(dataset_dir)
    pca = PCA(first_k=dim, use_threshold=False, threshold=0.5)
    proj = pca.fit(train_x)
    kmeans = KMeans(K=num_class)
    center, predict_y = kmeans.fit(proj)
    result = evaluate(proj, train_y, predict_y, k=num_class)
    visualization(center, proj, predict_y, dim)
    save_to_csv(raw_data, predict_y)
    print(result)


if __name__ == '__main__':
    main()
