/** @file spectra.h Documented includes for spectra module */

#ifndef __SPECTRA__
#define __SPECTRA__

#include "primordial.h"

/**
 * Structure containing everything about anisotropy and Fourier power spectra that other modules need to know.
 *
 * Once initialized by spectra_init(), contains a table of all
 * C_l's and P(k) as a function of multipole/wavenumber, 
 * mode (scalar/tensor...), type (for C_l's: TT, TE...), 
 * and pairs of initial conditions (adiabatic, isocurvatures...).
 */

struct spectra {

  /** @name - input parameters initialized by user in input module
      (all other quantitites are computed in this module, given these parameters
      and the content of the 'background', 'perturbs', 'transfers' and
      'primordial' structures) */

  //@{

  double z_max_pk;  /**< maximum value of z at which matter spectrum P(k,z) will be evaluated; keep fixed to zero if P(k) only needed today */
  
  //@}

   /** @name - information on number of modes and pairs of initial conditions */

  //@{
 
  int md_size;           /**< number of modes (scalar, tensor, ...) included in computation */

  int * ic_size;         /**< for a given mode, ic_size[index_mode] = number of initial conditions included in computation */
  int * ic_ic_size;      /**< for a given mode, ic_ic_size[index_mode] = number of pairs of (index_ic1, index_ic2) with index_ic2 >= index_ic1; this number is just N(N+1)/2  where N = ic_size[index_mode] */
  short * * is_non_zero; /**< for a given mode, is_non_zero[index_mode][index_ic1_ic2] is set to true if the pair of initial conditions (index_ic1, index_ic2) are statistically correlated, or to false if they are uncorrelated */
  
  //@}

  /** @name - information on number of type of C_l's (TT, TE...) */

  //@{

  int has_tt; /**< do we want C_l^TT ? (T = temperature) */
  int has_ee; /**< do we want C_l^EE ? (E = E-polarization) */
  int has_te; /**< do we want C_l^TE ? */
  int has_bb; /**< do we want C_l^BB ? (B = B-polarization) */
  int has_pp; /**< do we want C_l^phi-phi ? (phi = CMB lensing potential) */
  int has_tp; /**< do we want C_l^T-phi ? */
  int has_ep; /**< do we want C_l^E-phi ? */

  int index_ct_tt; /**< index for type C_l^TT */
  int index_ct_ee; /**< index for type C_l^EE */
  int index_ct_te; /**< index for type C_l^TE */
  int index_ct_bb; /**< index for type C_l^BB */
  int index_ct_pp; /**< index for type C_l^phi-phi */
  int index_ct_tp; /**< index for type C_l^T-phi */
  int index_ct_ep; /**< index for type C_l^E-phi */

  int ct_size; /**< number of C_l types requested */

  //@}

  /** @name - table of pre-computed C_l values, and related quantitites */

  //@{

  int * l_size;   /**< number of multipole values for each requested mode, l_size[index_mode] */
  int l_size_max; /**< greatest of all l_size[index_mode] */
  double * l;    /**< list of multipole values l[index_l] */

  int * l_max;    /**< last multipole (given as an input) at which we trust our C_ls;
		    l[index_mode][l_size[index_mode]-1] can be larger than l_max[index_mode], 
		    in order to ensure a better interpolation with no boundary effects */
  int l_max_tot;  /**< greatest of all l_max[index_mode] */

  double ** cl;   /**< table of anisotropy spectra for each mode, multipole, pair of initial conditions and types, cl[index_mode][(index_l * psp->ic_ic_size[index_mode] + index_ic1_ic2) * psp->ct_size + index_ct] */
  double ** ddcl; /**< second derivatives of previous table with respect to l, in view of spline interpolation */ 

  //@}

  /** @name - table of pre-computed matter power spectrum P(k) values, and related quantitites */

  //@{

  int index_md_scalars; /**< index for scalar modes (the matter power spectrum refers by construction to scalar modes) */

  int ln_k_size;    /**< number ln(k) values */
  double * ln_k;    /**< list of ln(k) values ln_k[index_k] */

  int ln_tau_size;  /**< number ln(tau) values (only one if z_max_pk = 0) */
  double * ln_tau;  /**< list of ln(tau) values ln_tau[index_tau] */

  double * ln_pk;   /**< Matter power spectrum.
		      depends on indices index_mode, index_ic1, index_ic2, index_k as:
		      ln_pk[(index_tau * psp->k_size + index_k)* psp->ic_ic_size[index_mode] + index_ic1_ic2]
		      where index_ic1_ic2 labels ordered pairs (index_ic1, index_ic2) (since 
		      the primordial spectrum is symmetric in (index_ic1, index_ic2)).
		      - for diagonal elements (index_ic1 = index_ic2) this arrays contains
		      ln[P(k)] where P(k) is positive by construction.
		      - for non-diagonal elements this arrays contains the k-dependent 
		      cosine of the correlation angle, namely
		      P(k)_(index_ic1, index_ic2)/sqrt[P(k)_index_ic1 P(k)_index_ic2]
		      This choice is convenient since the sign of the non-diagonal cross-correlation 
		      is arbitrary. For fully correlated or anti-correlated initial conditions,
		      this non-diagonal element is independent on k, and equal to +1 or -1.
		   */

