#ifndef __MATRIX_H
#define __MATRIX_H
#include <math.h>

/*
  Program: matrix.H
  Author:  D. Trinkle
  Date:    Sept. 27, 2002
  Purpose: Define a series of matrix manipulations, all inlined, for
           3 x 3 matrices.  Designed to allow matrix manipulation
	   on integer and double matrices, using a 9-vector notation.

	   The nine vector index is defined as (i,j) -> (i*3 + j), or:

	   | 0 1 2 |
	   | 3 4 5 |
	   | 6 7 8 |

	   We first define some conversion utilities to take a matrix
	   M into it's 9-v notation, and also a quick indexing
	   function index(i,j) that produces the correct index, so
	   that v[index(i,j)] gives the correct member of the matrix.

	   We define: determinant, inverse (after dividing by the
	   determinant, which is returned), matrix multiplication,
	   matrix "squaring" (aT a), matrix comparison, rotation,
	   eigenvalues, and eigenvectors.
*/

#include "dcomp.H"


// Convert between 3 x 3 matrix notation to 9 vector notation:
// We do all of our calculations, etc., in 9-v notation.
inline void MtoV (int m[3][3], int v[9]) 
{
  v[0] = m[0][0];  v[1] = m[0][1];  v[2] = m[0][2];
  v[3] = m[1][0];  v[4] = m[1][1];  v[5] = m[1][2];
  v[6] = m[2][0];  v[7] = m[2][1];  v[8] = m[2][2];
}

inline void VtoM (int v[9], int m[3][3])
{
  m[0][0] = v[0];  m[0][1] = v[1];  m[0][2] = v[2];
  m[1][0] = v[3];  m[1][1] = v[4];  m[1][2] = v[5];
  m[2][0] = v[6];  m[2][1] = v[7];  m[2][2] = v[8];
}

inline void MtoV (double m[3][3], double v[9]) 
{
  v[0] = m[0][0];  v[1] = m[0][1];  v[2] = m[0][2];
  v[3] = m[1][0];  v[4] = m[1][1];  v[5] = m[1][2];
  v[6] = m[2][0];  v[7] = m[2][1];  v[8] = m[2][2];
}

inline void VtoM (double v[9], double m[3][3])
{
  m[0][0] = v[0];  m[0][1] = v[1];  m[0][2] = v[2];
  m[1][0] = v[3];  m[1][1] = v[4];  m[1][2] = v[5];
  m[2][0] = v[6];  m[2][1] = v[7];  m[2][2] = v[8];
}

// Quick calculation to return the correct index in the 9-v
inline int index (int i, int j) 
{
  return 3*i + j;
}


// **** Matrix manipulation, all done in 9-v notation

// DET: Returns the det. of an integer matrix
inline int det (int x[9]) 
{
  return (x[0]*(x[4]*x[8] - x[5]*x[7])
    + x[1]*(x[6]*x[5] - x[3]*x[8])
    + x[2]*(x[3]*x[7] - x[6]*x[4]));
}

inline double det (double x[9]) 
{
  return (x[0]*(x[4]*x[8] - x[5]*x[7])
    + x[1]*(x[6]*x[5] - x[3]*x[8])
    + x[2]*(x[3]*x[7] - x[6]*x[4]));
}


// Rotate vectors in a matrix:
inline void rotate (double a[9], double a_rot[9], int rot)
{
  int i;
  for (i=0; i<9; ++i)
    a_rot[i] = a[index(i/3,((i%3)+rot)%3)];
}

inline void rotate (int a[9], int a_rot[9], int rot)
{
  int i;
  for (i=0; i<9; ++i)
    a_rot[i] = a[index(i/3,((i%3)+rot)%3)];
}


// Transpose of a matrix:
inline void transpose (int a[9], int b[9])
{
  int i;
  for (i=0; i<9; ++i)
    b[i] = a[index(i%3, i/3)];
}

inline void transpose (double a[9], double b[9])
{
  int i;
  for (i=0; i<9; ++i)
    b[i] = a[index(i%3, i/3)];
}



// INVERSE: Evaluates inverse of x; returns it in inv / inverse (return value
// is det x).  Need to divide by det to get correct inverse.
inline int inverse (int x[9], int inv[9])
{
  inv[0] = x[4]*x[8] - x[5]*x[7];
  inv[1] = x[2]*x[7] - x[1]*x[8];
  inv[2] = x[1]*x[5] - x[2]*x[4];

  inv[3] = x[5]*x[6] - x[3]*x[8];
  inv[4] = x[0]*x[8] - x[2]*x[6];
  inv[5] = x[2]*x[3] - x[0]*x[5];

  inv[6] = x[3]*x[7] - x[4]*x[6];
  inv[7] = x[1]*x[6] - x[0]*x[7];
  inv[8] = x[0]*x[4] - x[1]*x[3];
  
  return det(x);
}

