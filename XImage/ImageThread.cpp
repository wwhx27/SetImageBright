#include "ImageThread.h"
#include <vector>

static std::vector<ImageThread*> vecpThreads;

ImageThread::ImageThread()
{
}


ImageThread::~ImageThread()
{
}

void ImageThread::DealImage(unsigned char* pImg, unsigned int nSize, int nThreadCount, float fBright)
{
	for (int i = 0; i < vecpThreads.size(); ++i)
	{
		vecpThreads[i]->wait();
		delete vecpThreads[i];
	}
	vecpThreads.clear();

	int sizePerTh = nSize / nThreadCount;
	for (int i = 0; i < nThreadCount; ++i)
	{
		ImageThread* th = new ImageThread();
		th->m_nBegin = i * sizePerTh;
		th->m_nEnd = th->m_nBegin + sizePerTh;
		th->m_Img = pImg;
		th->m_fBright = fBright;
		if (i == nThreadCount-1)
		{
			th->m_nEnd = nSize - 1;
		}
		vecpThreads.push_back(th);
	}

	for (int i = 0; i < vecpThreads.size(); ++i)
	{
		vecpThreads[i]->start();
	}
}

int ImageThread::DealPercent()
{
	int nCur = 0;
	int nTotal = 0;
	for (int i = 0; i < vecpThreads.size(); ++i)
	{
		nCur += vecpThreads[i]->m_nCurrent - vecpThreads[i]->m_nBegin;
		nTotal += vecpThreads[i]->m_nEnd - vecpThreads[i]->m_nBegin;
	}
	if (nTotal == 0)
	{
		return 0;
	}
	
	return nCur / nTotal * 100;
}

void ImageThread::Wait()
{
	for (int i = 0; i < vecpThreads.size(); ++i)
	{
		vecpThreads[i]->wait();
	}
}

void ImageThread::run()
{
	if (!m_Img)
	{
		return;
	}
	if (m_nBegin<0 || m_nEnd<=0 || m_nEnd-m_nBegin<=0)
	{
		return;
	}

	for (int i = m_nBegin; i <= m_nEnd; ++i)
	{
		int B = m_Img[i * 4] * m_fBright;
		int G = m_Img[i * 4 + 1] * m_fBright;
		int R = m_Img[i * 4 + 2] * m_fBright;
		if (B > 255)
		{
			B = 255;
		}
		if (G > 255)
		{
			G = 255;
		}
		if (R > 255)
		{
			R = 255;
		}
		m_Img[i * 4] = B;
		m_Img[i * 4 + 1] = G; 
		m_Img[i * 4 + 2] = R;
		m_nCurrent = i;
	}
}
