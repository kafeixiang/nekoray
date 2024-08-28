#pragma once

#include "fmt/AbstractBean.hpp"

namespace NekoGui_fmt {
    class SSHBean : public AbstractBean {
    public:
        QString user;
        QString password;
        QString privateKey;
        QString privateKeyPath;
        QString privateKeyPassphrase;
        QString hostKey;
        QString hostKeyAlgorithms;
        QString clientVersion;

        SSHBean() : AbstractBean(0) {
            _add(new configItem("user", &user, itemType::string));
            _add(new configItem("password", &password, itemType::string));
            _add(new configItem("private_key", &privateKey, itemType::string));
            _add(new configItem("private_key_path", &privateKeyPath, itemType::string));
            _add(new configItem("private_key_passphrase", &privateKeyPassphrase, itemType::string));
            _add(new configItem("host_key", &hostKey, itemType::string));
            _add(new configItem("host_key_algorithms", &hostKeyAlgorithms, itemType::string));
            _add(new configItem("client_version", &clientVersion, itemType::string));
        };

        QString DisplayType() override { return "SSH"; };

        CoreObjOutboundBuildResult BuildCoreObjSingBox() override;

        bool TryParseLink(const QString &link);

        QString ToShareLink() override;
    };
} // namespace NekoGui_fmt
