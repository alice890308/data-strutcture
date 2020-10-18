pointTon=int(input())
point=[]
father=[]
kid=[]
extend=[]
k=0

# 從input裡面找東西
def find(a):
    for k in range(pointTon):
        for j in range(kid[k]):
            if a==point[k][j]:
                return 0
    return 1

# 吃input，把每個node的child用int存起來
for i in range(pointTon):
    point.append(input())
    point[i]=point[i].split(" ")
    kid.append(int(point[i].pop(0)))

#把一開始吃input的陣列裡面的資料也都轉成int
for i in range(pointTon):
    for j in range(len(point[i])):
        point[i][j]=int(point[i][j])
print(point)


for i in range(pointTon):
    if find(i+1):
        father.append([i+1])
father.append(list(point[father[0][0]-1]))

while 1:
    for i in range(len(father[k+1])):
        extend.append([])
        extend[k].extend(point[father[k+1][i]-1])
    if extend[k]==[]:
        break
    father.append(extend[k])
    k+=1 
print()
print(father)