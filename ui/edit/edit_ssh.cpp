#include "edit_ssh.h"
#include "ui_edit_ssh.h"

#include "fmt/SSHBean.hpp"

EditSSH::EditSSH(QWidget *parent) : QWidget(parent), ui(new Ui::EditSSH) {
    ui->setupUi(this);
}

EditSSH::~EditSSH() {
    delete ui;
}

void EditSSH::onStart(std::shared_ptr<NekoGui::ProxyEntity> _ent) {
    this->ent = _ent;
    auto bean = this->ent->SSHBean();

    ui->user->setText(bean->user);
    ui->password->setText(bean->password);
    ui->private_key->setText(bean->privateKey);
    ui->private_key_path->setText(bean->privateKeyPath);
    ui->private_key_passphrase->setText(bean->privateKeyPassphrase);
    ui->host_key->setText(bean->hostKey);
    ui->host_key_algorithms->setText(bean->hostKeyAlgorithms);
    ui->client_version->setText(bean->clientVersion);
}

bool EditSSH::onEnd() {
    auto bean = this->ent->SSHBean();

    bean->user = ui->user->text();
    bean->password = ui->password->text();
    bean->privateKey = ui->private_key->text();
    bean->privateKeyPath = ui->private_key_path->text();
    bean->privateKeyPassphrase = ui->private_key_passphrase->text();
    bean->hostKey = ui->host_key->text();
    bean->hostKeyAlgorithms = ui->host_key_algorithms->text();
    bean->clientVersion = ui->client_version->text();

    return true;
}