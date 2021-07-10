#ifndef COMMON_HPP
#define COMMON_HPP

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

inline quint64 getMask(Field field)
{
    quint64 mask, tmp;
    mask = (quint64)1 << (field.end + 1);
    mask--;
    tmp = (quint64)1 << field.start;
    tmp--;
    mask ^= tmp;
    return mask;
}

#endif // COMMON_HPP
