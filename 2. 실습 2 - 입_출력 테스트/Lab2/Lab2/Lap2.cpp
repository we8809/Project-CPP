#include "Lab2.h"
#include <cstring>
#include <iomanip>

using namespace std;

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		const int TEMP_LENGTH = 65536;

		int input;
		char* tempString = new char[TEMP_LENGTH];
		memset((void*)tempString, 0, sizeof(tempString));

		out << uppercase << right;
		out << setfill(' ') << setw(12) << "oct" << setw(11) << "dec" << setw(10) << "hex\n";
		out << setfill('-') << setw(13) << " " << setw(11) << " " << setw(9) << "\n";

		while (!in.eof())
		{
			in >> input;

			if (in.fail())
			{
				// 문자열을 받았을 시 tempString에 집어넣는 작업. => 우선적으로 fail bit 를 클리어하여 입력을 받게 한다!
				in.clear();
				in >> tempString;

				continue;
			}
			else
			{
				out << oct << setfill(' ') << setw(12) << right << input << " ";
				out << dec << setw(10) << right << input << " ";
				out << hex << setw(8) << right << input << "\n";
			}
		}

		delete[] tempString;
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		const int FLOAT_BUF_LENGTH = 65536;
		const int TEMP_LENGTH = 65536;

		int index = 0;
		float input;

		float maxFloat = 0.0;
		float* floatBuf = new float[FLOAT_BUF_LENGTH];
		char* tempString = new char[TEMP_LENGTH];

		memset((void*)floatBuf, 0, sizeof(floatBuf));
		memset((void*)tempString, 0, sizeof(tempString));

		/* 소수점 셋째 자리까지만 출력하고 싶다! => <fixed + setprecision(3)> 설정 ! */
		/* showpoint = 정수를 입력받더라도 소수점으로 첫째자리까지 0을 표현해준다. */
		/* showpos = 부호를 표시하여 출력 */
		out << setfill(' ') << showpoint << showpos << fixed << setprecision(3);
		
		while (!in.eof())
		{
			in >> input;

			if (in.fail())
			{
				in.clear();
				in >> tempString;

				continue;
			}
			else
			{
				out << setw(5) << left << " ";
				out << internal << setw(15) << input << "\n";
				
				if (index >= FLOAT_BUF_LENGTH)
					index = 0;

				floatBuf[index++] = input;
			}
		}



		if (index == 1)
		{
			maxFloat = floatBuf[0];
		}
		else
		{
			maxFloat = floatBuf[0];

			for (int i = 1; i <= index; i++)
			{
				if (maxFloat < floatBuf[i])
					maxFloat = floatBuf[i];
			}
		}

		out << setw(5) << left << "max:";
		out << internal << setw(15) << maxFloat << "\n";

		delete[] floatBuf;
		delete[] tempString;
	}
}