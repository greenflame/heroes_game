/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../heroes_server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_actionStart_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 23), // "on_actionStop_triggered"
QT_MOC_LITERAL(4, 61, 15), // "executeProgramm"
QT_MOC_LITERAL(5, 77, 5), // "Field"
QT_MOC_LITERAL(6, 83, 1), // "f"
QT_MOC_LITERAL(7, 85, 7), // "QPoint&"
QT_MOC_LITERAL(8, 93, 4), // "move"
QT_MOC_LITERAL(9, 98, 6), // "attack"
QT_MOC_LITERAL(10, 105, 10), // "writeInput"
QT_MOC_LITERAL(11, 116, 10), // "readOutput"
QT_MOC_LITERAL(12, 127, 11), // "renderField"
QT_MOC_LITERAL(13, 139, 13), // "QList<QPoint>"
QT_MOC_LITERAL(14, 153, 10), // "motionPath"
QT_MOC_LITERAL(15, 164, 10), // "motionStep"
QT_MOC_LITERAL(16, 175, 13), // "attackSuccess"
QT_MOC_LITERAL(17, 189, 6), // "damage"
QT_MOC_LITERAL(18, 196, 4), // "died"
QT_MOC_LITERAL(19, 201, 16), // "pointToFrameRect"
QT_MOC_LITERAL(20, 218, 1), // "p"
QT_MOC_LITERAL(21, 220, 16), // "updateTroopsInfo"
QT_MOC_LITERAL(22, 237, 5), // "sleep"
QT_MOC_LITERAL(23, 243, 5), // "msecs"
QT_MOC_LITERAL(24, 249, 13) // "validateInput"

    },
    "MainWindow\0on_actionStart_triggered\0"
    "\0on_actionStop_triggered\0executeProgramm\0"
    "Field\0f\0QPoint&\0move\0attack\0writeInput\0"
    "readOutput\0renderField\0QList<QPoint>\0"
    "motionPath\0motionStep\0attackSuccess\0"
    "damage\0died\0pointToFrameRect\0p\0"
    "updateTroopsInfo\0sleep\0msecs\0validateInput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    3,   66,    2, 0x0a /* Public */,
      10,    1,   73,    2, 0x0a /* Public */,
      11,    2,   76,    2, 0x0a /* Public */,
      12,    7,   81,    2, 0x0a /* Public */,
      19,    1,   96,    2, 0x0a /* Public */,
      21,    1,   99,    2, 0x0a /* Public */,
      22,    1,  102,    2, 0x0a /* Public */,
      24,    3,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 7,    6,    8,    9,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::QImage, 0x80000000 | 5, 0x80000000 | 13, QMetaType::Int, QMetaType::Bool, QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    6,   14,   15,   16,    9,   17,   18,
    QMetaType::QRect, QMetaType::QPoint,   20,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 7,    6,    8,    9,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionStart_triggered(); break;
        case 1: _t->on_actionStop_triggered(); break;
        case 2: _t->executeProgramm((*reinterpret_cast< const Field(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< QPoint(*)>(_a[3]))); break;
        case 3: _t->writeInput((*reinterpret_cast< const Field(*)>(_a[1]))); break;
        case 4: _t->readOutput((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 5: { QImage _r = _t->renderField((*reinterpret_cast< const Field(*)>(_a[1])),(*reinterpret_cast< QList<QPoint>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< QPoint(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])));
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = _r; }  break;
        case 6: { QRect _r = _t->pointToFrameRect((*reinterpret_cast< QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QRect*>(_a[0]) = _r; }  break;
        case 7: _t->updateTroopsInfo((*reinterpret_cast< const Field(*)>(_a[1]))); break;
        case 8: _t->sleep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->validateInput((*reinterpret_cast< const Field(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< QPoint(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QPoint> >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
