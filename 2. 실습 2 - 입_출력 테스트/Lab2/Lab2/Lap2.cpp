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
				// ���ڿ��� �޾��� �� tempString�� ����ִ� �۾�. => �켱������ fail bit �� Ŭ�����Ͽ� �Է��� �ް� �Ѵ�!
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

		/* �Ҽ��� ��° �ڸ������� ����ϰ� �ʹ�! => <fixed + setprecision(3)> ���� ! */
		/* showpoint = ������ �Է¹޴��� �Ҽ������� ù°�ڸ����� 0�� ǥ�����ش�. */
		/* showpos = ��ȣ�� ǥ���Ͽ� ��� */
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