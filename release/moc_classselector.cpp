/****************************************************************************
** Meta object code from reading C++ file 'classselector.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../classselector.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'classselector.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClassSelector_t {
    QByteArrayData data[14];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClassSelector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClassSelector_t qt_meta_stringdata_ClassSelector = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClassSelector"
QT_MOC_LITERAL(1, 14, 13), // "classSelected"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "class_index"
QT_MOC_LITERAL(4, 41, 15), // "channelSelected"
QT_MOC_LITERAL(5, 57, 13), // "channel_index"
QT_MOC_LITERAL(6, 71, 12), // "resetClicked"
QT_MOC_LITERAL(7, 84, 11), // "autoClicked"
QT_MOC_LITERAL(8, 96, 19), // "moreContrastClicked"
QT_MOC_LITERAL(9, 116, 19), // "lessContrastClicked"
QT_MOC_LITERAL(10, 136, 21), // "moreBrightnessClicked"
QT_MOC_LITERAL(11, 158, 21), // "lessBrightnessClicked"
QT_MOC_LITERAL(12, 180, 6), // "DragOn"
QT_MOC_LITERAL(13, 187, 11) // "selectClass"

    },
    "ClassSelector\0classSelected\0\0class_index\0"
    "channelSelected\0channel_index\0"
    "resetClicked\0autoClicked\0moreContrastClicked\0"
    "lessContrastClicked\0moreBrightnessClicked\0"
    "lessBrightnessClicked\0DragOn\0selectClass"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClassSelector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    0,   70,    2, 0x06 /* Public */,
       7,    0,   71,    2, 0x06 /* Public */,
       8,    0,   72,    2, 0x06 /* Public */,
       9,    0,   73,    2, 0x06 /* Public */,
      10,    0,   74,    2, 0x06 /* Public */,
      11,    0,   75,    2, 0x06 /* Public */,
      12,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,    3,

       0        // eod
};

void ClassSelector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClassSelector *_t = static_cast<ClassSelector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->classSelected((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->channelSelected((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->resetClicked(); break;
        case 3: _t->autoClicked(); break;
        case 4: _t->moreContrastClicked(); break;
        case 5: _t->lessContrastClicked(); break;
        case 6: _t->moreBrightnessClicked(); break;
        case 7: _t->lessBrightnessClicked(); break;
        case 8: _t->DragOn(); break;
        case 9: _t->selectClass((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClassSelector::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::classSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::channelSelected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::resetClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::autoClicked)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::moreContrastClicked)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::lessContrastClicked)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::moreBrightnessClicked)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::lessBrightnessClicked)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ClassSelector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassSelector::DragOn)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject ClassSelector::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ClassSelector.data,
      qt_meta_data_ClassSelector,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClassSelector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClassSelector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClassSelector.stringdata0))
        return static_cast<void*>(const_cast< ClassSelector*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ClassSelector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ClassSelector::classSelected(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClassSelector::channelSelected(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClassSelector::resetClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ClassSelector::autoClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ClassSelector::moreContrastClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ClassSelector::lessContrastClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ClassSelector::moreBrightnessClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ClassSelector::lessBrightnessClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void ClassSelector::DragOn()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
