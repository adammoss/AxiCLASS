import matplotlib.pyplot as plt
import numpy as np
import itertools

files = ['/home/charlotte/class_perso-ScalarField/class_perso-ScalarField/output/cubed_m_28_fluid_scf_perts_oncl.dat', '/home/charlotte/class_perso-ScalarField/class_perso-ScalarField/output/cubed_m_28_fluid_scf_perts_offcl.dat', '/home/charlotte/class_perso-ScalarField/class_perso-ScalarField/output/cubed_m_28_kg_scf_perts_offcl.dat']
data = []
for data_file in files:
    data.append(np.loadtxt(data_file))
roots = ['cubed_m_28_fluid_scf_perts_oncl', 'cubed_m_28_fluid_scf_perts_offcl', 'cubed_m_28_kg_scf_perts_offcl']

fig, ax = plt.subplots()

index, curve = 0, data[0]
y_axis = [u'TT']
tex_names = ['TT']
x_axis = 'l'
ylim = []
xlim = []
ax.semilogx(curve[:, 0], curve[:, 1])

index, curve = 1, data[1]
y_axis = [u'TT']
tex_names = ['TT']
x_axis = 'l'
ylim = []
xlim = []
ax.semilogx(curve[:, 0], curve[:, 1])

index, curve = 2, data[2]
y_axis = [u'TT']
tex_names = ['TT']
x_axis = 'l'
ylim = []
xlim = []
ax.semilogx(curve[:, 0], curve[:, 1])

ax.legend([root+': '+elem for (root, elem) in
    itertools.product(roots, y_axis)], loc='best')

ax.set_xlabel('$\ell$', fontsize=16)
plt.show()