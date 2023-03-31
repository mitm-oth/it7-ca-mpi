# MPI Hello World

## Installation unter Linux oder WSL

[Link zur Originalanleitung](https://amithkk.medium.com/setting-up-visual-studio-code-and-wsl-for-mpi-develoment-8df55758a31c)

### WSL Aufsetzen

[Ubuntu unter windows installieren](https://apps.microsoft.com/store/detail/ubuntu/9PDXGNCFSCZV?hl=en-us&gl=us&activetab=pivot%3Aoverviewtab)

oder in der Console ausführen:

```bat
wsl --install -d Ubuntu
```

### Installation OpenMPI

```bash
# install tools
sudo apt update && sudo apt install openmpi-bin libopenmpi-dev -y

# deactivate warning
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

# check version
mpicc --showme:version
```

### Repository klonen

Stelle sicher das du im dem Ordner bist, in dem das Repository gespeichert werden soll.  
Unter WSL sind alle Windowsdateien unter `/mnt/c/` (oder `/mnt/d/` etc.) zu finden.

Bsp für Speicherort:

```bash

cd /mnt/c/Users/<user>/Documents/CA


```bash

```bash




### Build and run

Entweder kann das Skript `serve.sh` ausgeführt werden oder manuell die Befehle ausführen. 

script:

```bash
./serve.sh
```

manuell:

```bash
mpicc mpi_hello_world.c -o mpi_hello_world

chmod +x mpi_hello_world.out

mpirun -np 2 ./mpi_hello_world
```


## Installation unter Windows

Beide Microsoft MPI SDK Installer herunterladen und ausführen: https://www.microsoft.com/en-us/download/details.aspx?id=57467 (2 Dateien)

Falls Visual Studio nicht installiert ist, müssen die Visual C++ 2015 Build Tools installiert werden (ist Visual Studio installiert müssen die Pfade in der build.bat entsprechend angepasst werden): https://go.microsoft.com/fwlink/?LinkId=691126

### Build and run Windows

"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\cl" /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include\x64" /I. /I"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include" /I"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include" /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt" /c MPIHelloWorld.cpp
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\link" /machine:x64 /out:MpiHelloWorld.exe /dynamicbase "msmpi.lib" /libpath:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" /LIBPATH:"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib\amd64" /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\ucrt\x64" MPIHelloWorld.obj

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -n 2 MpiHelloWorld.exe
