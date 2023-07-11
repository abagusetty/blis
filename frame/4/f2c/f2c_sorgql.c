/* f2c_sorgql.f -- translated by f2c (version 20100827). You must link the resulting object file with libf2c: on Microsoft Windows system, link with libf2c.lib;
 on Linux or Unix systems, link with .../path/to/libf2c.a -lm or, if you install libf2c.a in a standard place, with -lf2c -lm -- in that order, at the end of the command line, as in cc *.o -lf2c -lm Source for libf2c is in /netlib/f2c/libf2c.zip, e.g., http://www.netlib.org/f2c/libf2c.zip */
 #include "blis.h" /* Table of constant values */
 static bla_integer c__1 = 1;
 static bla_integer c_n1 = -1;
 static bla_integer c__3 = 3;
 static bla_integer c__2 = 2;
 /* > \brief \b SORGQL */
 /* =========== DOCUMENTATION =========== */
 /* Online html documentation available at */
 /* http://www.netlib.org/lapack/explore-html/ */
 /* > \htmlonly */
 /* > Download SORGQL + dependencies */
 /* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.tgz?format=tgz&filename=/lapack/lapack_routine/sorgql. f"> */
 /* > [TGZ]</a> */
 /* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.zip?format=zip&filename=/lapack/lapack_routine/sorgql. f"> */
 /* > [ZIP]</a> */
 /* > <a href="http://www.netlib.org/cgi-bin/netlibfiles.txt?format=txt&filename=/lapack/lapack_routine/sorgql. f"> */
 /* > [TXT]</a> */
 /* > \endhtmlonly */
 /* Definition: */
 /* =========== */
 /* SUBROUTINE SORGQL( M, N, K, A, LDA, TAU, WORK, LWORK, INFO ) */
 /* .. Scalar Arguments .. */
 /* INTEGER INFO, K, LDA, LWORK, M, N */
 /* .. */
 /* .. Array Arguments .. */
 /* REAL A( LDA, * ), TAU( * ), WORK( * ) */
 /* .. */
 /* > \par Purpose: */
 /* ============= */
 /* > */
 /* > \verbatim */
 /* > */
 /* > SORGQL generates an M-by-N bla_real matrix Q with orthonormal columns, */
 /* > which is defined as the last N columns of a product of K elementary */
 /* > reflectors of order M */
 /* > */
 /* > Q = H(k) . . . H(2) H(1) */
 /* > */
 /* > as returned by SGEQLF. */
 /* > \endverbatim */
 /* Arguments: */
 /* ========== */
 /* > \param[in] M */
 /* > \verbatim */
 /* > M is INTEGER */
 /* > The number of rows of the matrix Q. M >= 0. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] N */
 /* > \verbatim */
 /* > N is INTEGER */
 /* > The number of columns of the matrix Q. M >= N >= 0. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] K */
 /* > \verbatim */
 /* > K is INTEGER */
 /* > The number of elementary reflectors whose product defines the */
 /* > matrix Q. N >= K >= 0. */
 /* > \endverbatim */
 /* > */
 /* > \param[in,out] A */
 /* > \verbatim */
 /* > A is REAL array, dimension (LDA,N) */
 /* > On entry, the (n-k+i)-th column must contain the vector which */
 /* > defines the elementary reflector H(i), for i = 1,2,...,k, as */
 /* > returned by SGEQLF in the last k columns of its array */
 /* > argument A. */
 /* > On exit, the M-by-N matrix Q. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] LDA */
 /* > \verbatim */
 /* > LDA is INTEGER */
 /* > The first dimension of the array A. LDA >= bla_a_max(1,M). */
 /* > \endverbatim */
 /* > */
 /* > \param[in] TAU */
 /* > \verbatim */
 /* > TAU is REAL array, dimension (K) */
 /* > TAU(i) must contain the scalar factor of the elementary */
 /* > reflector H(i), as returned by SGEQLF. */
 /* > \endverbatim */
 /* > */
 /* > \param[out] WORK */
 /* > \verbatim */
 /* > WORK is REAL array, dimension (MAX(1,LWORK)) */
 /* > On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */
 /* > \endverbatim */
 /* > */
 /* > \param[in] LWORK */
 /* > \verbatim */
 /* > LWORK is INTEGER */
 /* > The dimension of the array WORK. LWORK >= bla_a_max(1,N). */
 /* > For optimum performance LWORK >= N*NB, where NB is the */
 /* > optimal blocksize. */
 /* > */
 /* > If LWORK = -1, then a workspace query is assumed;
 the routine */
 /* > only calculates the optimal size of the WORK array, returns */
 /* > this value as the first entry of the WORK array, and no error */
 /* > message related to LWORK is issued by XERBLA. */
 /* > \endverbatim */
 /* > */
 /* > \param[out] INFO */
 /* > \verbatim */
 /* > INFO is INTEGER */
 /* > = 0: successful exit */
 /* > < 0: if INFO = -i, the i-th argument has an illegal value */
 /* > \endverbatim */
 /* Authors: */
 /* ======== */
 /* > \author Univ. of Tennessee */
 /* > \author Univ. of California Berkeley */
 /* > \author Univ. of Colorado Denver */
 /* > \author NAG Ltd. */
 /* > \ingroup realOTHERcomputational */
 /* ===================================================================== */
 int f2c_sorgql_(bla_integer *m, bla_integer *n, bla_integer *k, bla_real *a, bla_integer *lda, bla_real *tau, bla_real *work, bla_integer *lwork, bla_integer *info) {
 /* System generated locals */
 bla_integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
 /* Local variables */
 bla_integer i__, j, l, ib, nb, kk, nx, iws, nbmin, iinfo;
 bla_integer ldwork, lwkopt;
 bla_logical lquery;
 /* -- LAPACK computational routine -- */
 /* -- LAPACK is a software package provided by Univ. of Tennessee, -- */
 /* -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */
 /* .. Scalar Arguments .. */
 /* .. */
 /* .. Array Arguments .. */
 /* .. */
 /* ===================================================================== */
 /* .. Parameters .. */
 /* .. */
 /* .. Local Scalars .. */
 /* .. */
 /* .. External Subroutines .. */
 /* .. */
 /* .. Intrinsic Functions .. */
 /* .. */
 /* .. External Functions .. */
 /* .. */
 /* .. Executable Statements .. */
 /* Test the input arguments */
 /* Parameter adjustments */
 a_dim1 = *lda;
 a_offset = 1 + a_dim1;
 a -= a_offset;
 --tau;
 --work;
 /* Function Body */
 *info = 0;
 lquery = *lwork == -1;
 if (*m < 0) {
 *info = -1;
 }
 else if (*n < 0 || *n > *m) {
 *info = -2;
 }
 else if (*k < 0 || *k > *n) {
 *info = -3;
 }
 else if (*lda < bla_a_max(1,*m)) {
 *info = -5;
 }
 if (*info == 0) {
 if (*n == 0) {
 lwkopt = 1;
 }
 else {
 nb = f2c_ilaenv_(&c__1, "SORGQL", " ", m, n, k, &c_n1, (ftnlen)6, (ftnlen)1);
 lwkopt = *n * nb;
 }
 work[1] = (bla_real) lwkopt;
 if (*lwork < bla_a_max(1,*n) && ! lquery) {
 *info = -8;
 }
 }
 if (*info != 0) {
 i__1 = -(*info);
 bla_xerbla_("SORGQL", &i__1, (ftnlen)6);
 return 0;
 }
 else if (lquery) {
 return 0;
 }
 /* Quick return if possible */
 if (*n <= 0) {
 return 0;
 }
 nbmin = 2;
 nx = 0;
 iws = *n;
 if (nb > 1 && nb < *k) {
 /* Determine when to cross over from blocked to unblocked code. */
 /* Computing MAX */
 i__1 = 0, i__2 = f2c_ilaenv_(&c__3, "SORGQL", " ", m, n, k, &c_n1, (ftnlen)6, (ftnlen)1);
 nx = bla_a_max(i__1,i__2);
 if (nx < *k) {
 /* Determine if workspace is large enough for blocked code. */
 ldwork = *n;
 iws = ldwork * nb;
 if (*lwork < iws) {
 /* Not enough workspace to use optimal NB: reduce NB and */
 /* determine the minimum value of NB. */
 nb = *lwork / ldwork;
 /* Computing MAX */
 i__1 = 2, i__2 = f2c_ilaenv_(&c__2, "SORGQL", " ", m, n, k, &c_n1, (ftnlen)6, (ftnlen)1);
 nbmin = bla_a_max(i__1,i__2);
 }
 }
 }
 if (nb >= nbmin && nb < *k && nx < *k) {
 /* Use blocked code after the first block. */
 /* The last kk columns are handled by the block method. */
 /* Computing MIN */
 i__1 = *k, i__2 = (*k - nx + nb - 1) / nb * nb;
 kk = bla_a_min(i__1,i__2);
 /* Set A(m-kk+1:m,1:n-kk) to zero. */
 i__1 = *n - kk;
 for (j = 1;
 j <= i__1;
 ++j) {
 i__2 = *m;
 for (i__ = *m - kk + 1;
 i__ <= i__2;
 ++i__) {
 a[i__ + j * a_dim1] = 0.f;
 /* L10: */
 }
 /* L20: */
 }
 }
 else {
 kk = 0;
 }
 /* Use unblocked code for the first or only block. */
 i__1 = *m - kk;
 i__2 = *n - kk;
 i__3 = *k - kk;
 f2c_sorg2l_(&i__1, &i__2, &i__3, &a[a_offset], lda, &tau[1], &work[1], &iinfo) ;
 if (kk > 0) {
 /* Use blocked code */
 i__1 = *k;
 i__2 = nb;
 for (i__ = *k - kk + 1;
 i__2 < 0 ? i__ >= i__1 : i__ <= i__1;
 i__ += i__2) {
 /* Computing MIN */
 i__3 = nb, i__4 = *k - i__ + 1;
 ib = bla_a_min(i__3,i__4);
 if (*n - *k + i__ > 1) {
 /* Form the triangular factor of the block reflector */
 /* H = H(i+ib-1) . . . H(i+1) H(i) */
 i__3 = *m - *k + i__ + ib - 1;
 f2c_slarft_("Backward", "Columnwise", &i__3, &ib, &a[(*n - *k + i__) * a_dim1 + 1], lda, &tau[i__], &work[1], &ldwork, (ftnlen)8, (ftnlen)10);
 /* Apply H to A(1:m-k+i+ib-1,1:n-k+i-1) from the left */
 i__3 = *m - *k + i__ + ib - 1;
 i__4 = *n - *k + i__ - 1;
 f2c_slarfb_("Left", "No transpose", "Backward", "Columnwise", & i__3, &i__4, &ib, &a[(*n - *k + i__) * a_dim1 + 1], lda, &work[1], &ldwork, &a[a_offset], lda, &work[ib + 1], &ldwork, (ftnlen)4, (ftnlen)12, (ftnlen)8, (ftnlen)10);
 }
 /* Apply H to rows 1:m-k+i+ib-1 of current block */
 i__3 = *m - *k + i__ + ib - 1;
 f2c_sorg2l_(&i__3, &ib, &ib, &a[(*n - *k + i__) * a_dim1 + 1], lda, & tau[i__], &work[1], &iinfo);
 /* Set rows m-k+i+ib:m of current block to zero */
 i__3 = *n - *k + i__ + ib - 1;
 for (j = *n - *k + i__;
 j <= i__3;
 ++j) {
 i__4 = *m;
 for (l = *m - *k + i__ + ib;
 l <= i__4;
 ++l) {
 a[l + j * a_dim1] = 0.f;
 /* L30: */
 }
 /* L40: */
 }
 /* L50: */
 }
 }
 work[1] = (bla_real) iws;
 return 0;
 /* End of SORGQL */
 }
 /* f2c_sorgql_ */
 
