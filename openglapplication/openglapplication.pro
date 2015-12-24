TEMPLATE = app

QT += core gui
CONFIG += c++11

HEADERS += %{WindowClassHeaderFileName}
SOURCES += %{MainCppFileName} %{WindowClassSourceFileName}

RESOURCES += %{ResourceFileName}

OTHER_FILES += shaders/simple_vs.glsl shaders/simple_fs.glsl texture.jpg

