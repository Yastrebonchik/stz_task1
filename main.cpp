#include "Matrix.h"

int main() {
	std::string	filename1;
	std::string	filename2;
	std::string	filename3;
	std::string	filename4;
	std::string	filename5;
	std::string	filename6;

	filename1 = "Test1.txt";
	filename2 = "Test2.txt";
	filename3 = "Test3.txt";
	filename4 = "Test4.txt";
	filename5 = "Test5.txt";
	filename6 = "Test6.txt";

	Matrix	test1(filename1);
	Matrix	test2(filename2);
	Matrix	test3(filename3);
	Matrix	test4(filename4);
	Matrix	test5(filename5);
	Matrix	test6(filename6);

	test1.solve();
	test2.solve();
	test3.solve();
	test4.solve();
	test5.solve();
	test6.solve();

	return 0;
}
