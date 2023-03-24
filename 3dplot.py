import matplotlib.pyplot as plt
import numpy as np
##
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.set_xlabel(r'$\theta$')
ax.set_ylabel(r'$\phi$')
ax.set_zlabel("Densidad de probabilidad")
datos=np.genfromtxt("datos.dat",delimiter=",",skip_header=1)
x=datos[:,0]
y=datos[:,1]
z=datos[:,2]
ax.plot_trisurf(x, y, z)
ax.view_init(25, 75)
#Se muestra la distribución porque se pierde la capacidad de rotarla al guardar.
#ERROR IMPORTANTE: LA GRÁFICA SIEMPRE SALE VACÍA. CORREGIR
plt.savefig("Distribucion.pdf")
plt.show()
plt.close()
