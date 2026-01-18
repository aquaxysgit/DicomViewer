# make env VTK, DCMTK with vcpkg
```
mkdir C:\vcpkg
cd C:\vcpkg
git clone https://github.com/microsoft/vcpkg .
bootstrap-vcpkg.bat
vcpkg integrate install
```
Applied user-wide integration for this vcpkg root.
CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
All MSBuild C++ projects can now #include any installed libraries. Linking will be handled automatically. Installing new libraries will make them instantly available.
```
vcpkg install vtk:x64-windows
```
Computing installation plan...
A suitable version of cmake was not found (required v3.31.10).
Downloading https://github.com/Kitware/CMake/releases/download/v3.31.10/cmake-3.31.10-windows-x86_64.zip -> cmake-3.31.10-windows-x86_64.zip
Successfully downloaded cmake-3.31.10-windows-x86_64.zip
Extracting cmake...
...
```
vcpkg install dcmtk:x64-windows
```

**문서 하단 VTK, DCMTK 오류 해결 방법 추가**



# 2026 1/17 code brief
→ 3D Volume Viewer 표시  
→ 사용자 Distance 측정  
→ SR 파일 생성  
→ SR → PACS C-STORE 전송  
→ Measurement PDF Report 생성  

### 1. SR → PACS 전송

#### **StoreSCUManager::SendSR()**

```
`DcmSCU scu; scu.sendSTORERequest()`
```

▶ DCMTK C-STORE SCU 수행  
▶ PACS Association → SR 전송

### 2 Measurement PDF Report 생성

#### **PdfReportWriter::WritePDF()**

```
ofstream pdf
```

▶ Patient 정보 + Distance 리포트 출력




# 2026/1/14 code brief

→ 3D Volume Viewer 표시  
→ 사용자 Distance 측정  
→ SR 파일 생성  

### 1. DICOM Series 로딩
#### **DicomSeriesLoader::LoadSeries()**
```
vtkDICOMImageReader reader;
reader->SetDirectoryName(folder);
reader->Update();
m_volume = reader->GetOutput();
```
▶ 폴더 단위 DICOM 시리즈 로드  
▶ VTK 이미지 볼륨(vtkImageData) 생성  

### 2. 환자 및 Study 메타데이터 추출
#### **ExtractMetaInfo()**
```
DCM_PatientName  
DCM_PatientID  
DCM_StudyInstanceUID  
DCM_SeriesInstanceUID
```
▶ PatientInfo 구조체에 저장  

### 3. GPU 기반 3D Volume Rendering
#### **Viewer3D::SetupVolumeRendering()**
```
vtkGPUVolumeRayCastMapper
vtkVolumeProperty
vtkColorTransferFunction
vtkPiecewiseFunction
```
▶ GPU RayCast 볼륨 렌더링  
▶ 컬러/Opacity Transfer Function 적용  
▶ 3D 볼륨 시각화  

### 4. VTK 인터랙티브 Distance 측정
#### **MeasurementManager::Initialize()**
```
vtkDistanceWidget
vtkDistanceRepresentation2D
```
▶ 마우스로 두 점 지정 거리 측정  
▶ InteractionEvent 발생 시 거리 계산  
▶ mm 단위 결과 저장  

### 5. DICOM Structured Report (SR) 생성
#### **SRWriter::WriteSR()**
```
DSRDocument sr;
sr.createNewDocument(DT_EnhancedSR);
```
▶ Enhanced SR 문서 생성  
▶ Patient / Study / Series 정보 매핑  
▶ Measurement Report 컨셉 노드 생성  
▶ Distance 수치(mm) 기록  

### 6. SR 파일 저장
#### **SRWriter::WriteSR()**
```
sr.writeFile("Measurement_SR.dcm");
```
▶ 결과 SR을 로컬 DICOM 파일로 저장  
