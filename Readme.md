# ПРиложение для мониторинга дорожного траффика
Финальный проект курса Otus C++ Basic.

## Назначение приложения
Приложение позволяет обрабатывать видео-поток, обнаруживать и отслеживать в нем транспортные средства и пешеходов, а также другие объекты.

## Зависимости и сборка
Приложение использует следующие основные зависимости:
- NVidia CUDA 12;
- OpenCV 4.10 с поддержкой CUDA.
Для сборки используется CMake.

Инструкиця для сборки:
```shell
mkdir build/ && cd build/
cmake ..
cmake --build .
```

Проще всего для сборки воспользоваться приложенным DevContainer, который самостоятельно установит все необходимые зависимости.

## Запуск приложения.
Для запуска приложения требуются:

- входной видео-файл с изображением дорожного траффика;
- веса нейросети YOLOv8n.

Примеры файлов, на которых можно опробовать приложение, можно скачать по [ссылке](https://disk.yandex.ru/d/CtuH7ehtXpyHog). *.onnx файл можно поместить в директорию ```weights/```.

Приложение принимает следующие параметры по порядку
- путь к входному видео-файлу;
- путь к файлу весов нейросети;
- опциональный флаг ```--gpu```. Если флаг установлен, приложение будет использовать GPU NVidia (если такая есть и поддерживает CUDA) для запуска нейросети. Если флаг не установлен, или нет подходящего GPU, приложение будет исполняться на CPU. С точки зрения результата нет почти никакой разницы в выполнении на GPU и CPU, но на GPU приложение работает быстрее.

Пример запуска приложения:
```shell
./main ./video.mov ./yolov8n.onnx --gpu
```

Результатом работы приложения станет видео-файл с именем входного файла и суффиксом ```_dets``` рядом с исходным файлом. В нем обнаруженные объекты будут выделены рамками с указанием уникального для каждого объекта индекса трека.

## О коде
Содержание проекта составляют файлы, содержащиеся непосредственно в директории ```src/```. Содержимое директорий ```src/yolo``` и ```src/sort``` вцелом позаимствовано (см. раздел "Ссылки") и подверглось минимальным необходимым для сборки проекта изменениям.

## Сслыки
- YOLOv8 - [официальный репозиторий Ultralytics](https://github.com/ultralytics/ultralytics/tree/main/examples/YOLOv8-CPP-Inference)
-  SORT - [реализация SORT на C++ от пользователя yasenh](https://github.com/yasenh/sort-cpp)
