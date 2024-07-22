## Проект протестирован на следующих устройствах:
1. Windows 10 RTX 3050Ti Laptop i5-12450-F
2. Windows 11 RTX 3060   Laptop i7-12700-H
3. Windows 10 Ryzen 7 5800U
4. Windows 11 GTX 1650   Laptop i3-10105F
5. Linux Ryzen 7 5800U 
6. Linux Geforce G205M Intel Core 2 DUO
## Сборка
Проект протестирован на Windows и Linux. Для сборки необходимы Git Bash, Cmake и компилятор.
Чтобы запустить проект нужно:
```powershell

1. Заходим в Git Bash
2. cd /d (вместо d может быть любой другой диск)
3. git clone https://github.com/oldFiSt/Tanki.git 
4. cd Tanki
5. mkdir build
6. cd build
7. cmake ..
8. cmake --build .
9. После прописывания этих команд заходим в Tanki/build/bin и открываем Tanki.exe
10. Теперь наш проект должен заработать
Чтобы выбрать режим нужно использовать кнопки W или S (движение вверх, вниз)
Enter - выбрать режим
```
Для линукса: 

```powershell
1. заранее прописываем
    sudo apt update
    sudo apt install libgl1-mesa-dev libglu1-mesa-dev
2. .после пункта (10) нужно дописать cd bin
3. ./Tanki
```
