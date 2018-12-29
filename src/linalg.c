/*
  @file qr.c
  @author Gerardo Veltri
  QR Decomposition
*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <mem.h>
#include <matrix.h>
#include <factorization.h>
#include <precision.h>

void printHelp(char message[])
{
	printf("%s\n\n", message);
	printf(
		"Commands:\n"
		"---------\n\n"
		"qrhh: QR factorization with Householder reduction\n"
		"qrgs: QR factorization with Gram-Schmidt method\n"
		"ge: Gaussian Elimination with Pivots\n\n"
		);
}

void qr(char method, int debug)
{
	MatrixStack stackNxM = allocMatrixStack(10,2,3);
	MatrixStack stackNxN = allocMatrixStack(10,10,1);

	Matrix A = popMatrixStack(stackNxM);
	Matrix QR[] = {
		popMatrixStack(stackNxN),
		popMatrixStack(stackNxM)
	};
	Matrix _A = popMatrixStack(stackNxM);

	setMatrixValues(2, 'R', A);

	printf("A=\n");
	drawMatrix(A);

	switch (method)
	{
	case 'h':
		hhReflectionsQR(A, QR, debug);
		break;
	case 'g':
		gramSchmidtQR(A, QR, debug);
		break;
	}

	printf("Q=\n");
	drawMatrix(QR[0]);
	printf("R=\n");
	drawMatrix(QR[1]);

	simpleMultiplyMatrices(QR[0], QR[1], _A);
	printf("QR=\n");
	drawMatrix(_A);

	double stats[2];
	matrixComparison(A, _A, stats);
	printf("Mean Error = %.16f\n", stats[0]);
	printf("Max Error = %.16f\n", stats[1]);

	freeMatrixStackAll(stackNxM);
	freeMatrixStackAll(stackNxN);
}

void ge(int debug)
{
	MatrixStack stack = allocMatrixStack(5,5,5);

	Matrix A = popMatrixStack(stack);
	Matrix B = popMatrixStack(stack);
	Matrix RREF[] = {
		popMatrixStack(stack),
		popMatrixStack(stack)
	};

	setMatrixValues(2, 'R', A);
	setMatrixValues(1, 'I', B);

	printf("A=\n");
	drawMatrix(A);

	printf("B=\n");
	drawMatrix(B);

	gaussianElimination(A, B, RREF, debug);

	printf("A^=\n");
	drawMatrix(RREF[0]);

	printf("B^=\n");
	drawMatrix(RREF[1]);

	Matrix C = popMatrixStack(stack);
	simpleMultiplyMatrices(A, RREF[1], C);

	printf("AA-1=\n");
	drawMatrix(C);

	double stats[2];
	identityPrecision(C, stats);
	printf("Mean Error=%.16f\n", stats[0]);
	printf("Max Error=%.16f\n", stats[1]);

	freeMatrixStackAll(stack);
}

void bs()
{
	Matrix A = allocMatrix(10,10);

	MatrixStack stack = allocMatrixStack(10,1,3);
	Matrix b = popMatrixStack(stack);
	Matrix solution = popMatrixStack(stack);
	Matrix _b = popMatrixStack(stack);

	double values[] = {
		1, 0, 5, 0, 9, 0, 3, 0, 9, 9,
		0, 3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 7, 0, 0, 9, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 4, 0, 0, 0,
		0, 0, 0, 0, 0, 8, 0, 0, 0, 2,
		0, 0, 0, 0, 0, 0, 1, 6, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 8
	};

	fillMatrix(values, A);
	double _values[] = {
		7.0, 8.0, 5.5, 9.7, 9.1, 0.8, 3.1, 0.2, 9.9, 9.0,
	};
	fillMatrix(_values, b);

	backSubstitution(A, solution, b);

	drawMatrix(A);
	drawMatrix(b);
	drawMatrix(solution);
	simpleMultiplyMatrices(A, solution, _b);
	drawMatrix(_b);
	subtractMatrix(_b, b);
	drawMatrix(_b);

	freeMatrix(A);
	freeMatrixStackAll(stack);
}

void ols()
{
	printf("filler");
}

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		printHelp("linalg must be called with a command");
		return 1;
	}

	int debug;
	if (argc < 3)
		debug = 0;
	else if (strcmp(argv[2],"-v") == 0)
		debug = 1;

	if (strcmp(argv[1], "qrhh") == 0)
	{
		qr('h', debug);
	}
	else if (strcmp(argv[1], "qrgs") == 0)
	{
		qr('g', debug);
	}
	else if (strcmp(argv[1], "ge") == 0)
	{
		ge(debug);
	}
	else if (strcmp(argv[1], "bs") == 0)
	{
		bs();
	}
	else if (strcmp(argv[1], "ols") == 0)
	{
		ols();
	}
	else
	{
		char message[100];
		strcat(message, "command not recognized: ");
		strcat(message, argv[1]);
		printHelp(message);
		return 1;
	}

	return 0;
}
