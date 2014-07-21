#pragma once
#include "ILineToImportSplitter.h"
#include <QRegularExpression>

class LineToImportSplitter: public ILineToImportSplitter
{
public:
    QStringList splitLine(const QString &line) override
    {
        QRegularExpression re(".* - .*");
        QRegularExpression reQA("Q:.*A:.*");

        if(line.contains(reQA))
        {
            QRegularExpression reQASplit("(Q:)|(A:)");
            auto strings =  line.split(reQASplit);
            strings.removeAll(QString(""));
            strings[0] = strings.at(0).trimmed();
            strings[1] = strings.at(1).trimmed();
            return strings;
        }

        if(line.contains(re))
            return line.split(" - ");
        throw std::logic_error("Unsupported file format");
    }
};
