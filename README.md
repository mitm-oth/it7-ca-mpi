# MPI Hello World

## Installation unter Linux oder WSL

Anweisungen von hier befolgen: [WSL/VM installieren](https://bookstack.kamaux.de/books/it-tools/page/wslvm-installieren)

## Installation OpenMPI

Bash starten und folgende Befehle ausführen:

WSL: Windows Taste + "Ubuntu", oder in der Console `wsl` eingeben


```bash
# install tools
sudo apt update && sudo apt install openmpi-bin libopenmpi-dev -y

# check version
mpicc --showme:version

# deactivate warning
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```

## Repository klonen


<!-- Stelle sicher das du im dem Ordner bist, in dem das Repository gespeichert werden soll.  
Unter WSL sind alle Windowsdateien unter `/mnt/c/` (oder `/mnt/d/` etc.) zu finden.

Bsp. für Speicherort: `cd /mnt/c/Users/<user>/Documents` -->


das Repository klonen:
    
    git clone https://github.com/Emergency1999/MPIHelloWorld.git

oder mit SSH:

    git clone git@github.com:Emergency1999/MPIHelloWorld.git

### Open in VScode

Das Projekt in VScode öffnen:
```bash
code .
```

### Build and run

Entweder kann das Skript `serve.sh` ausgeführt werden oder manuell die Befehle ausführen. 

script:

```bash
chmod +x serve.sh
./serve.sh
```
die serve.sh startet standardmäßig 4 Prozesse.
