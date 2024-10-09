# multithreadTestTask
## Сборка
Для сборки необходимо запустить следующую команду **cmake -S \path_to_source\ -B \path_to_build\*** , где path_to_source - путь до папки проекта с CMakeLists.txt, а path_to_build - путь, куда будет производится сборка.
После, находясь в папке path_to_build необходимо запустить команду ***cmake --build .*** для сборки исполняемого файла, который будет находится в папке ./debug .
## Запуск
Для запуска работы программы необходимо вызвать исполняемый файл со следующими параметрами:
- rps - количество обрабатываемых блоков данных в секунду в потоке-производителе;
- dataVolume - количество данных для записи в выходной файл в мегабайтах;
- outputFile - путь до файла для записи.
## Пример
***./testTask.exe 1000 400 "output.txt"***
