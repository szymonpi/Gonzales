#pragma once
#include <QString>
#include "QAFilePathSelector.h"

class QAFilePathSelector: public QAFilePathSelector
{
public:
    bool select()
    {
        QFileDialog dialog(this);
        QString filePath = dialog.getOpenFileName(this);
        if(filePath.isEmpty())
            return false;
        return true;
    }

    QString getSelected()
    {
        return m_selected;
    }

};
