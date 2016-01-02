TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Data.cpp \
    IEncryptionType.cpp \
    DataString.cpp \
    DataFile.cpp \
    Cryptographer.cpp \
    EncryptionAlgoFactory.cpp

HEADERS += \
    display.h \
    UnitTest.h \
    Data.h \
    IEncryptionType.h \
    utils.h \
    EncryptionType_StrShift.h \
    EncryptionType_ASCIIScramble.h \
    EncryptionTypeFactory.h \
    DataString.h \
    DataFile.h \
    Exceptions.h \
    EncryptionType_SimpleHash.h \
    EncryptionType_SimpleReversibleHash.h \
    Cryptographer.h

