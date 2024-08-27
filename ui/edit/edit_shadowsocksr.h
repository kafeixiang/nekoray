#pragma once

#include <QWidget>
#include "profile_editor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class EditShadowSocksR;
}
QT_END_NAMESPACE

class EditShadowSocksR : public QWidget, public ProfileEditor {
    Q_OBJECT

public:
    explicit EditShadowSocksR(QWidget *parent = nullptr);

    ~EditShadowSocksR() override;

    void onStart(std::shared_ptr<NekoGui::ProxyEntity> _ent) override;

    bool onEnd() override;

private:
    Ui::EditShadowSocksR *ui;
    std::shared_ptr<NekoGui::ProxyEntity> ent;
};