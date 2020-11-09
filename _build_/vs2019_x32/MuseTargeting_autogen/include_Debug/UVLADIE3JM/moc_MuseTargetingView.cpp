/****************************************************************************
** Meta object code from reading C++ file 'MuseTargetingView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "src/MuseTargetingView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MuseTargetingView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MuseTargetingView_t {
    QByteArrayData data[15];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MuseTargetingView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MuseTargetingView_t qt_meta_stringdata_MuseTargetingView = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MuseTargetingView"
QT_MOC_LITERAL(1, 18, 21), // "updateCurrentSettings"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 22), // "MuseTargetingSettings*"
QT_MOC_LITERAL(4, 64, 1), // "s"
QT_MOC_LITERAL(5, 66, 18), // "updateDesiredFocus"
QT_MOC_LITERAL(6, 85, 13), // "core::Vector3"
QT_MOC_LITERAL(7, 99, 2), // "df"
QT_MOC_LITERAL(8, 102, 17), // "sendObservedFocus"
QT_MOC_LITERAL(9, 120, 2), // "of"
QT_MOC_LITERAL(10, 123, 18), // "enterButtonClicked"
QT_MOC_LITERAL(11, 142, 11), // "refreshView"
QT_MOC_LITERAL(12, 154, 22), // "calculateButtonClicked"
QT_MOC_LITERAL(13, 177, 18), // "resetButtonClicked"
QT_MOC_LITERAL(14, 196, 20) // "receiveObservedFocus"

    },
    "MuseTargetingView\0updateCurrentSettings\0"
    "\0MuseTargetingSettings*\0s\0updateDesiredFocus\0"
    "core::Vector3\0df\0sendObservedFocus\0"
    "of\0enterButtonClicked\0refreshView\0"
    "calculateButtonClicked\0resetButtonClicked\0"
    "receiveObservedFocus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MuseTargetingView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       8,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   63,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,
      13,    0,   66,    2, 0x08 /* Private */,
      14,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    9,

       0        // eod
};

void MuseTargetingView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MuseTargetingView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateCurrentSettings((*reinterpret_cast< MuseTargetingSettings*(*)>(_a[1]))); break;
        case 1: _t->updateDesiredFocus((*reinterpret_cast< core::Vector3(*)>(_a[1]))); break;
        case 2: _t->sendObservedFocus((*reinterpret_cast< core::Vector3(*)>(_a[1]))); break;
        case 3: _t->enterButtonClicked(); break;
        case 4: _t->refreshView(); break;
        case 5: _t->calculateButtonClicked(); break;
        case 6: _t->resetButtonClicked(); break;
        case 7: _t->receiveObservedFocus((*reinterpret_cast< core::Vector3(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MuseTargetingSettings* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MuseTargetingView::*)(MuseTargetingSettings * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MuseTargetingView::updateCurrentSettings)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MuseTargetingView::*)(core::Vector3 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MuseTargetingView::updateDesiredFocus)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MuseTargetingView::*)(core::Vector3 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MuseTargetingView::sendObservedFocus)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MuseTargetingView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MuseTargetingView.data,
    qt_meta_data_MuseTargetingView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MuseTargetingView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MuseTargetingView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MuseTargetingView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MuseTargetingView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MuseTargetingView::updateCurrentSettings(MuseTargetingSettings * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MuseTargetingView::updateDesiredFocus(core::Vector3 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MuseTargetingView::sendObservedFocus(core::Vector3 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
