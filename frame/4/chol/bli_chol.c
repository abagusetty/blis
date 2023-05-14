/*

   BLIS
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2022, The University of Texas at Austin
   Copyright (C) 2022, Oracle Labs, Oracle Corporation

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name(s) of the copyright holder(s) nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"

#ifdef BLIS_ENABLE_LEVEL4

err_t bli_chol
     (
       const obj_t*  a
     )
{
	return bli_chol_ex( a, NULL, NULL );
}

err_t bli_chol_ex
     (
       const obj_t*  a,
       const cntx_t* cntx,
             rntm_t* rntm
     )
{
	bli_init_once();

	obj_t a_local;

	if ( bli_error_checking_is_enabled() )
		bli_chol_check( a, cntx );

	// If necessary, obtain a valid context from the gks using the induced
	// method id determined above.
	if ( cntx == NULL ) cntx = bli_gks_query_cntx();

	// Initialize a local runtime with global settings if necessary. Note
	// that in the case that a runtime is passed in, we make a local copy.
	rntm_t rntm_l;
	if ( rntm == NULL ) { bli_rntm_init_from_global( &rntm_l ); rntm = &rntm_l; }
	else                { rntm_l = *rntm;                       rntm = &rntm_l; }

	// Alias matrix A in case we need to apply any transformations.
	bli_obj_alias_to( a, &a_local );

	// Set the obj_t buffer field to the location currently implied by the row
	// and column offsets and then zero the offsets. If the original obj_t was
	// a view into a larger matrix, this step effectively makes that obj_t
	// "forget" its lineage.
	bli_obj_reset_origin( &a_local );

	// Clear the tansposition and conjugation bits since they are not honored
	// by this operation.
	bli_obj_set_conjtrans( BLIS_NO_TRANSPOSE, &a_local );

	const uplo_t uploa = bli_obj_uplo( &a_local );

	// Create a control tree for the uplo encoded in A.
	cntl_t* cntl = bli_chol_cntl_create( uploa, rntm );

	// Pass the control tree into the internal back-end.
	err_t r_val = bli_chol_int( &a_local, cntx, rntm, cntl );

	// Free the control tree.
	bli_chol_cntl_free( rntm, cntl, NULL );

	return r_val;
}

#endif