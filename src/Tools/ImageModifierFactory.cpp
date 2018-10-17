#include "ImageModifierFactory.h"
#include "ImageModifierNames.h"

#include "HistogramEqualizer.h"


ImageModifierFactory::ImageModifierFactory()
{
    m_imageModifiers[ImageModifierNames::ColorHistogramEqualization] = []() {return new HistogramEqualizer; };

}

ImageModifierFactory::~ImageModifierFactory()
{}

IImageModifier * ImageModifierFactory::createNewImageModifier(const std::string& name) const
{
    return m_imageModifiers.at(name)();
}
