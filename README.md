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


## troubleshooting
### VTK error
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: C:\\vcpkg\\downloads\\tools\\**ninja-1.13.2-windows\\ninja.exe -v**
    Working Directory: C:/vcpkg/buildtrees/vtk/x64-windows-rel/vcpkg-parallel-configure
    Error code: 1
    See logs for more information:
      C:\vcpkg\buildtrees\vtk\config-x64-windows-dbg-CMakeCache.txt.log
      C:\vcpkg\buildtrees\vtk\config-x64-windows-rel-CMakeCache.txt.log
      C:\vcpkg\buildtrees\vtk\config-x64-windows-dbg-CMakeConfigureLog.yaml.log
      C:\vcpkg\buildtrees\vtk\config-x64-windows-rel-CMakeConfigureLog.yaml.log
      C:\vcpkg\buildtrees\vtk\config-x64-windows-out.log

Call Stack (most recent call first):
  installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:269 (vcpkg_execute_required_process)
  ports/vtk/portfile.cmake:262 (vcpkg_cmake_configure)
  scripts/ports.cmake:206 (include)


error: building vtk:x64-windows failed with: BUILD_FAILED
See https://learn.microsoft.com/vcpkg/troubleshoot/build-failures?WT.mc_id=vcpkg_inproduct_cli for more information.
Elapsed time to handle vtk:x64-windows: 19 s
Please ensure you're using the latest port files with `git pull` and `vcpkg update`.
Then check for known issues at:
  https://github.com/microsoft/vcpkg/issues?q=is%3Aissue+is%3Aopen+in%3Atitle+vtk
You can submit a new issue at:
  https://github.com/microsoft/vcpkg/issues/new?title=%5Bvtk%5D%20build%20error%20on%20x64-windows&body=Copy%20issue%20body%20from%20C%3A%2Fvcpkg%2Finstalled%2Fvcpkg%2Fissue_body.md

#### Ninja 수동설치
```
https://github.com/ninja-build/ninja/releases
```
ninja-win.zip [다운로드](https://github.com/ninja-build/ninja/releases/download/v1.13.2/ninja-win.zip)
```
C:\tools\ninja\ninja.exe
setx PATH "%PATH%;C:\tools\ninja"
```
혹은 windows\system3 2에 복사
```
where ninja.exe
```
C:\vcpkg>where ninja.exe  
C:\Windows\System32\ninja.exe  
```
set VCPKG_FORCE_SYSTEM_BINARIES=1
vcpkg install vtk:x64-windows
```
