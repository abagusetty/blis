/*

   BLISPP
   C++ test driver for BLIS CPP herk routine and reference blis herk routine.

   Copyright (C) 2019, Advanced Micro Devices, Inc.

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
#include <complex>
#include <iostream>
#include "blis.hh"
#include "test.hh"

using namespace blis;
using namespace std;
//#define PRINT
#define ALPHA 1.0
#define BETA 0.0
#define N 6
#define K 6

/*
 * Test application assumes matrices to be column major, non-transposed
 */
template< typename T >
void ref_herk(int64_t n, int64_t k,
    real_type<T> * alpha,
    T *A,
    real_type<T> * beta,
    T *C )

{
   obj_t obj_a,obj_c;
   obj_t obj_alpha, obj_beta;
   num_t dt;

     if(is_same<T, complex<float>>::value)
         dt = BLIS_SCOMPLEX;
     else if(is_same<T, complex<double>>::value)
         dt = BLIS_DCOMPLEX;

   if(dt == BLIS_SCOMPLEX){
     bli_obj_create_with_attached_buffer( BLIS_FLOAT, 1, 1, alpha, 1,1,&obj_alpha );
     bli_obj_create_with_attached_buffer( BLIS_FLOAT, 1, 1, beta,  1,1,&obj_beta );
   }
   else if(dt == BLIS_DCOMPLEX){
     bli_obj_create_with_attached_buffer( BLIS_DOUBLE, 1, 1, alpha, 1,1,&obj_alpha );
     bli_obj_create_with_attached_buffer( BLIS_DOUBLE, 1, 1, beta,  1,1,&obj_beta );
   }

   bli_obj_create_with_attached_buffer( dt, n, k, A, 1,n,&obj_a );
   bli_obj_create_with_attached_buffer( dt, n, n, C, 1,n,&obj_c );

   bli_obj_set_struc( BLIS_HERMITIAN, &obj_c );
   bli_obj_set_uplo( BLIS_LOWER, &obj_c );
   bli_obj_set_conjtrans( BLIS_NO_TRANSPOSE, &obj_c );
   bli_herk( &obj_alpha,
             &obj_a,
             &obj_beta,
             &obj_c );
	
}
template< typename T >
void test_herk(  )
{
    T *A, *C, *C_ref;
   real_type<T> alpha;
   real_type<T> beta;
   int n,k;
   int    lda, ldc, ldc_ref;

    alpha = ALPHA; 
    beta = BETA;
    k = K;
    n = N;


    lda = k;
    ldc     = n;
    ldc_ref = n;
    srand (time(NULL));
    allocate_init_buffer(A , n , k);
    allocate_init_buffer(C , n , n);
    copy_buffer(C, C_ref , n ,n);

#ifdef PRINT
    printmatrix(A, lda ,n,k, (char *)"A");
    printmatrix(C, ldc ,n,n, (char *)"C");
#endif
	blis::herk(
	    CblasColMajor,
	    CblasLower,
	    CblasNoTrans,
            n,
            k,
	    alpha,
            A,
            lda,
            beta,
            C,
            ldc
            );

#ifdef PRINT
    printmatrix(C, ldc ,n,n, (char *)"C output");
#endif
   ref_herk(n, k, &alpha, A, &beta, C_ref);

#ifdef PRINT
    printmatrix(C_ref, ldc_ref ,n,n, (char *)"C ref output");
#endif
    if(computeErrorM(ldc, ldc_ref, n, n, C, C_ref )==1)
	    printf("%s TEST FAIL\n" ,__PRETTY_FUNCTION__);
    else
	    printf("%s TEST PASS\n" , __PRETTY_FUNCTION__);



    delete[]( A     );
    delete[]( C     );
    delete[]( C_ref );
}

// -----------------------------------------------------------------------------
int main( int argc, char** argv )
{
    test_herk<complex<float>>( );
    test_herk<complex<double>>( );
    return 0;

}
