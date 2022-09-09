import numpy as np

N=[10,100,1000,10000,100000,1000000,10000000]
nlist=np.array(N)
ilist=np.array([])
dlist=np.array([])
olist=np.array([])


for n in nlist:
    x=np.random.rand(n)
    y=np.sin(x)
    i=sum(y)/n
    d=abs(i-(1-np.cos(1)))
    ilist=np.append(ilist,i)
    dlist=np.append(dlist,d)

olist=np.log(dlist[0:-1]/dlist[1:])/np.log(nlist[1:]/nlist[0:-1])
print('order:',olist)


