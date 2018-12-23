#pragma once

#include <IImageModifier.h>
#include <vector>

class Intermeans :public IImageModifier
{
public:
    Intermeans();

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    double meanValue(std::vector<int> values) const;

    double m_epsilon = 0.1;
};