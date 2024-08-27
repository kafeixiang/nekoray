#include "edit_shadowsocksr.h"
#include "ui_edit_shadowsocksr.h"

#include "fmt/ShadowSocksRBean.hpp"
#include "fmt/Preset.hpp"

EditShadowSocksR::EditShadowSocksR(QWidget *parent) : QWidget(parent), ui(new Ui::EditShadowSocksR) {
    ui->setupUi(this);
    ui->method->addItems(Preset::SingBox::ShadowsocksMethods);
}

EditShadowSocksR::~EditShadowSocksR() {
    delete ui;
}

void EditShadowSocksR::onStart(std::shared_ptr<NekoGui::ProxyEntity> _ent) {
    this->ent = _ent;
    auto bean = this->ent->ShadowSocksRBean();

    ui->method->setCurrentText(bean->method);
    ui->password->setText(bean->password);
    ui->obfs->setCurrentText(bean->obfs);
    ui->obfs_param->setText(bean->obfsParam);
    ui->protocol->setCurrentText(bean->protocol);
    ui->protocol_param->setText(bean->protocolParam);
}

bool EditShadowSocksR::onEnd() {
    auto bean = this->ent->ShadowSocksRBean();

    bean->method = ui->method->currentText();
    bean->password = ui->password->text();
    bean->obfs = ui->obfs->currentText();
    bean->obfsParam = ui->obfs_param->text();
    bean->protocol = ui->protocol->currentText();
    bean->protocolParam = ui->protocol_param->text();

    return true;
}