inline double inverse (double x[9], double inv[9])
{
  inv[0] = x[4]*x[8] - x[5]*x[7];
  inv[1] = x[2]*x[7] - x[1]*x[8];
  inv[2] = x[1]*x[5] - x[2]*x[4];

  inv[3] = x[5]*x[6] - x[3]*x[8];
  inv[4] = x[0]*x[8] - x[2]*x[6];
  inv[5] = x[2]*x[3] - x[0]*x[5];

  inv[6] = x[3]*x[7] - x[4]*x[6];
  inv[7] = x[1]*x[6] - x[0]*x[7];
  inv[8] = x[0]*x[4] - x[1]*x[3];
  
  return det(x);
}


// MULT: evaluates the product of a * b, returns in c:
inline void mult (int a[9], int b[9], int c[9]) 
{
  c[0] = a[0]*b[0] + a[1]*b[3] + a[2]*b[6];
  c[1] = a[0]*b[1] + a[1]*b[4] + a[2]*b[7];
  c[2] = a[0]*b[2] + a[1]*b[5] + a[2]*b[8];
  c[3] = a[3]*b[0] + a[4]*b[3] + a[5]*b[6];
  c[4] = a[3]*b[1] + a[4]*b[4] + a[5]*b[7];
  c[5] = a[3]*b[2] + a[4]*b[5] + a[5]*b[8];
  c[6] = a[6]*b[0] + a[7]*b[3] + a[8]*b[6];
  c[7] = a[6]*b[1] + a[7]*b[4] + a[8]*b[7];
  c[8] = a[6]*b[2] + a[7]*b[5] + a[8]*b[8];
}

inline void mult (double a[9], int b[9], double c[9]) 
{
  c[0] = a[0]*b[0] + a[1]*b[3] + a[2]*b[6];
  c[1] = a[0]*b[1] + a[1]*b[4] + a[2]*b[7];
  c[2] = a[0]*b[2] + a[1]*b[5] + a[2]*b[8];
  c[3] = a[3]*b[0] + a[4]*b[3] + a[5]*b[6];
  c[4] = a[3]*b[1] + a[4]*b[4] + a[5]*b[7];
  c[5] = a[3]*b[2] + a[4]*b[5] + a[5]*b[8];
  c[6] = a[6]*b[0] + a[7]*b[3] + a[8]*b[6];
  c[7] = a[6]*b[1] + a[7]*b[4] + a[8]*b[7];
  c[8] = a[6]*b[2] + a[7]*b[5] + a[8]*b[8];
}

inline void mult (int a[9], double b[9], double c[9]) 
{
  c[0] = a[0]*b[0] + a[1]*b[3] + a[2]*b[6];
  c[1] = a[0]*b[1] + a[1]*b[4] + a[2]*b[7];
  c[2] = a[0]*b[2] + a[1]*b[5] + a[2]*b[8];
  c[3] = a[3]*b[0] + a[4]*b[3] + a[5]*b[6];
  c[4] = a[3]*b[1] + a[4]*b[4] + a[5]*b[7];
  c[5] = a[3]*b[2] + a[4]*b[5] + a[5]*b[8];
  c[6] = a[6]*b[0] + a[7]*b[3] + a[8]*b[6];
  c[7] = a[6]*b[1] + a[7]*b[4] + a[8]*b[7];
  c[8] = a[6]*b[2] + a[7]*b[5] + a[8]*b[8];
}

inline void mult (double a[9], double b[9], double c[9]) 
{
  c[0] = a[0]*b[0] + a[1]*b[3] + a[2]*b[6];
  c[1] = a[0]*b[1] + a[1]*b[4] + a[2]*b[7];
  c[2] = a[0]*b[2] + a[1]*b[5] + a[2]*b[8];
  c[3] = a[3]*b[0] + a[4]*b[3] + a[5]*b[6];
  c[4] = a[3]*b[1] + a[4]*b[4] + a[5]*b[7];
  c[5] = a[3]*b[2] + a[4]*b[5] + a[5]*b[8];
  c[6] = a[6]*b[0] + a[7]*b[3] + a[8]*b[6];
  c[7] = a[6]*b[1] + a[7]*b[4] + a[8]*b[7];
  c[8] = a[6]*b[2] + a[7]*b[5] + a[8]*b[8];
}


