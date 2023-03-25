import matplotlib.pyplot as plt
import numpy as np
##
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.set_xlabel(r'$\theta$')
ax.set_ylabel(r'$\phi$')
ax.set_zlabel("Densidad de probabilidad")
datos=np.genfromtxt("datos.dat",delimiter=",",skip_header=1,dtype=np.double)
x=datos[:,0]
y=datos[:,1]
z=datos[:,2]
ax.plot_trisurf(x, y, z)
ax.view_init(25, 75)
plt.savefig("Distribucion.pdf")
plt.show()
plt.close()

#datos2=np.genfromtxt("WDecay.dat",delimiter=",",skip_header=0,dtype=np.double)
#fig, ax = plt.subplots()

#ax.plot(datos2[:,0],datos2[:,1])
#plt.savefig("WDecay.pdf")
#plt.show()
#datos3=np.genfromtxt("JPsiDecay.dat",delimiter=",",skip_header=0,dtype=np.double)
#fig, ax = plt.subplots()

#ax.plot(datos3[:,0],datos3[:,1])
#plt.savefig("JPsiDecay.pdf")
#plt.show()
