#ifndef IODEVICE_H
#define IODEVICE_H

#include <QIODevice>

class IODeviceProxy
{
public:
    IODeviceProxy();

    operator QIODevice()
    {
        return  device;
    }

private:
    QIODevice device;
};

#endif // IODEVICE_H
