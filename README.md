Простейшая нейронная сеть определения стиля аудио-файла
---
[![Build Status](https://travis-ci.org/ADDinc/style_music.svg?branch=master)](https://travis-ci.org/ADDinc/style_music)

Приложение позволяет определить стиль музыки аудио-файла. Точность ответа зависит от изученных программой стилей музыки и количестве обучений у каждого стиля.
Более подробно описано в [wiki](https://github.com/ADDinc/style_music/wiki).

Версия
---
Version: 2.0.1
-  Определяет вероятность принадлежности аудио-файла к каждому из обученных стилей музыки
-  Программа поддерживает ключи: 
	-  **-f** <file name>  - файл содержащий список аудио-файлов для обработки
    -  **-d** <directory>  - обязательный ключ, параметр ключа - директория содержащая аудио-файлы
    -  **-l** <style name> - необязательный ключ, при использовании данного ключа включается режим обучения, параметр ключа - наименование стиля музыки
    -  **-i**              - вывод подробной информации об аудио-файлах.
-  Хранение базы стилей в файле формата .db

Установка
---

-  sudo apt-get install build-essential libyaml-dev libfftw3-dev libavcodec-dev libavformat-dev libavutil-dev libavresample-dev python-dev libsamplerate0-dev libtag1-dev
-  sudo apt-get install python-numpy-dev python-numpy python-yaml
-  make

Платфрмы
---

-  Linux.