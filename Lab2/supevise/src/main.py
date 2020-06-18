import numpy as np
import pandas as pd
import tqdm
from sklearn import preprocessing

from KNN import KNN
from SVM import SVM
from ID3 import ID3


def data_loader(dataset_dir, rnd=True, ratio=0.7, select_col=['G1', 'G2'], dst_col='G3'):
    data = pd.read_csv(dataset_dir, sep=';')
    data[dst_col] = data[dst_col] >= 10
    data['G1'] = data['G1'] >= 10
    data['G2'] = data['G2'] >= 10
    tmp = np.array(data['absences'])
    cls_0 = tmp < 5
    cls_1 = (tmp >= 5) & (tmp < 10)
    cls_2 = (tmp >= 10) & (tmp < 20)
    cls_3 = tmp >= 20
    tmp[cls_0] = 0
    tmp[cls_1] = 1
    tmp[cls_2] = 2
    tmp[cls_3] = 3
    data['absences'] = tmp

    # use LabelEncoder
    for c in data.columns:
        fields = list(set(data[c]))
        if not (isinstance(fields[0], str) or isinstance(fields[0], bool)):
            # need not to convert
            continue
        le = preprocessing.LabelEncoder()
        le.fit(fields)
        data[c] = le.transform(data[c])

    if select_col is not None:
        data_x = data[data.columns.difference([dst_col])][select_col].copy()
    else:
        data_x = data[data.columns.difference([dst_col])].copy()
    data_y = data[dst_col].copy()
    idx = np.arange(len(data))
    if rnd:
        np.random.shuffle(idx)
    idx_train = idx[:int(ratio * len(idx))]
    idx_test = idx[int(ratio * len(idx)):]

    train_x = np.array(data_x).copy()[idx_train]
    train_y = np.array(data_y).copy()[idx_train]
    test_x = np.array(data_x).copy()[idx_test]
    test_y = np.array(data_y).copy()[idx_test]

    return train_x.reshape(len(train_x), -1),\
           train_y.reshape(len(train_y), -1),\
           test_x.reshape(len(test_x), -1), \
           test_y.reshape(len(test_y), -1)


def evaluate(test_y, predict_y):
    assert test_y.shape == predict_y.shape
    TP, FP, TN, FN = 0, 0, 0, 0
    for i in range(len(test_y)):
        if test_y[i][0] == 0 and predict_y[i][0] == 0:
            TN += 1
        elif test_y[i][0] == 1 and predict_y[i][0] == 1:
            TP += 1
        elif test_y[i][0] == 1 and predict_y[i][0] == 0:
            FN += 1
        elif test_y[i][0] == 0 and predict_y[i][0] == 1:
            FP += 1
    P = TP / (TP + FP)
    R = TP / (TP + FN)
    F1 = (2 * P * R) / (P + R)
    return {
        'TP': TP,
        'FP': FP,
        'TN': TN,
        'FN': FN,
        'P': P,
        'R': R,
        'F1': F1,
    }


def main():
    dataset_dir = '../data/student-mat.csv'
    select_col = ['school', 'sex', 'age', 'address', 'famsize', 'Pstatus', 'Medu', 'Fedu', 'Mjob', 'Fjob', 'reason',
                  'guardian', 'traveltime', 'studytime', 'failures', 'schoolsup', 'famsup', 'paid', 'activities',
                  'nursery', 'higher', 'internet', 'romantic', 'famrel', 'freetime', 'goout', 'Dalc', 'Walc', 'health',
                  'absences']
    train_x, train_y, test_x, test_y = data_loader(dataset_dir, select_col=select_col)
    print(test_y.shape)
    knn = ID3()
    knn.fit(train_x, train_y)
    print(knn.tree)
    predict_y = knn.predict(test_x)
    result = evaluate(test_y, predict_y)
    print(result)


if __name__ == '__main__':
    main()
