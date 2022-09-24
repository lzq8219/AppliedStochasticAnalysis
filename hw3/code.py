import matplotlib.pyplot as plt
import numpy as np

def rand_sphere(n):
    theta=np.pi*2*np.random.rand(n)
    u=2*np.random.rand(n)-1
    t=(1-u*u)**0.5
    x=np.cos(theta)*t
    y=np.sin(theta)*t
    z=u
    return np.array([x,y,z])

def rand_sphere1(n):
    k=n;
    result=np.array([[],[],[]])
    while(k>0):
        x=2*np.random.rand(3,k)-1
        normx=(x[0]**2+x[1]**2+x[2]**2)**0.5
        l=(normx<=1)&(normx>0)
        x=x[:,l]/normx[l]
        result=np.append(result,x,axis=1)
        k=n-np.shape(result)[1]
    return result

N=1000
sample_1=rand_sphere(N)
sample_2=rand_sphere1(N)

ax=plt.subplot(1,2,1,projection='3d')
ax.set_title('sphere1')
ax.scatter(sample_1[0],sample_1[1],sample_1[2],c='r')


bx=plt.subplot(1,2,2,projection='3d')
bx.set_title('sphere2')
bx.scatter(sample_2[0],sample_2[1],sample_2[2],c='y')

plt.show()