  double * ddln_pk; /**< second derivative of above array with respect to log(tau), for spline interpolation. So: 
		      - for index_ic1 = index_ic, we spline ln[P(k)] vs. ln(k), which is
		      good since this function is usually smooth.
		      - for non-diagonal coefficients, we spline  
		      P(k)_(index_ic1, index_ic2)/sqrt[P(k)_index_ic1 P(k)_index_ic2]
		      vs. ln(k), which is fine since this quantity is often assumed to be
		      constant (e.g for fully correlated/anticorrelated initial conditions)
		      or nearly constant, and with arbitrary sign.
		   */
  
  double sigma8;    /**< sigma8 parameter */

  int index_tr_g;   /**< index of gamma transfer function */
  int index_tr_b;   /**< index of baryon transfer function */
  int index_tr_cdm; /**< index of cold dark matter transfer function */
  int index_tr_de;  /**< index of dark energy fluid transfer function */
  int index_tr_ur; /**< index of ultra-relativistic neutrinos/relics transfer function */
  int index_tr_ncdm1; /**< index of first species of non-cold dark matter (massive neutrinos, ...) */
  int index_tr_tot; /**< index of total matter transfer function */
  int tr_size;      /**< total number of species in transfer functions */

  double * matter_transfer;   /**< Matter transfer functions.  
	Depends on indices index_mode,index_tau,index_ic,index_k, index_tr as:
        matter_transfer[((index_tau*psp->ln_k_size + index_k) * psp->ic_size[index_mode] + index_ic) * psp->tr_size + index_tr]
		       */
  double * ddmatter_transfer; /**< second derivative of above array with respect to log(tau), for spline interpolation. */
  

  //@}

  /** @name - technical parameters */

  //@{

  short spectra_verbose; /**< flag regulating the amount of information sent to standard output (none if set to zero) */

  ErrorMsg error_message; /**< zone for writing error messages */

  //@}
};

/*************************************************************************************************************/

/*
 * Boilerplate for C++ 
 */
#ifdef __cplusplus
extern "C" {
#endif

  int spectra_cl_at_l(
		      struct spectra * psp,
		      double l,
		      double * cl,
		      double * * cl_md,
		      double * * cl_md_ic
		      );

  int spectra_pk_at_z(
		      struct background * pba,
		      struct spectra * psp,
		      enum linear_or_logarithmic mode, 
		      double z,
		      double * output_tot,
		      double * output_ic
		      );

  int spectra_pk_at_k_and_z(
			    struct background * pba,
			    struct primordial * ppm,
			    struct spectra * psp,
			    double k,
			    double z,
			    double * pk,
			    double * pk_ic
			    );

  int spectra_tk_at_z(
		      struct background * pba,
		      struct spectra * psp,
		      double z,
		      double * output
		      );

  int spectra_tk_at_k_and_z(
			    struct background * pba,
			    struct spectra * psp,
			    double k,
			    double z,
			    double * output
			    );

  int spectra_init(
		   struct precision * ppr,
		   struct background * pba,
		   struct perturbs * ppt,
		   struct transfers * ptr,
		   struct primordial * ppm,
		   struct spectra * psp
		   );

  int spectra_free(
		   struct spectra * psp
		   );

  int spectra_indices(
		      struct background * pba,
		      struct perturbs * ppt,
		      struct transfers * ptr,
		      struct primordial * ppm,
		      struct spectra * psp
		      );

  int spectra_cls(
		  struct perturbs * ppt,
		  struct transfers * ptr,
		  struct primordial * ppm,
		  struct spectra * psp
		  );

  int spectra_compute_cl(
			 struct perturbs * ppt,
			 struct transfers * ptr,
			 struct primordial * ppm,
			 struct spectra * psp,
			 int index_mode,
			 int index_ic1,
			 int index_ic2,
			 int index_l,
			 int cl_integrand_num_columns,
			 double * cl_integrand,
			 double * primordial_pk,
			 double * transfer_ic1,
			 double * transfer_ic2
			 );
  
  int spectra_k_and_tau(
			struct background * pba,
			struct perturbs * ppt,
			struct spectra * psp
			);

  int spectra_pk(
		 struct background * pba,
		 struct perturbs * ppt,
		 struct primordial * ppm,
		 struct spectra * psp
		 );
  
  int spectra_sigma(
		    struct background * pba,
		    struct primordial * ppm,
		    struct spectra * psp,
		    double R,
		    double z,
		    double *sigma 
		    );

  int spectra_matter_transfers(
			       struct background * pba,
			       struct perturbs * ppt,
			       struct spectra * psp
			       );

#ifdef __cplusplus
}
#endif

#endif
