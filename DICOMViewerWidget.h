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
	void LoadDICOM();
private:
	Ui::DICOMViewerWidget ui;
	void BuildViewWidget();
	vtkSmartPointer<vtkRenderWindow> m_AxialRenderWin;
	vtkSmartPointer<vtkRenderer> m_AxialRenderer;
	vtkSmartPointer<vtkInteractorStyleImage> m_AxialStyle;
	vtkSmartPointer<vtkRenderWindowInteractor> m_AxialInteractor;

	vtkSmartPointer<vtkRenderWindow> m_CoronalRenderWin;
	vtkSmartPointer<vtkRenderer> m_CoronalRenderer;
	vtkSmartPointer<vtkInteractorStyleImage> m_CoronalStyle;
	vtkSmartPointer<vtkRenderWindowInteractor> m_CoronalInteractor;

	vtkSmartPointer<vtkRenderWindow> m_SagitalRenderWin;
	vtkSmartPointer<vtkRenderer> m_SagitalRenderer;
	vtkSmartPointer<vtkInteractorStyleImage> m_SagitalStyle;
	vtkSmartPointer<vtkRenderWindowInteractor> m_SagitalInteractor;

	vtkSmartPointer<vtkImageData> m_ImageData;

	vtkSmartPointer<vtkImageViewer2> m_AxialViewer;
	vtkSmartPointer<vtkImageViewer2> m_CoronalViewer;
	vtkSmartPointer<vtkImageViewer2> m_SagitalViewer;
	double m_Spacing[3];
	int m_Extend[6];
};

#endif // DICOMVIEWERWIDGET_H
