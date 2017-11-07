/****************************************************************************
** Meta object code from reading C++ file 'annotatorview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../annotatorview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'annotatorview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnnotatorView_t {
    QByteArrayData data[10];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnnotatorView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnnotatorView_t qt_meta_stringdata_AnnotatorView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AnnotatorView"
QT_MOC_LITERAL(1, 14, 15), // "mouseMoveSignal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 39), // "boost::optional<AnnotatorScen..."
QT_MOC_LITERAL(4, 71, 16), // "m_current_region"
QT_MOC_LITERAL(5, 88, 16), // "mousePressSignal"
QT_MOC_LITERAL(6, 105, 22), // "AnnotatorScene::Region"
QT_MOC_LITERAL(7, 128, 13), // "mousePressPos"
QT_MOC_LITERAL(8, 142, 18), // "mouseReleaseSignal"
QT_MOC_LITERAL(9, 161, 15) // "mouseReleasePos"

    },
    "AnnotatorView\0mouseMoveSignal\0\0"
    "boost::optional<AnnotatorScene::Region>\0"
    "m_current_region\0mousePressSignal\0"
    "AnnotatorScene::Region\0mousePressPos\0"
    "mouseReleaseSignal\0mouseReleasePos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnnotatorView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,
       8,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    9,

       0        // eod
};

void AnnotatorView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnnotatorView *_t = static_cast<AnnotatorView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseMoveSignal((*reinterpret_cast< boost::optional<AnnotatorScene::Region>(*)>(_a[1]))); break;
        case 1: _t->mousePressSignal((*reinterpret_cast< AnnotatorScene::Region(*)>(_a[1]))); break;
        case 2: _t->mouseReleaseSignal((*reinterpret_cast< AnnotatorScene::Region(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AnnotatorView::*_t)(boost::optional<AnnotatorScene::Region> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorView::mouseMoveSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AnnotatorView::*_t)(AnnotatorScene::Region );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorView::mousePressSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AnnotatorView::*_t)(AnnotatorScene::Region );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnnotatorView::mouseReleaseSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject AnnotatorView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_AnnotatorView.data,
      qt_meta_data_AnnotatorView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AnnotatorView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnnotatorView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnnotatorView.stringdata0))
        return static_cast<void*>(const_cast< AnnotatorView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int AnnotatorView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AnnotatorView::mouseMoveSignal(boost::optional<AnnotatorScene::Region> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnnotatorView::mousePressSignal(AnnotatorScene::Region _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AnnotatorView::mouseReleaseSignal(AnnotatorScene::Region _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
