#include "ximage.h"
#include <QFileDialog>

XImage::XImage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

XImage::~XImage()
{

}

void XImage::Open()
{
	QString strFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit(""));
	if (strFileName.isEmpty())
	{
		return;
	}
	if (!m_img)
	{
		delete m_img;
		m_img = NULL;
	}
	m_img = new QImage(strFileName);
	if (!m_img)
	{
		return;
	}

	ViewImage(m_img);

}

void XImage::Deal()
{
	float fBright = (float)ui.bright->value() / 100;
	if (!m_img)
	{
		return;
	}
	m_ImgDeal = m_img->copy();
	unsigned char* pData = m_ImgDeal.bits();
	int nPixCount = m_img->width() * m_img->height();
	for (int i = 0; i < nPixCount; ++i)
	{
		int B = pData[i * 4] * fBright;
		int G = pData[i * 4 + 1] * fBright;
		int R = pData[i * 4 + 2] * fBright;
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
		pData[i * 4] = B;
		pData[i * 4 + 1] = G;
		pData[i * 4 + 2] = R;
	}

	ViewImage(&m_ImgDeal);
}

void XImage::ViewImage(QImage* img)
{
	QImage simg;
	if (img->width() > img->height())
	{
		simg = img->scaledToWidth(ui.view->width());
	}
	else
	{
		simg = img->scaledToHeight(ui.view->height());
	}
	ui.view->setPixmap(QPixmap::fromImage(simg));
}
