## 2026/1/14 code brief

### 1. DICOM Series 로딩
#### **DicomSeriesLoader::LoadSeries()**
```
vtkDICOMImageReader reader;
reader->SetDirectoryName(folder);
reader->Update();
m_volume = reader->GetOutput();
```
##### 폴더 단위 DICOM 시리즈 로드
##### VTK 이미지 볼륨(vtkImageData) 생성

### 2. 환자 및 Study 메타데이터 추출
#### **ExtractMetaInfo()**
```
DCM_PatientName  
DCM_PatientID  
DCM_StudyInstanceUID  
DCM_SeriesInstanceUID
```
##### PatientInfo 구조체에 저장

### 3. GPU 기반 3D Volume Rendering
#### **Viewer3D::SetupVolumeRendering()**
```
vtkGPUVolumeRayCastMapper
vtkVolumeProperty
vtkColorTransferFunction
vtkPiecewiseFunction
```
##### GPU RayCast 볼륨 렌더링
##### 컬러/Opacity Transfer Function 적용
##### 3D 볼륨 시각화

### 4. VTK 인터랙티브 Distance 측정
#### **MeasurementManager::Initialize()**
```
vtkDistanceWidget
vtkDistanceRepresentation2D
```
##### 마우스로 두 점 지정 거리 측정
##### InteractionEvent 발생 시 거리 계산
##### mm 단위 결과 저장

### 5. DICOM Structured Report (SR) 생성
#### **SRWriter::WriteSR()**
```
DSRDocument sr;
sr.createNewDocument(DT_EnhancedSR);
```
##### Enhanced SR 문서 생성
##### Patient / Study / Series 정보 매핑
##### Measurement Report 컨셉 노드 생성
##### Distance 수치(mm) 기록

### 6. SR 파일 저장
#### **SRWriter::WriteSR()**
```
sr.writeFile("Measurement_SR.dcm");
```
##### 결과 SR을 로컬 DICOM 파일로 저장
