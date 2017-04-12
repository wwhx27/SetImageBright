#ifndef XIMAGE_H
#define XIMAGE_H

#include <QtWidgets/QWidget>
#include "ui_ximage.h"

class XImage : public QWidget
{
	Q_OBJECT

public:
	XImage(QWidget *parent = 0);
	~XImage();

public:
	void ViewImage(QImage* img);

public slots:
	void Open();
	void Deal();

private:
	Ui::XImageClass ui;

	QImage* m_img=NULL;
	QImage m_ImgDeal;
};

#endif // XIMAGE_H
