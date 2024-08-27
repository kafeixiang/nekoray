#pragma once

#include "fmt/AbstractBean.hpp"

namespace NekoGui_fmt {
    class ShadowSocksRBean : public AbstractBean {
    public:
        QString method = "";
        QString password = "";
        QString obfs = "";
        QString obfsParam = "";
        QString protocol = "";
        QString protocolParam = "";

        ShadowSocksRBean() : AbstractBean(0) {
            _add(new configItem("method", &method, itemType::string));
            _add(new configItem("pass", &password, itemType::string));
            _add(new configItem("obfs", &obfs, itemType::string));
            _add(new configItem("obfs_param", &obfsParam, itemType::string));
            _add(new configItem("protocol", &protocol, itemType::string));
            _add(new configItem("protocol_param", &protocolParam, itemType::string));
        };

        QString DisplayType() override { return "ShadowsocksR"; };

        CoreObjOutboundBuildResult BuildCoreObjSingBox() override;

        bool TryParseLink(const QString &link);

        QString ToShareLink() override;
    };
} // namespace NekoGui_fmt
