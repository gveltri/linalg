# Linalg

Linalg is a lightweight numeric linear algebra CLI written in C. The core data structure of the library is the Matrix struct, which contains an array of doubles and size of the matrix, n and m.

mem.h
```
typedef struct _Matrix_ {

    int n; /* rows */
    int m; /* columns */

    double *values;

} *Matrix;
```

## High-level API

### Factorization

* gramSchmidtQR: A = QR

Decomposes an NxM matrix into an orthogonal Matrix, Q, and upper triangular matrix, R, using the Gram Schmidt process.

* hhReflectionsQR: A = QR

Decomposes an NxM matrix into an orthogonal Matrix, Q, and upper triangular matrix, R, using Householder reflections.

* luDecomposition: A = LU

Decomposes an NxM matrix into a lower matrix, L, and upper triangular matrix, U.


* gaussianElimination: Ax = (B|b)

Solve a system of linear equations by adding scalar multiples of rows to eliminate all values from square matrix A except the identity while applying the same operations to matrix or column vector B. If the identity is provided as B, its reduced row echelon form is the inverse of A.

* backSubstitution: Ax = b

Solves a system of linear equations for where A is an upper triangular matrix. backSubstition will exit in the case of a contradiction.


### Estimation

* ordinaryLeastSquares: Ax = b

Approximates the best fit values for x in an overdetermined system of linear equations.

* linearRegression: Ax = b

Appends a column of ones to A before calling ordinaryLeastSquares.

### Eigenvalue

*in development*
* eigenvalueQR: Av = λv


## Build and Use

To compile for your operating system:
```
cd linalg/
make
```

For demonstration purposes, the cli may be called with verbose flag:

```
bin/linalg ols -v
```

will demonstrate ordinary least squares.