/****************************************************************************
** Meta object code from reading C++ file 'chipannotator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chipannotator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chipannotator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChipAnnotator_t {
    QByteArrayData data[30];
    char stringdata0[432];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChipAnnotator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChipAnnotator_t qt_meta_stringdata_ChipAnnotator = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ChipAnnotator"
QT_MOC_LITERAL(1, 14, 15), // "newCurrentClass"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "name"
QT_MOC_LITERAL(4, 36, 8), // "modified"
QT_MOC_LITERAL(5, 45, 17), // "mouseMoveFunction"
QT_MOC_LITERAL(6, 63, 39), // "boost::optional<AnnotatorScen..."
QT_MOC_LITERAL(7, 103, 16), // "m_current_region"
QT_MOC_LITERAL(8, 120, 18), // "mousePressFunction"
QT_MOC_LITERAL(9, 139, 22), // "AnnotatorScene::Region"
QT_MOC_LITERAL(10, 162, 13), // "mousePressPos"
QT_MOC_LITERAL(11, 176, 20), // "mouseReleaseFunction"
QT_MOC_LITERAL(12, 197, 15), // "mouseReleasePos"
QT_MOC_LITERAL(13, 213, 12), // "processClick"
QT_MOC_LITERAL(14, 226, 3), // "pos"
QT_MOC_LITERAL(15, 230, 9), // "tagRegion"
QT_MOC_LITERAL(16, 240, 6), // "region"
QT_MOC_LITERAL(17, 247, 23), // "boost::optional<quint8>"
QT_MOC_LITERAL(18, 271, 7), // "classes"
QT_MOC_LITERAL(19, 279, 17), // "leaveViewFunction"
QT_MOC_LITERAL(20, 297, 14), // "showAnnotation"
QT_MOC_LITERAL(21, 312, 20), // "m_display_annotation"
QT_MOC_LITERAL(22, 333, 11), // "displayGrid"
QT_MOC_LITERAL(23, 345, 5), // "Reset"
QT_MOC_LITERAL(24, 351, 15), // "classAtPosition"
QT_MOC_LITERAL(25, 367, 15), // "hasImagesLoaded"
QT_MOC_LITERAL(26, 383, 17), // "sceneScaleChanged"
QT_MOC_LITERAL(27, 401, 5), // "scale"
QT_MOC_LITERAL(28, 407, 9), // "PaintGrid"
QT_MOC_LITERAL(29, 417, 14) // "m_display_grid"

    },
    "ChipAnnotator\0newCurrentClass\0\0name\0"
    "modified\0mouseMoveFunction\0"
    "boost::optional<AnnotatorScene::Region>\0"
    "m_current_region\0mousePressFunction\0"
    "AnnotatorScene::Region\0mousePressPos\0"
    "mouseReleaseFunction\0mouseReleasePos\0"
    "processClick\0pos\0tagRegion\0region\0"
    "boost::optional<quint8>\0classes\0"
    "leaveViewFunction\0showAnnotation\0"
    "m_display_annotation\0displayGrid\0Reset\0"
    "classAtPosition\0hasImagesLoaded\0"
    "sceneScaleChanged\0scale\0PaintGrid\0"
    "m_display_grid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChipAnnotator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    0,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   98,    2, 0x0a /* Public */,
       8,    1,  101,    2, 0x0a /* Public */,
      11,    1,  104,    2, 0x0a /* Public */,
      13,    1,  107,    2, 0x0a /* Public */,
      15,    2,  110,    2, 0x0a /* Public */,
      15,    1,  115,    2, 0x2a /* Public | MethodCloned */,
      19,    0,  118,    2, 0x0a /* Public */,
      20,    1,  119,    2, 0x0a /* Public */,
      22,    0,  122,    2, 0x0a /* Public */,
      23,    0,  123,    2, 0x0a /* Public */,
      24,    1,  124,    2, 0x0a /* Public */,
      25,    0,  127,    2, 0x0a /* Public */,
      26,    1,  128,    2, 0x0a /* Public */,
      28,    1,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   12,
    QMetaType::Void, 0x80000000 | 9,   14,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 17,   16,   18,
    QMetaType::Void, 0x80000000 | 9,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UChar, 0x80000000 | 9,   14,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Bool,   29,

       0        // eod
};

void ChipAnnotator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChipAnnotator *_t = static_cast<ChipAnnotator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newCurrentClass((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->modified(); break;
        case 2: _t->mouseMoveFunction((*reinterpret_cast< boost::optional<AnnotatorScene::Region>(*)>(_a[1]))); break;
        case 3: _t->mousePressFunction((*reinterpret_cast< AnnotatorScene::Region(*)>(_a[1]))); break;
        case 4: _t->mouseReleaseFunction((*reinterpret_cast< AnnotatorScene::Region(*)>(_a[1]))); break;
        case 5: _t->processClick((*reinterpret_cast< const AnnotatorScene::Region(*)>(_a[1]))); break;
        case 6: _t->tagRegion((*reinterpret_cast< const AnnotatorScene::Region(*)>(_a[1])),(*reinterpret_cast< boost::optional<quint8>(*)>(_a[2]))); break;
        case 7: _t->tagRegion((*reinterpret_cast< const AnnotatorScene::Region(*)>(_a[1]))); break;
        case 8: _t->leaveViewFunction(); break;
        case 9: _t->showAnnotation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->displayGrid(); break;
        case 11: _t->Reset(); break;
        case 12: { quint8 _r = _t->classAtPosition((*reinterpret_cast< const AnnotatorScene::Region(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->hasImagesLoaded();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->PaintGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChipAnnotator::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChipAnnotator::newCurrentClass)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ChipAnnotator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChipAnnotator::modified)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ChipAnnotator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChipAnnotator.data,
      qt_meta_data_ChipAnnotator,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ChipAnnotator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChipAnnotator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChipAnnotator.stringdata0))
        return static_cast<void*>(const_cast< ChipAnnotator*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChipAnnotator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ChipAnnotator::newCurrentClass(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChipAnnotator::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
