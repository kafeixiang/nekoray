#include "QtExtKeySequenceEdit.h"

QtExtKeySequenceEdit::QtExtKeySequenceEdit(QWidget *parent)
        : QKeySequenceEdit(parent) {
}

QtExtKeySequenceEdit::~QtExtKeySequenceEdit() {
}

void QtExtKeySequenceEdit::keyPressEvent(QKeyEvent *pEvent) {
    QKeySequenceEdit::keyPressEvent(pEvent);

    QKeySequence keySeq = keySequence();
    if (keySeq.count() <= 0) {
        return;
    }
    QKeyCombination key(keySeq[0]);
    if (key == QKeyCombination(Qt::Key_Backspace) || key == QKeyCombination(Qt::Key_Delete)) {
        key = QKeyCombination();
    }
    setKeySequence(key);
}
