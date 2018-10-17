#pragma once
#include <string>
#include <map>
#include <functional>

class IImageModifier;

class ImageModifierFactory
{
public:
    ImageModifierFactory();
    ~ImageModifierFactory();

    IImageModifier* createNewImageModifier(const std::string& name) const;

private:

    std::map<std::string, std::function<IImageModifier*()>> m_imageModifiers;

};

