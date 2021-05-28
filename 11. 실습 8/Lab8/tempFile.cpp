template <size_t N>
bool FixedVector<bool, N>::Remove(bool findData)
{
	bool chkFlag = false;
	size_t findIdx = 0;
	size_t bitIdx = 0;

	if (findData != false)
	{
		for (size_t i = 0; i < (mCount / 32 + 1); i++)
		{
			for (size_t j = 0; j < mCount - ((mCount / 32 + 1) * 32); j++)
			{
				if ((mVector[i] & (findData << j)) == (findData << j))
				{
					chkFlag = true;
					findIdx = i;
					bitIdx = j;

					break;
				}
			}
		}
	}
	else
	{
		int tempFalse = 0;

		for (size_t i = 0; i < (mCount / 32 + 1); i++)
		{
			tempFalse = ~mVector[i];

			for (size_t j = 0; j < mCount - ((mCount / 32 + 1) * 32); j++)
			{
				if ((tempFalse & (1 << j)) == (1 << j))
				{
					chkFlag = true;
					findIdx = i;
					bitIdx = j;

					break;
				}
			}
		}
	}

	if (chkFlag != false)
	{
		if (findData != false)
		{
			int temp = 0;
			for (size_t i = bitIdx; i < 32; i++)
			{
				temp |= (1 << i);
			}

			mVector[findIdx] >>= 1;
			mVector[findIdx] &= temp;

			if ((mCount / 32 + 1) > (findIdx + 1))
			{
				for (size_t i = (findIdx + 1); i < (mCount / 32 + 1); i++)
				{
					mVector[i] >>= 1;

				}
			}

			mCount--;
		}
		else
		{
			int temp = 0;
			for (size_t i = bitIdx; i < 32; i++)
			{
				temp |= (mVector[findIdx] & (1 << i));
			}
			temp >>= 1;

			mVector[findIdx] &= ~(1 << (mCount - 1));
			mVector[findIdx] |= temp;

			if ((mCount / 32 + 1) > (findIdx + 1))
			{
				for (size_t i = (findIdx + 1); i < (mCount / 32 + 1); i++)
				{
					mVector[i] >>= 1;

				}
			}

			mCount--;
		}

		return true;
	}
	else
	{
		return false;
	}
}