/****************************************************************************
** Meta object code from reading C++ file 'annotatorscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../annotatorscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'annotatorscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnnotatorScene_t {
    QByteArrayData data[9];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnnotatorScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnnotatorScene_t qt_meta_stringdata_AnnotatorScene = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AnnotatorScene"
QT_MOC_LITERAL(1, 15, 11), // "selectClass"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "class_id"
QT_MOC_LITERAL(4, 37, 6), // "gridOn"
QT_MOC_LITERAL(5, 44, 7), // "enabled"
QT_MOC_LITERAL(6, 52, 12), // "AnnotationOn"
QT_MOC_LITERAL(7, 65, 16), // "annotationSignal"
QT_MOC_LITERAL(8, 82, 21) // "m_display_annotations"

    },
    "AnnotatorScene\0selectClass\0\0class_id\0"
    "gridOn\0enabled\0AnnotationOn\0"
    "annotationSignal\0m_display_annotations"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnnotatorScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,
       7,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void AnnotatorScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnnotatorScene *_t = static_cast<AnnotatorScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectClass((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->gridOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->AnnotationOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->annotationSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AnnotatorScene::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorScene::selectClass)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AnnotatorScene::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorScene::gridOn)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AnnotatorScene::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorScene::AnnotationOn)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AnnotatorScene::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorScene::annotationSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject AnnotatorScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_AnnotatorScene.data,
      qt_meta_data_AnnotatorScene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AnnotatorScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnnotatorScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnnotatorScene.stringdata0))
        return static_cast<void*>(const_cast< AnnotatorScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int AnnotatorScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AnnotatorScene::selectClass(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnnotatorScene::gridOn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AnnotatorScene::AnnotationOn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AnnotatorScene::annotationSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