// MULT_VECT: Multiplies vector b by matrix a, result in c
inline void mult_vect (int a[9], int b[3], int c[3]) 
{
  c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  c[1] = a[3]*b[0] + a[4]*b[1] + a[5]*b[2];
  c[2] = a[6]*b[0] + a[7]*b[1] + a[8]*b[2];
}

inline void mult_vect (double a[9], int b[3], double c[3]) 
{
  c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  c[1] = a[3]*b[0] + a[4]*b[1] + a[5]*b[2];
  c[2] = a[6]*b[0] + a[7]*b[1] + a[8]*b[2];
}

inline void mult_vect (int a[9], double b[3], double c[3]) 
{
  c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  c[1] = a[3]*b[0] + a[4]*b[1] + a[5]*b[2];
  c[2] = a[6]*b[0] + a[7]*b[1] + a[8]*b[2];
}

inline void mult_vect (double a[9], double b[3], double c[3]) 
{
  c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  c[1] = a[3]*b[0] + a[4]*b[1] + a[5]*b[2];
  c[2] = a[6]*b[0] + a[7]*b[1] + a[8]*b[2];
}


// MULT_VECT_MATRIX_VECT: Takes the inner product v1.a.v2

inline double innerprod (double v1[3], double a[9], double v2[3]) 
{
  return ( v1[0]*a[0]*v2[0] + v1[0]*a[1]*v2[1] + v1[0]*a[2]*v2[2] +
	   v1[1]*a[3]*v2[0] + v1[1]*a[4]*v2[1] + v1[1]*a[5]*v2[2] +
	   v1[2]*a[6]*v2[0] + v1[2]*a[7]*v2[1] + v1[2]*a[8]*v2[2] );
}


