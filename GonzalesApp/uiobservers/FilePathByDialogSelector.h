#ifndef FILEPATHBYDIALOGSELECTOR_H
#define FILEPATHBYDIALOGSELECTOR_H
#include "filepathselector.h"
#include <QFileDialog>

class FilePathByDialogSelector: public FilePathSelector
{
public:

    bool select()
    {
        QFileDialog dialog;
        m_selected = dialog.getOpenFileName();
        if(m_selected.isEmpty())
            return false;
        return true;
    }

    QString getSelected() const
    {
        return m_selected;
    }
private:
    QString m_selected;
};

#endif // FILEPATHBYDIALOGSELECTOR_H
