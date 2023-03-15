#include "Matrix.h"

int main() {
	std::string	filename1;
	std::string	filename2;
	std::string	filename3;
	std::string	filename4;
	std::string	filename5;
	std::string	filename6;
	std::string	filename7;
	std::string	filename8;
	std::string	filename9;
	std::string	filename10;
	std::string	filename11;
	std::string	filename12;

	filename1 = "TestMatrices/Test1A.txt";
	filename2 = "TestMatrices/Test1B.txt";
	filename3 = "TestMatrices/Test2A.txt";
	filename4 = "TestMatrices/Test2B.txt";
	filename5 = "TestMatrices/Test3A.txt";
	filename6 = "TestMatrices/Test3B.txt";
	filename7 = "TestMatrices/Test4A.txt";
	filename8 = "TestMatrices/Test4B.txt";
	filename9 = "TestMatrices/Test5A.txt";
	filename10 = "TestMatrices/Test5B.txt";
	filename11 = "TestMatrices/Test6A.txt";
	filename12 = "TestMatrices/Test6B.txt";

	Matrix	test1A(filename1);
	Matrix	test1B(filename2);
	Matrix	test2A(filename3);
	Matrix	test2B(filename4);
	Matrix	test3A(filename5);
	Matrix	test3B(filename6);
	Matrix	test4A(filename7);
	Matrix	test4B(filename8);
	Matrix	test5A(filename9);
	Matrix	test5B(filename10);
	Matrix	test6A(filename11);
	Matrix	test6B(filename12);

	std::cout << "\033[1;32mFirst Matrix solution\033[0m" << std::endl << test1A.solve(test1B);
	std::cout << "\033[1;32mFirst inverse Matrix\033[0m"  << std::endl << test1A.inverseMatrix();
	std::cout << "\033[1;32mSecond Matrix solution\033[0m" << std::endl << test2A.solve(test2B);
	std::cout << "\033[1;32mSecond inverse Matrix\033[0m"  << std::endl << test2A.inverseMatrix();
	std::cout << "\033[1;32mThird Matrix solution\033[0m" << std::endl << test3A.solve(test3B);
	std::cout << "\033[1;32mThird inverse Matrix\033[0m"  << std::endl << test3A.inverseMatrix();
	std::cout << "\033[1;32mFourth Matrix solution\033[0m" << std::endl << test4A.solve(test4B);
	std::cout << "\033[1;32mFourth inverse Matrix\033[0m"  << std::endl << test4A.inverseMatrix();
	std::cout << "\033[1;32mFifth Matrix solution\033[0m" << std::endl << test5A.solve(test5B);
	std::cout << "\033[1;32mFifth inverse Matrix\033[0m"  << std::endl << test5A.inverseMatrix();
	std::cout << "\033[1;32mSixth Matrix solution\033[0m" << std::endl << test6A.solve(test6B);
	std::cout << "\033[1;32mSixth inverse Matrix\033[0m"  << std::endl << test6A.inverseMatrix();

	return 0;
}
