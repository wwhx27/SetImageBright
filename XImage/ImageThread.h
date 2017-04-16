#pragma once
#include <QThread>
class ImageThread : public QThread
{
public:
	ImageThread();
	~ImageThread();

	static void DealImage(unsigned char* pImg, unsigned int nSize, int nThreadCount, float fBright);
	static int DealPercent();
	static void Wait();

	void run();

private:
	unsigned int m_nBegin = 0;
	unsigned int m_nEnd = 0;
	unsigned int m_nCurrent = 0;
	unsigned char* m_Img = NULL;
	float m_fBright = 1.0f;
};

