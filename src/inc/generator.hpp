#pragma once
#include "utils.hpp"
#include "./parser.hpp"


class Generator {
    public:
        inline Generator(NodeExit root)
        : m_root(std::move(root))
        {}

        std::string generate() const;

    private:
        const NodeExit m_root;
};