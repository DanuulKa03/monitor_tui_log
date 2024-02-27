//
// Created by dika on 27.02.2024.
//

#ifndef LOG_MONITOR_EXPANDER_HPP
#define LOG_MONITOR_EXPANDER_HPP

#include <memory>
#include <vector>

class ExpanderImpl;
using Expander = std::unique_ptr<ExpanderImpl>;

class ExpanderImpl {
public:
    ~ExpanderImpl();
    static Expander Root();
    Expander Child();

    bool Expand();
    bool Collapse();

    int MinLevel() const;
    int MaxLevel() const;

    bool expanded = false;
private:
    void Expand(int minLevel);
    void Collapse(int maxLevel);

    ExpanderImpl* parent_ = nullptr;
    std::vector<ExpanderImpl*> children_;
};

#endif //LOG_MONITOR_EXPANDER_HPP
