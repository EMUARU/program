# A = B = C = 20
# print(A)
# print(B)
# print(C)

# A, B, C = 10, 15, 20

# print(A)
# print(B)
# print(C)

# *A, B, C = 10, 15, 20, 30, 40, 50
# print(A, B, C)
# print(B)
# print(C)

# A = 10, 15, 20
# print(type(A))

# A = [1, 2, 3, 4]
# B = [5, 6]
# for data in [(x,y) for x in A for y in B]:
#     print(data)

# s2=set('APPLE')
# print(s2, sep = '\n')

# def test1(listA):
#     print(id(listA))
#     listA.append(1)
#     listA = [2]
#     print(id(listA))
# listV=[]
# test1(listV)
# print(id(listV), '\n', listV)

# import numpy as np
# arr = np.array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]], dtype='int32')

# reshaped_c = arr.reshape((6, 2), order='C')
# reshaped_f = arr.reshape((6, 2), order='F')
# print(reshaped_c)
# print(reshaped_f)

for n in range(2, 10):
    for x in range(2, n):
        if n % x == 0:
            print(n, "is not a prime number")
            break