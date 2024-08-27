#pragma once

#include "fmt/AbstractBean.hpp"

namespace NekoGui_fmt {
    class WireGuardBean : public AbstractBean {
    public:
        QString privateKey;
        QString publicKey;
        QString preSharedKey;
        QString localAddress;
        QString reserved;
        int MTU = 1408;
        bool useSystemInterface = false;
        bool enableGSO = false;

        WireGuardBean() : AbstractBean(0) {
            _add(new configItem("private_key", &privateKey, itemType::string));
            _add(new configItem("public_key", &publicKey, itemType::string));
            _add(new configItem("pre_shared_key", &preSharedKey, itemType::string));
            _add(new configItem("local_address", &localAddress, itemType::string));
            _add(new configItem("reserved", &reserved, itemType::string));
            _add(new configItem("mtu", &MTU, itemType::integer));
            _add(new configItem("use_system_proxy", &useSystemInterface, itemType::boolean));
            _add(new configItem("enable_gso", &enableGSO, itemType::boolean));
        };

        QString DisplayType() override { return "WireGuard"; };

        CoreObjOutboundBuildResult BuildCoreObjSingBox() override;

        bool TryParseLink(const QString &link);

        QString ToShareLink() override;
    };
} // namespace NekoGui_fmt
