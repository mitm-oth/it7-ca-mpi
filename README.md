# MPI Hello World

## Installation unter Linux oder WSL

[Link zur Originalanleitung](https://amithkk.medium.com/setting-up-visual-studio-code-and-wsl-for-mpi-develoment-8df55758a31c)

### WSL Aufsetzen

[Ubuntu unter windows installieren](https://apps.microsoft.com/store/detail/ubuntu/9PDXGNCFSCZV?hl=en-us&gl=us&activetab=pivot%3Aoverviewtab)

oder in der cmd ausführen:

```bat
wsl --install -d Ubuntu
```

Anschließend einen Nutzernamen und ein Passwort eingeben.

#### Fehler "The Windows Subsystem for Linux optional component is not enabled"

WSL muss erst aktiviert werden:

Powershell als Admin öffnen und

```bat
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

### Installation OpenMPI

WSL starten (Windows Taste + "Ubuntu", oder in der Console `wsl` eingeben)

```bash
# install tools
sudo apt update && sudo apt install openmpi-bin libopenmpi-dev -y

# check version
mpicc --showme:version

# deactivate warning
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```

### Repository klonen

Stelle sicher das du im dem Ordner bist, in dem das Repository gespeichert werden soll.  
Unter WSL sind alle Windowsdateien unter `/mnt/c/` (oder `/mnt/d/` etc.) zu finden.

Bsp. für Speicherort:

```bash
cd /mnt/c/Users/<user>/Documents/CA
```

Anschließend das Repository klonen:
    
    git clone https://github.com/Emergency1999/MPIHelloWorld.git

oder mit SSH:

    git clone git@github.com:Emergency1999/MPIHelloWorld.git

#### Fehler "Operation not permitted"

```bash
cd /mnt
sudo umount /mnt/c
sudo mount -t drvfs C: /mnt/c -o metadata
```

anschließend in Windows CMD ausführen
    
```bat
wsl --shutdown
```

jetzt WSL wieder starten und des Repository klonen.

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
