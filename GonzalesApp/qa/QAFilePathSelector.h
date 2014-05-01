#ifndef QAFILEPATHSELECTOR_H
#define QAFILEPATHSELECTOR_H
#include <QString>
#include "../dialogselectgroup.h"

class QAFilePathSelector
{
public:
    virtual bool select() = 0;
    virtual QString getSelected() = 0;
    virtual ~QAFilePathSelector(){}
};

class QAFileDialogFilePathSelector: public QAFilePathSelector
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

#endif // QAFILEPATHSELECTOR_H
