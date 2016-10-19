#include "stdafx.h"
#include "DICOMViewerWidget.h"

DICOMViewerWidget::DICOMViewerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->BuildViewWidget();
}

DICOMViewerWidget::~DICOMViewerWidget()
{

}

void DICOMViewerWidget::BuildViewWidget()
{

	m_AxialRenderWin = vtkSmartPointer<vtkRenderWindow>::New();;
	m_AxialRenderer=vtkSmartPointer<vtkRenderer>::New() ;
	m_AxialStyle=vtkSmartPointer<vtkInteractorStyleImage>::New() ;
	m_AxialInteractor=vtkSmartPointer<vtkRenderWindowInteractor>::New() ;
	
	m_AxialRenderWin->AddRenderer(m_AxialRenderer);
	m_AxialInteractor->SetInteractorStyle(m_AxialStyle);
	m_AxialRenderWin->SetInteractor(m_AxialInteractor);
	ui.AxialWidget->SetRenderWindow(m_AxialRenderWin);
	m_AxialInteractor->Initialize();

	m_CoronalRenderWin=vtkSmartPointer<vtkRenderWindow>::New() ;
	m_CoronalRenderer=vtkSmartPointer<vtkRenderer>::New() ;
	m_CoronalStyle=vtkSmartPointer<vtkInteractorStyleImage>::New() ;
	m_CoronalInteractor=vtkSmartPointer<vtkRenderWindowInteractor>::New() ;

	m_CoronalRenderWin->AddRenderer(m_CoronalRenderer);
	m_CoronalInteractor->SetInteractorStyle(m_CoronalStyle);
	m_CoronalRenderWin->SetInteractor(m_CoronalInteractor);
	ui.CoronalWidget->SetRenderWindow(m_CoronalRenderWin);
	m_CoronalInteractor->Initialize();

	m_SagitalRenderWin=vtkSmartPointer<vtkRenderWindow>::New() ;
	m_SagitalRenderer=vtkSmartPointer<vtkRenderer>::New() ;
	 m_SagitalStyle=vtkSmartPointer<vtkInteractorStyleImage>::New();
	m_SagitalInteractor=vtkSmartPointer<vtkRenderWindowInteractor>::New() ;

	m_SagitalRenderWin->AddRenderer(m_SagitalRenderer);
	m_SagitalInteractor->SetInteractorStyle(m_SagitalStyle);
	m_SagitalRenderWin->SetInteractor(m_SagitalInteractor);
	ui.SagitalWidget->SetRenderWindow(m_SagitalRenderWin);
	m_SagitalInteractor->Initialize();

}



void DICOMViewerWidget::LoadDICOM()
{
	QString filepath = QFileDialog::getExistingDirectory(this, "Choose the dir of the dicom files", NULL);
	if (filepath.isEmpty())
	{
		return;
	}

	typedef signed short PixelType;
	const unsigned int Dimension = 3;
	typedef itk::Image< PixelType, Dimension > ImageType;

	typedef itk::ImageSeriesReader< ImageType > ReaderType;
	ReaderType::Pointer reader = ReaderType::New();

	typedef itk::GDCMImageIO ImageIOType;
	ImageIOType::Pointer dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);

	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
	nameGenerator->AddSeriesRestriction("0008|0021");
	nameGenerator->SetDirectory(filepath.toStdString());

	typedef std::vector< std::string > SeriesIdContainer;
	const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();

	std::string seriesIdentifier;
	seriesIdentifier = seriesUID.begin()->c_str();

	typedef std::vector< std::string > FileNamesContainer;
	FileNamesContainer fileNames;
	fileNames = nameGenerator->GetFileNames(seriesIdentifier);

	reader->SetFileNames(fileNames);
	reader->Update();
	typedef itk::ImageToVTKImageFilter<ImageType> itk2vtkfilter;
	itk2vtkfilter::Pointer itk2vtk = itk2vtkfilter::New();

	itk2vtk->SetInput(reader->GetOutput());
	itk2vtk->Update();

	m_ImageData = vtkSmartPointer<vtkImageData>::New();
	m_ImageData->DeepCopy(itk2vtk->GetOutput());
	m_ImageData->GetSpacing(m_Spacing);
	m_ImageData->GetExtent(m_Extend);

	int axialIndex = (m_Extend[4] + m_Extend[5]) / 2;
	int coronalIndex = (m_Extend[2] + m_Extend[3]) / 2;
	int  sagitalIndex= (m_Extend[0] + m_Extend[1]) / 2;

	m_AxialViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_AxialViewer->SetInputData(m_ImageData);
	m_AxialViewer->SetRenderWindow(m_AxialRenderWin);
	m_AxialViewer->SetSliceOrientationToXY();
	m_AxialViewer->SetSlice(axialIndex);

	m_CoronalViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_CoronalViewer->SetInputData(m_ImageData);
	m_CoronalViewer->SetRenderWindow(m_CoronalRenderWin);
	m_CoronalViewer->SetSliceOrientationToXZ();
	m_CoronalViewer->SetSlice(coronalIndex);

	m_SagitalViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_SagitalViewer->SetInputData(m_ImageData);
	m_SagitalViewer->SetRenderWindow(m_SagitalRenderWin);
	m_SagitalViewer->SetSliceOrientationToYZ();
	m_SagitalViewer->SetSlice(sagitalIndex);


}
