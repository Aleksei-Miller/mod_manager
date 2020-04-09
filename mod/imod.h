#ifndef IMOD_H
#define IMOD_H

#include <QPixmap>

#include "qzipreader_p.h"

class IMod
{
public:
    virtual ~IMod(){}

    virtual QString value(const QString &){ return ""; }
    virtual QPixmap logo(){ return QPixmap(); }
};

#endif //IMOD_H
