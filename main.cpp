#include <QGuiApplication>
#include "%{WindowClassHeaderFileName}"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    %{WindowClass} w;
    w.resize(1280, 720);
    w.show();

    return a.exec();
}

