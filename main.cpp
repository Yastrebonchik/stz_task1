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

	filename1 = "Test1.txt";
	filename2 = "Test2.txt";
	filename3 = "Test3.txt";
	filename4 = "Test4.txt";
	filename5 = "Test5.txt";
	filename6 = "Test6.txt";
	filename7 = "TestMultiply1";
	filename8 = "TestMultiply2";
	filename9 = "Test7";

	Matrix	test1(filename1);
	Matrix	test2(filename2);
	Matrix	test3(filename3);
	Matrix	test4(filename4);
	Matrix	test5(filename5);
	Matrix	test6(filename6);
	Matrix	m1(filename7);
	Matrix	inversem1;
	Matrix	m2(filename8);
	Matrix	ret;
	std::pair<Matrix, Matrix>	LU;

	std::cout << "First Matrix solution" << std::endl << test1.solve();
	std::cout << "Second Matrix solution" << std::endl << test2.solve();
	std::cout << "Third Matrix solution" << std::endl << test3.solve();
	std::cout << "Fourth Matrix solution" << std::endl << test4.solve();
	std::cout << "Fifth Matrix solution" << std::endl << test5.solve();
	std::cout << "Sixth Matrix solution" << std::endl << test6.solve();

	std::cout << "--------------------------------------------" << std::endl;
	//test6.LU();
	Matrix	test7(filename9);

	std::cout << "--------------------------------------------" << std::endl;
	std::cout << m1 << "--------------------\n" << m2;
	std::cout << "Multiply result----------------" << std::endl;
	ret = m1 * m2;
	std::cout << ret;
//	std::cout << "-----------------------Matrix L" << std::endl;
//	LU = test7.LU();
//	std::cout << LU.first;
//	std::cout << "-----------------------Matrix Y" << std::endl;
//	std::cout << LU.second;
//	std::cout << "-----------------------Matrix entered" << std::endl;
//	std::cout << LU.first * LU.second;
	std::cout << "Matrix inverse-----------------------" << std::endl;
	inversem1 = test7.inverseMatrix();
	std::cout << inversem1;


	return 0;
}
