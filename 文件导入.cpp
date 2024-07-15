#include<iostream>
#include<fstream>
using namespace std;

void transition()
{
	string sourcefile = "≥« –æ‡¿Î.txt";
	string destfile = "vity.txt";

	ifstream src(sourcefile, ios::binary);
	ofstream dest(destfile, ios::binary);

	dest << src.rdbuf();

	src.close();
	dest.close();

}

int main()
{
	transition();
	return 0;
}