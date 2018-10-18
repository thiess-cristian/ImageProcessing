#include "ImageModifierFactory.h"
#include "ImageModifierNames.h"

#include "HistogramEqualizer.h"
#include "BinaryImage.h"
#include "InvertColors.h"
#include "MirrorImage.h"


ImageModifierFactory::ImageModifierFactory()
{
    m_imageModifiers[ImageModifierNames::BinaryImage] = []() {return new BinaryImage; };
    m_imageModifiers[ImageModifierNames::InvertColors] = []() {return new InvertColors; };
    m_imageModifiers[ImageModifierNames::MirrorImage] = []() {return new MirrorImage; };
    m_imageModifiers[ImageModifierNames::ColorHistogramEqualization] = []() {return new HistogramEqualizer; };
}

ImageModifierFactory::~ImageModifierFactory()
{

}

IImageModifier * ImageModifierFactory::createNewImageModifier(const std::string& name) const
{
    return m_imageModifiers.at(name)(); //cant do [] because of const function
}
