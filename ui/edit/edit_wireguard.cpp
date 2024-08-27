#include "edit_wireguard.h"
#include "ui_edit_wireguard.h"

#include "fmt/WireGuardBean.hpp"

EditWireGuard::EditWireGuard(QWidget *parent) : QWidget(parent), ui(new Ui::EditWireGuard) {
    ui->setupUi(this);
}

EditWireGuard::~EditWireGuard() {
    delete ui;
}

void EditWireGuard::onStart(std::shared_ptr<NekoGui::ProxyEntity> _ent) {
    this->ent = _ent;
    auto bean = this->ent->WireGuardBean();

#ifndef Q_OS_LINUX
    ui->enable_gso->hide();
    adjustSize();
#endif

    ui->private_key->setText(bean->privateKey);
    ui->public_key->setText(bean->publicKey);
    ui->preshared_key->setText(bean->preSharedKey);
    ui->local_address->setText(bean->localAddress);
    ui->reserved->setText(bean->reserved);
    ui->mtu->setText(Int2String(bean->MTU));
    ui->sys_ifc->setChecked(bean->useSystemInterface);
    ui->enable_gso->setChecked(bean->enableGSO);
}

bool EditWireGuard::onEnd() {
    auto bean = this->ent->WireGuardBean();

    bean->privateKey = ui->private_key->text();
    bean->publicKey = ui->public_key->text();
    bean->preSharedKey = ui->preshared_key->text();
    bean->localAddress = ui->local_address->text();
    bean->reserved = ui->reserved->text();
    bean->MTU = ui->mtu->text().toInt();
    bean->useSystemInterface = ui->sys_ifc->isChecked();
    bean->enableGSO = ui->enable_gso->isChecked();

    return true;
}