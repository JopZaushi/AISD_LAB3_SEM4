#include "pch.h"
#include "CppUnitTest.h"
#include "..\AISD_LAB3_SEM4\FloydWarshallAlgorithm.h"
#include "..\AISD_LAB3_SEM4\String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFloydWarshallAlgorithm
{
	TEST_CLASS(UnitTestFloydWarshallAlgorithm)
	{
	public:

		TEST_METHOD(ROW_OF_VERTEXES)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "Petersburg;Moscow;10;20\nMoscow;Khabarovsk;40;35\nPetersburg;Khabarovsk;14;N/A\nVladivostok;Khabarovsk;13;8\nVladivostok;Petersburg;N/A;20";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			Assert::IsTrue(only_peaks[0] == 'P');
			Assert::IsTrue(only_peaks[11] == 'M');
			Assert::IsTrue(only_peaks[18] == 'K');
			Assert::IsTrue(only_peaks[29] == 'V');
			Assert::IsTrue(only_peaks[10] == ' ');
			Assert::IsTrue(only_peaks[17] == ' ');
			Assert::IsTrue(only_peaks[28] == ' ');
		}

		TEST_METHOD(SIZE)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "Petersburg;Moscow;10;20\nMoscow;Khabarovsk;40;35\nPetersburg;Khabarovsk;14;N/A\nVladivostok;Khabarovsk;13;8\nVladivostok;Petersburg;N/A;20";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			Assert::IsTrue(only_peaks[0] == 'P');
			Assert::IsTrue(only_peaks[11] == 'M');
			Assert::IsTrue(only_peaks[18] == 'K');
			Assert::IsTrue(only_peaks[29] == 'V');
			Assert::IsTrue(only_peaks[10] == ' ');
			Assert::IsTrue(only_peaks[17] == ' ');
			Assert::IsTrue(only_peaks[28] == ' ');

			Assert::IsTrue(dimension(only_peaks) == 4);
		}

		TEST_METHOD(MATRIX)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "Petersburg;Moscow;10;20\nMoscow;Khabarovsk;40;35\nPetersburg;Khabarovsk;14;N/A\nVladivostok;Khabarovsk;13;8\nVladivostok;Petersburg;N/A;20";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			int matrix_dimension = dimension(only_peaks);
			//matrix creation
			int** matrix = new int* [matrix_dimension];
			for (int i = 0; i < matrix_dimension; i++) {
				matrix[i] = new int[matrix_dimension];
			}
			matrix = initial_matrix(start_text, only_peaks);
			Assert::IsTrue(only_peaks[0] == 'P');
			Assert::IsTrue(only_peaks[11] == 'M');
			Assert::IsTrue(only_peaks[18] == 'K');
			Assert::IsTrue(only_peaks[29] == 'V');
			Assert::IsTrue(only_peaks[10] == ' ');
			Assert::IsTrue(only_peaks[17] == ' ');
			Assert::IsTrue(only_peaks[28] == ' ');

			Assert::IsTrue(dimension(only_peaks) == 4);

			Assert::IsTrue(matrix[0][0] == 0);
			Assert::IsTrue(matrix[1][1] == 0);
			Assert::IsTrue(matrix[0][2] == 14);
			Assert::IsTrue(matrix[3][2] == 13);
			Assert::IsTrue(matrix[2][3] == 8);
			Assert::IsTrue(matrix[1][0] == 20);
		}


		TEST_METHOD(FLOYD_WARSHELL_ALGORITHM)
		{
			const int buff = 512;
			char* start_text = new char[buff];
			start_text = "Petersburg;Moscow;10;20\nMoscow;Khabarovsk;40;35\nPetersburg;Khabarovsk;14;N/A\nVladivostok;Khabarovsk;13;8\nVladivostok;Petersburg;N/A;20";
			String only_peaks;
			only_peaks = string_peaks(start_text);
			int matrix_dimension = dimension(only_peaks);
			//matrix creation
			int** matrix = new int* [matrix_dimension];
			for (int i = 0; i < matrix_dimension; i++) {
				matrix[i] = new int[matrix_dimension];
			}
			matrix = initial_matrix(start_text, only_peaks);
			Assert::IsTrue(only_peaks[0] == 'P');
			Assert::IsTrue(only_peaks[11] == 'M');
			Assert::IsTrue(only_peaks[18] == 'K');
			Assert::IsTrue(only_peaks[29] == 'V');
			Assert::IsTrue(only_peaks[10] == ' ');
			Assert::IsTrue(only_peaks[17] == ' ');
			Assert::IsTrue(only_peaks[28] == ' ');

			Assert::IsTrue(dimension(only_peaks) == 4);


			for (int i = 0; i < matrix_dimension; i++) {
				for (int j = 0; j < matrix_dimension; j++) {
					for (int k = 0; k < matrix_dimension; k++) {
						if (matrix[j][i] + matrix[i][k] < matrix[j][k]) {
							matrix[j][k] = matrix[j][i] + matrix[i][k];
						}
					}
				}
			}

			Assert::IsTrue(matrix[0][0] == 0);
			Assert::IsTrue(matrix[1][1] == 0);
			Assert::IsTrue(matrix[0][2] == 14);
			Assert::IsTrue(matrix[3][2] == 13);
			Assert::IsTrue(matrix[2][3] == 8);
			Assert::IsTrue(matrix[1][0] == 20);
			Assert::IsTrue(matrix[1][2] == 34);
			Assert::IsTrue(matrix[1][3] == 40);
			Assert::IsTrue(matrix[2][0] == 55);
			Assert::IsTrue(matrix[3][0] == 68);
		}
	};
}
