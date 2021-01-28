#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

const int DEFAULT_M = 3;
const int DEFAULT_N = 3;

template <typename T>
T** Matrix_Creator(int size);

template <typename T>
void fillMat(T** arr);

template <typename T>
void printMat(T** arr);

template <typename T>
T** transpose(T** arr);

template <typename T>
T** minor(T** arr, int m, int n);

template <typename T>
T determinant(T** arr, int size);

template <typename T>
T cofactor(T** arr, int m, int n);

template <typename T>
T** cofactor_matrix(T** arr);

template <typename T>
T trace(T** arr);

template <typename T>
T** adjoint(T** arr);

template <typename T>
T** inverse(T** arr);


/*** Work in Progress ***/
template <typename T>
T** rowEchelon(T** arr);

template <typename T>
T** rref(T** arr);

int main() {

	double** one;
	one = new double* [DEFAULT_M];
	for (int i = 0; i < DEFAULT_M; i++)
		one[i] = new double[DEFAULT_N];
	
	fillMat(one);

	cout << "\n";
	cout << "Matrix: " << endl;
	printMat(one);

	cout << "\n";
	cout << "Creating a transposed matrix: " << endl;
	printMat(transpose(one));

	cout << "\n";
	cout << "Determinant: " << determinant(one, 3) << endl;
	cout << "Trace: " << trace(one) << endl;

	cout << "\n";
	cout << "Cofactor Matrix: " << endl;
	printMat(cofactor_matrix(one));

	cout << "\n";
	cout << "Adjoint: " << endl;
	printMat(adjoint(one));

	cout << "\n";
	cout << "Inverse: " << endl;
	printMat(inverse(one));

}

template <typename T>
T** Matrix_Creator(int size) { // Used for dynamically allocating space for matrices
	T** newMat = new T * [size];
	for (int i = 0; i < DEFAULT_M; i++) {
		newMat[i] = new T[DEFAULT_N];
	}
}

template <typename T>
void fillMat(T** arr)
{
	for (int i = 0; i < DEFAULT_N; i++) {
		for (int j = 0; j < DEFAULT_M; j++) {
			cout << "Fill in the matrix at [" << i << "][" << j << "]: ";
			cin >> arr[i][j];
		}
	}
}

template <typename T>
void printMat(T** arr)
{
	for (int i = 0; i < DEFAULT_N; i++) {
		for (int j = 0; j < DEFAULT_M; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}

template <typename T>
T** transpose(T** arr) {

	T** transposed = new T * [DEFAULT_M];
	for (int i = 0; i < DEFAULT_M; i++) {
		transposed[i] = new T[DEFAULT_N];
	}

	for (int i = 0; i < DEFAULT_M; i++) {
		for (int j = 0; j < DEFAULT_M; j++) {
			transposed[i][j] = arr[j][i];
		}
	}

	return transposed;
}

template <typename T>
T** minor(T** arr, int m, int n)
{
	T** minor_mat = new T * [DEFAULT_M - 1];
	for (int i = 0; i < DEFAULT_M - 1; i++) {
		minor_mat[i] = new T[DEFAULT_N - 1];
	}

	if ((m == 0 || m == 2) && (n == 0 || n == 2)) { // Covers [0][0], [0][2], [2][0], [2][2]
		minor_mat[0][0] = arr[(m + 1) % 3][(n + 1) % 3];
		minor_mat[0][1] = arr[(m + 1) % 3][(n + 2) % 3];
		minor_mat[1][0] = arr[(m + 2) % 3][(n + 1) % 3];
		minor_mat[1][1] = arr[(m + 2) % 3][(n + 2) % 3];
		return minor_mat;
	}

	else if (m == 1 && (n == 0 || n == 2)) {  // Covers [1][0], and [1][2]
		minor_mat[0][0] = arr[(m + 2) % 3][(n + 1) % 3];
		minor_mat[0][1] = arr[(m + 2) % 3][(n + 2) % 3];
		minor_mat[1][0] = arr[(m + 1) % 3][(n + 1) % 3];
		minor_mat[1][1] = arr[(m + 1) % 3][(n + 2) % 3];
		return minor_mat;
	}


	else if ((m == 0 || m == 2) && n == 1) { // Covers [0][1] and [2][1]
		minor_mat[0][0] = arr[(m + 1) % 3][(n + 2) % 3];
		minor_mat[0][1] = arr[(m + 1) % 3][(n + 1) % 3];
		minor_mat[1][0] = arr[(m + 2) % 3][(n + 2) % 3];
		minor_mat[1][1] = arr[(m + 2) % 3][(n + 1) % 3];
		return minor_mat;
	}

	else { // Covers [1][1]
		minor_mat[0][0] = arr[(m + 2) % 3][(n + 2) % 3];
		minor_mat[0][1] = arr[(m + 2) % 3][(n + 1) % 3];
		minor_mat[1][0] = arr[(m + 1) % 3][(n + 2) % 3];
		minor_mat[1][1] = arr[(m + 1) % 3][(n + 1) % 3];
		return minor_mat;
	}
}
// Method found thanks to m4ster r0shi and manasij7479 on cplusplus.com/forum/beginner/25439/ 

template <typename T>
T determinant(T** arr, int size)
{
	T det = 0;

	if (size == 2) {
		det = (arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1]);
		return det;
	}

	else {
		for (int i = 0; i < DEFAULT_M; i++) {
			if (i % 2 != 0) {
				det -= (arr[0][i] * cofactor(arr, 0, i));
			}
			else {
				det += (arr[0][i] * cofactor(arr, 0, i));
			}
		}
	}
	return det;
}

template <typename T>
T cofactor(T** arr, int m, int n)
{
	return determinant(minor(arr, m, n), DEFAULT_M - 1);
}

template <typename T>
T** cofactor_matrix(T** arr) {

	// Creating the cofactor matrix
	T** cofactor_mat = new T * [DEFAULT_M];
	for (int i = 0; i < DEFAULT_M; i++) {
		cofactor_mat[i] = new T[DEFAULT_N];
	}

	for (int i = 0; i < DEFAULT_N; i++) {
		for (int j = 0; j < DEFAULT_M; j++)
			cofactor_mat[i][j] = pow(-1, i + j) * determinant(minor(arr, i, j), DEFAULT_M - 1);
	}
	return cofactor_mat;
}

template <typename T>
T trace(T** arr)
{
	T trace = 0;
	for (int i = 0; i < DEFAULT_M; i++)
	{
		trace += arr[i][i];
	}
	return trace;
}

template <typename T>
T** adjoint(T** arr) {
	return transpose(cofactor_matrix(arr));
}

template <typename T>
T** inverse(T** arr) {
	if (determinant(arr, 3) == 0) {
		cout << "Matrix does not have inverse. Returning original array. " << endl;
		return arr;
	}

	else {
		T** inverse = new T * [DEFAULT_M];
		for (int i = 0; i < DEFAULT_M; i++)
			inverse[i] = new T[DEFAULT_N];

		for (int i = 0; i < DEFAULT_N; i++) {
			for (int j = 0; j < DEFAULT_M; j++) {
				inverse[i][j] = adjoint(arr)[i][j] * (1 / determinant(arr, 3));
			}
		}
		return inverse;
	}
}

/*** Work in Progress ***/
template <typename T>
T** rowEchelon(T** arr) {}

template <typename T>
T** rref(T** arr) {}
