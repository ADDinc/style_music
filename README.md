Простейшая нейронная сеть определения стиля аудио-файла
=======================================================

Приложение позволяет определить стиль музыки аудио-файла. Точность ответа зависит от изученных программой стилей музыки и количестве обучений у каждого стиля.
Более подробно описано в [wiki](https://github.com/ADDinc/style_music/wiki).

Версия
------
Release 1.0:
-  Определяет вероятность принадлежности аудио-файла к каждому из обученных стилей музыки
-  Программа поддерживает ключи: 
    -  -d <directory>  - обязательный ключ, параметр ключа - директория содержащая аудио-файлы
    -  -l <style name> - необязательный ключ, при использовании данного ключа включается режим обучения, параметр ключа - наименование стиля музыки
-  Хранение базы стилей в файле формата .db

Building
--------

-  sudo apt-get install build-essential libyaml-dev libfftw3-dev libavcodec-dev libavformat-dev libavutil-dev libavresample-dev python-dev libsamplerate0-dev libtag1-dev
-  sudo apt-get install python-numpy-dev python-numpy python-yaml
-  make

Build status
------------

[![Build Status](https://travis-ci.org/ADDinc/style_music.svg?branch=master)](https://travis-ci.org/ADDinc/style_music)
