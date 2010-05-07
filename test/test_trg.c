/** @file test_trg.c 
 * 
 */
 
#include "precision.h"
#include "background.h"
#include "thermodynamics.h"
#include "perturbations.h"
#include "bessel.h"
#include "transfer.h"
#include "primordial.h"
#include "spectra.h"
#include "output.h"
#include "trg.h"

main() {

  struct precision pr;        /* for precision parameters */
  struct background ba;       /* for cosmological background */
  struct thermo th;           /* for thermodynamics */
  struct perturbs pt;         /* for source functions */
  struct bessels bs;          /* for bessel functions */
  struct transfers tr;        /* for transfer functions */
  struct primordial pm;       /* for primordial spectra */
  struct output op;
  struct spectra sp;          /* for output spectra */
  struct spectra_nl nl; 
 
  if (precision_init(&pr) == _FAILURE_) {
    printf("\n\nError running precision_init \n=>%s\n",pr.error_message); 
    return _FAILURE_;
  }

  if (input_init(&ba,&th,&pt,&bs,&tr,&pm,&sp,&op) == _FAILURE_) {
    printf("\n\nError running input_init"); 
    return _FAILURE_;
  }

  pr.k_scalar_kmax_for_pk=10.;
  pr.k_scalar_k_per_decade_for_pk=10.;

  pt.has_cl_cmb_temperature = _FALSE_;
  pt.has_cl_cmb_polarization = _FALSE_;
  pt.has_cl_cmb_lensing_potential = _FALSE_;
  pt.has_pk_matter = _TRUE_;

  sp.z_max_pk = 100.;

  if (background_init(&pr,&ba) == _FAILURE_) {
    printf("\n\nError running background_init \n=>%s\n",ba.error_message);
    return _FAILURE_;
  }

  if (thermodynamics_init(&ba,&pr,&th) == _FAILURE_) {
    printf("\n\nError in thermodynamics_init \n=>%s\n",th.error_message);
    return _FAILURE_;
  }

  if (perturb_init(&ba,&th,&pr,&pt) == _FAILURE_) {
    printf("\n\nError in perturb_init \n=>%s\n",pt.error_message);
    return _FAILURE_;
  }

  if (bessel_init(&ba,&pt,&pr,&bs) == _FAILURE_) {
    printf("\n\nError in bessel_init \n =>%s\n",bs.error_message);
    return _FAILURE_;
  }

  if (transfer_init(&ba,&th,&pt,&bs,&pr,&tr) == _FAILURE_) {
    printf("\n\nError in transfer_init \n=>%s\n",tr.error_message);
    return _FAILURE_;
  }

  if (primordial_init(&pr,&pt,&pm) == _FAILURE_) {
    printf("\n\nError in transfer_init \n=>%s\n",pm.error_message);
    return _FAILURE_;
  }

  if (spectra_init(&ba,&pt,&tr,&pm,&sp) == _FAILURE_) {
    printf("\n\nError in spectra_init \n=>%s\n",sp.error_message);
    return _FAILURE_;
  }

  if (trg_init(&pr,&ba,&pm,&sp,&nl) == _FAILURE_) {
    printf("\n\nError in trg_init \n=>%s\n",nl.error_message);
    return _FAILURE_;
  }

  /****** done ******/

  if (spectra_free(&sp) == _FAILURE_) {
    printf("\n\nError in spectra_free \n=>%s\n",sp.error_message);
    return _FAILURE_;
  }

  if (primordial_free(&pm) == _FAILURE_) {
    printf("\n\nError in primordial_free \n=>%s\n",pm.error_message);
    return _FAILURE_;
  }

  if (transfer_free() == _FAILURE_) {
    printf("\n\nError in transfer_free \n=>%s\n",tr.error_message);
    return _FAILURE_;
  }

  if (bessel_free() == _FAILURE_)  {
    printf("\n\nError in bessel_free \n=>%s\n",bs.error_message);
    return _FAILURE_;
  }

  if (perturb_free() == _FAILURE_) {
    printf("\n\nError in perturb_free \n=>%s\n",pt.error_message);
    return _FAILURE_;
  }

  if (thermodynamics_free() == _FAILURE_) {
    printf("\n\nError in thermodynamics_free \n=>%s\n",th.error_message);
    return _FAILURE_;
  }

  if (background_free() == _FAILURE_) {
    printf("\n\nError in background_free \n=>%s\n",ba.error_message);
    return _FAILURE_;
  }

  if (trg_free() == _FAILURE_) {
    printf("\n\nError in trg_free \n=>%s\n",nl.error_message);
    return _FAILURE_;
  }

}
