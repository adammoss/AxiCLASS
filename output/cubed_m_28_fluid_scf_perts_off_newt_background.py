import matplotlib.pyplot as plt
import numpy as np
import itertools

files = ['/home/charlotte/class_perso-ScalarField/class_perso-ScalarField/output/cubed_m_28_fluid_scf_perts_off_newt_background.dat', '/home/charlotte/class_perso-ScalarField/class_perso-ScalarField/output/cubed_m_28_kg_scf_perts_off_newtbackground.dat']
data = []
for data_file in files:
    data.append(np.loadtxt(data_file))
roots = ['cubed_m_28_fluid_scf_perts_off_newt_background', 'cubed_m_28_kg_scf_perts_off_newtbackground']

fig, ax = plt.subplots()

index, curve = 0, data[0]
y_axis = [u'rho_scf', u'rho_cdm', u'rho_g']
tex_names = [u'(8\\pi G/3)rho_g', u'(8\\pi G/3)rho_cdm', u'(8\\pi G/3)rho_scf']
x_axis = 'z'
ylim = []
xlim = []
ax.loglog(curve[:, 0], abs(curve[:, 14]))
ax.loglog(curve[:, 0], abs(curve[:, 10]))
ax.loglog(curve[:, 0], abs(curve[:, 8]))

index, curve = 1, data[1]
y_axis = [u'rho_scf', u'rho_cdm', u'rho_g']
tex_names = [u'(8\\pi G/3)rho_g', u'(8\\pi G/3)rho_cdm', u'(8\\pi G/3)rho_scf']
x_axis = 'z'
ylim = []
xlim = []
ax.loglog(curve[:, 0], abs(curve[:, 14]))
ax.loglog(curve[:, 0], abs(curve[:, 10]))
ax.loglog(curve[:, 0], abs(curve[:, 8]))

ax.legend([root+': '+elem for (root, elem) in
    itertools.product(roots, y_axis)], loc='best')

ax.set_xlabel('z', fontsize=16)
plt.show()