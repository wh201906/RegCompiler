#ifndef FIELD_H
#define FIELD_H

#include <QMetaType>

struct Field
{
    int start, end;
    bool operator ==(const Field& f) const
    {
        return (start == f.start && end == f.end);
    }
    bool operator<(const Field& f) const
    {
        return (start < f.start ? true : (end < f.end));
    }
};

Q_DECLARE_METATYPE(Field);

#endif // FIELD_H
