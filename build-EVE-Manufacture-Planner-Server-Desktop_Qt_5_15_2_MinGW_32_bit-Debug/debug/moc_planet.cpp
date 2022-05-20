/****************************************************************************
** Meta object code from reading C++ file 'planet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../EVE-Manufacture-Planner-Server/planet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'planet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Planet_t {
    QByteArrayData data[10];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Planet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Planet_t qt_meta_stringdata_Planet = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Planet"
QT_MOC_LITERAL(1, 7, 11), // "PlanetTypes"
QT_MOC_LITERAL(2, 19, 6), // "Barren"
QT_MOC_LITERAL(3, 26, 3), // "Gas"
QT_MOC_LITERAL(4, 30, 3), // "Ice"
QT_MOC_LITERAL(5, 34, 4), // "Lava"
QT_MOC_LITERAL(6, 39, 7), // "Oceanic"
QT_MOC_LITERAL(7, 47, 6), // "Plasma"
QT_MOC_LITERAL(8, 54, 5), // "Storm"
QT_MOC_LITERAL(9, 60, 9) // "Temperate"

    },
    "Planet\0PlanetTypes\0Barren\0Gas\0Ice\0"
    "Lava\0Oceanic\0Plasma\0Storm\0Temperate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Planet[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    8,   19,

 // enum data: key, value
       2, uint(Planet::Barren),
       3, uint(Planet::Gas),
       4, uint(Planet::Ice),
       5, uint(Planet::Lava),
       6, uint(Planet::Oceanic),
       7, uint(Planet::Plasma),
       8, uint(Planet::Storm),
       9, uint(Planet::Temperate),

       0        // eod
};

void Planet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Planet::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Planet.data,
    qt_meta_data_Planet,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Planet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Planet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Planet.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Planet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
