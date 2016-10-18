#ifndef DICOMVIEWERWIDGET_H
#define DICOMVIEWERWIDGET_H

#include <QWidget>
#include "ui_DICOMViewerWidget.h"

class DICOMViewerWidget : public QWidget
{
	Q_OBJECT

public:
	DICOMViewerWidget(QWidget *parent = 0);
	~DICOMViewerWidget();

private:
	Ui::DICOMViewerWidget ui;
};

#endif // DICOMVIEWERWIDGET_H
