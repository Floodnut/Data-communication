import numpy as np

intDict = dict()
a = np.random.randint(0,50,500)     # generate 500 int (>=0)

for i in enumerate(a.flatten(), 0): # change ndarray to dictionary ('num' : frequency )
    if intDict.get(str(i[1])) is None:
        intDict[str(i[1])] = 1
    else:
        intDict[str(i[1])] += 1

for i in range(3):                  # print dictionary sorted by frequency.reverse
    num = sorted(intDict.items(), key=lambda x: x[1], reverse=True)[i]
    print("정수: " + str(num[0]) +"\t 중복 횟수: "+ str(num[1]))