// MULT_SCALAR: Multiplies matrix a by scalar b, result in c
inline void mult (int a[9], int b, int c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (int b, int a[9], int c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (int a[9], double b, double c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (double b, int a[9], double c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (double a[9], int b, double c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (int b, double a[9], double c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (double a[9], double b, double c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }

inline void mult (double b, double a[9], double c[9]) 
{ for (int i=0; i<9; ++i) c[i] = b*a[i]; }


// SQUARE: Calculate xT * x
//   Note: the product is symmetric, so we get to do a smaller number
//   of multiplications.

inline void square (int x[9], int s[9]) 
{
  s[0] = x[0]*x[0] + x[3]*x[3] + x[6]*x[6];
  s[1] = x[0]*x[1] + x[3]*x[4] + x[6]*x[7];
  s[2] = x[0]*x[2] + x[3]*x[5] + x[6]*x[8];
  s[3] = s[1];
  s[4] = x[1]*x[1] + x[4]*x[4] + x[7]*x[7];
  s[5] = x[1]*x[2] + x[4]*x[5] + x[7]*x[8];
  s[6] = s[2];
  s[7] = s[5];
  s[8] = x[2]*x[2] + x[5]*x[5] + x[8]*x[8];
}

inline void square (double x[9], double s[9]) 
{
  s[0] = x[0]*x[0] + x[3]*x[3] + x[6]*x[6];
  s[1] = x[0]*x[1] + x[3]*x[4] + x[6]*x[7];
  s[2] = x[0]*x[2] + x[3]*x[5] + x[6]*x[8];
  s[3] = s[1];
  s[4] = x[1]*x[1] + x[4]*x[4] + x[7]*x[7];
  s[5] = x[1]*x[2] + x[4]*x[5] + x[7]*x[8];
  s[6] = s[2];
  s[7] = s[5];
  s[8] = x[2]*x[2] + x[5]*x[5] + x[8]*x[8];
}


// ********************************* magnsq ****************************
// Returns the squared magnitude of a vector, where metric[9] is the
// SYMMETRIC metric, and u is the vector in direct coordinates
inline double magnsq (double metric[9], double u[3]) 
{
  return metric[0]*u[0]*u[0] + metric[4]*u[1]*u[1] + metric[8]*u[2]*u[2]
    + 2*metric[1]*u[0]*u[1] + 2*metric[2]*u[0]*u[2] + 2*metric[5]*u[1]*u[2];
}

inline double magnsq (int metric[9], double u[3]) 
{
  return metric[0]*u[0]*u[0] + metric[4]*u[1]*u[1] + metric[8]*u[2]*u[2]
    + 2*metric[1]*u[0]*u[1] + 2*metric[2]*u[0]*u[2] + 2*metric[5]*u[1]*u[2];
}

inline double magnsq (double metric[9], int u[3]) 
{
  return metric[0]*u[0]*u[0] + metric[4]*u[1]*u[1] + metric[8]*u[2]*u[2]
    + 2*metric[1]*u[0]*u[1] + 2*metric[2]*u[0]*u[2] + 2*metric[5]*u[1]*u[2];
}

inline int magnsq (int metric[9], int u[3]) 
{
  return metric[0]*u[0]*u[0] + metric[4]*u[1]*u[1] + metric[8]*u[2]*u[2]
    + 2*metric[1]*u[0]*u[1] + 2*metric[2]*u[0]*u[2] + 2*metric[5]*u[1]*u[2];
}


// EQUAL: determine if two matrices are equal
inline int equal (int a[9], int b[9]) 
{
  return (a[0]==b[0]) && (a[1]==b[1]) &&(a[2]==b[2]) &&
    (a[3]==b[3]) && (a[4]==b[4]) && (a[5]==b[5]) &&
    (a[6]==b[6]) && (a[7]==b[7]) && (a[8]==b[8]);
}

inline int equal (double a[9], double b[9]) 
{
  return dcomp(a[0], b[0]) && dcomp(a[1], b[1]) && dcomp(a[2], b[2]) &&
    dcomp(a[3], b[3]) && dcomp(a[4], b[4]) && dcomp(a[5], b[5]) &&
    dcomp(a[6], b[6]) && dcomp(a[7], b[7]) && dcomp(a[8], b[8]);
}


// EIGEN: Calculate the eigenvalues of a symmetric matrix.
//        We only do this for double matrices.
// Calculates the eigenvalues by solving directly the third order
// characteristic equation.  It assumes that D is symmetric.

// Cube root of x>0.
inline double cube (double x)
{
  return exp(log(x)/3.);
}

void eigen(double D[9], double* lambda)
{
  double q, p, r;     // coeffecients of char. eqn
  double a, b;        // shifted coeff.
  double a0, b0;      // A = cube(a0 + i*b0), B = cube(a0 - i*b0)
  double theta, magn; // a0+i*b0 = magn*exp(i theta)
  double ApB, AmB;    // A+B, A-B
  
  // This follows the method of solution outlined in CRC 16th ed., p. 93
  // Our equation is written:
  // lambda^3 + p*lambda^2 + q*lambda + r = 0

  p = -(D[0]+D[4]+D[8]);  // -Tr D

  q = D[0]*D[4] + D[0]*D[8] + D[4]*D[8]
    - D[1]*D[1] - D[2]*D[2] - D[5]*D[5];

  r = D[0]*D[5]*D[5] + D[4]*D[2]*D[2] + D[8]*D[1]*D[1]
    - D[0]*D[4]*D[8] - 2*D[1]*D[2]*D[5];  // -det D

  // We then perform a shift: lambda = x - p/3
  // x^3 + a*x + b = 0
  a = q - p*p/3.;
  b = 2.*p*p*p/27. - p*q/3. + r;

  a0 = -0.5*b;
  b0 = -(0.25*b*b + a*a*a/27.);
  if (b0 < -1e-10) {
    // cerr << "Something is wrong...";
    lambda[0] = 0.;
    lambda[1] = 0.;
    lambda[2] = 0.;
    return;
  }
  if (b0 > 0)
    b0 = sqrt(b0);
  else
    b0 = sqrt(fabs(b0));
  
  // magn*exp(i theta) = a0 + i*b0 = A^3; a0 - i*b0 = B^3.
  theta = atan2(b0, a0);
  magn = sqrt(a0*a0 + b0*b0);

  // ABp = A+B, ABm = A-B (without the i)
  if (magn > 1e-24) {
    ApB = 2*cos(theta/3.)*cube(magn);
    AmB = 2*sin(theta/3.)*cube(magn);
  }
  else {
    ApB = 0.;
    AmB = 0.;
  }
  // x1 = A+B -> lambda = x1 - p/3
  lambda[0] = ApB - p/3.;
  // x2 = -(A+B)/2 + sqrt(3/4)*(A-B)
  lambda[1] = -0.5*ApB + sqrt(0.75)*AmB - p/3.;
  // x3 = -(A+B)/2 - sqrt(3/4)*(A-B)
  lambda[2] = -0.5*ApB - sqrt(0.75)*AmB - p/3.;

  // Sort list from least to greatest:
  // This is a bizarre, sneaky piece of code, but it will work.
  int t;
  t = 0;
  if (lambda[0] < lambda[1])
    t += 4;
  if (lambda[1] < lambda[2])
    t += 2;
  if (lambda[0] < lambda[2])
    t += 1;
  
  switch (t) {
  case 0:
    // (210) -> (012)
    // Swap 0 & 2: a=c, c=a
    p=lambda[0]; lambda[0]=lambda[2]; lambda[2]=p;
    break;
  case 2:
    // (201) -> (012)
    // Rotate: a=b, b=c, c=a
    p=lambda[0]; lambda[0]=lambda[1]; lambda[1]=lambda[2]; lambda[2]=p;
    break;
  case 3: 
    // (102) -> (012)
    // Swap 0 & 1: a=b, b=a
    p=lambda[0]; lambda[0]=lambda[1]; lambda[1]=p;
    break;
  case 4: 
    // (120) -> (012)
    // Rotate: a=c, c=b, b=a
    p=lambda[0]; lambda[0]=lambda[2]; lambda[2]=lambda[1]; lambda[1]=p;
    break;
  case 5: 
    // (021) -> (012)
    // Swap 1 & 2: b=c, c=b
    p=lambda[1]; lambda[1]=lambda[2]; lambda[2]=p;
    break;
  default: ;
    // (012) -> (012)
    // Do nothing (also case 7)
  }
  return;
}


// Determine the corresponding eigenvector for a given eigenvalue.
// We assume:
//   (a) D is symmetric
//   (b) lambda is an eigenvalue
// The results of this procedure are not defined for
// lambda outside the eigenvalue set.
//
// Additionally, we assume that our eigenvalue lambda is unique;
// I'm not really sure what this procedure will do for a value
// of lambda which is degenerate.

void eigenvect(double D[9], double lambda, double vect[3]) 
{
  double a, c;
  double sqrta, sqrtc;
  int signb, signab;
  double D22minusl;
  double magn;
  
  D22minusl = D[8] - lambda;
  // If D22minusl = 0, we do a different solution:
  if (dcomp(D22minusl, 0.)) {
    a = D[2]*D[5];
    vect[0] = a - D[5]*D[5];
    vect[1] = a - D[2]*D[2];
    vect[2] = D[5]*(D[1] - D[0] + lambda) + D[2]*(D[1] - D[4] + lambda);
  }
  else {
    // Our normal solution
    a = D[2]*D[2] - (D[0]-lambda)*D22minusl;
    c = D[5]*D[5] - (D[4]-lambda)*D22minusl;
    // b = D[2]*D[5] - D[1]*(D[8] - lambda), so sign(b) =
    if ((D[2]*D[5]) > (D[1]*D22minusl))
      signb = 1;
    else
      signb = -1;
    // Now, we need to know sign(a) * sign(b)
    // Also, go ahead and calc. our sqrt's.
    if (dcomp(a, 0.)) {
      sqrta = 0.;
      if (c > 0) sqrtc = sqrt(c); else sqrtc = sqrt(-c);
      signab = 0;
    }
    else {
      if (a > 0.) {
	signab = signb;
	// This is for safety:
	sqrta = sqrt(a);
	if (dcomp(c, 0.)) sqrtc = 0.; else sqrtc = sqrt(c);
      }
      else {
	signab = -signb;
	// This is for safety:
	sqrta = sqrt(-a);
	if (dcomp(c, 0.)) sqrtc = 0.; else sqrtc = sqrt(-c);
      }
    }
    vect[0] = D22minusl * sqrtc;
    // Now the two sign dependent terms:
    if (signab == 1) {
      vect[1] = -sqrta*D22minusl;
      vect[2] = -(D[2]*sqrtc - D[5]*sqrta);
    }
    else {
      vect[1] = sqrta*D22minusl;
      vect[2] = -(D[2]*sqrtc + D[5]*sqrta);
    }
  }
  
  // Now, normalize it:
  magn = sqrt(vect[0]*vect[0] + vect[1]*vect[1] + vect[2]*vect[2]);
  if (dcomp(magn, 0.)) {
    vect[2] = 1.;
  }
  else {
    magn = 1./magn;
    vect[0] *= magn;
    vect[1] *= magn;
    vect[2] *= magn;
  }
}
#endif
