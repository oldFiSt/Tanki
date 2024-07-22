## Сборка
Проект протестирован на Windows и Linux. Для сборки необходимы Git Bash, Cmake и компилятор.
Чтобы запустить проект нужно:
```powershell

1. Заходим в Git Bash
2. cd/d (вместо d может быть любой другой диск)
3. git clone https://github.com/oldFiSt/Tanki.git 
4. cd Tanki
5. mkdir build
6. cd build
7. cmake ..
8. cmake --build.
9. После прописывания этих команд заходим в Tanki/build/bin и открываем Tanki.exe
10. Теперь наш проект должен заработать
```
Для линукса: 

```powershell
1. заранее прописываем
    sudo apt update
    sudo apt install libgl1-mesa-dev libglu1-mesa-dev
2. .после пункта (10) нужно дописать cd bin
3. ./Tanki
```