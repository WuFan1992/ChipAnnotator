/****************************************************************************
** Meta object code from reading C++ file 'menuaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../menuaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuAction_t {
    QByteArrayData data[16];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuAction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuAction_t qt_meta_stringdata_MenuAction = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MenuAction"
QT_MOC_LITERAL(1, 11, 10), // "resetScene"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 18), // "displayImageSignal"
QT_MOC_LITERAL(4, 42, 21), // "std::array<QPixmap,3>"
QT_MOC_LITERAL(5, 64, 3), // "res"
QT_MOC_LITERAL(6, 68, 23), // "displayAnnotationSignal"
QT_MOC_LITERAL(7, 92, 8), // "QString&"
QT_MOC_LITERAL(8, 101, 9), // "file_path"
QT_MOC_LITERAL(9, 111, 17), // "displayGridSignal"
QT_MOC_LITERAL(10, 129, 20), // "setWindowTitleSignal"
QT_MOC_LITERAL(11, 150, 9), // "file_name"
QT_MOC_LITERAL(12, 160, 20), // "saveAnnotationSignal"
QT_MOC_LITERAL(13, 181, 13), // "onOpenClicked"
QT_MOC_LITERAL(14, 195, 13), // "onSaveClicked"
QT_MOC_LITERAL(15, 209, 20) // "onAnnotationModified"

    },
    "MenuAction\0resetScene\0\0displayImageSignal\0"
    "std::array<QPixmap,3>\0res\0"
    "displayAnnotationSignal\0QString&\0"
    "file_path\0displayGridSignal\0"
    "setWindowTitleSignal\0file_name\0"
    "saveAnnotationSignal\0onOpenClicked\0"
    "onSaveClicked\0onAnnotationModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuAction[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       6,    1,   63,    2, 0x06 /* Public */,
       9,    0,   66,    2, 0x06 /* Public */,
      10,    1,   67,    2, 0x06 /* Public */,
      12,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   73,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,   11,
    QMetaType::Void, 0x80000000 | 7,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MenuAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuAction *_t = static_cast<MenuAction *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetScene(); break;
        case 1: _t->displayImageSignal((*reinterpret_cast< std::array<QPixmap,3>(*)>(_a[1]))); break;
        case 2: _t->displayAnnotationSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->displayGridSignal(); break;
        case 4: _t->setWindowTitleSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->saveAnnotationSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->onOpenClicked(); break;
        case 7: _t->onSaveClicked(); break;
        case 8: _t->onAnnotationModified(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MenuAction::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuAction::resetScene)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MenuAction::*_t)(std::array<QPixmap,3> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuAction::displayImageSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MenuAction::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuAction::displayAnnotationSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MenuAction::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuAction::displayGridSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MenuAction::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuAction::setWindowTitleSignal)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MenuAction::*_t)(QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuAction::saveAnnotationSignal)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MenuAction::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MenuAction.data,
      qt_meta_data_MenuAction,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MenuAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuAction::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuAction.stringdata0))
        return static_cast<void*>(const_cast< MenuAction*>(this));
    return QWidget::qt_metacast(_clname);
}

int MenuAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MenuAction::resetScene()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MenuAction::displayImageSignal(std::array<QPixmap,3> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MenuAction::displayAnnotationSignal(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MenuAction::displayGridSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MenuAction::setWindowTitleSignal(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MenuAction::saveAnnotationSignal(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
