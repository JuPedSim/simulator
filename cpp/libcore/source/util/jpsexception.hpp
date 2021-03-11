#pragma once

#include <exception>
#include <string>
#include <utility>

class JPSException : public std::exception
{
private:
    std::string m_msg;

public:
    explicit JPSException(std::string p_msg) : m_msg(std::move(p_msg)) {}

    auto what() const noexcept -> const char * override { return m_msg.c_str(); }
};

class JPSGeometryException : public JPSException
{
public:
    explicit JPSGeometryException(const std::string & p_msg) : JPSException(p_msg) {}
};
